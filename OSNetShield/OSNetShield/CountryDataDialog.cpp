// CountryDataDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "CountryDataDialog.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Country_Data.h"
// диалоговое окно CountryDataDialog

IMPLEMENT_DYNAMIC(CountryDataDialog, CDialogEx)

void StartCountryDataWindow()
{
	CountryDataDialog CountryDataDialog;
	CountryDataDialog.DoModal();
	//CountryDataDialog.OnBnClickedButton1();
	
}

CountryDataDialog::CountryDataDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CountryDataDialog::IDD, pParent)
{
	
}

CountryDataDialog::~CountryDataDialog()
{
}

void CountryDataDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, Combo);
}


BEGIN_MESSAGE_MAP(CountryDataDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CountryDataDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CountryDataDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CountryDataDialog::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CountryDataDialog::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// обработчики сообщений CountryDataDialog


void CountryDataDialog::OnBnClickedButton1()
{
	DataBase.UpdateDB();
	std::set<std::string> ComboList;
	Combo.ResetContent();
	for (int i = 0; i < DataBase.amount; i++)
	{
		if (ComboList.find(DataBase.Base[i].LongName) == ComboList.end())
		{
			ComboList.insert(DataBase.Base[i].LongName);
			//LPCTSTR buf = DataBase.Base[i].ShortName;
			//std::cout << &buf << "\n";
			//_getch();
			//СДЕЛАТЬ НОРМАЛЬНЫЙ ВЫВОД
			CString buf(DataBase.Base[i].LongName.c_str());
			Combo.AddString(buf.GetString());
		}
	}
	// TODO: добавьте свой код обработчика уведомлений
}


void CountryDataDialog::OnBnClickedButton2()
{
	
	CString s;
	Combo.GetWindowTextW(s);
	for (int i = 0; i < DataBase.amount; i++)
	{
		if (s == DataBase.Base[i].LongName.c_str()) {
			//TODO
		};
	}
	
}


void CountryDataDialog::OnBnClickedButton3()
{
	CString s;
	Combo.GetWindowTextW(s);
	for (int i = 0; i < DataBase.amount; i++)
	{
		if (s == DataBase.Base[i].LongName.c_str()) {
			//TODO
		};
	}
}


void CountryDataDialog::OnCbnSelchangeCombo1()
{
	// TODO: добавьте свой код обработчика уведомлений
}
