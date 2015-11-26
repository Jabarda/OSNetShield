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

// диалоговое окно Basic_window

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
	ON_EN_CHANGE(IDC_EDIT1, &Basic_window::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &Basic_window::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &Basic_window::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Basic_window::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Basic_window::OnBnClickedButton3)
END_MESSAGE_MAP()


// обработчики сообщений Basic_window


void Basic_window::OnBnClickedBlock()
{
	CString s;
	GetDlgItem(IDC_EDIT1)->GetWindowText(s);
	// TODO: добавьте свой код обработчика уведомлений
	if(s.GetLength() != 0)
		pFwAccess->controlFwGUI(std::wstring(s), 1);
}


void Basic_window::OnBnClickedUnblock()
{
	CString s;
	GetDlgItem(IDC_EDIT1)->GetWindowText(s);
	// TODO: добавьте свой код обработчика уведомлений

	pFwAccess->controlFwGUI(std::wstring(s), 2);
}


void Basic_window::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.


	// TODO:  Добавьте код элемента управления
}


void Basic_window::OnEnChangeEdit2()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()

	// TODO:  Добавьте код элемента управления
}


void Basic_window::OnBnClickedButton1()
{
	std::thread TCPwindow(thread_Proc2);
	TCPwindow.detach();
	// TODO: добавьте свой код обработчика уведомлений
}


void Basic_window::OnBnClickedButton2()
{
	std::thread CountryDataDialog(StartCountryDataWindow, pFwAccess);
	CountryDataDialog.detach();
	// TODO: добавьте свой код обработчика уведомлений
}


void Basic_window::OnBnClickedButton3()
{	
	CDialog::OnOK();

	// TODO: добавьте свой код обработчика уведомлений
}
