
//TODO: make proper descrirtion
//range doesn't use mask

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



cIP::cIP(std::wstring &str)
{
	int nTemp = 0, nCount = 0;

	for(int i = 0; i < str.length(); i++)
	{
		if(str[i] >= 48 && str[i] <= 57)
		{
			nTemp = nTemp * 10;
			nTemp += str[i] - 48;
		}
		else if(str[i] == 46)
		{
			nOctet[nCount] = nTemp;
			nTemp = 0;
			nCount++;
		}
	}

	nOctet[3] = nTemp;

	sAddr = str;
}

cIP::~cIP()
{

}

std::wstring cIP::getAddress()
{
	return sAddr;
}

void cIP::operator ++()
{
	if(nOctet[3] != 255)
		nOctet[3]++;
	else if(nOctet[2] != 255)
	{
		nOctet[3] = 0;
		nOctet[2]++;
	}
	else if(nOctet[1] != 255)
	{
		nOctet[3] = 0;
		nOctet[2] = 0;
		nOctet[1]++;
	}
	else
	{
		nOctet[3] = 0;
		nOctet[2] = 0;
		nOctet[1] = 0;
		nOctet[0]++;
	}

	sAddr = std::to_wstring(nOctet[0]) + std::wstring(L".") + std::to_wstring(nOctet[1]) + std::wstring(L".") + std::to_wstring(nOctet[2]) + std::wstring(L".") + std::to_wstring(nOctet[3]);
}

void cIP::operator --()
{
	if(nOctet[3] != 0)
		nOctet[3]--;
	else if(nOctet[2] != 0)
	{
		nOctet[3] = 255;
		nOctet[2]--;
	}
	else if(nOctet[1] != 0)
	{
		nOctet[3] = 255;
		nOctet[2] = 255;
		nOctet[1]--;
	}
	else
	{
		nOctet[3] = 255;
		nOctet[2] = 255;
		nOctet[1] = 255;
		nOctet[0]--;
	}

	sAddr = std::to_wstring(nOctet[0]) + std::wstring(L".") + std::to_wstring(nOctet[1]) + std::wstring(L".") + std::to_wstring(nOctet[2]) + std::wstring(L".") + std::to_wstring(nOctet[3]);
}



cFwAccess::cFwAccess(void)
{
	std::wstring sName = std::wstring(L"Name"), sDescription = std::wstring(L"Block "), sAddr = std::wstring(L"0.0.0.0");
	makeRule(sName, sDescription, sAddr, 0, NET_FW_RULE_DIR_OUT);
}

cFwAccess::~cFwAccess(void)
{
}

