#ifndef _RESULT_BG_H_
#define _RESULT_BG_H_
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "main.h"
#include "scene2d.h"
//----------------------------------------------
//マクロ定義
//----------------------------------------------
#define MAX_BG_GA 2
#define MAX_PATTERN 2	//アニメーションの最大枚数

//------------------------------------
//クラス処理
//------------------------------------
class CResultBg :public CScene2d
{
public:
	CResultBg(int nPriorit = 5);			//コンストラクタ
	~CResultBg();							//デストラクタ

	static HRESULT	Load(void);		//テクスチャ読み込み
	static void		Unload(void);	//テクスチャの破棄
	static CResultBg*	Create(void);	//生成処理

	HRESULT			Init(void);		//初期化処理
	void			Uninit(void);	//終了処理
	void			Update(void);	//更新処理
	void			Draw(void);		//描画処理

private:
	static LPDIRECT3DTEXTURE9	m_apTexture;					//テクスチャへのポインタ
	CScene2d					*m_apScene2D;					//2Dポリゴンの数
};
#endif