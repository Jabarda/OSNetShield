#include "stdafx.h"
#include "Country_Data.h"

	Country_Data::Country_Data()
	{
		Base.reserve(200000);
	}

	std::string Country_Data::UpdateDB()
	{	
		
		
		std::fstream BaseFile("IPBase.data");
		if (!BaseFile.is_open()) // если файл не открыт
			return "Файл не может быть открыт!\n"; // сообщить об этом
		int CurrentBaseElement = 0;//start parsing
		while (!BaseFile.eof())
		{

			char Buf[1000];
			int addr = 0;
			
			BaseFile >> Buf;
			int i = 0;
			while (Buf[i] != ',')
			{
				addr = addr * 10 + (int)Buf[i] - 48;
				i++;
			}
			Base[CurrentBaseElement].from.s_addr = addr;
			
			addr = 0;
			i++;
			while (Buf[i] != ',')
			{
				addr = addr * 10 + (int)Buf[i] - 48;
				i++;
			}
			Base[CurrentBaseElement].to.s_addr = addr;
			i++;
			Base[CurrentBaseElement].ShortName = "";
			while (Buf[i] != ',')
			{
				Base[CurrentBaseElement].ShortName+= Buf[i];
				i++;
			}
			i++;
			Base[CurrentBaseElement].LongName = "";
			while (Buf[i] != ';')
			{
				Base[CurrentBaseElement].LongName+=Buf[i];
				i++;
			}
			i++; 
		
			CurrentBaseElement++;
			
		}
		BaseFile.close();
		amount = CurrentBaseElement;//set data size
		return "Data update successfully";
	}
	void Country_Data::print()
	{
		for (int i = 0; i < amount; i++)
		{
			_getch();
			std::cout << "\n";
			std::cout << Base[i].from.S_un.S_addr << "\n" << Base[i].to.S_un.S_addr << "\n" << Base[i].ShortName << "\n" << Base[i].LongName << "\n";
		}
	}

	Country_Data::~Country_Data()
	{
	}

