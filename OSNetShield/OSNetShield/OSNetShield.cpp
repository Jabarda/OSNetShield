#include "stdafx.h"
#include <stdio.h>
#include "Basic_window.h"
#include "Country_Data.h"

int __cdecl main()
{
	AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);

	cFwAccess oFwChanger;

	std::thread thr(thread_Proc, &oFwChanger);
	thr.detach();
	oFwChanger.controlFw();

    return 0;
}