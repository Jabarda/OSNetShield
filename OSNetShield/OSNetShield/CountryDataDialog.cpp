// CountryDataDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "CountryDataDialog.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Country_Data.h"
// диалоговое окно CountryDataDialog

IMPLEMENT_DYNAMIC(CountryDataDialog, CDialogEx)

void StartCountryDataWindow(cFwAccess *pFwAccessIn)
{
	CountryDataDialog CountryDataDialog(pFwAccessIn);
	CountryDataDialog.DoModal();
	//CountryDataDialog.OnBnClickedButton1();
	
}

CountryDataDialog::CountryDataDialog(cFwAccess *pFwAccessIn, CWnd* pParent /*=NULL*/)
	: CDialogEx(CountryDataDialog::IDD, pParent)
{
	pFwAccess = pFwAccessIn;
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
	std::wstring wsIPRange;
	Combo.GetWindowTextW(s);
	for (int i = 0; i < DataBase.amount; i++)
	{
		if (s == DataBase.Base[i].LongName.c_str()) 
		//CString buf(DataBase.Base[i].LongName.c_str());
		//if(s.GetString() == buf.GetString())
		{
			wsIPRange = std::wstring(inet_ntoa(DataBase.Base[i].from), inet_ntoa(DataBase.Base[i].from)+strlen(inet_ntoa(DataBase.Base[i].from)));
			pFwAccess->controlFwGUI(wsIPRange, 1);
		}
		//
		// добавить проверку строки s с DataBase.Base[i].LongName, если верно то
		// заблокировать диапазон DataBase.Base[i].from - DataBase.Base[i].to
	}
	
}


void CountryDataDialog::OnBnClickedButton3()
{
	CString s;
	std::wstring wsIPRange;
	Combo.GetWindowTextW(s);
	for (int i = 0; i < DataBase.amount; i++)
	{
		if (s == DataBase.Base[i].LongName.c_str()) 
		//CString buf(DataBase.Base[i].LongName.c_str());
		//if(s.GetString() == buf.GetString())
		{
			wsIPRange = std::wstring(inet_ntoa(DataBase.Base[i].from), inet_ntoa(DataBase.Base[i].from)+strlen(inet_ntoa(DataBase.Base[i].from)));
			pFwAccess->controlFwGUI(wsIPRange, 2);
		}
		//
		// добавить проверку строки s с DataBase.Base[i].ShortName, если верно то
		// РАЗблокировать диапазон DataBase.Base[i].from - DataBase.Base[i].to
	}
}


void CountryDataDialog::OnCbnSelchangeCombo1()
{
	// TODO: добавьте свой код обработчика уведомлений
}
