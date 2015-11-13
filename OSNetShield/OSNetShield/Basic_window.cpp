// Basic_window.cpp: файл реализации
//

#include "stdafx.h"
#include "Basic_window.h"
#include "afxdialogex.h"
#include <iostream>

// диалоговое окно Basic_window

IMPLEMENT_DYNAMIC(Basic_window, CDialogEx)


Basic_window::Basic_window(CWnd* pParent /*=NULL*/)
	: CDialog(Basic_window::IDD, pParent)
	, text_blablalba(_T(""))
{
	CString text_edit2;
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
END_MESSAGE_MAP()


// обработчики сообщений Basic_window


void Basic_window::OnBnClickedBlock()
{
	CString s;
	GetDlgItem(IDC_EDIT2)->GetWindowText(s);
	// TODO: добавьте свой код обработчика уведомлений
	
	std::wcout << "Block clicked   " << s.GetString() << "   " << s.GetLength();
	
}


void Basic_window::OnBnClickedUnblock()
{
	CString s;
	GetDlgItem(IDC_EDIT2)->GetWindowText(s);
	std::cout << "UnBlock clicked   " << *s;
	// TODO: добавьте свой код обработчика уведомлений
	
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
