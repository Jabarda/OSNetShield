#pragma once
#include "resource.h"
#include "afxwin.h"
#include "Country_Data.h"
// ���������� ���� CountryDataDialog
void StartCountryDataWindow();
class CountryDataDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CountryDataDialog)

public:
	Country_Data DataBase;
	CountryDataDialog(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CountryDataDialog();

// ������ ����������� ����
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox Combo;
};
