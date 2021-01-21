//=============================================================================
//
//	ボタン（仮）[button.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _BUTTONP_H_
#define _BUTTONP_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

typedef enum  //ボタンテクスチャ種類
{
	BUTTON_NORMAL =0,
	BUTTON_PUSH,
	BUTTON_MAX
}BUTTON_STATE;

//=============================================================================
// クラス定義
//=============================================================================
class CButtonp :public CScene2d
{
public:

	CButtonp(int nPriorit = 0);			//コンストラクタ
	~CButtonp();						//デストラクタ
	static HRESULT	Load(void);
	static void		Unload(void);

	HRESULT		Init(void);				//初期化処理
	void		Uninit(void);			//終了処理
	void		Update(void);			//更新処理
	void		Draw(void);				//描画処理
	bool		Hit(void);				//当たり判定

private:
	static TEXTURE_DATA	m_TextureData[BUTTON_MAX];	//テクスチャデータ
	CScene2d*			m_pScene2d;					//オブジェクトポインタ
};
#endif
