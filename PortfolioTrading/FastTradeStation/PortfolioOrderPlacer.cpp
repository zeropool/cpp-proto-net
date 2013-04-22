#include "PortfolioOrderPlacer.h"
#include "InputOrder.h"
#include "Portfolio.h"
#include "OrderProcessor2.h"
#include "globalmembers.h"
#include "orderhelper.h"
#include "OrderEvent.h"
#include "charsetconvert.h"

#include <boost/foreach.hpp>
#include <boost/format.hpp>
// back-end
#include <boost/msm/back/state_machine.hpp>
//front-end
#include <boost/msm/front/state_machine_def.hpp>
// functors
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>
// for func_state and func_state_machine
#include <boost/msm/front/euml/state_grammar.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;

string PendingTimeUpEventName("struct evtPendingTimeUp");
string NextQuoteInEventName("struct evtNextQuoteIn");

namespace // Concrete FSM implementation
{
	struct OrderPlacer_ : public msm::front::state_machine_def<OrderPlacer_>
	{
		typedef int activate_deferred_events;

		CPortfolioOrderPlacer* m_pPlacer;

		// constructor with arguments
		OrderPlacer_(CPortfolioOrderPlacer* pPlacer):m_pPlacer(pPlacer)
		{}

		// state machines also have entry/exit actions 
		template <class Event, class Fsm> 
		void on_entry(Event const&, Fsm& fsm) 
		{
			// Set Order placer pointer to Submachine Sent
			OrderPlacer_::Sent& s = fsm.template get_state<OrderPlacer_::Sent&>();
			s.m_pPlacer = fsm.m_pPlacer;
		} 

		// States definition
		struct Sending : public msm::front::state<> 
		{
			// every (optional) entry/exit methods get the event passed.
			template <class Event,class FSM>
			void on_entry(Event const&,FSM& fsm) 
			{
				LOG_DEBUG(logger, "entering: Sending");
				fsm.m_pPlacer->OnSend();
			}

			template <class Event,class FSM>
			void on_exit(Event const&,FSM& ) { LOG_DEBUG(logger, "leaving: Sending"); }
		};

		struct LegOrderFilled : public msm::front::state<> 
		{
			template <class Event,class FSM>
			void on_entry(Event const& evt,FSM& fsm) 
			{
				LOG_DEBUG(logger, "entering: LegOrderFilled");
				fsm.m_pPlacer->OnFilled(evt.m_pOrd.get());
			}

			template <class Event,class FSM>
			void on_exit(Event const&,FSM& ) { LOG_DEBUG(logger, "leaving: LegOrderFilled"); }
		};

		struct LegOrderCanceled : public msm::front::state<> 
		{
			template <class Event,class FSM>
			void on_entry(Event const& evt,FSM& fsm) 
			{
				fsm.m_pPlacer->OnLegCanceled(evt.m_pOrd.get());
			}

			template <class Event,class FSM>
			void on_exit(Event const&,FSM& ) {}
		};

		struct LegOrderRejected : public msm::front::state<>
		{
			template <class Event,class FSM>
			void on_entry(Event const& evt,FSM& fsm) 
			{
				fsm.m_pPlacer->OnLegRejected(evt.m_pOrd.get());
			}

			template <class Event,class FSM>
			void on_exit(Event const&,FSM& ) {}
		};

		struct Completed :  public msm::front::terminate_state<>
		{
			template <class Event,class FSM>
			void on_entry(Event const&,FSM& fsm) 
			{
				fsm.m_pPlacer->OnCompleted();
			}
			template <class Event,class FSM>
			void on_exit(Event const&,FSM& ) {}
		};

		struct Canceled :  public msm::front::terminate_state<>
		{
			template <class Event,class FSM>
			void on_entry(Event const&,FSM& fsm) 
			{
				fsm.m_pPlacer->OnPortfolioCanceled();
			}
			template <class Event,class FSM>
			void on_exit(Event const&,FSM& ) {}
		};

		struct AllOk : public msm::front::state<> {};

