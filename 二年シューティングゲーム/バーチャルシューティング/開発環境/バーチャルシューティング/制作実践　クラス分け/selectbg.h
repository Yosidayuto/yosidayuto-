#ifndef _SELECTBG_H_
#define _SELECTBG_H_
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "main.h"
#include "scene.h"
#include "manager.h"
//----------------------------------------------
//マクロ定義
//----------------------------------------------
#define MAX_SELECT_BG 2
//----------------------------------------------
//前置処理
//----------------------------------------------
class CScene2d;
//------------------------------------
//クラス処理
//------------------------------------
class CSelectBg :public CScene
{
public:
	CSelectBg(int nPriorit = 0);			//コンストラクタ
	~CSelectBg();							//デストラクタ

	static HRESULT		Load(void);		//テクスチャ読み込み
	static void			Unload(void);	//テクスチャの破棄
	static CSelectBg*	Create(void);	//生成処理

	HRESULT			Init(void);		//初期化処理
	void			Uninit(void);	//終了処理
	void			Update(void);	//更新処理
	void			Draw(void);		//描画処理

private:

	static LPDIRECT3DTEXTURE9	m_apTexture[MAX_SELECT_BG];	//テクスチャへのポインタ
	CScene2d					*m_apScene2D[MAX_SELECT_BG];	//2Dポリゴンの数
	typedef struct
	{
		D3DXVECTOR3			m_Pos;			//位置
		D3DXVECTOR3			m_Size;			//サイズ
	}SELECT_DATA;
	static char			*m_dTexture[MAX_SELECT_BG];			//テクスチャ名
	static SELECT_DATA		m_Data[MAX_SELECT_BG];					//背景データ
};
#endif