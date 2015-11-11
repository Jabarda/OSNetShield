#include "stdafx.h"
#include "cFwAccess.h"

// Instantiate INetFwPolicy2
HRESULT WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2)
{
    HRESULT hr = S_OK;

    hr = CoCreateInstance(
        __uuidof(NetFwPolicy2), 
        NULL, 
        CLSCTX_INPROC_SERVER, 
        __uuidof(INetFwPolicy2), 
        (void**)ppNetFwPolicy2);

    if (FAILED(hr))
    {
        printf("CoCreateInstance for INetFwPolicy2 failed: 0x%08lx\n", hr);
    }

    return hr;
}

cFwAccess::cFwAccess(void)
{

}

cFwAccess::~cFwAccess(void)
{
}

void cFwAccess::ruleMaker(std::string &sName, std::string &sDscr, std::string &sGrp, std::string &sAddr, int nAction, std::vector<std::wstring> &vFwAddedRules)
{
	HRESULT hrComInit = S_OK;
    HRESULT hr = S_OK;

    INetFwPolicy2 *pNetFwPolicy2 = NULL;
    INetFwRules *pFwRules = NULL;
    INetFwRule *pFwRule = NULL;

	BSTR bstrRuleName = CString(sName.c_str()).AllocSysString();
	BSTR bstrRuleDescription = CString(sDscr.c_str()).AllocSysString();
    BSTR bstrRuleGroup = CString(sGrp.c_str()).AllocSysString();
	BSTR bstrRuleRemoteAdresses = CString(sAddr.c_str()).AllocSysString();
	
	// Initialize COM.
	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED
		);

	// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
	// initialized with a different mode. Since we don't care what the mode is,
	// we'll just use the existing mode.
	if (hrComInit != RPC_E_CHANGED_MODE)
	{
		if (FAILED(hrComInit))
		{
			printf("CoInitializeEx failed: 0x%08lx\n", hrComInit);
			cleanup(
				bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses,
				pFwRule, pFwRules, pNetFwPolicy2,
				vFwAddedRules,
				hrComInit
				);
			return;
		}
	}
		
	// Retrieve INetFwPolicy2
	hr = WFCOMInitialize(&pNetFwPolicy2);
	if (FAILED(hr))
	{
		cleanup(
			bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses,
			pFwRule, pFwRules, pNetFwPolicy2,
			vFwAddedRules,
			hrComInit
			);
		return;
	}
	
	// Retrieve INetFwRules
	hr = pNetFwPolicy2->get_Rules(&pFwRules);
	if (FAILED(hr))
	{
		printf("get_Rules failed: 0x%08lx\n", hr);
		cleanup(
			bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses,
			pFwRule, pFwRules, pNetFwPolicy2,
			vFwAddedRules,
			hrComInit
			);
		return;
	}
	
	// Create a new Firewall Rule object.
	hr = CoCreateInstance(
		__uuidof(NetFwRule),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(INetFwRule),
		(void**)&pFwRule);
   if (FAILED(hr))
    {
        printf("CoCreateInstance for Firewall Rule failed: 0x%08lx\n", hr);
		cleanup(
				bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses,
				pFwRule, pFwRules, pNetFwPolicy2,
				vFwAddedRules,
				hrComInit
				);
		return;
    }
	
    // Populate the Firewall Rule object
    pFwRule->put_Name(bstrRuleName);
    pFwRule->put_Description(bstrRuleDescription);
    pFwRule->put_Grouping(bstrRuleGroup);
	pFwRule->put_RemoteAddresses(bstrRuleRemoteAdresses);
    pFwRule->put_Profiles(NET_FW_PROFILE2_ALL);
	pFwRule->put_Direction(NET_FW_RULE_DIR_OUT);
	pFwRule->put_Action(NET_FW_ACTION_BLOCK);
	pFwRule->put_Enabled(VARIANT_TRUE);
	
	if (std::find(vFwAddedRules.begin(), vFwAddedRules.end(), bstrRuleName) == vFwAddedRules.end() && nAction == 1)
	{
		// Add the Firewall Rule
		hr = pFwRules->Add(pFwRule);
		if (FAILED(hr))
		{
			printf("Firewall Rule Add failed: 0x%08lx\n", hr);
			cleanup(
				bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses,
				pFwRule, pFwRules, pNetFwPolicy2,
				vFwAddedRules,
				hrComInit
				);
			return;
		}
		else
		{
			vFwAddedRules.push_back(std::wstring (bstrRuleName, SysStringLen(bstrRuleName)));
			std::cout << "IP successfully blocked.\n";
		}
	}
	else if (std::find(vFwAddedRules.begin(), vFwAddedRules.end(), bstrRuleName) != vFwAddedRules.end() && nAction == 1)
	{
		std::cout << "IP already blocked.\n";
	}
	else if (std::find(vFwAddedRules.begin(), vFwAddedRules.end(), bstrRuleName) != vFwAddedRules.end() && nAction == 2)
	{
		// Remove the Firewall Rule
		hr = pFwRules->Remove(bstrRuleName);
		if (FAILED(hr))
		{
			printf("Firewall Rule Remove failed: 0x%08lx\n", hr);
			cleanup(
				bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses,
				pFwRule, pFwRules, pNetFwPolicy2,
				vFwAddedRules,
				hrComInit
				);
			return;
		}
		else
		{
			std::cout << "IP successfully unblocked.\n";
			for( std::vector<std::wstring>::iterator iter = vFwAddedRules.begin(); iter != vFwAddedRules.end(); ++iter )
			{
				if( *iter == std::wstring (bstrRuleName, SysStringLen(bstrRuleName)) )
				{
					vFwAddedRules.erase( iter );
					break;
				}
			}
		}
	}
	else if (std::find(vFwAddedRules.begin(), vFwAddedRules.end(), bstrRuleName) == vFwAddedRules.end() && nAction == 2)
	{
		std::cout << "No such rule.\n";
	}

	// Get the existing rule
	//if(nAction == 0)
	//{
	//	hr = pFwRules->Item(bstrRuleName, &pFwRule);
//
	//	if (SUCCEEDED(hr))
	//	{
	//		vFwAddedRules.push_back(bstrRuleName);
	//	}
	//}

	cleanup(
		bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses,
		pFwRule, pFwRules, pNetFwPolicy2,
		vFwAddedRules,
		hrComInit
		);
}

void cFwAccess::cleanup(
	BSTR &bstrRuleName, BSTR &bstrRuleDescription, BSTR &bstrRuleGroup, BSTR &bstrRuleRemoteAdresses, 
	INetFwRule *pFwRule, INetFwRules *pFwRules,  INetFwPolicy2 *pNetFwPolicy2,
	std::vector<std::wstring> &vFwAddedRules,
	HRESULT &hrComInit
	)
{
	// Free BSTR's
    SysFreeString(bstrRuleName);
    SysFreeString(bstrRuleDescription);
    SysFreeString(bstrRuleGroup);
	SysFreeString(bstrRuleRemoteAdresses);

	// Free vector
	if(vFwAddedRules.empty())
	{
		vFwAddedRules.clear();
	}
	
    // Release the INetFwRule object
    if (pFwRule != NULL)
    {
        pFwRule->Release();
    }

    // Release the INetFwRules object
    if (pFwRules != NULL)
    {
        pFwRules->Release();
    }

    // Release the INetFwPolicy2 object
    if (pNetFwPolicy2 != NULL)
    {
        pNetFwPolicy2->Release();
    }

    // Uninitialize COM.
    if (SUCCEEDED(hrComInit))
    {
        CoUninitialize();
    }
}