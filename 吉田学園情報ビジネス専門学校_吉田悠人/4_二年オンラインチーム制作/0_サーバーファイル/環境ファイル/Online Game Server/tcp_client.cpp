//=============================================================================
//
// 接続処理 [tcp_client.cpp]
// Author : 吉田 悠人
//
//=============================================================================

#include"tcp_client.h"
//=============================================================================
//コンストラクタ
//=============================================================================
CTcpClient::CTcpClient()
{
	m_sock = -1;
}
//=============================================================================
//デストラクタ
//=============================================================================
CTcpClient::~CTcpClient()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CTcpClient *CTcpClient::Create(const char*pHostName, int nPortNum)
{
	CTcpClient*pTcpClient = new CTcpClient;
	if (pTcpClient->Init(pHostName, nPortNum) == false)
	{
		delete pTcpClient;
		pTcpClient = NULL;
	}
	return pTcpClient;
}

//=============================================================================
// CTcpClient生成 (connectによる接続)
//=============================================================================
CTcpClient *CTcpClient::Create(SOCKET sock)
{
	CTcpClient*pTcpClient=new CTcpClient;
	if (pTcpClient->Init(sock) == false)
	{
		delete pTcpClient;
		pTcpClient = NULL;
	}
	return pTcpClient;
}

//=============================================================================
// 開放処理
//=============================================================================
void CTcpClient::Release(void)
{
	Close();
	delete this;
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CTcpClient::Init(SOCKET sock)
{
	//接続用ソケットの生成
	m_sock = sock;
	return true;
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CTcpClient::Init(const char * pHostName, int nPortNum)
 {
	 //接続用ソケットの生成
	 m_sock = socket(AF_INET, SOCK_STREAM, 0);
	 if (m_sock == INVALID_SOCKET)
	 {
		 return false;
	 }
	 //接続受付情報の設定
	 struct sockaddr_in addr;

	 addr.sin_family = AF_INET;							//IPv4
	 addr.sin_port = htons(nPortNum);					//ポート番号
	 inet_pton(addr.sin_family, (PCSTR)(nPortNum),&addr.sin_addr.S_un.S_addr);//すべての接続を受け付ける
														//接続
	 if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	 {
		 return false;
	 }
	 return true;
 }


//=============================================================================
// 送信処理
//=============================================================================
int CTcpClient::Send(char * pSendData, int nSendDataSize)
{
	if (m_sock < 0)
	{
		return 0;
	}
	int nSendSize = send(m_sock, pSendData, nSendDataSize, 0);
	return nSendSize;
}

//=============================================================================
// 受信処理
//=============================================================================
int CTcpClient::Recv(char * pRecvBuf, int nRecvBufsize)
{
	int nRecvSize = recv(m_sock, pRecvBuf, nRecvBufsize, 0);
	if (nRecvSize <= 0)
	{
		Close();
		//切断
		return 0;
	
	}
	return nRecvSize;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTcpClient::Close()
{
	if (m_sock < 0)
	{
		return;
	}
	closesocket(m_sock);
	m_sock = -1;
}

