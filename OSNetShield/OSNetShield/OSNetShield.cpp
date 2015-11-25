#include "stdafx.h"
#include <stdio.h>
#include "NetShieldSniffer.h"
#include "Basic_window.h"
#include "Country_Data.h"
//#include "cFwAccess.h"

int __cdecl main()
{
	//setlocale(LC_ALL, "rus");
	AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);

	cFwAccess oFwChanger;

	std::thread thr(thread_Proc, &oFwChanger);
	thr.detach();

	//Country_Data Base;
	//std::cout << Base.UpdateDB();
	//Base.print();
	//N1tShieldSniffer mySniffa;
	//mySniffa.startListen();
	//std::cout << "Sniffer started sniffing\n";
	
	oFwChanger.controlFw();

    return 0;
}