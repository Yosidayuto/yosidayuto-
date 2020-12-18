#ifndef _TELOP_BER_H_
#define _TELOP_BER_H_
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "main.h"
#include "scene.h"
//----------------------------------------------
//マクロ定義
//----------------------------------------------

//----------------------------------------------
//前置処理
//----------------------------------------------
class CScene2d;
//------------------------------------
//クラス処理
//------------------------------------
class CTelopBer :public CScene
{
public:
	CTelopBer();						//コンストラクタ
	~CTelopBer();						//デストラクタ
	static HRESULT	Load(void);		//テクスチャ読み込み
	static void		Unload(void);	//テクスチャの破棄
	static CTelopBer	*Create(void);	//生成処理
	HRESULT			Init(void);		//初期化処理
	void			Uninit(void);	//終了処理
	void			Update(void);	//更新処理
	void			Draw(void);		//描画処理
private:
	static LPDIRECT3DTEXTURE9	m_apTexture;		//テクスチャへのポインタ
	CScene2d					*m_apScene2D;		//2Dポリゴンの数
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;			//頂点バッファへのポインタ
};
#endif