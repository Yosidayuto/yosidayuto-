//=============================================================================
//
// ゲーム処理 [game.h]
// Author : 俵谷 健太郎 吉田悠人
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;
class CCommunication;
class CUi;
class CDieScreen;
//*****************************************************************************
// ゲームクラス
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame();									// コンストラクタ
	~CGame();									// デストラクタ
	typedef enum	//勝負の状態
	{
		MODE_CONTINUE = 0,						// 継続
		MODE_SETTLED,							// 決着
		MODE_MAX
	}MODE;
	typedef enum	//通信の状態
	{
		COMMUNICATTION_MODE_GAME = 0,			// 勝敗が決まったかの処理
		COMMUNICATTION_MODE_TURN,				// ターン処理
		COMMUNICATTION_MODE_WINNER,				// 勝利時の処理
		COMMUNICATTION_MODE_MAX
	}COMMUNICATTION_MODE;

	COMMUNICATTION_MODE CommuMode;				// 現在の処理のモード
	MODE				Mode;					// 勝敗の変数


	static CGame *Create(D3DXVECTOR3 size);		// 作成処理
	HRESULT Init(D3DXVECTOR3 size);				// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理
	static void Load(void);						// 情報読み込み
	static bool GetPlayerDie(int nPlayer);		// プレイヤーが死んでいるかの確認関数
private:
	int				m_nTouch;					// タッチする歯
	bool			m_bSelect;					// 歯の選択
	static CCommunication	*pCommunication;	// コミュニケーションクラス
	static CPolygon *pPolgon;					// 牙のポインタ
	static bool		m_bLoad;					// ロード処理をしているか
	CUi				*m_pUi;						// UIクラス
	CDieScreen		*m_pDieScreen;				// 死亡画面クラス
	static bool		m_bPlayerDie[4];			// プレイヤー4人の状態
};





#endif // !_GAME_H_


