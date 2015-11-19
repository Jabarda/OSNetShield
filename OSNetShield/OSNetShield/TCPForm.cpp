// TCPForm.cpp: файл реализации
//

#include "stdafx.h"
#include "TCPForm.h"
#include "afxdialogex.h"
#include "resource.h"
#include "TCPTabel.h"


// диалоговое окно TCPForm

IMPLEMENT_DYNAMIC(TCPForm, CDialog)
void thread_Proc2()
{
	TCPForm TCPForm;
	TCPForm.DoModal();
	
}

TCPForm::TCPForm(CWnd* pParent /*=NULL*/)
	: CDialog(TCPForm::IDD, pParent)
{
	
}

void TCPForm::HideLabel()
{
	GetDlgItem(IDC_STATIC)->ShowWindow(SW_HIDE);
}

TCPForm::~TCPForm()
{
}

void TCPForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TCPForm, CDialog)
	ON_BN_CLICKED(IDOK, &TCPForm::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &TCPForm::OnBnClickedButton1)
END_MESSAGE_MAP()


// обработчики сообщений TCPForm


void TCPForm::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnOK();
}


void TCPForm::OnBnClickedButton1()
{
	CWnd* button = GetDlgItem(IDC_BUTTON1);
	button->SetWindowTextW(L"Please, wait...");
	CWnd* pWnd = GetDlgItem(IDC_EDIT5);
	//CWnd* waitLabel = GetDlgItem(IDC_STATIC);
	Get_Info(pWnd, button);
	/*CString before;
	pWnd->GetWindowTextW(before);
	SetDlgItemText(IDC_EDIT5, before+L"\r\nDesired Text String");*/
	// TODO: добавьте свой код обработчика уведомлений
}
