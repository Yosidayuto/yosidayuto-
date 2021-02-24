
//=============================================================================
//	
//	テクスチャ[texture.h]
//	テキスト画像やUIアイコンなどの表示
//	Author:吉田　悠人
//
//=============================================================================
#ifndef  _TEXTURE_H
#define  _TEXTURE_H
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
//=============================================================================
// 前方宣言
//=============================================================================
typedef struct
{
	LPDIRECT3DTEXTURE9	m_Texture;	// テクスチャへのポインタ
	char*				m_cFileName;// ファイルの名前
} TEXTURE_ICON;
//=============================================================================
// クラス定義
//=============================================================================
class CTexture
{
public:
	CTexture();				// コンストラクタ
	~CTexture();			// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void	Uninit(void);	// 終了処理
	void	Update(void);	// 更新処理
	void	Draw(void);		// 描画処理

	void	SetPos(D3DXVECTOR3 pos);	// 位置セッター
	void	SetSize(D3DXVECTOR3 size);	// サイズセッター

	D3DXVECTOR3	GetPos(void);			// 位置ゲッター
	D3DXVECTOR3 GetSize(void);			// サイズゲッター
	
	void	BindTexture(LPDIRECT3DTEXTURE9 pTexture);	// テクスチャの読み込み処理
	void	TextureAnim(D3DXVECTOR2 *Texture);			// テクスチャアニメーション処理
private:
	LPDIRECT3DTEXTURE9			m_Texture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;	// 頂点バッファへのポインタ
	D3DXVECTOR3					m_pos;		// 位置
	D3DXVECTOR3					m_size;		// サイズ

};
#endif