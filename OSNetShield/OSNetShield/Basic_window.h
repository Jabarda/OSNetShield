#pragma once
#include "resource.h"
#include "cFwAccess.h"

// dialog window Basic_window

void thread_Proc(cFwAccess *pFwAccessIn);

class Basic_window : public CDialog
{
	DECLARE_DYNAMIC(Basic_window)

public:
	Basic_window(cFwAccess *pFwAccessIn, CWnd* pParent = NULL);   // standart constructor
	virtual ~Basic_window();
	
// dialog window data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	
	afx_msg void OnBnClickedBlock();
	afx_msg void OnBnClickedUnblock();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();

private:
	cFwAccess *pFwAccess;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