		struct Error :  public msm::front::terminate_state<>
		{
			template <class Event,class FSM>
			void on_entry(Event const& evt,FSM& fsm) 
			{
				fsm.m_pPlacer->OnError(evt.m_ErrorMsg);
			}
			template <class Event,class FSM>
			void on_exit(Event const&,FSM& ) {}
		};
		
		struct Sent_ : public msm::front::state_machine_def<Sent_>
		{
			// if the evtNextQuoteIn event is fired while in this state, defer it until a state
			// handles or rejects it
			typedef mpl::vector<evtRetry> deferred_events;

			CPortfolioOrderPlacer* m_pPlacer;

			Sent_():m_pPlacer(NULL){}

			struct Accepted : public msm::front::state<> 
			{
				// every (optional) entry/exit methods get the event passed.
				template <class Event,class FSM>
				void on_entry(Event const& evt,FSM& fsm) 
				{
					LOG_DEBUG(logger, "entering: Accepted");
					fsm.m_pPlacer->OnAccept(evt.m_pOrd.get());
				}

				template <class Event,class FSM>
				void on_exit(Event const&,FSM& ) { LOG_DEBUG(logger, "leaving: Accepted"); }
			};

			struct Pending : public msm::front::state<> 
			{
				template <class Event,class FSM>
				void on_entry(Event const& evt,FSM& fsm) 
				{ 
					LOG_DEBUG(logger, "entering: Pending");
					fsm.m_pPlacer->OnPending(evt.m_pOrd.get());
				}

				template <class Event,class FSM>
				void on_exit(Event const&,FSM& ) { LOG_DEBUG(logger, "leaving: Pending"); }
			};

			struct PartiallyFilled : public msm::front::state<> 
			{
				template <class Event,class FSM>
				void on_entry(Event const& evt, FSM& fsm) 
				{ 
					LOG_DEBUG(logger, "entering: PartiallyFilled");
					fsm.m_pPlacer->OnPartiallyFilled(evt.m_pOrd.get());
				}

				template <class Event,class FSM>
				void on_exit(Event const&,FSM& ) { LOG_DEBUG(logger, "leaving: PartiallyFilled"); }
			};

			struct Canceling : public msm::front::state<> 
			{
				template <class Event,class FSM>
				void on_entry(Event const& evt, FSM& fsm) 
				{ 
					LOG_DEBUG(logger, "entering: Canceling");
					fsm.m_pPlacer->OnCanceling();
				}

				template <class Event,class FSM>
				void on_exit(Event const&,FSM& ) { LOG_DEBUG(logger, "leaving: Canceling"); }
			};

			// transitions internal to Empty
			void duplicate_pending(evtPending const&){ LOG_DEBUG(logger, "Ignore duplicate pending"); }

			// the initial state. Must be defined
			typedef Accepted initial_state;

			typedef Sent_ s;

			// Transition table for OrderPlacer
			struct transition_table : mpl::vector<
				//    Start				Event				Next			Action                     Guard
				//  +------------+--------------------+-----------------+---------------------------+----------------------+
				_row < Accepted  , evtPending	      , Pending		    >,
				_row < Accepted  , evtPartiallyFilled , PartiallyFilled >,
				_row < Accepted  , evtSubmit	      , Accepted		>,
				_row < Pending	 , evtPendingTimeUp   , Canceling		>,
			  a_irow < Pending   , evtPending		  ,					   &s::duplicate_pending	>,
				_row < Pending	 , evtPartiallyFilled , PartiallyFilled >,
			  a_irow < Canceling , evtPending	      ,					   &s::duplicate_pending	>
			> {};

		};
		// back-end
		typedef msm::back::state_machine<Sent_> Sent;

		typedef mpl::vector<Sending, AllOk> initial_state;

		// transitions
		void on_cancel_success(evtCancelSuccess const& evt)       
		{
			m_pPlacer->OnOrderCanceled(evt.m_pOrd.get());
		}

		// guards
		bool first_leg_canceled(evtCancelSuccess const&)
		{
			return m_pPlacer->IsActiveFirstLeg();
		}
		bool other_leg_canceled(evtCancelSuccess const&)
		{
			return !(m_pPlacer->IsActiveFirstLeg());
		}
		bool if_cancel_failed(evtCancelFailure const& evt)
		{
			// If Cancel failed due to order finished, DON'T go to Error
			return evt.m_ErrorId != 26;
		}
		typedef OrderPlacer_ p;

