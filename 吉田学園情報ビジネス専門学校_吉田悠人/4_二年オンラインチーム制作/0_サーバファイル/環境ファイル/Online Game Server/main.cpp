//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 吉田 悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<thread>
#include<mutex>
#include<WinSock2.h>
#include"main.h"
#include"tcp_client.h"
#include"tcp_listener.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define SERVER_PORT_NUM 12345		//接続先サーバーの接続先ポート
#define MAX_PLAYER 4				//最大プレイヤー人数
//=============================================================================
//プロトタイプ宣言
//=============================================================================
//通信処理
void GameData(CTcpClient *pTcpClient[MAX_PLAYER]);
//歯の当たりはずれを決める
void RandomTeeth(void);					

//=============================================================================
//グローバル変数
//=============================================================================
PlayerData	g_aTeethData[MAX_PLAYER];
TEETH		g_Teeth[MAX_TEETH];
std::mutex	g_mtx;

//=============================================================================
//メイン関数
//=============================================================================
int main()
{
	//winsockの初期化
	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	if (nErr != 0)
	{
		//何らかの原因で初期化に失敗した
		printf("WSAStartup failed\n");
		return 1;
	}

	//CTcpListener生成
	CTcpListener *pTcpListener = CTcpListener::Create(SERVER_PORT_NUM);;

	while (1)
	{

		//接続待ち
		CTcpClient *pTcpClient[MAX_PLAYER] ;
		//グローバル変数の初期化
		memset(g_aTeethData, NULL, sizeof(g_aTeethData));

		for (int nCont = 0; nCont < MAX_PLAYER; nCont++)
		{
			pTcpClient[nCont] = pTcpListener->Accept();
			if (pTcpClient[nCont] == NULL)
			{
				continue;
			}

		}
		//歯の情報処理
		RandomTeeth();
		//スレッド生成
		std::thread th(GameData, pTcpClient);
		th.detach();

	}

	//CTcpListener破棄
	pTcpListener->Release();
	//winsockの終了処理
	WSACleanup();

	

	//WriteFile();
}

