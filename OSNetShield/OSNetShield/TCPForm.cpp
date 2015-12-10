#include "stdafx.h"
#include "TCPForm.h"
#include "afxdialogex.h"
#include "resource.h"
#include "TCPTabel.h"

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
	ON_BN_CLICKED(ID_UPDATE_BUTTON, &TCPForm::OnBnClickedUpdate)
END_MESSAGE_MAP()


// Event handlers

void TCPForm::OnBnClickedOk()
{
	CDialog::OnOK();
}

///
/// Updates info on the TCP connections window
///
void TCPForm::OnBnClickedUpdate()
{
	CWnd* button = GetDlgItem(ID_UPDATE_BUTTON);
	button->SetWindowTextW(L"Please, wait...");
	CWnd* pWnd = GetDlgItem(IDC_EDIT5);
	Get_Info(pWnd, button);
}