		// Transition table for OrderPlacer
		struct transition_table : mpl::vector<
			//    Start					Event					Next			Action                     Guard
			//  +-------------------+-------------------+-------------------+---------------------------+--------------------------+
			_row < Sending			, evtSubmit			, Sent				>,
			_row < Sending			, evtSubmitFailure	, Error			    >,
			_row < Sent				, evtFilled			, LegOrderFilled	>,
			 row < Sent				, evtCancelSuccess	, LegOrderCanceled	 , &p::on_cancel_success	, &p::other_leg_canceled >,
			 row < Sent				, evtCancelSuccess	, Canceled			 , &p::on_cancel_success	, &p::first_leg_canceled >,
		   g_row < Sent				, evtCancelFailure	, Error											, &p::if_cancel_failed   >,
			_row < Sent				, evtReject			, LegOrderRejected	>,
			 Row < Sent				, evtRetry		    , none				 , Defer					, none					 >,
			_row < LegOrderFilled	, evtAllFilled		, Completed			>,
			_row < LegOrderFilled	, evtNextLeg		, Sending		    >,
			_row < LegOrderCanceled	, evtRetry			, Sending			>,
			_row < LegOrderCanceled	, evtFilledCanceled	, Error				>,
			_row < AllOk			, evtErrorFound		, Error				>
		> {};
		// Replaces the default no-transition response.
		template <class FSM,class Event>
		void no_transition(Event const& e, FSM& fsm, int state)
		{
			string unExpectedEvtName = typeid(e).name();
			LOG_DEBUG(logger, boost::str(boost::format(
				"no transition from state %d on event %s")
				% state % unExpectedEvtName));

			if(PendingTimeUpEventName == unExpectedEvtName ||
				NextQuoteInEventName == unExpectedEvtName)
			{
				logger.Warning(boost::str(boost::format("Event %s is ignored") % unExpectedEvtName));
			}
			else
			{
				fsm.process_event(evtErrorFound("遇到无法处理的事件"));
			}
		}
	};
	// Pick a back-end
	typedef msm::back::state_machine<OrderPlacer_> OrderPlacerFsm;
}

CPortfolioOrderPlacer::CPortfolioOrderPlacer(void)
	: m_pPortf(NULL)
	, m_pOrderProcessor(NULL)
	, m_activeOrdPlacer(NULL)
	, m_isReady(false)
	, m_isWorking(false)
	, m_isFirstLeg(false)
{
	m_fsm = boost::shared_ptr<void>(new OrderPlacerFsm(this));
}

CPortfolioOrderPlacer::~CPortfolioOrderPlacer(void)
{
	m_thCleanup.join();
}

void CPortfolioOrderPlacer::Initialize( const string& mlOrdId )
{
	m_multiLegOrderTemplate->set_orderid(mlOrdId);
	m_multiLegOrderTemplate->set_openorderid(mlOrdId);

	m_multiLegOrderTemplate->set_haswarn(false);
	m_multiLegOrderTemplate->set_statusmsg("");

	// Clear leg order status
	int count = m_multiLegOrderTemplate->legs_size();
	google::protobuf::RepeatedPtrField<trade::Order>* legs = m_multiLegOrderTemplate->mutable_legs();
	for(int i = 0; i < count; ++i)
	{
		trade::Order* pOrd = legs->Mutable(i);
		pOrd->set_volumetotaloriginal(0);
		pOrd->set_volumetraded(0);
		pOrd->set_ordersubmitstatus(trade::NOT_SUBMITTED);
		pOrd->set_orderstatus(trade::STATUS_UNKNOWN);
		pOrd->set_statusmsg("");
	}
}

void CPortfolioOrderPlacer::Prepare()
{
	BuildTemplateOrder();

	// Create input orders from template multi-leg order, then m_inputOrders will have items
	GenLegOrderPlacers();
	
	m_isReady = true;
}

