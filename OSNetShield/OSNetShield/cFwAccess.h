#include <windows.h>
#include <netfw.h>
#include <iostream>
#include <vector>
#include <string>
//#include <afx.h>
#include "atlstr.h"

#pragma once
#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "oleaut32.lib" )

class cFwAccess
{
public:
	cFwAccess(void);
	~cFwAccess(void);
	void ruleMaker(std::string &sName, std::string &sDscr, std::string &sGrp, std::string &sAddr, int nAction, std::vector<BSTR> &vFwAddedRules);
	void addRule(std::string &sName, std::string &sDscr, std::string &sGrp, std::string &sAddr);
	void removeRule(std::string &sName);
	void cleanup(
		BSTR &bstrRuleName, BSTR &bstrRuleDescription, BSTR &bstrRuleGroup, BSTR &bstrRuleRemoteAdresses, 
		INetFwRule *pFwRule, INetFwRules *pFwRules,  INetFwPolicy2 *pNetFwPolicy2,
		std::vector<BSTR> &vFwAddedRules,
		HRESULT &hrComInit
		);
	int getRulesCount();

//private:
	//std::vector<BSTR> vFwAddedRules;
};

