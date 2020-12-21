#ifndef _MOUSE_POINTER_H_
#define _MOUSE_POINTER_H_


#define MOUSE_POINTER "data/TEXTURE/brush1.png"	// テクスチャパス

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2D.h"


//*****************************************************************************
// マウスポインタークラス
//*****************************************************************************
class CPointer : public CScene2d
{
public:
	typedef enum  //マウスポインター種類
	{
		POINTER_TYPE_SELECR = 0,
		POINTER_TYPE_GAME,
		POINTER_TYPE_MAX
	}POINTER_TYPE;

	CPointer(int nPriorit = 5);										// コンストラクタ
	~CPointer();									// デストラクタ
	static HRESULT Load(void);						// テクスチャ読み込み
	static void Unload(void);						// テクスチャ破棄

	static CPointer *Create(POINTER_TYPE Type);					// 作成処理

	HRESULT Init(POINTER_TYPE Type);								// 初期化処理
	void	Uninit(void);							// 終了処理
	void	Update(void);							// 更新処理
	void	Draw(void);								// 描画処理

private:


	static LPDIRECT3DTEXTURE9	m_pTexture[POINTER_TYPE_MAX];	// テクスチャのポインタ
	static char					*pTexture[POINTER_TYPE_MAX];	// テキスト名

	POINTER_TYPE				m_Type;							// タイプ
	D3DXVECTOR3					m_pos;							// 位置
	D3DXVECTOR3					m_size;							// サイズ

};



#endif // !_POLYGON_H_
