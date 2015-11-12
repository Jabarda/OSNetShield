#pragma once

class mainForm
{
public:
	mainForm();
	void Button_Block_Clicked();
	int WINAPI WinMain(HINSTANCE hInst, // дескриптор экземпл€ра приложени€
		HINSTANCE hPreviousInst, // в Win32 не используетс€, но объ€вление нужно
		LPSTR lpCommandLine, // нужен дл€ запуска окошка в режиме командной строки
		int nCommandShow);
	~mainForm();
};