// Adding (nAction = 1), removing rules (nAction = 2)
// Filling vFwAddedRules with previously added rules (nAction = 0) (used for proper naming)
void cFwAccess::makeRule(std::wstring &sName, std::wstring &sDscr, std::wstring &sAddr, int nAction, NET_FW_RULE_DIRECTION_ dir)
{
	std::size_t foundRule, foundIP;

	std::wstring sTemp1, sTemp2;

	HRESULT hrComInit = S_OK;
    HRESULT hr = S_OK;

    INetFwPolicy2 *pNetFwPolicy2 = NULL;
    INetFwRules *pFwRules = NULL;
    INetFwRule *pFwRule = NULL;

	BSTR bstrRuleName = SysAllocString(sName.c_str());
	BSTR bstrRuleDescription = SysAllocString(sDscr.c_str());
    BSTR bstrRuleGroup = SysAllocString(L"OSNetShield");
	BSTR bstrRuleRemoteAdresses = SysAllocString(sAddr.c_str());
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
	
	// Enumerating rules
	if(nAction == 0 || nAction == 2)
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

				if (SUCCEEDED(hr))
				{
					hr = (V_DISPATCH(&var))->QueryInterface(__uuidof(INetFwRule), reinterpret_cast<void**>(&pFwRule));
				}	
			
				if (SUCCEEDED(hr))
				{
					switch(nAction)
					{
					case 0:
						// Add rule name to the vector if it belongs to apps group
						if (SUCCEEDED(pFwRule->get_Grouping(&bstrVal)))
							if (std::wstring (bstrVal, SysStringLen(bstrVal)) == SysAllocString(L"OSNetShield"))
								if (SUCCEEDED(pFwRule->get_Name(&bstrVal)))
									(this->vFwAddedRules).push_back(std::wstring (bstrVal, SysStringLen(bstrVal)));
						break;
					case 2:
						// Remove rule if it belongs to apps group and blocks specified IP
						if (SUCCEEDED(pFwRule->get_Grouping(&bstrVal)))
							if (std::wstring (bstrVal, SysStringLen(bstrVal)) == SysAllocString(L"OSNetShield"))
								if (SUCCEEDED(pFwRule->get_RemoteAddresses(&bstrVal)))
								{
									sTemp1 = std::wstring(bstrVal, SysStringLen(bstrVal));
									sTemp2 = std::wstring(bstrRuleRemoteAdresses, SysStringLen(bstrRuleRemoteAdresses));

									foundRule = sTemp1.find('-');
									foundIP = sTemp2.find('-');

									if(foundIP == std::string::npos)
									{
										if(sTemp1 == sTemp2)
											makeRuleHelper(bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
												pFwRule, pFwRules,  pNetFwPolicy2,
												hrComInit, hr);
										else if(foundRule != std::string::npos)
										{
											sTemp2 = sTemp2.substr(0, sTemp2.find('/'));
											if(!(sTemp2 < sTemp1.substr(0, foundRule) || sTemp2 > sTemp1.substr(foundRule+1, sTemp1.length()-foundRule-1)))
											{
												if(sTemp2 == sTemp1.substr(0, foundRule))
												{
													makeRuleHelper(bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules,  pNetFwPolicy2,
														hrComInit, hr);

													cIP ipTemp(sTemp2);
													ipTemp++;
													if(ipTemp.getAddress() != sTemp1.substr(foundRule+1, sTemp1.length()-foundRule-1))
														sTemp2 = ipTemp.getAddress() + L"-" + sTemp1.substr(foundRule+1, sTemp1.length()-foundRule-1);
													else
														sTemp2 = ipTemp.getAddress();
													sName = makeRuleName();
													sDscr = L"Block " + sTemp2;
													makeRule(sName+std::wstring(L"out"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_OUT);
													makeRule(sName+std::wstring(L"in"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_IN);
													cleanup(
														bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules, pNetFwPolicy2,
														hrComInit
														);
													return;
												}
												else if(sTemp2 ==  sTemp1.substr(foundRule+1, sTemp1.length()-foundRule-1))
													{
													makeRuleHelper(bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules,  pNetFwPolicy2,
														hrComInit, hr);

													cIP ipTemp(sTemp2);
													ipTemp--;
													if(ipTemp.getAddress() != sTemp1.substr(0, foundRule))
														sTemp2 = sTemp1.substr(0, foundRule) + L"-" + ipTemp.getAddress();
													else
														sTemp2 = ipTemp.getAddress();
													sName = makeRuleName();
													sDscr = L"Block " + sTemp2;
													makeRule(sName+std::wstring(L"out"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_OUT);
													makeRule(sName+std::wstring(L"in"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_IN);
													cleanup(
														bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules, pNetFwPolicy2,
														hrComInit
														);
													return;
												}
												else 
												{
													makeRuleHelper(bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules,  pNetFwPolicy2,
														hrComInit, hr);

													cIP ipTemp(sTemp2);
													ipTemp--;
													if(ipTemp.getAddress() != sTemp1.substr(0, foundRule))
														sTemp2 = sTemp1.substr(0, foundRule) + L"-" + ipTemp.getAddress();
													else
														sTemp2 = ipTemp.getAddress();
													sName = makeRuleName();
													sDscr = L"Block " + sTemp2;
													makeRule(sName+std::wstring(L"out"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_OUT);
													makeRule(sName+std::wstring(L"in"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_IN);

													ipTemp++; ipTemp++;
													if(ipTemp.getAddress() != sTemp1.substr(foundRule+1, sTemp1.length()-foundRule-1))
														sTemp2 = ipTemp.getAddress() + L"-" + sTemp1.substr(foundRule+1, sTemp1.length()-foundRule-1);
													else
														sTemp2 = ipTemp.getAddress();
													sName = makeRuleName();
													sDscr = L"Block " + sTemp2;
													makeRule(sName+std::wstring(L"out"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_OUT);
													makeRule(sName+std::wstring(L"in"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_IN);
													cleanup(
														bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules, pNetFwPolicy2,
														hrComInit
														);
													return;
												}
											}
										}
									}
									else
									{
										if(sTemp1 == sTemp2)
											makeRuleHelper(bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
												pFwRule, pFwRules,  pNetFwPolicy2,
												hrComInit, hr);
										else if(foundRule == std::string::npos)
										{
											sTemp1 = sTemp1.substr(0, sTemp1.find('/'));
											if(sTemp1 >= sTemp2.substr(0, foundIP) && sTemp1 <= sTemp2.substr(foundIP+1, sTemp2.length()-foundIP-1))
												makeRuleHelper(bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules,  pNetFwPolicy2,
														hrComInit, hr);
										}
										else
											if(sTemp1.substr(0, foundRule) >= sTemp2.substr(0, foundIP))
												if(sTemp1.substr(foundRule+1, sTemp1.length()-foundRule-1) <= sTemp2.substr(foundIP+1, sTemp2.length()-foundIP-1))
													makeRuleHelper(bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules,  pNetFwPolicy2,
														hrComInit, hr);
												else
												{
													makeRuleHelper(bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules,  pNetFwPolicy2,
														hrComInit, hr);
													cIP ipTemp(sTemp2.substr(foundIP+1, sTemp2.length()-foundIP-1));
													ipTemp++;
													if(ipTemp.getAddress() != sTemp1.substr(foundRule+1, sTemp1.length()-foundRule-1))
														sTemp2 = ipTemp.getAddress() + L"-" + sTemp1.substr(foundRule+1, sTemp1.length()-foundRule-1);
													else
														sTemp2 = ipTemp.getAddress();
													sName = makeRuleName();
													sDscr = L"Block " + sTemp2;
													makeRule(sName+std::wstring(L"out"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_OUT);
													makeRule(sName+std::wstring(L"in"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_IN);
													cleanup(
														bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules, pNetFwPolicy2,
														hrComInit
														);
													return;
												}
											else if(sTemp1.substr(foundRule+1, sTemp1.length()-foundRule-1) <= sTemp2.substr(foundIP+1, sTemp2.length()-foundIP-1))
												{
													makeRuleHelper(bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules,  pNetFwPolicy2,
														hrComInit, hr);
													cIP ipTemp(sTemp2.substr(0, foundIP));
													ipTemp--;
													if(ipTemp.getAddress() != sTemp1.substr(0, foundRule))
														sTemp2 = sTemp1.substr(0, foundRule) + L"-" + ipTemp.getAddress();
													else
														sTemp2 = ipTemp.getAddress();
													sName = makeRuleName();
													sDscr = L"Block " + sTemp2;
													makeRule(sName+std::wstring(L"out"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_OUT);
													makeRule(sName+std::wstring(L"in"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_IN);
													cleanup(
														bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules, pNetFwPolicy2,
														hrComInit
														);
													return;
												}
											else
												{
													makeRuleHelper(bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules,  pNetFwPolicy2,
														hrComInit, hr);
													std::wstring sTemp3 = sTemp2;
													cIP ipTemp(sTemp2.substr(0, foundIP));
													ipTemp--;
													if(ipTemp.getAddress() != sTemp1.substr(0, foundRule))
														sTemp2 = sTemp1.substr(0, foundRule) + L"-" + ipTemp.getAddress();
													else
														sTemp2 = ipTemp.getAddress();
													sName = makeRuleName();
													sDscr = L"Block " + sTemp2;
													makeRule(sName+std::wstring(L"out"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_OUT);
													makeRule(sName+std::wstring(L"in"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_IN);

													sTemp2 = sTemp3;
													ipTemp = cIP(sTemp2.substr(foundIP+1, sTemp2.length()-foundIP-1));
													ipTemp++;
													if(ipTemp.getAddress() != sTemp1.substr(foundRule+1, sTemp1.length()-foundRule-1))
														sTemp2 = ipTemp.getAddress() + L"-" + sTemp1.substr(foundRule+1, sTemp1.length()-foundRule-1);
													else
														sTemp2 = ipTemp.getAddress();
													sName = makeRuleName();
													sDscr = L"Block " + sTemp2;
													makeRule(sName+std::wstring(L"out"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_OUT);
													makeRule(sName+std::wstring(L"in"), sDscr, sTemp2, 1, NET_FW_RULE_DIR_IN);
													cleanup(
														bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
														pFwRule, pFwRules, pNetFwPolicy2,
														hrComInit
														);
													return;
												}
									}
								}
					break;
					}
				}
			}
		}
		cleanup(
		bstrRuleName, bstrRuleDescription, bstrRuleGroup, bstrRuleRemoteAdresses, bstrVal,
		pFwRule, pFwRules, pNetFwPolicy2,
		hrComInit
		);
		return;
	}
	else if (nAction == 1)
	{
		// Populate the Firewall Rule object
		pFwRule->put_Name(bstrRuleName);
		pFwRule->put_Description(bstrRuleDescription);
		pFwRule->put_Grouping(bstrRuleGroup);
		pFwRule->put_RemoteAddresses(bstrRuleRemoteAdresses);
		pFwRule->put_Profiles(NET_FW_PROFILE2_ALL);
		pFwRule->put_Direction(dir);
		pFwRule->put_Action(NET_FW_ACTION_BLOCK);
		pFwRule->put_Enabled(VARIANT_TRUE);
	
		// Add the Firewall Rule
		hr = pFwRules->Add(pFwRule);
		if (FAILED(hr))
		{
			if(hr == E_ACCESSDENIED)
				std::cout << "access denied\n";
			if(hr == E_INVALIDARG)
				std::cout << "invalid arg\n";
			if(hr == E_UNEXPECTED)
				std::cout << "unexpected\n";
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
			(this->vFwAddedRules).push_back(std::wstring (bstrRuleName, SysStringLen(bstrRuleName)));
			std::cout << "IP successfully blocked.\n";
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

// Method allows to avoid many repetitions in makeRule
void cFwAccess::makeRuleHelper(
		BSTR &bstrRuleName, BSTR &bstrRuleDescription, BSTR &bstrRuleGroup, BSTR &bstrRuleRemoteAdresses, BSTR &bstrVal,
		INetFwRule *pFwRule, INetFwRules *pFwRules,  INetFwPolicy2 *pNetFwPolicy2,
		HRESULT &hrComInit, HRESULT &hr)
{
	if (SUCCEEDED(pFwRule->get_Name(&bstrVal)))
	{
		hr = pFwRules->Remove(bstrVal);
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
			for( std::vector<std::wstring>::iterator iter = (this->vFwAddedRules).begin(); iter != (this->vFwAddedRules).end(); ++iter )
			{
				if( *iter == std::wstring (bstrVal, SysStringLen(bstrVal)) )
				{
					(this->vFwAddedRules).erase( iter );
					break;
				}
			}
		}
		std::wstring sTemp = std::wstring (bstrVal, SysStringLen(bstrVal));
		if(sTemp[sTemp.length()-1] == 't')
			sTemp = sTemp.substr(0, sTemp.length()-3) + L"in";
		else
			sTemp = sTemp.substr(0, sTemp.length()-2) + L"out";
		hr = pFwRules->Remove(SysAllocString(sTemp.c_str()));
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
			for( std::vector<std::wstring>::iterator iter = (this->vFwAddedRules).begin(); iter != (this->vFwAddedRules).end(); ++iter )
			{
				if( *iter == sTemp )
				{
					(this->vFwAddedRules).erase( iter );
					break;
				}
			}
		}
	}
}

// Naming the rule, based on the number of previously added rules
// New name has to be unique
std::wstring cFwAccess::makeRuleName()
{
	std::wstring sName, sNameTemp;

	for(int i=1; i<=(this->vFwAddedRules).size()+1; i++)
	{
		sName = std::wstring(L"OSNetShield") + std::to_wstring(i);
		sNameTemp = sName + std::wstring(L"in");
		if(std::find((this->vFwAddedRules).begin(), (this->vFwAddedRules).end(), sNameTemp) == (this->vFwAddedRules).end())
			return sName;
	}
	sName = std::wstring(L"OSNetShield") + std::to_wstring((this->vFwAddedRules).size()+1);
	return sName;
}

// Manipulate the rules using console
void cFwAccess::controlFw()
{
	int menuAction = 0;
	std::wstring sName = std::wstring(L"Name"), sDescription = std::wstring(L"Block "), sAddr = std::wstring(L"0.0.0.0");

	std::cout << "The application blocks and unblocks a site by its IP\n";

	while(menuAction != 3)
	{
		std::cout << "\n1) Block IP\n2) Unblock IP\n3) Exit\n";
		std::cin >> menuAction;
		getchar();
		if(menuAction == 1)
		{
			sName = makeRuleName();
			std::cout << "Enter the IP to block:\t";
			std::getline(std::wcin, sAddr);
			if(isWstringIP(sAddr))
			{
				std::wcout << "The rule name is " << sName << "\n";
				sDescription = sDescription + sAddr;
				std::wcout << "The rule description is " << sDescription << "\n";
				std::wcout << "The rule group is OSNetShield\n";
				makeRule(sName+std::wstring(L"in"), sDescription, sAddr, 1, NET_FW_RULE_DIR_IN);
				makeRule(sName+std::wstring(L"out"), sDescription, sAddr, 1, NET_FW_RULE_DIR_OUT);
			}
			else
			{
				std::size_t found = sAddr.find('-');
				if(found!=std::string::npos)
					if(isWstringIP(sAddr.substr(0, found)) && isWstringIP(sAddr.substr(found+1, sAddr.length()-found-1)))
					{
						if(sAddr.substr(0, found) == sAddr.substr(found+1, sAddr.length()-found-1))
							sAddr = sAddr.substr(0, found);
						std::wcout << "The rule name is " << sName << "\n";
						sDescription = sDescription + sAddr;
						std::wcout << "The rule description is " << sDescription << "\n";
						std::wcout << "The rule group is OSNetShield\n";
						makeRule(sName+std::wstring(L"in"), sDescription, sAddr, 1, NET_FW_RULE_DIR_IN);
						makeRule(sName+std::wstring(L"out"), sDescription, sAddr, 1, NET_FW_RULE_DIR_OUT);
					}
					else
						std::cout << "Inappropriate input\n";
				else
					std::cout << "Inappropriate input\n";
			}
		}
		else if(menuAction == 2)
		{
			std::cout << "Enter the IP to unblock:\t";
			std::getline(std::wcin, sAddr);
			if(isWstringIP(sAddr))
			{
				sAddr += std::wstring(L"/255.255.255.255");
				makeRule(sName, sDescription, sAddr, 2, NET_FW_RULE_DIR_IN);
			}
			else
			{
				std::size_t found = sAddr.find('-');
				if(found!=std::string::npos)
					if(isWstringIP(sAddr.substr(0, found)) && isWstringIP(sAddr.substr(found+1, sAddr.length()-found-1)))
					{
						if(sAddr.substr(0, found) == sAddr.substr(found+1, sAddr.length()-found-1))
							sAddr = sAddr.substr(0, found);
						makeRule(sName, sDescription, sAddr, 2, NET_FW_RULE_DIR_IN);
					}
					else
						std::cout << "Inappropriate input\n";
				else
					std::cout << "Inappropriate input\n";
			}
		}
	}
}

// Manipulate the rules using GUI
void cFwAccess::controlFwGUI(std::wstring &sIP, int nAction)
{
	std::wstring sName = std::wstring(L"Name"), sDescription = std::wstring(L"Block "), sAddr = std::wstring(L"0.0.0.0");

	if(nAction == 1){
		sName = makeRuleName();
		sAddr = sIP;
		sDescription = sDescription + sAddr;

		// Checking if input is *.*.*.* or *.*.*.*-*.*.*.*
		if(isWstringIP(sAddr))
		{
			makeRule(sName+std::wstring(L"in"), sDescription, sAddr, 1, NET_FW_RULE_DIR_IN);
			makeRule(sName+std::wstring(L"out"), sDescription, sAddr, 1, NET_FW_RULE_DIR_OUT);
		}
		else
		{
			std::size_t found = sAddr.find('-');
			if(found!=std::string::npos)
				if(isWstringIP(sAddr.substr(0, found)) && isWstringIP(sAddr.substr(found+1, sAddr.length()-found-1)))
				{
					if(sIP.substr(0, found) == sIP.substr(found+1, sIP.length()-found-1))
						sIP = sIP.substr(0, found);
					makeRule(sName+std::wstring(L"in"), sDescription, sAddr, 1, NET_FW_RULE_DIR_IN);
					makeRule(sName+std::wstring(L"out"), sDescription, sAddr, 1, NET_FW_RULE_DIR_OUT);
				}
				else
					std::cout << "Inappropriate input\n";
			else
				std::cout << "Inappropriate input\n";
		}
	}
	else if(nAction == 2)
	{
		if(isWstringIP(sIP))
		{
			sAddr = sIP + std::wstring(L"/255.255.255.255");
			makeRule(sName, sDescription, sAddr, 2, NET_FW_RULE_DIR_IN);
		}
		else
		{
			std::size_t found = sIP.find('-');
			if(found!=std::string::npos)
				if(isWstringIP(sIP.substr(0, found)) && isWstringIP(sIP.substr(found+1, sIP.length()-found-1)))
				{
					if(sIP.substr(0, found) == sIP.substr(found+1, sIP.length()-found-1))
						sIP = sIP.substr(0, found);
					sAddr = sIP;
					makeRule(sName, sDescription, sAddr, 2, NET_FW_RULE_DIR_IN);
				}
				else
					std::cout << "Inappropriate input\n";
			else
				std::cout << "Inappropriate input\n";
		}
	}
}

// Determine if the wstring can be interpreted as an IP
bool cFwAccess::isWstringIP(std::wstring &str)
{
	int nTemp = 0, nCount = 0;
	for(int i = 0; i < str.length(); i++)
	{
		if(str[i] >= 48 && str[i] <= 57)
		{
			nTemp = nTemp * 10;
			nTemp += str[i] - 48;
		}
		else if(str[i] == 46)
			if(nTemp >= 0 && nTemp <= 255 && nCount < 4)
			{
				nTemp = 0;
				nCount++;
			}
			else
				return false;
		else
			return false;
	}
	if(nTemp >= 0 && nTemp <= 255 && nCount == 3)
		return true;
	else
		return false;
}