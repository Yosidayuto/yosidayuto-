//=====================================================================
//
// 通信 communication.h
// Author:中川涼
//
//=====================================================================

#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

//=====================================================================
// インクルードファイル
//=====================================================================
#include "tcp_client.h"
#include "main.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define MAX_TOOTH       (20)                //歯の最大数
#define MAX_LOSS        (3)                 //はずれの最大数
#define BUFFER_NUM      (128)               //バッファ最大数
#define IP_ADDR			"127.0.0.1"		//接続先のIPアドレス
#define SERVER_PORT_NUM (12345)             //接続先サーバーのポート
#define MAX_PLAYER      (3)                 //プレイヤー最大数

//=====================================================================
// 通信クラス
//=====================================================================
class CCommunication
{
public:

	typedef enum	//歯の状態
	{
		TEETH_NONE = 0,	//選択済み
		TEETH_PER,		//当たり
		TEETH_OFF,		//外れ
		TEETH_MAX
	}TEETH;

	typedef enum //プレイヤーの状態
	{
		PLAYERSTATE_NONE = 0,
		PLAYERSTATE_ALIVE,
		PLAYERSTATE_DEAD,
		PLAYERSTATE_MAX
	}PLAYERSTATE;

	CCommunication();
	~CCommunication();

	//メンバ関数
	static CCommunication *Create(void);                        //生成
	HRESULT Init(const char *pHostName, int nPartNum);          //初期化
	void Uninit(void);                                          //終了

	void PicPlayer(int nNumTooth);                              //プレイヤーが〇番を引いたか
	static void RecvPlayer(void);                               //プレイヤー情報取得
	bool DisplacePlayer(void);                                  //プレイヤーの順番をずらす
	int Winner(void);                                           //勝者判定

																//ゲット、セット
	static int GetPlayerTurn(void) { return m_nPlayerTurn; }     //プレイヤーターン取得
	static int GetnPlayer(void) { return m_nPlayer; }            //プレイヤー番号取得
	static bool GetbHit(void) { return m_bHit; }                 //当たりかはずれか取得
	static int GetMode(void) { return m_nMode; }                 //現在のモード取得
	static void SetMode(int nMode);                              //モード設定
	static bool GetbPlayer(void) { return m_bPlayer; }           //プレイヤーの使用状態取得
	static bool GetabTooth(int nNum) { return m_abTooth[nNum]; } //歯の情報取得
	static bool GetbRecv(void) { return m_bRecv; }
	static void SetbRecv(void) { m_bRecv = false; }				 //受信受け取り状況
	static int  GetnTooth(void) { return nTooth; }
	static int  GetnDie(void){ return nDie-1; }					//やられたプレイヤーの状態取得
private:
	//メンバ変数
	int  m_nLoss;                                               //はずれ回数
	static bool m_bHit;                                         //当たりかどうか
	static bool  m_abTooth[MAX_TOOTH];                          //歯の配列
	static int  m_nPlayerTurn;                                  //プレイヤーのターン
	static int  m_nPlayer;                                      //何番目のプレイヤーか
	static bool m_bPlayer;                                      //使用されているか
	static int  m_nMode;                                        //現在のモード
	static char m_aRecvBuff[BUFFER_NUM];                        //受信用バッファ
	static CTcpClient *m_pClient;
	static bool m_bRecv;										//受信が終わったか
	static int  nTooth;											//前に選んだ歯の情報
	static int  nDie;											//やられたプレイヤー
};

#endif // !_COMMUNICATION_H_

