// TCPForm.cpp: файл реализации
//

#include "stdafx.h"
#include "TCPForm.h"
#include "afxdialogex.h"
#include "resource.h"



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
	SetDlgItemText(IDC_EDIT1, L"jabarda");
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
END_MESSAGE_MAP()


// обработчики сообщений TCPForm


void TCPForm::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnOK();
}
