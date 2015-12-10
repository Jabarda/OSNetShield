#include "TCPTabel.h"
#include "stdafx.h"

// Need to link with Iphlpapi.lib and Ws2_32.lib
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
/* Note: could also use malloc() and free() */

///
/// Fills the table in the TCP window with active TCP connections
///
int Get_Info(CWnd* pWnd, CWnd* waitLabel)
{
	setlocale(LC_ALL, "");
	CString before;
	CString inp;
	
	pWnd->SetWindowTextW(inp);
	
	// Declare and initialize variables
	PMIB_TCPTABLE2 pTcpTable;
	ULONG ulSize = 0;
	DWORD dwRetVal = 0;

	char szLocalAddr[128];
	char szRemoteAddr[128];
	char localh[128] = "127.0.0.1";
	char zeros[128] = "0.0.0.0";

	struct in_addr IpAddr;

	//in_addr localh;
	//inet_pton(AF_INET, "127.0.0.1", );
	int i;
	
	pTcpTable = (MIB_TCPTABLE2 *)MALLOC(sizeof(MIB_TCPTABLE2));
	if (pTcpTable == NULL) {
		pWnd->GetWindowTextW(before);
		pWnd->SetWindowTextW(before + L"Error allocating memory\r\n");
		//printf("Error allocating memory\n");
		return 1;
	}

	ulSize = sizeof(MIB_TCPTABLE);
	// Make an initial call to GetTcpTable2 to
	// get the necessary size into the ulSize variable
	if ((dwRetVal = GetTcpTable2(pTcpTable, &ulSize, TRUE)) ==
		ERROR_INSUFFICIENT_BUFFER) {
		FREE(pTcpTable);
		pTcpTable = (MIB_TCPTABLE2 *)MALLOC(ulSize);
		if (pTcpTable == NULL) {
			pWnd->GetWindowTextW(before);
			pWnd->SetWindowTextW(before + L"Error allocating memory\r\n");
			return 1;
		}
	}
	// Make a second call to GetTcpTable2 to get
	// the actual data we require
	if ((dwRetVal = GetTcpTable2(pTcpTable, &ulSize, TRUE)) == NO_ERROR) {
		inp.Format(_T("Number of entries: %d\r\n"), (int)pTcpTable->dwNumEntries);
		pWnd->GetWindowTextW(before);
		pWnd->SetWindowTextW(before + inp);
		for (i = 0; i < (int)pTcpTable->dwNumEntries; i++) {

			IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
			strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));
			//if (*szRemoteAddr != *localh && *szRemoteAddr != *zeros)
			//{
				
				inp.Format(_T("\r\nTCP[%d] State: %ld - "), i,
					pTcpTable->table[i].dwState);
				pWnd->GetWindowTextW(before);
				pWnd->SetWindowTextW(before + inp);
				switch (pTcpTable->table[i].dwState) {
				case MIB_TCP_STATE_CLOSED:
				{
					inp.Format(_T("CLOSED\r\n"));
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				case MIB_TCP_STATE_LISTEN:
				{
					inp.Format(_T("LISTEN\r\n"));
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				case MIB_TCP_STATE_SYN_SENT:
				{
					inp.Format(_T("SYN-SENT\r\n"));
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				case MIB_TCP_STATE_SYN_RCVD:
				{
					inp.Format(_T("SYN-RECEIVED\r\n"));
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				case MIB_TCP_STATE_ESTAB:
				{
					inp.Format(_T("ESTABLISHED\r\n"));
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				case MIB_TCP_STATE_FIN_WAIT1:
				{
					inp.Format(_T("FIN-WAIT-1\r\n"));
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				case MIB_TCP_STATE_FIN_WAIT2:
				{
					inp.Format(_T("FIN-WAIT-2 \r\n"));
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				case MIB_TCP_STATE_CLOSE_WAIT:
				{
					inp.Format(_T("CLOSE-WAIT\r\n"));
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				case MIB_TCP_STATE_CLOSING:
				{
					inp.Format(_T("CLOSING\r\n"));
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				case MIB_TCP_STATE_LAST_ACK:
				{
					inp.Format(_T("LAST-ACK\r\n"));
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				case MIB_TCP_STATE_TIME_WAIT:
				{
					inp.Format(_T("TIME-WAIT\r\n"));
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				case MIB_TCP_STATE_DELETE_TCB:
				{
					inp.Format(_T("DELETE-TCB\r\n"));
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				default:
				{
					inp.Format(_T("UNKNOWN dwState value: %d\r\n"), pTcpTable->table[i].dwState);
					pWnd->GetWindowTextW(before);
					pWnd->SetWindowTextW(before + inp);
					break;
				}
				}

				IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
				strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr));
				CString adr;
				adr = szLocalAddr;
				inp.Format(_T("TCP[%d] Local Addr: %s \r\n"), i, adr);
				pWnd->GetWindowTextW(before);
				pWnd->SetWindowTextW(before + inp);

				inp.Format(_T("TCP[%d] Local Port: %d \r\n"), i,
					ntohs((u_short)pTcpTable->table[i].dwLocalPort));
				pWnd->GetWindowTextW(before);
				pWnd->SetWindowTextW(before + inp);
				adr = szRemoteAddr;
				//!!!!
				inp.Format(_T("TCP[%d] Remote Addr: %s \r\n"), i, adr);
				pWnd->GetWindowTextW(before);
				pWnd->SetWindowTextW(before + inp);

				inp.Format(_T("TCP[%d] Remote Port: %d\r\n"), i,
					ntohs((u_short)pTcpTable->table[i].dwRemotePort));
				pWnd->GetWindowTextW(before);
				pWnd->SetWindowTextW(before + inp);
				inp.Format(_T("TCP[%d] Owning PID: %d\r\n"), i, pTcpTable->table[i].dwOwningPid);
				pWnd->GetWindowTextW(before);
				pWnd->SetWindowTextW(before + inp);
				inp.Format(_T("TCP[%d] Offload State: %ld - "), i,
					pTcpTable->table[i].dwOffloadState);
				pWnd->GetWindowTextW(before);
				pWnd->SetWindowTextW(before + inp);
				switch (pTcpTable->table[i].dwOffloadState) {
				case TcpConnectionOffloadStateInHost:
					inp.Format(_T("Owned by the network stack and not offloaded \r\n"));
					break;
				case TcpConnectionOffloadStateOffloading:
					inp.Format(_T("In the process of being offloaded\r\n"));
					break;
				case TcpConnectionOffloadStateOffloaded:
					inp.Format(_T("Offloaded to the network interface control\r\n"));
					break;
				case TcpConnectionOffloadStateUploading:
					inp.Format(_T("In the process of being uploaded back to the network stack \r\n"));
					break;
				default:
					inp.Format(_T("UNKNOWN Offload state value\r\n"));
					break;
				}
				pWnd->GetWindowTextW(before);
				pWnd->SetWindowTextW(before + inp);
			//}

		}
	}
	else {
		inp.Format(_T("GetTcpTable2 failed with %d\r\n"), dwRetVal);
		pWnd->GetWindowTextW(before);
		pWnd->SetWindowTextW(before + inp);
		FREE(pTcpTable);
		return 1;
	}

	if (pTcpTable != NULL) {
		FREE(pTcpTable);
		pTcpTable = NULL;
	}
	waitLabel->SetWindowTextW(L"Update");
	return 0;

}