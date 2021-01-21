//=============================================================================
//
//	スタートボタン[start button.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _START_BUTTON_H_
#define _START_BUTTON_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "button p.h"

//=============================================================================
//前方宣言
//=============================================================================
class CNumber;

//=============================================================================
// クラス定義
//=============================================================================
class CStartButton :public CButtonp
{
public:

	CStartButton(int nPriorit = 0);			//コンストラクタ
	~CStartButton();						//デストラクタ
	static HRESULT			Load(void);
	static void				Unload(void);
	static CStartButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	HRESULT			Init(void);		//初期化処理
	void			Uninit(void);	//終了処理
	void			Update(void);	//更新処理
	void			Draw(void);		//描画処理
private:
	static TEXTURE_DATA	m_TextureData;	//テクスチャデータ
	CNumber*			m_pNumber;		//ナンバー

};
#endif
