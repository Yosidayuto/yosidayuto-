//=============================================================================
//
//	ボタン（仮）[button.h]
//	Author:吉田　悠人
//
//=============================================================================
#ifndef _LIFE_UI_H_
#define _LIFE_UI_H_
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "main.h"
#include "scene2d.h"
//=============================================================================
//前方宣言
//=============================================================================
class CUi;
//------------------------------------
//クラス処理
//------------------------------------
class CLifeUi :public CScene2d
{
public:
	CLifeUi(int nPriorit = 3);		//コンストラクタ
	~CLifeUi();						//デストラクタ

	static HRESULT	Load(void);					//テクスチャ読み込み
	static void		Unload(void);				//テクスチャの破棄
	static CLifeUi*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//生成処理

	HRESULT			Init(void);		//初期化処理
	void			Uninit(void);	//終了処理
	void			Update(void);	//更新処理
	void			Draw(void);		//描画処理
private:
	static TEXTURE_DATA	m_TextureData;	//テクスチャデータ
};



#endif
