#include "stdafx.h"
#include "mainForm.h"
#include "windows.h"
//#include "Basic_window.h"	
#include "resource.h"

mainForm::mainForm()
{
}

void Button_Block_Clicked()
{

}

HINSTANCE TheInstance = 0;

int WINAPI mainForm::WinMain(HINSTANCE hInst, // дескриптор экземпл€ра приложени€
	HINSTANCE hPreviousInst, // в Win32 не используетс€, но объ€вление нужно
	LPSTR lpCommandLine, // нужен дл€ запуска окошка в режиме командной строки
	int nCommandShow) // режим отображени€ окна
{
	
	TheInstance = hInst;
	//_set_new_handler(& NewHandler);

	HWND hDialog = 0;
	
	hDialog = CreateDialog(hInst, (LPCWSTR)IDD_DIALOG1, 0,NULL);
	ShowWindow(hDialog, nCommandShow);
	
	MSG  msg;
	int status;
	while ((status = GetMessage(&msg, 0, 0, 0)) != 0)
	{
		if (status == -1)
			return -1;
		if (!IsDialogMessage(hDialog, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	/*
	Basic_window *pParent = new Basic_window();
	//Check if new succeeded and we got a valid pointer to a dialog object
	if (pParent != NULL)
	{
		CWnd *a = new CWnd();
		BOOL ret = pParent->Create((LPCTSTR)IDD_DIALOG1, a);
		//BOOL ret = pParent->Create(NULL, NULL, NULL, CRect(0, 0, 20, 20), this, IDD_DIALOG1, NULL);

		if (!ret)   //Create failed.
			AfxMessageBox(_T("Error creating Dialog"));

		pParent->ShowWindow(SW_SHOW);
	}
	else
	{
		AfxMessageBox(_T("Error Creating Dialog Object"));
	}
	*/
	return NULL;
}

mainForm::~mainForm()
{
}
