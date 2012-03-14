#include "StdAfx.h"
#include "ClientBase.h"
#include "QuoteAggregator.h"

extern CQuoteAggregator g_quoteAggregator;

ClientBase::ClientBase(void):
	m_pbfRunner(NULL)
{
	m_pbfRunner = new CBufferRunner< boost::shared_ptr<CTP::Quote> >(boost::bind(&ClientBase::_internalProcessQuote, this, _1));
	m_pbfRunner->Start();
}


ClientBase::~ClientBase(void)
{
	if(m_pbfRunner != NULL)
	{
		m_pbfRunner->Stop();
		delete m_pbfRunner;
	}
}

void ClientBase::OnQuoteRecevied( boost::shared_ptr<CTP::Quote>& pQuote )
{
	m_pbfRunner->Enqueue(pQuote);
}

void ClientBase::Subscribe( vector<string>& symbols )
{
	if(GetUuid().is_nil())
	{
		SetSymbols(symbols);
		g_quoteAggregator.SubscribeQuotes(this);
	}
	else
	{
		if(symbols.size() > 0)
			g_quoteAggregator.ChangeQuotes(this, symbols);
		else
			UnSubscribe();
	}
}

void ClientBase::UnSubscribe()
{
	if(!(GetUuid().is_nil()))
		g_quoteAggregator.UnsubscribeQuotes(GetUuid());
}

void ClientBase::_internalProcessQuote( boost::shared_ptr<CTP::Quote>& pQuote )
{
	ProcessQuote(pQuote);
}
