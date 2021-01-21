//=============================================================================
//
// サーバー処理 [tcp_listener.cpp]
// Author : 吉田 悠人
//
//=============================================================================
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "tcp_listener.h"
//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_ACCEPT_CONN 100		//接続受付最大数

//=============================================================================
// 生成処理
//=============================================================================
CTcpListener *CTcpListener::Create(int nPortNum)
{
	//メモリの動的確保
	CTcpListener*pTcpListener = new CTcpListener;
	if (pTcpListener->Init(nPortNum)==false)
	{
		//メモリの開放
		delete pTcpListener;
		pTcpListener = NULL;
	}
	return pTcpListener;
}
//=============================================================================
// コンストラクタ
//=============================================================================
CTcpListener::CTcpListener()
{
	m_serverSock = -1;		//接続受付用ソケットの初期化
}
//=============================================================================
// デストラクタ
//=============================================================================
CTcpListener::~CTcpListener()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
bool CTcpListener::Init(int nPortNum)
{
	struct sockaddr_in addr;
	// 接続受付用ソケットの生成 (socket)
	m_serverSock = socket(AF_INET, SOCK_STREAM, 0);
	//接続受付情報の設定
	addr.sin_family = AF_INET;					//IPv4
	addr.sin_port = htons(nPortNum);			//ポート番号
	addr.sin_addr.S_un.S_addr = INADDR_ANY;		//すべての接続を受け付ける

	if (m_serverSock == NULL)	//serverSockがNULLだったら
	{
		return false;
	}
	//ソケットにIPアドレスとポート番号を設定する
	bind(m_serverSock, (struct sockaddr*)&addr, sizeof(addr));

	//接続要求受付を開始する
	listen(m_serverSock, MAX_ACCEPT_CONN);

	return true;
}

//=============================================================================
//接続受付処理
//=============================================================================
CTcpClient *CTcpListener::Accept()
{
	if (m_serverSock < 0)
	{
		return NULL;
	}

	struct sockaddr_in client;
	int nAddrLength = sizeof(client);

	// 接続受付処理
	SOCKET sock = accept(m_serverSock, (struct sockaddr*)&client, &nAddrLength);
	CTcpClient *pTcpClient = CTcpClient::Create(sock);
	return pTcpClient;
}

//=============================================================================
//破棄処理
//=============================================================================
void CTcpListener::Release()
{
	// 切断処理
	Close();
	// インスタンス削除
	delete this;
}

//=============================================================================
//クローズ処理
//=============================================================================
void CTcpListener::Close()
{
	if (m_serverSock < 0)
	{
		return;
	}
	//待ち受けソケットをクローズ
	closesocket(m_serverSock);

}