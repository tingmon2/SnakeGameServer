#include "stdafx.h"
#include "SendFunctions.h"

std::string userName;

DWORD WINAPI ThreadFunction(LPVOID pParam)
{
	SOCKET hClient = (SOCKET)pParam;
	PACKET packet;
	packet.opcode = 0;
	packet.data = "";
	while (::recv(hClient, (char*)&packet, sizeof(PACKET), 0) > 0)
	{
		if (packet.opcode < 700)
		{
			switch (packet.opcode)
			{
			case S_RECV_ERROR:
				ErrorHandler("UNKOWN ERROR");
				break;
			case S_RECV_PONG:
				break;
			case S_RECV_EXIT:
				puts("Client disconnected.");
				fflush(stdout);
				Sleep(100);
				::shutdown(hClient, SD_BOTH);
				::closesocket(hClient);
				Sleep(1000);
				return 0;
				break;
			case S_RECV_USER_NAME_INFO:
				userName = packet.data;
				break;
			case S_RECV_MAIN_MENU_SELECT:
				break;
			case S_RECV_GAME_MODE_SELECT:
				break;
			case S_RECV_SCORE_MODE_SELECT:
				break;
			case S_RECV_GAME_START_REQ:
				GameStart(hClient);
				break;
			case S_RECV_TURN_RIGHT:
				break;
			case S_RECV_TURN_LEFT:
				break;
			case S_RECV_TURN_UP:
				break;
			case S_RECV_TURN_DOWN:
				break;
			case S_RECV_NEW_TAIL_REQUEST:
				break;
			default:
				//ErrorHandler("ERROR: OPCODE INVALID");
				break;
			}
		}

	}

	// 4-4. receive disconnection request from client
	puts("Client disconnected.");
	fflush(stdout);
	Sleep(100);
	::shutdown(hClient, SD_BOTH);
	::closesocket(hClient);
	Sleep(1000);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsa = { 0 };
	if (::WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		ErrorHandler("Winsock Initialisation Failed.");

	SOCKET hSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandler("Listening Socket Creating Failed.");

	// Port binding
	SOCKADDR_IN	svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (::bind(hSocket,
		(SOCKADDR*)&svraddr, sizeof(svraddr)) == SOCKET_ERROR)
		ErrorHandler("Failed to Bind IP Address and Port Number to Socket.");

	// Listen
	if (::listen(hSocket, SOMAXCONN) == SOCKET_ERROR)
		ErrorHandler("Failed to Change State to Listen.");
	puts("Game Server on Service.");

	// Accept client connection and create new communication socket
	SOCKADDR_IN clientaddr = { 0 };
	int nAddrLen = sizeof(clientaddr);
	SOCKET hClient;
	DWORD dwThreadID = 0;
	HANDLE hThread;

	while ((hClient = ::accept(hSocket, (SOCKADDR*)&clientaddr, &nAddrLen)) != INVALID_SOCKET)
	{
		AcceptConnection(hClient);

		puts("New client has been connected.");
		fflush(stdout);

		// create thread once new client is accepted
		hThread = ::CreateThread(
			NULL, // inherit security authority
			0, // defualt stack size
			ThreadFunction, // your thread function 
			(LPVOID)hClient, // thread function parameter
			0, // default flag
			&dwThreadID); // thread ID storing address
		::CloseHandle(hThread);
	}
	


	// client disconnect server
	::closesocket(hClient);
	puts("Client Disconnected");

	// close listen socket
	::closesocket(hSocket);
	// discharge winsock
	::WSACleanup();
	return 0;
}
