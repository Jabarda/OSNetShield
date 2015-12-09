#include <windows.h>
#include <netfw.h>
#include <iostream>
#include <vector>
#include "atlstr.h"

#pragma once
#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "oleaut32.lib" )

/// Initialize INetFwPolicy2 object
/// Taken from the example
HRESULT WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2);

/// Class to ease the work with IPs
/// Allows to move to the previous or next IP easily
class cIP
{
public:
	cIP(std::wstring &str);
	~cIP();
	std::wstring getAddress();
	void operator ++();
	void operator --();
private:
	int nOctet[4];
	std::wstring sAddr;
};

///
/// Class to manipulate Windows Firewall
/// 
class cFwAccess
{
public:
	cFwAccess(void);
	~cFwAccess(void);
	void makeRule(std::wstring &sName, std::wstring &sDscr, std::wstring &sAddr, int nAction, NET_FW_RULE_DIRECTION_ dir);
	void cleanup(
		BSTR &bstrRuleName, BSTR &bstrRuleDescription, BSTR &bstrRuleGroup, BSTR &bstrRuleRemoteAdresses, BSTR &bstrVal,
		INetFwRule *pFwRule, INetFwRules *pFwRules,  INetFwPolicy2 *pNetFwPolicy2,
		HRESULT &hrComInit);
	void RuleUnblocker(
		BSTR &bstrRuleName, BSTR &bstrRuleDescription, BSTR &bstrRuleGroup, BSTR &bstrRuleRemoteAdresses, BSTR &bstrVal,
		INetFwRule *pFwRule, INetFwRules *pFwRules,  INetFwPolicy2 *pNetFwPolicy2,
		HRESULT &hrComInit, HRESULT &hr);
	std::wstring makeRuleName();
	void controlFw();
	void controlFwGUI(std::wstring &sIP, int nAction);
	bool isWstringIP(std::wstring &str);
private:
	// Vector contains the names of the previously added rules
	std::vector<std::wstring> vFwAddedRules;
};

