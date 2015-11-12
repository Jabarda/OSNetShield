
#include <winsock2.h>
#include <conio.h>
#include <iostream>
#include <thread>

#define MAX_PACKET_SIZE 0x10000

static char  Buffer[MAX_PACKET_SIZE];
#pragma once

typedef struct _IPHeader
{
	unsigned char  verlen;   // ������ � ����� ���������
	unsigned char  tos;      // ��� ������� 
	unsigned short length;   // ����� ����� ������ 
	unsigned short id;       // Id 
	unsigned short offset;   // ����� � �������� 
	unsigned char  ttl;      // ����� ����� 
	unsigned char  protocol; // �������� 
	unsigned short xsum;     // ����������� ����� 
	unsigned long  src;      // IP-����� ����������� 
	unsigned long  dest;     // IP-����� ���������� 
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

