#include "StdAfx.h"
#include "SgOrderStateMachine.h"
#include "globalmembers.h"
#include "OrderProcessor2.h"
#include "charsetconvert.h"
#include "Portfolio.h"

#include <boost/format.hpp>

using namespace op2;

string CSgOrderPlacer::EmptyParentOrderId;

trade::Order* GetOrderBySymbol(trade::MultiLegOrder* mlOrder, const string& symbol, trade::TradeDirectionType direction)
{
	trade::Order* pOrdFound = NULL;
	int count = mlOrder->legs_size();
	google::protobuf::RepeatedPtrField<trade::Order>* legs = mlOrder->mutable_legs();
	for(int i = 0; i < count; ++i)
	{
		trade::Order* pOrd = legs->Mutable(i);
		if(pOrd->instrumentid() == symbol && pOrd->direction() == direction)
		{
			// find it
			pOrdFound = pOrd;
			break;
		}
	}
	return pOrdFound;
}

CSgOrderStateMachine::CSgOrderStateMachine(void)
{
	Initialize();
}


CSgOrderStateMachine::~CSgOrderStateMachine(void)
{
}

void CSgOrderStateMachine::Initialize()
{
	OrderStatePtr sent(new OrderSent);
	m_orderStates.insert(make_pair(sent->State(), sent));
	OrderStatePtr pending(new OrderPending);
	m_orderStates.insert(make_pair(pending->State(), pending));
	OrderStatePtr complete(new OrderComplete);
	m_orderStates.insert(make_pair(complete->State(), complete));
	OrderStatePtr failed(new OrderPlaceFailed);
	m_orderStates.insert(make_pair(failed->State(), failed));

	sent->AddEventState(ORDER_EVENT_COMPLETE, complete.get());
	sent->AddEventState(ORDER_EVENT_PENDING, pending.get());
	sent->AddEventState(ORDER_EVENT_SUBMIT_FAILED, failed.get());
	sent->AddEventState(ORDER_EVENT_REJECTED, failed.get());

	pending->AddEventState(ORDER_EVENT_CANCEL_FAILED, failed.get());
	pending->AddEventState(ORDER_EVENT_CANCEL_SUCCESS, sent.get());
	pending->AddEventState(ORDER_EVENT_PENDING, pending.get());
	pending->AddEventState(ORDER_EVENT_COMPLETE, complete.get());
}

void CSgOrderStateMachine::Transition( const string& orderId/*orderRef*/, COrderEvent& event )
{
	COrderStateMachine::Transition(orderId, event);
}


void CSgOrderPlacer::Do()
{
	COrderState* sentState = m_pStateMachine->GetState(ORDER_STATE_SENT);
	sentState->Run(this, NULL);
}

bool CSgOrderPlacer::OnEnter( ORDER_STATE state, COrderEvent* transEvent )
{
	string dbText = boost::str(boost::format("Order(%s - %s) enter %s") 
		% ParentOrderId() % Symbol() % PrintState(state));
	logger.Debug(dbText);
	bool isTerminal = false;

	CSgOrderEvent* pSgOrderEvent = NULL;
	if(ORDER_STATE_SENT != state)
	{
		pSgOrderEvent = dynamic_cast<CSgOrderEvent*>(transEvent);
		_ASSERT(pSgOrderEvent != NULL);
		if(pSgOrderEvent == NULL)
			return isTerminal;
	}

	switch(state)
	{
	case ORDER_STATE_SENT:
		{
			if(m_submitTimes <= m_maxRetryTimes)
			{
				if(m_submitTimes > 0)
				{
					m_pStateMachine->RemovePlacer(Id());
					ModifyOrderPrice();
				}

				// lock and generate order ref
				int iOrdRef = m_pOrderProcessor->LockForSubmit(m_currentOrdRef);
				if(iOrdRef < 0) // Cannot correctly generate order ref, something wrong
				{
					m_succ = false;
					m_errorMsg = "δ������ί������(OrderRef)";
					isTerminal = true;
				}
				else
				{
					m_pInputOrder->set_orderref(m_currentOrdRef);
					m_pStateMachine->AddPlacer(OrderPlacerPtr(this));

					string submitInfo = boost::str(boost::format("Submit Order(%s - %s) [No. %d time(s)]")
						% ParentOrderId() % Symbol() % m_submitTimes);
					logger.Info(submitInfo);
					// real submit order and unlock to allow next order ref generation
					bool succ = m_pOrderProcessor->SubmitAndUnlock(m_pInputOrder.get());
					++m_submitTimes;
				}
			}
			else
			{
				m_succ = false;
				m_errorMsg = boost::str(boost::format("%d��׷������δ�ɽ���") % m_maxRetryTimes);
				logger.Info(boost::str(boost::format("Submit order (%s - %s ) -> Retry times is used up")
					% ParentOrderId() % Symbol()));
				isTerminal = true;

				RaiseMultiLegOrderEvent(LegCanceledEvent(Symbol()));
			}
		}
		break;
	case ORDER_STATE_PENDING:
		{
			trade::Order* pOrd = pSgOrderEvent->RtnOrder();
			if(pOrd != NULL)
			{
				OnOrderUpdate(pOrd);

				if(!m_allowPending)
				{
					const std::string& ordRef = pOrd->orderref();
					const std::string& exchId = pOrd->exchangeid();
					const std::string& ordSysId = pOrd->ordersysid(); 
					const std::string& userId = pOrd->userid();
					const std::string& symbol = pOrd->instrumentid();
					m_pOrderProcessor->CancelOrder(ordRef, exchId, ordSysId, userId, symbol);
				}
			}
		}
		break;
	case ORDER_STATE_COMPLETE:
		{
			OnOrderUpdate(pSgOrderEvent->RtnOrder());
			m_succ = true;
			isTerminal = true;

			RaiseMultiLegOrderEvent(LegCompletedEvent(Symbol()));
		}
		break;
	case ORDER_STATE_PLACE_FAILED:
		{
			m_succ = false;

			if(pSgOrderEvent != NULL)
			{
				OnOrderPlaceFailed(pSgOrderEvent);
			}
			else
			{
				m_errorMsg = "Order not completed due to unexpected event";
			}
			isTerminal = true;

			RaiseMultiLegOrderEvent(LegRejectedEvent(Symbol()));
		}
		break;
	
	default:
		logger.Warning(boost::str(boost::format("Entering Single order UNHANDLED state %s")
			% PrintState(state)));
	}

	return isTerminal;
}

