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
	CountryDataDialog CountryDialog(pFwAccessIn);
	CountryDialog.DoModal();
	
	
	
}

std::wstring intToIP(int compressedIp)
{
	unsigned char bytes[4];
    bytes[0] = compressedIp & 0xFF;
    bytes[1] = (compressedIp >> 8) & 0xFF;
    bytes[2] = (compressedIp >> 16) & 0xFF;
    bytes[3] = (compressedIp >> 24) & 0xFF;	
	return std::to_wstring(bytes[3]) + std::wstring(L".") + std::to_wstring(bytes[2]) + std::wstring(L".") + std::to_wstring(bytes[1]) + std::wstring(L".") + std::to_wstring(bytes[0]);
}

BOOL CountryDataDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_EDIT1)->SetWindowText((LPCTSTR)L"IPBase.data");
	return TRUE;
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
	CString s;
	GetDlgItem(IDC_EDIT1)->GetWindowText(s);
	DataBase.UpdateDB(s);
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

	s = s + L" loaded";
	int msgboxID = MessageBox(
				(LPCTSTR)s,
				(LPCTSTR)L"Database load",
				MB_OK
			);
}


void CountryDataDialog::OnBnClickedButton2()
{
	
	CString s;
	std::wstring wsIPRange;
	Combo.GetWindowTextW(s);
	for (int i = 0; i < DataBase.amount; i++)
	{
		if (s == DataBase.Base[i].LongName.c_str()) 
		{
			wsIPRange = intToIP(DataBase.Base[i].from.S_un.S_addr) +
				L"-" +
				intToIP(DataBase.Base[i].to.S_un.S_addr);
			pFwAccess->controlFwGUI(wsIPRange, 1);
		}
		//
		// добавить проверку строки s с DataBase.Base[i].LongName, если верно то
		// заблокировать диапазон DataBase.Base[i].from - DataBase.Base[i].to
	}
	
	int msgboxID = MessageBox(
				(LPCTSTR)L"Group from database blocked",
				(LPCTSTR)L"Group block",
				MB_OK
			);
}


void CountryDataDialog::OnBnClickedButton3()
{
	CString s;
	std::wstring wsIPRange;
	Combo.GetWindowTextW(s);
	for (int i = 0; i < DataBase.amount; i++)
	{
		if (s == DataBase.Base[i].LongName.c_str())
		{
			wsIPRange = intToIP(DataBase.Base[i].from.S_un.S_addr) +
				L"-" +
				intToIP(DataBase.Base[i].to.S_un.S_addr);
			pFwAccess->controlFwGUI(wsIPRange, 2);
		}
		//
		// добавить проверку строки s с DataBase.Base[i].ShortName, если верно то
		// РАЗблокировать диапазон DataBase.Base[i].from - DataBase.Base[i].to
	}

	int msgboxID = MessageBox(
				(LPCTSTR)L"Group from database unblocked",
				(LPCTSTR)L"Group unblock",
				MB_OK
			);
}


void CountryDataDialog::OnCbnSelchangeCombo1()
{
	// TODO: добавьте свой код обработчика уведомлений
}
