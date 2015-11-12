#include <windows.h>
#include <netfw.h>
#include <iostream>
#include <vector>
#include <string>
#include "atlstr.h"
#include "mainForm.h"
#include <stdio.h>
#include <thread>

#pragma once
#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "oleaut32.lib" )

std::string makeRuleName(std::vector<std::wstring> &vFwAddedRules);

HRESULT WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2);

class cFwAccess
{
public:
	cFwAccess(void);
	~cFwAccess(void);
	void ruleMaker(std::string &sName, std::string &sDscr, std::string &sAddr, int nAction, std::vector<std::wstring> &vFwAddedRules, NET_FW_RULE_DIRECTION_ dir);
	void cleanup(
		BSTR &bstrRuleName, BSTR &bstrRuleDescription, BSTR &bstrRuleGroup, BSTR &bstrRuleRemoteAdresses, BSTR &bstrVal,
		INetFwRule *pFwRule, INetFwRules *pFwRules,  INetFwPolicy2 *pNetFwPolicy2,
		HRESULT &hrComInit
		);
	std::string makeRuleName(std::vector<std::wstring> &vFwAddedRules);
	void controlFw();
	//void thread_Proc();
};

