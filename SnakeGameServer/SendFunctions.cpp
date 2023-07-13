#include "stdafx.h"
#include "RecvFunctions.h"
#include "SendFunctions.h"

void ErrorHandler(const char* pszMessage)
{
	printf("ERROR: %s\n", pszMessage);
	::WSACleanup();
	exit(1);
}

void SendPing(SOCKET hClient)
{
	PACKET op;
	op.opcode = S_SEND_PING;
	send(hClient, (const char*)&op, sizeof(op), 0);
}

void AcceptConnection(SOCKET hClient)
{
	PACKET op;
	op.opcode = S_SEND_ACCEPT_CONNECTION;
	op.data = MENU_DOMAIN;
	send(hClient, (const char*)&op, sizeof(op), 0);
}

void TerminateConnection(SOCKET hClient)
{
	PACKET op;
	op.opcode = S_SEND_TERMINATE_CONNECTION;
	send(hClient, (const char*)&op, sizeof(op), 0);
}

void ShowMode(SOCKET hClient, int flag) // flag
{
	PACKET op;
	if (flag == 0) // game domain
	{
		op.opcode = S_SEND_SHOW_GAME_MODE;
	}
	else if (flag == 1) // score domain
	{
		op.opcode = S_SEND_SHOW_SCORE_MODE;
	}
	op.data = NORMAL;
	op.data += LARGE;
	send(hClient, (const char*)&op, sizeof(op), 0);
}

void BackToMain(SOCKET hClient)
{
	PACKET op;
	op.opcode = S_SEND_TERMINATE_CONNECTION;
	send(hClient, (const char*)&op, sizeof(op), 0);
}

void GameStart(SOCKET hClient)
{

}



