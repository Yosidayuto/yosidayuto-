#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "player.h"
#include "scene.h"

//----------------------------------------------
//マクロ定義
//----------------------------------------------
#define GAME_WIDTH 780

//------------------------------------
//前置処理
//------------------------------------
class CRenderer;
class CInihKeyboard;
class CInihMouse;
class CSound;
class CPause;
class CTitle;
class CScore;
class CScene;
class CFade;
class CGame;
class CSelect;
class CPlayer;
class CTutorial;
//------------------------------------
//クラス処理
//------------------------------------
class CManager
{
public:
	CManager();		//コンストラクタ
	~CManager();	//デストラクタ

	typedef enum	//ゲームモード
	{
		GAME_MODE_NONE = 0,
		GAME_MODE_FADE,			//フェイド
		GAME_MODE_TITLE,		//タイトル
		GAME_MODE_TUTORIAL,		//チュートリアル
		GAME_MODE_SELECT,		//セレクト
		GAME_MODE_STAGE,		//ステージ
		GAME_MODE_CLEAR,		//クリア
		GAME_MODE_MAX,
	}GAME_MODE;


	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);	//初期化処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理
	void Draw(void);					//描画処理
	static void SetMode(GAME_MODE mode);		//ゲームモードセット

	static CRenderer		*GetRenderer(void);		//レンダリング取得
	static CInihKeyboard	*GetKeyboard(void);		//キーボード取得
	static CInihMouse		*GetMouse(void);		//マウス取得
	static CSound			*GetSound(void);		//サウンド取得
	static CFade			*GetFade(void);			//フェードアウト取得

	static int				GetScore(void);		//スコア取得
	static void				SetScore(int nScore) { m_nScore = nScore; };

	static int				GetPlayer(int nPlayerData);		//プレイヤー取得
	static void				SetPlayer(int nLife,int nSpeed);
	static CPlayer::WEAPON_MODE GetWeapon(int nWeaponData) {return m_Player.m_nWeapon[nWeaponData];};
	static void				SetWeapon(CPlayer::WEAPON_MODE nWeaponData1, CPlayer::WEAPON_MODE nWeaponData2) ;
	//static int				GetStage(void) { return m_StageType; };
private:
	static CRenderer		*m_pRenderer;			//レンダリングクラス
	static CInihKeyboard	*m_pInput;				//インプット（キーボード）クラス
	static CInihMouse		*m_pInihMouse;			//インプット（マウス）クラス
	static CSound			*m_pSound;				//サウンドクラス
	static CScene			*m_pScene;				//シーンクラス
	static CTitle			*m_pTitle;				//タイトルクラス
	static CFade			*m_pFade;				//フェイドアウトクラス
	static CTutorial		*m_pTutorial;			//タイトルクラス

	typedef struct
	{
		int				m_nLife;
		int				m_nSpeed;
		CPlayer::WEAPON_MODE m_nWeapon[MAX_WEAPON];
	}PLAYER_DATA;
	 
	static PLAYER_DATA		m_Player;				//プレイヤーデータ
	static int				m_nScore;				//スコア保存先
	static CGame			*m_pGame;				//ゲーム処理
	static CSelect			*m_pSelect;				//セレクト処理
	static GAME_MODE		m_Mode;					//ゲームモード
	
};



#endif