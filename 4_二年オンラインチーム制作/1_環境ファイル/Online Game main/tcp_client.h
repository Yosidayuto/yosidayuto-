//=====================================================================
//
// クライアント通信 tcp_client.h
// Author:中川涼
//
//=====================================================================

#ifndef _TCP_CLIENT_H
#define _TCP_CLIENT_H

//=====================================================================
// インクルードファイル
//=====================================================================
#include "main.h"

//=====================================================================
// TCPクライアントクラス
//=====================================================================
class CTcpClient
{
public:
	CTcpClient();
	~CTcpClient();

	//メンバ関数
	static CTcpClient *Create(const char *pHostName, int nPartNum);     //生成(クライアント)
	static CTcpClient *CreateServer(SOCKET sock);                       //生成(サーバー)
	void Relese(void);                                                  //開放
	bool Init(const char *pHostName, int nPortNum);                     //初期化(クライアント)
	bool InitServer(SOCKET sock);                                       //初期化(サーバー)
	int Send(char *pSendData, int nSendDateSize);                       //送信
	int Recv(char *pRecvBuf, int nRecvBufSize);                         //受信
	void Close();                                                       //終了

private:
	//メンバ変数
	SOCKET m_sock;                                                      //受信用
	bool m_bRecv;                                                       //受信フラグ
};

#endif // !_TCP_CLIENT_H