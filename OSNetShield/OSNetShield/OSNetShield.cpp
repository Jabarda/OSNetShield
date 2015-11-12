#include "stdafx.h"
#include <stdio.h>
#include "NetShieldSniffer.h"
#include "cFwAccess.h"
#include "Basic_window.h"	
#include "mainForm.h"
#include "windows.h"
#include "Basic_window.h"


void thread_Proc()
{
	mainForm *ok = new mainForm();
	ok->WinMain(NULL, NULL, NULL, 1);
}

int __cdecl main()
{
	AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
	Basic_window window;
	window.DoModal();
	
	
	//std::thread thr(thread_Proc);
	/*
	NetShieldSniffer mySniffa;
	mySniffa.startListen();
	std::cout << "Sniffer started sniffing\n";
	*/
	cFwAccess oFwChanger;
	oFwChanger.controlFw();

    return 0;
}