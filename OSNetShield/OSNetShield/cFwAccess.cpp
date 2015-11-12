
//TODO: change removal: enumerating instead of item method
//TODO: make proper descrirtion

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

void cFwAccess::ruleMaker(std::string &sName, std::string &sDscr, std::string &sAddr, int nAction, std::vector<std::wstring> &vFwAddedRules, NET_FW_RULE_DIRECTION_ dir)
{
	HRESULT hrComInit = S_OK;
    HRESULT hr = S_OK;

    INetFwPolicy2 *pNetFwPolicy2 = NULL;
    INetFwRules *pFwRules = NULL;
    INetFwRule *pFwRule = NULL;

	BSTR bstrRuleName = SysAllocString(std::wstring(sName.begin(), sName.end()).c_str());
	BSTR bstrRuleDescription = SysAllocString(std::wstring(sDscr.begin(), sDscr.end()).c_str());
    BSTR bstrRuleGroup = SysAllocString(L"OSNetShield");
	BSTR bstrRuleRemoteAdresses = SysAllocString(std::wstring(sAddr.begin(), sAddr.end()).c_str());
	BSTR bstrVal = SysAllocString(L"value");

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
				bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
				pFwRule, pFwRules, pNetFwPolicy2,
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
			bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
			pFwRule, pFwRules, pNetFwPolicy2,
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
			bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
			pFwRule, pFwRules, pNetFwPolicy2,
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
				bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
				pFwRule, pFwRules, pNetFwPolicy2,
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
	pFwRule->put_Direction(dir);
	pFwRule->put_Action(NET_FW_ACTION_BLOCK);
	pFwRule->put_Enabled(VARIANT_TRUE);
	
	if (std::find(vFwAddedRules.begin(), vFwAddedRules.end(), std::wstring (bstrRuleName, SysStringLen(bstrRuleName))) == vFwAddedRules.end() && nAction == 1)
	{
		// Add the Firewall Rule
		hr = pFwRules->Add(pFwRule);
		if (FAILED(hr))
		{
			printf("Firewall Rule Add failed: 0x%08lx\n", hr);
			cleanup(
				bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
				pFwRule, pFwRules, pNetFwPolicy2,
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
	else if (std::find(vFwAddedRules.begin(), vFwAddedRules.end(), std::wstring (bstrRuleName, SysStringLen(bstrRuleName))) != vFwAddedRules.end() && nAction == 1)
	{
		std::cout << "IP already blocked.\n";
	}
	else if (std::find(vFwAddedRules.begin(), vFwAddedRules.end(), std::wstring (bstrRuleName, SysStringLen(bstrRuleName))) != vFwAddedRules.end() && nAction == 2)
	{
		// Remove the Firewall Rule
		hr = pFwRules->Remove(bstrRuleName);
		if (FAILED(hr))
		{
			printf("Firewall Rule Remove failed: 0x%08lx\n", hr);
			cleanup(
				bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
				pFwRule, pFwRules, pNetFwPolicy2,
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
	else if (std::find(vFwAddedRules.begin(), vFwAddedRules.end(), std::wstring (bstrRuleName, SysStringLen(bstrRuleName))) == vFwAddedRules.end() && nAction == 2)
	{
		std::cout << "No such rule.\n";
	}

	// Get the existing rule
	if(nAction == 0)
	{
		ULONG cFetched = 0; 
		CComVariant var;
		IUnknown *pEnumerator;
		IEnumVARIANT* pVariant = NULL;
		long fwRuleCount;

		hr = pFwRules->get_Count(&fwRuleCount);
		if (FAILED(hr))
		{
			wprintf(L"get_Count failed: 0x%08lx\n", hr);
			cleanup(
					bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
					pFwRule, pFwRules, pNetFwPolicy2,
					hrComInit
					);
			return;
		}

		pFwRules->get__NewEnum(&pEnumerator);

		if(pEnumerator)
		{
			hr = pEnumerator->QueryInterface(__uuidof(IEnumVARIANT), (void **) &pVariant);
		}

		while(SUCCEEDED(hr) && hr != S_FALSE)
		{
			var.Clear();
			hr = pVariant->Next(1, &var, &cFetched);

			if (S_FALSE != hr)
			{
				if (SUCCEEDED(hr))
				{
					hr = var.ChangeType(VT_DISPATCH);
				}
				else
					std::cout << 1;
				if (SUCCEEDED(hr))
				{
					hr = (V_DISPATCH(&var))->QueryInterface(__uuidof(INetFwRule), reinterpret_cast<void**>(&pFwRule));
				}
				else
					std::cout << 2;

				if (SUCCEEDED(hr))
					// Add rule name to the vector if it belongs to apps group
					if (SUCCEEDED(pFwRule->get_Grouping(&bstrVal)))
					{
						if (bstrVal == SysAllocString(L"OSNetShield"))
							if (SUCCEEDED(pFwRule->get_Name(&bstrVal)))
							{
								std::wcout << std::wstring (bstrVal, SysStringLen(bstrVal)) << std::endl;
								vFwAddedRules.push_back(std::wstring (bstrVal, SysStringLen(bstrVal)));
							}
						SysFreeString(bstrVal);
					}
			}
		}
	}

	cleanup(
		bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
		pFwRule, pFwRules, pNetFwPolicy2,
		hrComInit
		);
}

void cFwAccess::cleanup(
	BSTR &bstrRuleName, BSTR &bstrRuleDescription, BSTR &bstrRuleGroup, BSTR &bstrRuleRemoteAdresses,  BSTR &bstrVal, 
	INetFwRule *pFwRule, INetFwRules *pFwRules,  INetFwPolicy2 *pNetFwPolicy2,
	HRESULT &hrComInit)
{
	// Free BSTR's
    SysFreeString(bstrRuleName);
    SysFreeString(bstrRuleDescription);
    SysFreeString(bstrRuleGroup);
	SysFreeString(bstrRuleRemoteAdresses);
	SysFreeString(bstrVal);
	
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

std::string cFwAccess::makeRuleName(std::vector<std::wstring> &vFwAddedRules)
{
	std::string sName, sNameTemp;

	for(int i=1; i<=vFwAddedRules.size()+1; i++)
	{
		sName = "OSNetShield" + std::to_string(i);
		sNameTemp = sName + "in";
		if(std::find(vFwAddedRules.begin(), vFwAddedRules.end(), (std::wstring(sNameTemp.begin(), sNameTemp.end()))) == vFwAddedRules.end())
			return sName;
	}
	sName = "OSNetShield" + std::to_string(vFwAddedRules.size()+1);
	return sName;
}



void cFwAccess::controlFw()
{

	int menuAction = 0;
	std::string sName = "Name", sDescription = "Block ", sAddr = "0.0.0.0";
	std::vector<std::wstring> vFwAddedRules;
	
	ruleMaker(sName, sDescription, sAddr, 0, vFwAddedRules, NET_FW_RULE_DIR_OUT);
	ruleMaker(sName, sDescription, sAddr, 0, vFwAddedRules, NET_FW_RULE_DIR_IN);

	std::cout << "The application blocks and unblocks a site by its IP\n";

	while(menuAction != 4)
	{
		std::cout << "\n1) Block IP\n2) Unblock IP\n3) Start GUI\n3) Exit\n";
		std::cin >> menuAction;
		getchar();

		if(menuAction == 1)
		{
			sName = makeRuleName(vFwAddedRules);
			std::cout << "Enter the IP to block:\t";
			std::getline(std::cin, sAddr);
			std::cout << "The rule name is " << sName << "\n";
			sDescription = "Block " + sAddr;
			std::cout << "The rule description is " << sDescription << "\n";
			std::cout << "The rule group is OSNetShield\n";
			ruleMaker(sName+"in", sDescription, sAddr, 1, vFwAddedRules, NET_FW_RULE_DIR_IN);
			ruleMaker(sName+"out", sDescription, sAddr, 1, vFwAddedRules, NET_FW_RULE_DIR_OUT);
		}
		if(menuAction == 2)
		{
			std::cout << "Enter the rule name:\t";
			std::getline(std::cin, sName);
			ruleMaker(sName+"in", sDescription, sAddr, 2, vFwAddedRules, NET_FW_RULE_DIR_IN);
			ruleMaker(sName+"out", sDescription, sAddr, 2, vFwAddedRules, NET_FW_RULE_DIR_OUT);
		}
		//if (menuAction == 3) std::thread thr(thread_Proc);
	}
}