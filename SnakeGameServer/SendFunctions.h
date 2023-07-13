#pragma once
void ErrorHandler(const char* pszMessage);
void SendPing(SOCKET hClient);
void AcceptConnection(SOCKET hClient);
void TerminateConnection(SOCKET hClient);
void ShowMode(SOCKET hClient, int flag);
void BackToMain(SOCKET hClient);
void GameStart(SOCKET hClient);