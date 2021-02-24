//==========================================
// チーム制作 tcp_client.cpp
// Author:中川涼
//==========================================
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//==================================================
// インクルードファイル
//==================================================
#include "tcp_client.h"
#include <stdio.h>

//==================================================
// コンストラクタ
//==================================================
CTcpClient::CTcpClient()
{
	m_sock = -1;
	m_bRecv = false;
}

//==================================================
// デストラクタ
//==================================================
CTcpClient::~CTcpClient()
{
}

//==================================================
// インスタンス生成
//==================================================
CTcpClient * CTcpClient::Create(const char * pHostName, int nPartNum)
{
	CTcpClient *pTcpClient = new CTcpClient;

	//初期化
	if (pTcpClient->Init(pHostName, nPartNum) == false)
	{
		//falseが帰ってきたら開放する
		delete pTcpClient;
		pTcpClient = NULL;

	}

	return pTcpClient;
}

//=============================================================================
// CTcpClient生成 (acceptによる接続)
//=============================================================================
CTcpClient* CTcpClient::CreateServer(SOCKET sock)
{
	// TCP送受信クラスのインスタンス生成
	CTcpClient *pTcpClient = new CTcpClient;

	//初期化
	if (pTcpClient->InitServer(sock) == false)
	{
		//falseが帰ってきたら開放する
		delete pTcpClient;
		pTcpClient = NULL;
	}

	return pTcpClient;
}

//==================================================
// 開放
//==================================================
void CTcpClient::Relese(void)
{
	Close(); //終了

	delete this; //このポインタを開放
}

//==================================================
// 初期化
//==================================================
bool CTcpClient::Init(const char * pHostName, int nPortNum)
{
	//接続用ソケットを作成
	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock == INVALID_SOCKET)
	{
		printf("socket:%d\n", WSAGetLastError());
		return false;
	}

	//接続受付情報の設定
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPortNum);
	addr.sin_addr.S_un.S_addr = inet_addr(pHostName);

	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		//失敗
		printf("connect:%d\n", WSAGetLastError());

		m_bRecv = false;

		return false;
	}

	return true;
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CTcpClient::InitServer(SOCKET sock)
{
	m_sock = sock;
	return true;
}

//==================================================
// 送信
//==================================================
int CTcpClient::Send(char * pSendData, int nSendDateSize)
{
	if (m_sock < 0)
	{
		return 0;
	}

	//送信
	int nSendSize = send(m_sock, pSendData, nSendDateSize, 0);

	return nSendSize;
}

//==================================================
// 受信
//==================================================
int CTcpClient::Recv(char * pRecvBuf, int nRecvBufSize)
{
	if (m_sock < 0)
	{
		return 0;
	}

	//受信
	int nRecvSize = recv(m_sock, pRecvBuf, nRecvBufSize, 0);

	if (nRecvSize <= 0)
	{
		//切断
		Close();
	}
	return nRecvSize;
}

//==================================================
// 終了
//==================================================
void CTcpClient::Close()
{
	if (m_sock < 0)
	{
		return;
	}
	//ソケット接続をクローズ
	closesocket(m_sock);
	m_sock = -1;
}
