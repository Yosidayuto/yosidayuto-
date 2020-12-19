//=============================================================================
//
// 歯磨きエフェクト処理 [clean.h]
// Author : 若山言稀
//
//=============================================================================
#ifndef _CLEAN_H_
#define _CLEAN_H_


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ANIMATION (10)
#define CLEAN_TEXTURE "data/TEXTURE/aa.png"		// テクスチャパス


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include"scene2d.h"



class CClean :public CScene2D
{
public:
	CClean();
	~CClean();

	static HRESULT Load(void);
	static void Unload(void);
	static CClean *Create(D3DXVECTOR3 size);

	HRESULT Init(D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャのポインタ
	int m_nCountAnime;								// カウンター
	int m_nPatternAnime;							// パターンNo
};

#endif