void CPortfolioOrderPlacer::GenLegOrderPlacers()
{
	int openTimeout = m_pPortf->OpenPendingTimeout();
	int maxRetryTimes = m_pPortf->RetryTimes();

	int legIdx = 0;
	BOOST_FOREACH(const trade::Order& o, m_multiLegOrderTemplate->legs())
	{
		boost::shared_ptr<CLegOrderPlacer> legOrderPlacer(new CLegOrderPlacer(this, openTimeout, maxRetryTimes));
		
		legOrderPlacer->InputOrder().set_brokerid(o.brokerid());
		legOrderPlacer->InputOrder().set_investorid(o.investorid());
		legOrderPlacer->InputOrder().set_symbol(o.instrumentid());
		legOrderPlacer->InputOrder().set_orderref(o.orderref());
		legOrderPlacer->InputOrder().set_userid(o.userid());
		legOrderPlacer->InputOrder().set_orderpricetype(o.orderpricetype());
		legOrderPlacer->InputOrder().set_direction(o.direction());
		legOrderPlacer->InputOrder().set_combhedgeflag(o.combhedgeflag());
		legOrderPlacer->InputOrder().set_comboffsetflag(o.comboffsetflag());
		legOrderPlacer->InputOrder().set_limitprice(o.limitprice());
		legOrderPlacer->InputOrder().set_volumetotaloriginal(o.volumetotaloriginal());
		legOrderPlacer->InputOrder().set_timecondition(o.timecondition());
		legOrderPlacer->InputOrder().set_gtddate(o.gtddate());
		legOrderPlacer->InputOrder().set_volumecondition(	o.volumecondition());
		legOrderPlacer->InputOrder().set_minvolume(o.minvolume());
		legOrderPlacer->InputOrder().set_contingentcondition(	o.contingentcondition());
		legOrderPlacer->InputOrder().set_stopprice(o.stopprice());
		legOrderPlacer->InputOrder().set_forceclosereason(o.forceclosereason());
		legOrderPlacer->InputOrder().set_isautosuspend(o.isautosuspend());
		legOrderPlacer->InputOrder().set_businessunit(o.businessunit());
		legOrderPlacer->InputOrder().set_requestid(o.requestid());
		legOrderPlacer->InputOrder().set_userforceclose(o.userforceclose());

		legOrderPlacer->LegIndex(legIdx++);
		double pxTick = m_pPortf->PriceTick();
		legOrderPlacer->SetPriceTick(pxTick);

		if(o.preferred())	// always put preferred order at front
		{
			m_legPlacers.insert(m_legPlacers.begin(), legOrderPlacer);
			legOrderPlacer->SequenceNo(0);
		}
		else
		{
			m_legPlacers.push_back(legOrderPlacer);
			legOrderPlacer->SequenceNo(m_legPlacers.size() - 1);
		}
	}
}

void CPortfolioOrderPlacer::Run(trade::PosiDirectionType posiDirection, double* pLmtPxArr, int iPxSize,
		const boost::chrono::steady_clock::time_point& trigQuoteTimestamp)
{
	if(!m_isReady)
		Prepare();

	m_isWorking.store(true, boost::memory_order_release);

	// Direction
	SetDirection(posiDirection);

	// Limit price
	SetLimitPrice(pLmtPxArr, iPxSize);

	// Sending the first leg
	m_activeOrdPlacer = m_legPlacers[0].get();
	m_isFirstLeg = true;
	m_trigQuoteTimestamp = trigQuoteTimestamp;

	// start fsm
	boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->start();
}

void CPortfolioOrderPlacer::Run( trade::PosiDirectionType posiDirection, double* pLmtPxArr, int iPxSize )
{
	Run(posiDirection, pLmtPxArr, iPxSize, boost::chrono::steady_clock::now());
}

