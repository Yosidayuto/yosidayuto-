//=============================================================================
//
// セレクト処理 [select.h]
// Author : 吉田 悠人
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"
#include "scene.h"
#include "player.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_NUMBER 2

//=============================================================================
//前方宣言
//=============================================================================
class CSelectBg;
class CButton;
class CScore;
class CUiCount;
class CTelop;
class CStartButton;
class CLifeButton;
class CPlayer;

//------------------------------------
//クラス処理
//------------------------------------
class CSelect 
{
public:
	CSelect();	//コンストラクタ
	~CSelect();	//デストラクタ

	typedef enum
	{
		NUMBER_TYPE_LIEF = 0,
		NUMBER_TYPE_SPEED,
		NUMBER_TYPE_MAX
	}NUMBER_TYPE;

	HRESULT			Init(void);		//初期化処理
	void			Uninit(void);	//終了処理
	void			Update(void);	//更新処理
	void			Draw(void);		//描画処理

	static CUiCount*	GetNumber(NUMBER_TYPE NumberType);	// ナンバーゲット
	static CScore*		GetScore(void);						// スコアゲット
	static CScore*		GetMinusScore(void);				// 消費スコアゲット
	static CTelop*		GetTelop(void);						// テロップゲット
private:
	CSelectBg*			m_pSelectBg;				// 背景クラス
	static CScore*		m_pScore;					// スコアクラス
	static CScore*		m_pMinusScore;				// 消費スコアクラス
	static CUiCount*	Number[NUMBER_TYPE_MAX];	// カウントクラス
	static CTelop*		m_pTelop;					// テロップクラス
};
#endif