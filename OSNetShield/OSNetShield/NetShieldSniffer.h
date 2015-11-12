
#include <winsock2.h>
#include <conio.h>
#include <iostream>
#include <thread>

#define MAX_PACKET_SIZE 0x10000

static char  Buffer[MAX_PACKET_SIZE];
#pragma once

typedef struct _IPHeader
{
	unsigned char  verlen;   // версия и длина заголовка
	unsigned char  tos;      // тип сервиса 
	unsigned short length;   // длина всего пакета 
	unsigned short id;       // Id 
	unsigned short offset;   // флаги и смещения 
	unsigned char  ttl;      // время жизни 
	unsigned char  protocol; // протокол 
	unsigned short xsum;     // контрольная сумма 
	unsigned long  src;      // IP-адрес отправителя 
	unsigned long  dest;     // IP-адрес назначения 
}IPHeader;

void listenFunThr(SOCKET &s,boolean &isRun);
class NetShieldSniffer
{
private:
	WSADATA wsadata;
	SOCKET s;
	char name[128];
	HOSTENT* phe;
	SOCKADDR_IN sa;
	u_long flag;
	boolean isRunning;
public:
	NetShieldSniffer();
	~NetShieldSniffer();
	void startListen();
	void stopListen();
};