void CPortfolioOrderPlacer::OnSend()
{
	assert(m_activeOrdPlacer != NULL);
	LOG_DEBUG(logger, boost::str(boost::format("Sending Active Order placer's Id:%d ") 
		% m_activeOrdPlacer->SequenceNo()));
	m_activeOrdPlacer->AddSubmitTimes();

	// lock and generate order ref
	string sendingOrderRef;
	int iOrdRef = m_pOrderProcessor->LockForSubmit(sendingOrderRef);
	assert(iOrdRef > 0);

	// set order ref to input order to be sent
	m_activeOrdPlacer->OrderRef(sendingOrderRef);

	// Add this to order processor, so that return order can get back
	m_pOrderProcessor->AddOrderPlacer(this);

	// real submit order and unlock to allow next order ref generation
	bool succ = m_pOrderProcessor->SubmitAndUnlock(&(m_activeOrdPlacer->InputOrder()));

	boost::chrono::steady_clock::duration elapsed = 
		boost::chrono::steady_clock::now() - m_trigQuoteTimestamp;
	long usElapse = boost::chrono::duration_cast<boost::chrono::microseconds>(elapsed).count();

	LOG_INFO(logger, boost::str(boost::format("Submit Order(%s - %s) [No. %d time(s)] in %d us after the lastest QUOTE")
		% m_multiLegOrderTemplate->orderid() % m_activeOrdPlacer->Symbol() % m_activeOrdPlacer->SubmitTimes() % usElapse));

	if(m_isFirstLeg && m_activeOrdPlacer->SubmitTimes() == 1)	// Only publish it for the first time
	{
		// Generate order Id
		string mlOrderId;
		m_pPortf->NewOrderId(mlOrderId);
		Initialize(mlOrderId);
		m_isFirstLeg = false;

		m_pOrderProcessor->PublishMultiLegOrderUpdate(m_multiLegOrderTemplate.get());
	}
}

void CPortfolioOrderPlacer::OnAccept(trade::Order* pRtnOrder)
{
	UpdateLegOrder(pRtnOrder);
}

void CPortfolioOrderPlacer::OnPending( trade::Order* pRtnOrder )
{
	assert(m_activeOrdPlacer != NULL);
	if(!m_activeOrdPlacer->IsPending())
	{
		m_activeOrdPlacer->StartPending(pRtnOrder);

		UpdateLegOrder(pRtnOrder);
	}
	else
		LOG_DEBUG(logger, boost::str(boost::format("Duplicate pending order event.(ordRef: %s, sysId: %s)")
					% pRtnOrder->orderref() % pRtnOrder->ordersysid()));
}

void CPortfolioOrderPlacer::OnFilled( trade::Order* pRtnOrder )
{
	// The first thing is to cancel pending timer
	m_activeOrdPlacer->CancelPending();
	AfterLegDone();
	UpdateLegOrder(pRtnOrder);

	int sendingIdx = m_activeOrdPlacer->SequenceNo();
	LOG_DEBUG(logger, boost::str(boost::format("No.%d OrderPlacer gets filled") % sendingIdx));
	++sendingIdx;
	if(sendingIdx < (int)m_legPlacers.size())
	{
		// Go to send next order
		m_activeOrdPlacer = m_legPlacers[sendingIdx].get();
		boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtNextLeg());
	}
	else
	{
		// All leg order done
		boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtAllFilled());
	}
}

void CPortfolioOrderPlacer::OnPartiallyFilled( trade::Order* pRtnOrder )
{
	int remained = pRtnOrder->volumetotal();
	int finished = pRtnOrder->volumetraded();

	assert(false);
	// Cancel remaining
	OnCanceling();
	UpdateLegOrder(pRtnOrder);
}

void CPortfolioOrderPlacer::OnOrderCanceled( trade::Order* pRtnOrder )
{
	UpdateLegOrder(pRtnOrder);
	m_activeOrdPlacer->Reset(true);
	m_pOrderProcessor->RemoveOrderPlacer(Id());
}

void CPortfolioOrderPlacer::OnCompleted()
{
	trade::MlOrderOffset offset = m_multiLegOrderTemplate->offset();
	if(offset == trade::ML_OF_OPEN || offset == trade::ML_OF_OTHER)
		m_pPortf->AddPosition(*m_multiLegOrderTemplate);
	else if(offset == trade::ML_OF_CLOSE)
		m_pPortf->RemovePosition(*m_multiLegOrderTemplate);
	
	AfterPortfolioDone();
}

