#include "stdafx.h"
#include "SendFunctions.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsa = { 0 };
	if (::WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		Send::ErrorHandler("Winsock Initialisation Failed.");

	SOCKET hSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		Send::ErrorHandler("Listening Socket Creating Failed.");

	// Port binding
	SOCKADDR_IN	svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (::bind(hSocket,
		(SOCKADDR*)&svraddr, sizeof(svraddr)) == SOCKET_ERROR)
		Send::ErrorHandler("Failed to Bind IP Address and Port Number to Socket.");

	// Listen
	if (::listen(hSocket, SOMAXCONN) == SOCKET_ERROR)
		Send::ErrorHandler("Failed to Change State to Listen.");
	puts("Game Server on Service.");

	// Accept client connection and create new communication socket
	SOCKADDR_IN clientaddr = { 0 };
	int nAddrLen = sizeof(clientaddr);

	SOCKET hClient = ::accept(hSocket, (SOCKADDR*)&clientaddr, &nAddrLen);
	if (hClient == INVALID_SOCKET)
		Send::ErrorHandler("Creating Client Communication Socket Failed.");
	puts("Client Connected.");

	Send::AcceptConnection(hClient);

	// Event loop to receive packet, process data and response to client
	PACKET packet;
	while (::recv(hClient, (char*)&packet, sizeof(PACKET), 0) > 0)
	{
		switch (packet.opcode)
		{
		

		default:
			Send::ErrorHandler("�� �� ���� ����� �����߽��ϴ�.");
			break;
		}
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
