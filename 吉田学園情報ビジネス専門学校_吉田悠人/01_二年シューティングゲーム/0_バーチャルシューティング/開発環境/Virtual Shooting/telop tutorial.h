//=============================================================================
//
//	チュートリアルテロップ[telop tutorial.h]
//	Author:吉田　悠人
//
//=============================================================================
#ifndef  _TELOP_TUTORIAL_H
#define  _TELOP_TUTORIAL_H
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
//=============================================================================
// 前方宣言
//=============================================================================
//=============================================================================
// クラス定義
//=============================================================================
class CTelopTutorial :public CScene2d
{
public:
	CTelopTutorial(int nPriorit = PRIORITY_UI_1);	// コンストラクタ
	~CTelopTutorial();	// デストラクタ
	
	static HRESULT		Load(void);
	static void			Unload(void);
	static CTelopTutorial*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(void);		// 初期化処理
	void	Uninit(void);	// 終了処理
	void	Update(void);	// 更新処理
	void	Draw(void);		// 描画処理

	void	TelopMove(void);// テロップを回す処理
private:
	int					m_nPatternAnim;	//アニメーションパターンNo
	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ

};
#endif