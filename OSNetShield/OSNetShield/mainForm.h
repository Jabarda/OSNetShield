#pragma once

class mainForm
{
public:
	CString text;
	mainForm();
	void Button_Block_Clicked();
	int WINAPI WinMain(HINSTANCE hInst, // ���������� ���������� ����������
		HINSTANCE hPreviousInst, // � Win32 �� ������������, �� ���������� �����
		LPSTR lpCommandLine, // ����� ��� ������� ������ � ������ ��������� ������
		int nCommandShow);
	~mainForm();
};

