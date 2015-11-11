#include "stdafx.h"
#include "NetShieldSniffer.h"


NetShieldSniffer::NetShieldSniffer()
{
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	s = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
	gethostname(name, sizeof(name));
	phe = gethostbyname(name);

	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = ((struct in_addr *)phe->h_addr_list[0])->s_addr;
	bind(s, (SOCKADDR *)&sa, sizeof(SOCKADDR));

	// Включение promiscuous mode.
	ioctlsocket(s, 0x98000001, &flag);
}


NetShieldSniffer::~NetShieldSniffer()
{
}

void listenFunThr(){
	int count;
	count = recv(s, Buffer, sizeof(Buffer), 0);

	if (count >= sizeof(IPHeader))
	{
		IPHeader* hdr = (IPHeader *)Buffer;
		std::cout << hdr;
	}
}
void NetShieldSniffer::startListen(){

	// Приём IP-пакетов.
	std::thread t(listenFunThr);
	
		
}

void NetShieldSniffer::stopListen(){

	// Конец работы.
	closesocket(s);
	WSACleanup();
}

