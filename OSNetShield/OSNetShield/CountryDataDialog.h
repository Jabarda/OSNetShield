#pragma once
#include "resource.h"
#include "afxwin.h"
#include "Country_Data.h"
#include "cFwAccess.h"

// ���������� ���� CountryDataDialog
void StartCountryDataWindow(cFwAccess *pFwAccessIn);
std::wstring intToIP(int compressedIp);

class CountryDataDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CountryDataDialog)

public:
	Country_Data DataBase;
	CountryDataDialog(cFwAccess *pFwAccessIn, CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CountryDataDialog();

// ������ ����������� ����
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	cFwAccess *pFwAccess;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox Combo;
};
