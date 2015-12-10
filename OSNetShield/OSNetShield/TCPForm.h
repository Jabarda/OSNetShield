#pragma once
#include "resource.h"

///
/// The method puts the TCP connections window in its own thread
///
void thread_Proc2();

class TCPForm : public CDialog
{
	DECLARE_DYNAMIC(TCPForm)

public:
	TCPForm(CWnd* pParent = NULL);   // standart constructor
	void TCPForm::HideLabel();
	virtual ~TCPForm();

// dialog window data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    //DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedUpdate();
};
