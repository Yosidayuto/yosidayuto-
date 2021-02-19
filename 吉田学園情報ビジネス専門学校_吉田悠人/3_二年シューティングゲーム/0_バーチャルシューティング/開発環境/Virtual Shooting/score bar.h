//=============================================================================
//
//	スコア背景[score bar.h]
//	Author:吉田　悠人
//
//=============================================================================
#ifndef _SCORE_BAR_H_
#define _SCORE_BAR_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "texture.h"

//=============================================================================
// クラス定義
//=============================================================================
class CScoreBar :public CTexture
{
public:
	CScoreBar();	//コンストラクタ
	~CScoreBar();	//デストラクタ

	static HRESULT			Load(void);
	static void				Unload(void);
	static CScoreBar*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT			Init(void);		// 初期化処理
	void			Uninit(void);	// 終了処理
	void			Update(void);	// 更新処理
	void			Draw(void);		// 描画処理
private:
	static TEXTURE_ICON	m_TextureData;	// テクスチャデータ
};
#endif
