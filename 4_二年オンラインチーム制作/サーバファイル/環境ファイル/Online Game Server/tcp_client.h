#pragma once
#include<stdio.h>
#include<WinSock2.h>
#include <Ws2tcpip.h>

class CTcpClient
{
public:
	CTcpClient();
	~CTcpClient();
	static CTcpClient* Create(SOCKET sock);
	static CTcpClient* Create(const char*pHostName, int nPortNum);

	void Release(void);

	bool Init(const char *pHostName, int nPortNum);
	bool Init(SOCKET sock);
	int Send(char *pSendData, int nSendDataSize);
	int Recv(char* pRecvBuf, int nRecvBufsize);
	void Close();
private:
	SOCKET      m_sock;
};