void CSgOrderPlacer::OnOrderUpdate( trade::Order* pOrd )
{
	if(pOrd != NULL)
	{
		trade::Order* pLegOrder = GetOrderBySymbol(m_pMultiLegOrder, pOrd->instrumentid(), pOrd->direction());

		pLegOrder->CopyFrom(*pOrd);

		string ordStatusMsg;
		GB2312ToUTF_8(ordStatusMsg, pOrd->statusmsg().c_str());
		pLegOrder->set_statusmsg(ordStatusMsg);

		m_pOrderProcessor->PublishOrderUpdate(m_pMultiLegOrder->portfolioid(), m_pMultiLegOrder->orderid(), pLegOrder);
	}
}

void CSgOrderPlacer::ModifyOrderPrice()
{
	CLeg* pLeg = m_pPortf->GetLeg(Symbol());
	_ASSERT(pLeg != NULL);
	if(pLeg != NULL)
	{
		trade::TradeDirectionType direction = m_pInputOrder->direction();
		double origLmtPx = m_pInputOrder->limitprice();
		if(direction == trade::BUY)
		{
			double ask = pLeg->Ask();
			logger.Trace(boost::str(boost::format("Buy: Ask(%f) ?> Lmt Px(%f)")
				% ask % origLmtPx));
			logger.Trace(boost::str(boost::format("Modify order(%s): Buy @ %f")
				% Symbol() % ask));
			m_pInputOrder->set_limitprice(ask);
		}
		else if(direction == trade::SELL)
		{
			double bid = pLeg->Bid();
			logger.Trace(boost::str(boost::format("Sell: Bid(%f) ?< Lmt Px(%f)")
				% bid % origLmtPx));
			logger.Trace(boost::str(boost::format("Modify order(%s): Sell @ %f")
				% Symbol() % bid));
			m_pInputOrder->set_limitprice(bid);
		}
	}
	
}

void CSgOrderPlacer::RaiseMultiLegOrderEvent( COrderEvent& orderEvent )
{
	m_pOrderProcessor->RaiseMLOrderPlacerEvent(ParentOrderId(), orderEvent);
}

void CSgOrderPlacer::OnOrderPlaceFailed( COrderEvent* pOrdEvent )
{
	CSgOrderEvent* pSgOrderEvent = dynamic_cast<CSgOrderEvent*>(pOrdEvent);
	trade::Order* pOrd = pSgOrderEvent->RtnOrder();
	if(pOrd != NULL)
	{
		OnOrderUpdate(pOrd);
	}
	else
	{
		trade::Order* pLegOrder = GetOrderBySymbol(m_pMultiLegOrder, 
			m_pInputOrder->instrumentid(), m_pInputOrder->direction());

		pLegOrder->set_orderref(m_currentOrdRef);
		pLegOrder->set_ordersubmitstatus(trade::INSERT_REJECTED);
		const string& errorMsg = pSgOrderEvent->StatusMsg();
		if(!errorMsg.empty())
		{
			GB2312ToUTF_8(m_errorMsg, errorMsg.c_str());
		}
		else
		{
			m_errorMsg = "Order not completed";
		}
		pLegOrder->set_statusmsg(m_errorMsg);

		m_pOrderProcessor->PublishOrderUpdate(m_pMultiLegOrder->portfolioid(), 
			m_pMultiLegOrder->orderid(), pLegOrder);
	}
}

void CManualSgOrderPlacer::ModifyOrderPrice()
{
	entity::Quote* pQuote = NULL;
	bool succ = m_pOrderProcessor->QuerySymbol(Symbol(), &pQuote);
	if(succ)
	{
		trade::TradeDirectionType direction = m_pInputOrder->direction();
		double origLmtPx = m_pInputOrder->limitprice();
		if(direction == trade::BUY)
		{
			double ask = pQuote->ask();
			logger.Trace(boost::str(boost::format("Buy: Ask(%f) ?> Lmt Px(%f)")
				% ask % origLmtPx));
			logger.Trace(boost::str(boost::format("Modify order(%s): Buy @ %f")
				% Symbol() % ask));
			m_pInputOrder->set_limitprice(ask);
		}
		else if(direction == trade::SELL)
		{
			double bid = pQuote->bid();
			logger.Trace(boost::str(boost::format("Sell: Bid(%f) ?< Lmt Px(%f)")
				% bid % origLmtPx));
			logger.Trace(boost::str(boost::format("Modify order(%s): Sell @ %f")
				% Symbol() % bid));
			m_pInputOrder->set_limitprice(bid);
		}
	}
	else
	{
		logger.Warning(boost::str(boost::format("Cannot query quote %s") % Symbol()));
	}
}

bool CManualSgOrderPlacer::DoAndWait()
{
	Do();

	return m_succ;
}