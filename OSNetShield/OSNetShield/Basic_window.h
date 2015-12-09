#pragma once
#include "resource.h"
#include "cFwAccess.h"

///
/// Method which puts the main window into its own thread
///
void thread_Proc(cFwAccess *pFwAccessIn);

///
/// The main window which allows block and unblock IPs
/// Also provides access to other windows
///
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
	afx_msg void OnBnClickedTCP();
	afx_msg void OnBnClickedBase();
	afx_msg void OnBnClickedExit();

private:
	cFwAccess *pFwAccess;
	
};
