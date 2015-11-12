#include "stdafx.h"
#include <stdio.h>
#include "NetShieldSniffer.h"
#include "cFwAccess.h"

int __cdecl main()
{
	NetShieldSniffer mySniffa;
	mySniffa.startListen();
	std::cout << "Sniffer started sniffing\n";
<<<<<<< HEAD
	mySniffa.stopListen();
	std::string sName = "Name", sDescription = "Description", sGroup = "Group", sAddr = "0.0.0.0";
=======
>>>>>>> refs/remotes/origin/WinFWDev

	cFwAccess oFwChanger;
	oFwChanger.controlFw();

    return 0;
}