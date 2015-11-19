#include "stdafx.h"
#include <windows.h>
#include <netfw.h>
//#include <iostream>
#include <vector>
#include "atlstr.h"
#include "TCPForm.h"
#pragma once
#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "oleaut32.lib" )

std::string makeRuleName(std::vector<std::wstring> &vFwAddedRules);

HRESULT WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2);

// Class to ease the work with IPs
class cIP
{
public:
	cIP(std::wstring &str);
	~cIP();
	std::wstring getAddress();
	bool operator >=(cIP &toCompare);
	bool operator ==(cIP &toCompare);
private:
	int nOctet[4];
	std::wstring sAddr;
};
//void TCPWindow_start();
// Class to manipulate Windows Firewall
class cFwAccess
{
public:
	cFwAccess(void);
	~cFwAccess(void);
	void makeRule(std::wstring &sName, std::wstring &sDscr, std::wstring &sAddr, int nAction, NET_FW_RULE_DIRECTION_ dir);
	void cleanup(
		BSTR &bstrRuleName, BSTR &bstrRuleDescription, BSTR &bstrRuleGroup, BSTR &bstrRuleRemoteAdresses, BSTR &bstrVal,
		INetFwRule *pFwRule, INetFwRules *pFwRules,  INetFwPolicy2 *pNetFwPolicy2,
		HRESULT &hrComInit
		);
	std::wstring makeRuleName();
	void controlFw();
	void controlFwGUI(std::wstring &sIP, int nAction);
	bool isWstringIP(std::wstring &str);
private:
	std::vector<std::wstring> vFwAddedRules;
};

