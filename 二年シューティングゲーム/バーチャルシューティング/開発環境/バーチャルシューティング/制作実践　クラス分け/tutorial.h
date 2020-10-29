#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "scene2d.h"
#include "main.h"

//------------------------------------
//前置処理
//------------------------------------
class CBossAnime;
class CBullet;
//----------------------------------------------
//クラス
//----------------------------------------------
class CTutorial :public CScene2d
{
public:

	CTutorial(int nPriorit = 3);		//コンストラクタ
	~CTutorial();						//デストラクタ	


	static HRESULT		Load(void);				//テクスチャ読み込み
	static void			Unload(void);			//テクスチャの破棄
	static CTutorial*	Create(void);//生成処理

	HRESULT			Init(void);						//初期化処理
	void			Uninit(void);					//終了処理
	void			Update(void);					//更新処理
	void			Draw(void);						//描画処理

private:
	static char					*pTexture;		//テキスト名
	static LPDIRECT3DTEXTURE9	m_Texture;		//テクスチャのポインタ

	int							m_nCountTexture;	//テクスチャの現在の枚数
};
#endif