void CPortfolioOrderPlacer::OnCanceling()
{
	assert(m_activeOrdPlacer != NULL);
	assert(m_activeOrdPlacer->IsPending());
	LOG_DEBUG(logger, boost::str(boost::format("Canceling order (ref:%s, sysId:%s)")
		% m_activeOrdPlacer->OrderRef() % m_activeOrdPlacer->OrderSysId()));
	
	m_activeOrdPlacer->WaitForNextQuote();
	m_pOrderProcessor->CancelOrder(m_activeOrdPlacer->OrderRef(), 
		m_activeOrdPlacer->ExchId(), m_activeOrdPlacer->OrderSysId(), 
		m_activeOrdPlacer->UserId(), m_activeOrdPlacer->Symbol());
}

void CPortfolioOrderPlacer::OnLegCanceled( trade::Order* pRtnOrder )
{
	assert(m_activeOrdPlacer != NULL);

	if(m_activeOrdPlacer->CanRetry())
	{
		// wait until next quote in
	}
	else
	{
		AfterLegDone();
		LOG_INFO(logger, boost::str(boost::format("Retry times is used up. Order(%s) has been retried %d times")
			% pRtnOrder->instrumentid() % m_activeOrdPlacer->SubmitTimes()));
		
		boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(
			evtFilledCanceled("单腿:平仓失败"));
	}
}

void CPortfolioOrderPlacer::OnLegRejected( trade::Order* pRtnOrder )
{
	AfterLegDone();
	UpdateLegOrder(pRtnOrder);
	
	boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtErrorFound(pRtnOrder->statusmsg()));
}

void CPortfolioOrderPlacer::OnPortfolioCanceled()
{
	AfterLegDone();
	AfterPortfolioDone();
}

void CPortfolioOrderPlacer::OnError(const string& errMsg)
{
	AfterLegDone();
	AfterPortfolioDone();

	string ordStatusMsg;
	GB2312ToUTF_8(ordStatusMsg, errMsg.c_str());

	m_multiLegOrderTemplate->set_haswarn(true);
	m_multiLegOrderTemplate->set_statusmsg(ordStatusMsg);

	UpdateMultiLegOrder();
}

void CPortfolioOrderPlacer::OnPendingTimeUp()
{
	boost::lock_guard<boost::mutex> l(m_mutOuterAccessFsm);
	boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtPendingTimeUp());
}

void CPortfolioOrderPlacer::OnQuoteReceived( boost::chrono::steady_clock::time_point& quoteTimestamp, entity::Quote* pQuote )
{
	// Only for close order
	if(m_activeOrdPlacer->IsReadyForNextQuote())
	{
		if(m_activeOrdPlacer->CanRetry())
		{
			boost::lock_guard<boost::mutex> l(m_mutOuterAccessFsm);

			m_activeOrdPlacer->ModifyPrice(pQuote);

			m_trigQuoteTimestamp = quoteTimestamp;

			LOG_DEBUG(logger, boost::str(boost::format("Active Order Placer(No.%d) Go to retry ") % m_activeOrdPlacer->SequenceNo()));
			// retry
			boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtRetry());
		}
	}
}

void CPortfolioOrderPlacer::UpdateMultiLegOrder()
{
	// Copy order info from legOrder Placer
	BOOST_FOREACH(const LegOrderPlacerPtr& legPlacer, m_legPlacers)
	{
		int legIdx = legPlacer->LegIndex();
		assert(legIdx < m_multiLegOrderTemplate->legs_size());

		trade::Order* pOrd = m_multiLegOrderTemplate->mutable_legs(legIdx);
		if(legPlacer->IsOrderReady())
			pOrd->CopyFrom(legPlacer->Order());
	}

	m_pOrderProcessor->PublishMultiLegOrderUpdate(m_multiLegOrderTemplate.get());
}

void CPortfolioOrderPlacer::OutputStatus( const string& statusMsg )
{
	m_multiLegOrderTemplate->set_statusmsg(statusMsg);
	UpdateMultiLegOrder();
}