//=============================================================================
// ゲームデータ通信
//=============================================================================
void GameData(CTcpClient *pTcpClient[MAX_PLAYER])
{
	char	aSendBuf[128];		//送るデータ
	char	aRecvBuffer[128];	//送信された内容
	int		nIndexRecv;			//送信されたデータ量
	int		nIndeSehd;			//送るデータ量
	int		nTeeth;				//磨いた歯
	int		nDie = 0;			//死んだプレイヤー
	int		nNumberPlayer = MAX_PLAYER;

	for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
	{
		memset(aSendBuf, 0, sizeof(aSendBuf));				//バッファを0クリアする
		memset(aRecvBuffer, 0, sizeof(aRecvBuffer));		//バッファを0クリアする

		nIndeSehd = 0;
		int nData;
		//モード送信（決着がついたか０なら継続１なら決着）
		if (nNumberPlayer <= 0)
		{
			nData = 1;
			//収納
			memcpy(&aSendBuf[nIndeSehd], &nData, sizeof(int));
			nIndeSehd += sizeof(int);
		}
		else
		{
			nData = 0;
			//収納
			memcpy(&aSendBuf[nIndeSehd], &nData, sizeof(int));
			nIndeSehd += sizeof(int);
		}
		if (g_aTeethData[nPlayer].bPlayer != false)
		{
			g_aTeethData[nPlayer].bPlayer = false;
		}
		//プレイヤーが生きているか
		nData= (int)htonl(g_aTeethData[nPlayer].bPlayer);
		//プレイヤーの収納
		memcpy(&aSendBuf[nIndeSehd], &nData, sizeof(int));
		nIndeSehd += sizeof(int);
		
		//プレイヤーナンバー設定
		g_aTeethData[nPlayer].nPlayer = nPlayer;
		//エンディアン変更
		nData = (int)htonl(g_aTeethData[nPlayer].nPlayer);
		//ナンバーの収納
		memcpy(&aSendBuf[nIndeSehd], &nData, sizeof(int));
		nIndeSehd += sizeof(int);
		

		//送信（プレイヤー番号）
		pTcpClient[nPlayer]->Send(aSendBuf, sizeof(aSendBuf));		
	}
	while (1)
	{
		//プレイヤーからの情報受付
		for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
		{
			if (g_aTeethData[nPlayer].nPlayer == 0)
			{
				memset(aSendBuf, 0, sizeof(aSendBuf));				//バッファを0クリアする
				memset(aRecvBuffer, 0, sizeof(aRecvBuffer));		//バッファを0クリアする
				nIndexRecv = 0;
				//受信処理(ここでプレイヤーの当たりはずれの情報を受け取る)
				pTcpClient[nPlayer]->Recv(aRecvBuffer, sizeof(aRecvBuffer));
				//歯の情報
				nTeeth = *(int*)&aRecvBuffer[nIndexRecv];
				nTeeth=ntohl(nTeeth);

				if (g_Teeth[nTeeth] == TEETH_OFF)
				{
					g_aTeethData[nPlayer].bPlayer = true;
					nDie = nPlayer+1;
					nNumberPlayer--;
				}
				g_Teeth[nTeeth] = TEETH_NONE;
				break;
			}
		}
		//人数分送信ここで４人分
		for (int nCountPlayer = 0; nCountPlayer < MAX_PLAYER; nCountPlayer++)
		{
			nIndeSehd = 0;
			int nData = 0;
		
			//モード送信（決着がついたか０なら継続 ,１なら決着）
			if (nNumberPlayer <= 1)
			{
				nData = 1;
				//収納
				memcpy(&aSendBuf[nIndeSehd], &nData, sizeof(int));
				nIndeSehd += sizeof(int);
			}
			else
			{
				nData = 0;
				//収納
				memcpy(&aSendBuf[nIndeSehd], &nData, sizeof(int));
				nIndeSehd += sizeof(int);
			}


			//プレイヤーが生きているか
			nData = (int)htonl(g_aTeethData[nCountPlayer].bPlayer);
			//情報の収納
			memcpy(&aSendBuf[nIndeSehd], &nData, sizeof(int));
			nIndeSehd += sizeof(int);


			//プレイヤーの番号処理
			g_aTeethData[nCountPlayer].nPlayer = g_aTeethData[nCountPlayer].nPlayer - 1;
			if (g_aTeethData[nCountPlayer].nPlayer < 0)
			{
				g_aTeethData[nCountPlayer].nPlayer = MAX_PLAYER - 1;
			}
			//エンディアン変更
			nData = (int)htonl(g_aTeethData[nCountPlayer].nPlayer);
			//ナンバーの収納
			memcpy(&aSendBuf[nIndeSehd], &nData, sizeof(int));
			nIndeSehd += sizeof(int);


			//選択した歯の情報
			nData = (int)htonl(nTeeth);
			//ナンバーの収納
			memcpy(&aSendBuf[nIndeSehd], &nData, sizeof(int));
			nIndeSehd += sizeof(int);
			
			//死んだプレイヤーの情報
			nData = (int)htonl(nDie);
			//ナンバーの収納
			memcpy(&aSendBuf[nIndeSehd], &nData, sizeof(int));
			nIndeSehd += sizeof(int);


			//送信（生きてるか　プレイヤーの順番）
			pTcpClient[nCountPlayer]->Send(aSendBuf, sizeof(aSendBuf));
		}

	}
}

//=============================================================================
//歯の外れを決める
//=============================================================================
void RandomTeeth(void)
{
	int nCountOff = 0;
	//歯の情報設定
	for (int nTeeth = 0; nTeeth < MAX_TEETH; nTeeth++)
	{
		g_Teeth[nTeeth] = TEETH_PER;
	}
	for (int nTeeth = 0; nTeeth < MAX_TEETH; nTeeth++)
	{
		//ランダムで外れを３つ選ぶ
		int nSwapIndex = rand() % MAX_TEETH;
		if (nCountOff < 3)
		{
			if (g_Teeth[nSwapIndex] != TEETH_OFF)
			{
				g_Teeth[nSwapIndex] = TEETH_OFF;
				nCountOff++;
			}
		}
	}

}

//=============================================================================
//当たりはずれの判定
//=============================================================================
bool HitTeeth(int nTeeth)
{
	if (g_Teeth[nTeeth] == TEETH_OFF)		//外れの場合
	{
		//歯を選択済みにする
		g_Teeth[nTeeth] = TEETH_NONE;
		return true;
	}
	else		//当たりの場合
	{
		//歯を選択済みにする
		g_Teeth[nTeeth] = TEETH_NONE;
		return false;
	}
}


