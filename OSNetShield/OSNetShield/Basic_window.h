#pragma once
#include "resource.h"
#include "cFwAccess.h"

// ���������� ���� Basic_window

void thread_Proc(cFwAccess *pFwAccessIn);

class Basic_window : public CDialog
{
	DECLARE_DYNAMIC(Basic_window)

public:
	Basic_window(cFwAccess *pFwAccessIn, CWnd* pParent = NULL);   // ����������� �����������
	virtual ~Basic_window();
	
// ������ ����������� ����
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()

public:
	
	afx_msg void OnBnClickedBlock();
	afx_msg void OnBnClickedUnblock();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();

private:
	cFwAccess *pFwAccess;
};
