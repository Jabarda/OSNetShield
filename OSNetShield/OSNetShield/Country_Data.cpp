#include "stdafx.h"
#include "Country_Data.h"

/*
	struct Country_Data::Value
	{
		std::string ShortName, LongName;
		in_addr from, to;
	};
	*/
	Country_Data::Country_Data()
	{
		Base.reserve(200000);
		//for(int i = 0; i < 200000; i++)
		//{
		//	Base[i].ShortName = "";
		//	Base[i].LongName = "";
		//	Base[i].from = in_addr();
		//	Base[i].to = ;
		//}
	}

	std::string Country_Data::UpdateDB()
	{	
		
		//std::cout << "Beginning DataBase updating\n";
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
			//std::cout << ip_addr.S_un.S_addr;
			//_getch();
			//Base[CurrentBaseElement].from = inet_ntoa(ip_addr);
			//std::cout << "\n" << addr;
			//unsigned char bytes[4];
			//bytes[0] = addr & 0xFF;
			//bytes[1] = (addr >> 8) & 0xFF;
			//bytes[2] = (addr >> 16) & 0xFF;
			//bytes[3] = (addr >> 24) & 0xFF;
			//std::cout << (char)bytes[3] << "." << (char)bytes[2] << "." << (char)bytes[1] << "." << (char)bytes[0] << "\n";
			//_getch();
			/*
			Base[CurrentBaseElement].from = (reinterpret_cast<char*>(bytes));
			std::cout << Base[CurrentBaseElement].from<<"   jabarda\n";
			_getch();
			*/
			
			addr = 0;
			i++;
			while (Buf[i] != ',')
			{
				addr = addr * 10 + (int)Buf[i] - 48;
				i++;
			}
			Base[CurrentBaseElement].to.s_addr = addr;
			//Base[CurrentBaseElement].to = inet_ntoa(ip_addr);
			//std::cout << "\n" << addr<<"\n";
			//Base[CurrentBaseElement].to = (addr & 0xFF) + ((addr >> 8) & 0xFF) + ((addr >> 16) & 0xFF) + ((addr >> 24) & 0xFF);
			i++;
			//int num = 0;
			
			//Base[CurrentBaseElement].LongName = '\0';
			//Base[CurrentBaseElement].ShortName.;
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
			//std::cout << Base[CurrentBaseElement].from << "\n" << Base[CurrentBaseElement].to << "\n" << Base[CurrentBaseElement].ShortName << "\n" << Base[CurrentBaseElement].LongName << "\n";
			//_getch();
			//std::cout << CurrentBaseElement << "\n";
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