void CPortfolioOrderPlacer::OnOrderReturned( boost::shared_ptr<trade::Order>& pRtnOrder )
{
	boost::lock_guard<boost::mutex> l(m_mutOuterAccessFsm);

	trade::OrderSubmitStatusType submitStatus = pRtnOrder->ordersubmitstatus();
	trade::OrderStatusType status = pRtnOrder->orderstatus();

	LOG_DEBUG(logger, boost::str(boost::format("Order(%s, %s) - submit status(%s), order status(%s)")
		% pRtnOrder->orderref() %  pRtnOrder->ordersysid() % GetSumbitStatusText(submitStatus) % GetStatusText(status)));

	if(submitStatus > trade::NOT_SUBMITTED && 
		submitStatus <= trade::ACCEPTED && status >= trade::STATUS_UNKNOWN)
	{
		boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtSubmit(pRtnOrder));
	}
	else if(submitStatus > trade::ACCEPTED)
	{
		boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtReject(pRtnOrder));
	}
	else if(status == trade::ALL_TRADED)
	{
		boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtFilled(pRtnOrder));
	}
	else if(status == trade::ORDER_CANCELED)
	{
		boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtCancelSuccess(pRtnOrder));
	}
	else if(status == trade::NO_TRADE_QUEUEING ||
		status == trade::NO_TRADE_NOT_QUEUEING)
	{
		boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtPending(pRtnOrder));
	}
	else if(status == trade::PART_TRADED_QUEUEING ||
		status == trade::PART_TRADED_NOT_QUEUEING)
	{
		boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtPartiallyFilled(pRtnOrder));
	}
	else
	{
		logger.Warning(boost::str(boost::format("Cannot identify status of order (ref: %s, sysId: %s)") 
			% pRtnOrder->orderref() % pRtnOrder->ordersysid()));
	}
}

void CPortfolioOrderPlacer::UpdateLegOrder( trade::Order* pRtnOrder )
{
	if(pRtnOrder != NULL)
	{
		m_activeOrdPlacer->UpdateOrder(*pRtnOrder);
		trade::Order& legOrder = m_activeOrdPlacer->Order();

		string ordStatusMsg;
		GB2312ToUTF_8(ordStatusMsg, pRtnOrder->statusmsg().c_str());
		legOrder.set_statusmsg(ordStatusMsg);

		m_pOrderProcessor->PublishOrderUpdate(m_multiLegOrderTemplate->portfolioid(), 
			m_multiLegOrderTemplate->orderid(), &legOrder);
	}
}

void CPortfolioOrderPlacer::AfterLegDone()
{
	m_activeOrdPlacer->Reset();
	m_pOrderProcessor->RemoveOrderPlacer(Id());
}

void CPortfolioOrderPlacer::AfterPortfolioDone()
{
	m_isWorking.store(false, boost::memory_order_release);
}

void CPortfolioOrderPlacer::OnOrderPlaceFailed( const string& errMsg )
{
	boost::lock_guard<boost::mutex> l(m_mutOuterAccessFsm);
	boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtSubmitFailure(errMsg));
}

void CPortfolioOrderPlacer::OnOrderCancelFailed( int errorId, const string& errMsg )
{
	boost::lock_guard<boost::mutex> l(m_mutOuterAccessFsm);
	boost::static_pointer_cast<OrderPlacerFsm>(m_fsm)->process_event(evtCancelFailure(errorId, errMsg));
}

void CPortfolioOrderPlacer::Cleanup()
{
	m_thCleanup = boost::thread(boost::bind(&CPortfolioOrderPlacer::CleanupProc, this));
}

void CPortfolioOrderPlacer::CleanupProc()
{
	while(m_isWorking.load(boost::memory_order_acquire))
	{
		boost::this_thread::sleep_for(boost::chrono::seconds(1));
	}

	m_activeOrdPlacer = NULL;
	m_multiLegOrderTemplate.reset();
	m_legPlacers.clear();
}

bool CPortfolioOrderPlacer::IsActiveFirstLeg()
{
	assert(m_activeOrdPlacer != NULL);
	return m_activeOrdPlacer->SequenceNo() == 0;
}










