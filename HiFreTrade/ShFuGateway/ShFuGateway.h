#if !defined(SHFU_GATEWAY_H)
#define SHFU_GATEWAY_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef SHFUGATEWAY_EXPORTS
#define SHFU_GATEWAY_EXPORT __declspec(dllexport)
#else
#define SHFU_GATEWAY_EXPORT __declspec(dllimport)
#endif

typedef void (__stdcall *QuoteCallback)(const char* quoteStr);

extern "C"
{
	SHFU_GATEWAY_EXPORT int __stdcall TestCall(int a, int b);

	SHFU_GATEWAY_EXPORT bool __stdcall ConnectMarketAgent(const char* brokerID, 
		const char* userID, const char* password, QuoteCallback callbackHandler);

	SHFU_GATEWAY_EXPORT void __stdcall DisconnectMarketAgent();

	SHFU_GATEWAY_EXPORT void __stdcall SetSymbol(const char* symbol);
};

#endif