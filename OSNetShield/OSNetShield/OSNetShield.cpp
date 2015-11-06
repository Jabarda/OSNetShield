#include "stdafx.h"
#include <stdio.h>
#include <cFwAccess.h>

int __cdecl main()
{
	int menuAction = 0;

	std::string sName = "Name", sDescription = "Description", sGroup = "Group", sAddr = "0.0.0.0";

	cFwAccess oFwChanger;

	std::vector<BSTR> vFwAddedRules;
	
	oFwChanger.ruleMaker(sName, sDescription, sGroup, sAddr, 0, vFwAddedRules);

	std::cout << "The application blocks and unblocks a site by its IP\n";

	while(menuAction != 3)
	{
		std::cout << vFwAddedRules.size() << "\n";
		std::cout << "\n1) Block IP\n2) Unblock IP\n3) Exit\n";
		std::cin >> menuAction;
		getchar();
		if(menuAction == 1)
		{
			std::cout << "The rule name is OSNetShield" << vFwAddedRules.size()+1 << "\n";
			sName = "OSNetShield"+std::to_string(vFwAddedRules.size()+1);
			std::cout << "Enter the rule description:\t";
			std::getline(std::cin, sDescription);
			std::cout << "Enter the rule group:\t";
			std::getline(std::cin, sGroup);
			std::cout << "Enter the IP to block:\t";
			std::getline(std::cin, sAddr);
			oFwChanger.ruleMaker(sName, sDescription, sGroup, sAddr, 1, vFwAddedRules);
		}
		else if(menuAction == 2)
		{
			std::cout << "Enter the rule name:\t";
			std::getline(std::cin, sName);
			oFwChanger.ruleMaker(sName, sDescription, sGroup, sAddr, 2, vFwAddedRules);
		}
	}

    return 0;
}