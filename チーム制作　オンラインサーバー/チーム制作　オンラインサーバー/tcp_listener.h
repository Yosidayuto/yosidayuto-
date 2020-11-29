//--------------------------------------------------
//サーバー制作クラス化
//吉田悠人
//--------------------------------------------------
#pragma once
#include <winsock2.h>
#include "tcp_client.h"
#include "main.h"
//---------------------------------------------------
//	前方宣言
//---------------------------------------------------
class CTcpClient;
//---------------------------------------------------
//	TCP接続受付クラス
//---------------------------------------------------
class CTcpListener
{
public:
	CTcpListener();					//コンストラクタ
	~CTcpListener();				//デストラクタ

	static CTcpListener * Create(int nPortNum);	//CTcpListener生成
	bool Init(int nPortNum);				//初期化処理
	CTcpClient * Accept(void);				//接続受付処理
	void Release(void);						//破棄処理
	void Close(void);						//クローズ処理
private:
	SOCKET m_serverSock;		// 接続受付用ソケット
	

};