#include "stdafx.h"
#include <stdio.h>
#include "NetShieldSniffer.h"
#include "cFwAccess.h"

int __cdecl main()
{
	int menuAction = 0;
	NetShieldSniffer mySniffa;
	mySniffa.startListen();
	std::cout << "Sniffer started sniffing\n";
	cFwAccess oFwChanger;
	oFwChanger.controlFw();

    return 0;
}