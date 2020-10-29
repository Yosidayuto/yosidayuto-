#ifndef  _UI_H
#define  _UI_H
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "main.h"
#include "scene2d.h"
//------------------------------------
//マクロ定義
//------------------------------------
//------------------------------------
//クラス処理
//------------------------------------
class CUi
{
public:

	CUi();															//コンストラクタ
	~CUi();															//デストラクタ
	typedef enum
	{
		TEXTURE_TYPE_SCORE = 0,
		TEXTURE_TYPE_LIFE,
		TEXTURE_TYPE_BULLET,
		TEXTURE_TYPE_LASER,
		TEXTURE_TYPE_HOMING,
		TEXTURE_TYPE_MAX
	}CUI_TYPE;

	static HRESULT	Load(void);														//テクスチャ読み込み
	static void		Unload(void);													//テクスチャの破棄
	static CUi*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTexture);		//生成処理

	HRESULT			Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTexture);		//初期化処理
	void			Uninit(void);									//終了処理
	void			Update(void);									//更新処理
	void			Draw(void);										//描画処理
private:

	static char						*pTexture[TEXTURE_TYPE_MAX];				//テキスト名
	static LPDIRECT3DTEXTURE9		m_pTexture[TEXTURE_TYPE_MAX];			//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;				//頂点バッファへのポインタ
	int								m_nTexture;				//数値
};




#endif