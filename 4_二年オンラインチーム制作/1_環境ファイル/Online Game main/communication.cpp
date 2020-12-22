//==================================================================
//
// クライアント通信 communication.cpp
// Author:中川涼・吉田悠人
//
//==================================================================

//==================================================================
// インクルードファイル
//==================================================================
#include "communication.h"
#include "game.h"
//==================================================================
// 静的メンバ変数宣言
//==================================================================
int CCommunication::m_nPlayer = 0;
int CCommunication::m_nPlayerTurn = 0;
bool CCommunication::m_bPlayer = false;
bool CCommunication::m_bHit = false;
int CCommunication::m_nMode = CGame::MODE_CONTINUE;
char CCommunication::m_aRecvBuff[BUFFER_NUM] = {};
bool CCommunication::m_abTooth[MAX_TOOTH] = {};
CTcpClient *CCommunication::m_pClient = NULL;
bool CCommunication::m_bRecv = false;
int CCommunication::nTooth = 0;
int CCommunication::nDie = 0;
//==================================================================
// コンストラクタ
//==================================================================
CCommunication::CCommunication()
{
	//変数クリア
	m_nLoss = 0;
	nDie = 0;
	nTooth = 0;
	m_bRecv = false;
	m_pClient = NULL;
	m_nMode = CGame::MODE_CONTINUE;
	m_bHit = false;
	m_bPlayer = false;
	m_nPlayer = 0;
	m_nPlayerTurn = 0;
	memset(m_abTooth, 0, sizeof(m_abTooth));
}

//==================================================================
// デストラクタ
//==================================================================
CCommunication::~CCommunication()
{
}

//==================================================================
// 生成
//==================================================================
CCommunication * CCommunication::Create(void)
{
	CCommunication *pCommunication = new CCommunication;

	//初期化
	if (FAILED(pCommunication->Init(IP_ADDR, SERVER_PORT_NUM)))
	{
		//falseが帰ってきたら開放する
		delete pCommunication;
		pCommunication = NULL;

	}

	m_bPlayer = true;                         //プレイヤーを使用している状態にする
	memset(&m_abTooth, 1, sizeof(m_abTooth)); //歯を使用している状態にする

	std::thread thWorker(RecvPlayer);
	thWorker.detach();

	return pCommunication;
}

//==================================================================
// 初期化
//==================================================================
HRESULT CCommunication::Init(const char * pHostName, int nPartNum)
{
	//TCPクライアント生成
	m_pClient=CTcpClient::Create(pHostName, nPartNum);

	return S_OK;
}

//==================================================================
// 終了
//==================================================================
void CCommunication::Uninit(void)
{
	CTcpClient *pClient = new CTcpClient;
	pClient->Relese();
}

//==================================================================
// プレイヤーが〇番を引いたか
//==================================================================
void CCommunication::PicPlayer(int nNumTooth)
{

	char aSendBuffer[BUFFER_NUM];
	int nTooth= nNumTooth;
	nTooth = htonl(nTooth);

	//バッファに選んだ歯の番号を入れる
	memcpy(&aSendBuffer[0], &nTooth, sizeof(int));
	if (nNumTooth != -1)
	{
		//選ばれた歯を不使用状態にする
		m_abTooth[nNumTooth] = false;
	}
	//送信
	int SendBuff = m_pClient->Send(aSendBuffer, sizeof(aSendBuffer));
}

//==================================================================
// プレイヤー情報取得
//==================================================================
void CCommunication::RecvPlayer(void)
{
	memset(m_aRecvBuff, 0, sizeof(m_aRecvBuff)); //バッファ0クリア

	 //受信
	int nRecvSize = m_pClient->Recv(m_aRecvBuff, sizeof(m_aRecvBuff));
	if (nRecvSize < 0)
	{
		return;
	}

	int nIndexRecv = 0;                          //インデックスを初期化

	//モード
	m_nMode = *(int*)&m_aRecvBuff[nIndexRecv];
	nIndexRecv += sizeof(int);					//エンディアン変更(重要)
	m_nMode= ntohl(m_nMode);
	
	//プレイヤーがいきているか
	int nData = *(int*)&m_aRecvBuff[nIndexRecv];
	nIndexRecv += sizeof(int);                   //インデックスを進める
	nData = ntohl(nData);                        //エンディアン変更(重要)
	if (nData != 0)                              //プレイヤーの使用状態
	{
		m_bPlayer = false;
	}
	else
	{
		m_bPlayer = true;
	}

	//エンディアン変換
	m_nPlayer = *(int*)&m_aRecvBuff[nIndexRecv]; //プレイヤーの番号
	m_nPlayer = ntohl(m_nPlayer);                //エンディアン変更(重要)
	nIndexRecv += sizeof(int);                   //インデックスを進める

		 
	nTooth = *(int*)&m_aRecvBuff[nIndexRecv];//前のプレイヤーが選んだ番号
	nIndexRecv += sizeof(int);                   //インデックスを進める
	nTooth = ntohl(nTooth);                      //エンディアン変更(重要)
	if (nTooth != -1)
	{
		m_abTooth[nTooth] = false;                   //歯を不使用状態にする
	}

	nDie= *(int*)&m_aRecvBuff[nIndexRecv];	//プレイヤーがやられているか
	nIndexRecv += sizeof(int);               //インデックスを進める
	nDie = ntohl(nDie);                      //エンディアン変更(重要)


	m_bRecv = true;
}

//==================================================================
// プレイヤーの順番をずらす
//==================================================================
bool CCommunication::DisplacePlayer(void)
{
	//自分のターン
	if (m_nMode != CGame::MODE_SETTLED)
	{
		if (m_nPlayer == 0)
		{
			if (m_bPlayer)
			{
				//プレイヤーが生きていた場合、歯を選ぶ
				return true;
			}
		}
	}
	return false;
}

//==================================================================
// 勝者判定
//==================================================================
int CCommunication::Winner(void)
{
	int nNum = PLAYERSTATE_NONE;

	if (m_bPlayer)
	{
		//生き残ったプレイヤー
		nNum = PLAYERSTATE_ALIVE;
	}
	else
	{
		//死んだプレイヤー
		nNum = PLAYERSTATE_DEAD;
	}

	return nNum;
}

//==================================================================
// モード設定
//==================================================================
void CCommunication::SetMode(int nMode)
{
	m_nMode = nMode;
}
