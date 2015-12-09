// Basic_window.cpp: файл реализации
//

#include "stdafx.h"
#include "Basic_window.h"
#include "afxdialogex.h"
#include <iostream>
#include "TCPForm.h"
#include "thread"
#include "CountryDataDialog.h"


void thread_Proc(cFwAccess *pFwAccessIn)
{
	Basic_window window(pFwAccessIn);
	window.DoModal();
}


IMPLEMENT_DYNAMIC(Basic_window, CDialogEx)


Basic_window::Basic_window(cFwAccess *pFwAccessIn, CWnd* pParent /*=NULL*/)
	: CDialog(Basic_window::IDD, pParent)
{
	pFwAccess = pFwAccessIn;
}

Basic_window::~Basic_window()
{
}

void Basic_window::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Basic_window, CDialog)
	ON_BN_CLICKED(IDBlock, &Basic_window::OnBnClickedBlock)
	ON_BN_CLICKED(IDUnblock, &Basic_window::OnBnClickedUnblock)
	ON_BN_CLICKED(ID_TCP_BUTTON, &Basic_window::OnBnClickedTCP)
	ON_BN_CLICKED(ID_DATABASE_BUTTON, &Basic_window::OnBnClickedBase)
	ON_BN_CLICKED(ID_EXIT, &Basic_window::OnBnClickedExit)
END_MESSAGE_MAP()


// Event handlers

// If input is correct blocks it
void Basic_window::OnBnClickedBlock()
{
	CString s;
	GetDlgItem(IDC_EDIT1)->GetWindowText(s);

	int msgboxID;

	if(pFwAccess->isWstringIP(std::wstring(s)))
		{
			if(s.GetLength() != 0)
				pFwAccess->controlFwGUI(std::wstring(s), 1);

			s = "Blocked " + s;
			msgboxID = MessageBox(
				(LPCTSTR)s,
				(LPCTSTR)L"Block",
				MB_OK
			);
		}
	else
		{
			std::size_t found = std::wstring(s).find('-');
			if(found!=std::string::npos)
				if(pFwAccess->isWstringIP(std::wstring(s).substr(0, found)) && pFwAccess->isWstringIP(std::wstring(s).substr(found+1, std::wstring(s).length()-found-1)))
				{
					if(s.GetLength() != 0)
						pFwAccess->controlFwGUI(std::wstring(s), 1);

						s = "Blocked " + s;
						msgboxID = MessageBox(
							(LPCTSTR)s,
							(LPCTSTR)L"Block",
							MB_OK
						);
				}
				else
					msgboxID = MessageBox(
						(LPCTSTR)L"Inappropriate input",
						(LPCTSTR)L"Error",
						MB_ICONERROR | MB_OK
					);
			else
				msgboxID = MessageBox(
						(LPCTSTR)L"Inappropriate input",
						(LPCTSTR)L"Error",
						MB_ICONERROR | MB_OK
					);
		}
}

// If input is correct unblocks it
void Basic_window::OnBnClickedUnblock()
{
	CString s;
	GetDlgItem(IDC_EDIT1)->GetWindowText(s);

	int msgboxID;

	if(pFwAccess->isWstringIP(std::wstring(s)))
		{
			if(s.GetLength() != 0)
				pFwAccess->controlFwGUI(std::wstring(s), 2);

			s = "Unblocked " + s;
			int msgboxID = MessageBox(
				(LPCTSTR)s,
				(LPCTSTR)L"Unblock",
				MB_OK
			);
		}
	else
		{
			std::size_t found = std::wstring(s).find('-');
			if(found!=std::string::npos)
				if(pFwAccess->isWstringIP(std::wstring(s).substr(0, found)) && pFwAccess->isWstringIP(std::wstring(s).substr(found+1, std::wstring(s).length()-found-1)))
				{
					if(s.GetLength() != 0)
						pFwAccess->controlFwGUI(std::wstring(s), 2);

						s = "Unblocked " + s;
						int msgboxID = MessageBox(
							(LPCTSTR)s,
							(LPCTSTR)L"Unblock",
							MB_OK
						);
				}
				else
					msgboxID = MessageBox(
						(LPCTSTR)L"Inappropriate input",
						(LPCTSTR)L"Error",
						MB_ICONERROR | MB_OK
					);
			else
				msgboxID = MessageBox(
						(LPCTSTR)L"Inappropriate input",
						(LPCTSTR)L"Error",
						MB_ICONERROR | MB_OK
					);
		}
}

// Open the window with TCP connections
void Basic_window::OnBnClickedTCP()
{
	std::thread TCPwindow(thread_Proc2);
	TCPwindow.detach();
	// TODO: добавьте свой код обработчика уведомлений
}

// Open the window that allows blocking a database
void Basic_window::OnBnClickedBase()
{
	std::thread CountryDataDialog(StartCountryDataWindow, pFwAccess);
	CountryDataDialog.detach();
	// TODO: добавьте свой код обработчика уведомлений
}

// Guess what
void Basic_window::OnBnClickedExit()
{	
	CDialog::OnOK();
	exit(0);

	// TODO: добавьте свой код обработчика уведомлений
}
