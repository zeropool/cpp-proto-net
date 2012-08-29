#pragma once

#include "../Entity/gen/cpp/trade.pb.h"
#include "TradeAgentCallback.h"
#include "TradeAgent.h"

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

using namespace std;

typedef boost::shared_ptr<trade::MultiLegOrder> MultiLegOrderPtr;
typedef boost::function<void(trade::MultiLegOrder*)> PushMultiLegOrderFunc;
typedef boost::function<void(trade::Trade*)> PushTradeFunc;

class COrderProcessor : public CTradeAgentCallback
{
public:
	COrderProcessor(void);
	~COrderProcessor(void);

	void Initialize(CTradeAgent* pTradeAgent);

	void OpenOrder(MultiLegOrderPtr multilegOrder);
	void CloseOrder(const string& orderId);
	void CancelOrder(const string& orderId);

	//////////////////////////////////////////////////////////////////////////
	// Below methods are callbacks for CTradeAgent 

	///登录请求响应
	virtual void OnRspUserLogin(bool succ, std::string& msg, int initOrderRefID);

	///报单录入请求响应
	virtual void OnRspOrderInsert(bool succ, const std::string& orderRef, const std::string& msg);

	///报单操作请求响应
	virtual void OnRspOrderAction(bool succ, const std::string& orderRef, const std::string& msg){}

	///报单通知
	virtual void OnRtnOrder(trade::Order* order);

	///成交通知
	virtual void OnRtnTrade(trade::Trade* pTrade);

	///投资者结算结果确认响应
	virtual void OnRspSettlementInfoConfirm(){}

	///请求查询合约响应
	virtual void OnRspQryInstrument(){}

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(){}

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(){}

	//////////////////////////////////////////////////////////////////////////

	void PublishMultiLegOrderUpdate(trade::MultiLegOrder* pOrder)
	{
		if(!m_pushMultiOrdFunc.empty())
		{
			m_pushMultiOrdFunc(pOrder);
		}
	}
	void SetPushPortfolioFunc(PushMultiLegOrderFunc funcPushMLOrder)
	{
		m_pushMultiOrdFunc = funcPushMLOrder;
	}

	void PublishTradeUpdate(trade::Trade* pTrade)
	{
		if(!m_pushTradeFunc.empty())
		{
			m_pushTradeFunc(pTrade);
		}
	}
	void SetPushTradeFunc(PushTradeFunc funcPushTrade)
	{
		m_pushTradeFunc = funcPushTrade;
	}

private:
	int IncrementalOrderRef(trade::MultiLegOrder* pMlOrder, int maxOrderRef);
	void RemoveFromPending(trade::MultiLegOrder* pMlOrder);

	map<string, MultiLegOrderPtr> m_pendingMultiLegOrders;
	typedef map<string, MultiLegOrderPtr>::iterator MultiLegOrderIter;
	map<string /* orderRef */, string /* mlOrderId */> m_pendingTicketOrderMap;
	typedef map<string, string>::iterator PendingTktOrdMapIter;
	boost::mutex m_mutTicketOrderMap;
	 
	CTradeAgent* m_pTradeAgent;

	PushMultiLegOrderFunc m_pushMultiOrdFunc;
	PushTradeFunc m_pushTradeFunc;

	int m_maxOrderRef;
	boost::mutex m_mutOrdRefIncr;
};

