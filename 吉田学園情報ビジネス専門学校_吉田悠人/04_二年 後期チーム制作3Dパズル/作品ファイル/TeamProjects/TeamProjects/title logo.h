//=============================================================================
//
//	タイトルロゴ[title logo.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "inputmouse.h"
#include "ui.h"

//=============================================================================
// クラス定義
//=============================================================================
class CTitleLoge :public CUi
{
public:

	CTitleLoge(int nPriority = PRIORITY_UI_0);	// コンストラクタ
	~CTitleLoge();								// デストラクタ
	static CTitleLoge*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT		 Init(void);			// 初期化処理
	void		 Update(void);			// 更新処理

private:
	const int m_nTexture = 41;			// テクスチャ番号

};
#endif
