#include "stdafx.h"
#include <stdio.h>
#include "NetShieldSniffer.h"
#include "Basic_window.h"
#include "TCPForm.h"
//#include "cFwAccess.h"



int __cdecl main()
{
	AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);

	cFwAccess oFwChanger;

	std::thread thr(thread_Proc, &oFwChanger);
	
	thr.detach();

	NetShieldSniffer mySniffa;
	mySniffa.startListen();
	std::cout << "Sniffer started sniffing\n";

	oFwChanger.controlFw();

    return 0;
}