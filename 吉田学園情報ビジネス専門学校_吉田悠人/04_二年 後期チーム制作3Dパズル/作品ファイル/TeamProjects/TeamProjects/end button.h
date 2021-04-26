//=============================================================================
//
//	終了ボタン[end button.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _END_BUTTONP_H_
#define _END_BUTTONP_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "button.h"

//=============================================================================
// クラス定義
//=============================================================================
class CEndButton :public CButton
{
public:

	CEndButton();		// コンストラクタ
	~CEndButton();		// デストラクタ
	static CEndButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	HRESULT		Init(void);		// 初期化処理
	void		Uninit(void);	// 終了処理
	void		Update(void);	// 更新処理
	void		Draw(void);		// 描画処理
	void		Push(void);		// プッシュ判定処理

private:
	const int m_nTexture = 1;			// テクスチャ番号
};
#endif
