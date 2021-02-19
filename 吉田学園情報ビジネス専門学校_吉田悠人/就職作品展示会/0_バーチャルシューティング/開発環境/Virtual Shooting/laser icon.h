//=============================================================================
//
//	レーザーアイコン[laser icon.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _LASER_ICON_H_
#define _LASER_ICON_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "texture.h"

//=============================================================================
// クラス定義
//=============================================================================
class CLaserIcon :public CTexture
{
public:
	CLaserIcon();	//コンストラクタ
	~CLaserIcon();	//デストラクタ

	static HRESULT		Load(void);
	static void			Unload(void);
	static CLaserIcon*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT			Init(void);		// 初期化処理
	void			Uninit(void);	// 終了処理
	void			Update(void);	// 更新処理
	void			Draw(void);		// 描画処理
private:
	static TEXTURE_ICON	m_TextureData;	// テクスチャデータ
};
#endif
