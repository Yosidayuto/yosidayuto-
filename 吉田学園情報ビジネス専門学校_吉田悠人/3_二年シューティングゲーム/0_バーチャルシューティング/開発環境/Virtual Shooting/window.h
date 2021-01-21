#ifndef _WINDOW_H_
#define _WINDOW_H_
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include"main.h"
#include"scene2d.h"
//------------------------------------
//前置処理
//------------------------------------
class CButton;
class CScore;
//----------------------------------------------
//クラス
//----------------------------------------------
class CWindow :public CScene2d
{
public:

	CWindow(int nPriorit = 4);			//コンストラクタ
	~CWindow();						//デストラクタ	
	typedef enum
	{
		WINDOW_TYPE_SELECT = 0,
		WINDOW_TYPE_MAX
	}WINDOW_TYPE;

	static CWindow*	Create(D3DXVECTOR3 Pos, D3DXVECTOR3 size, WINDOW_TYPE Type);//生成処理
	static HRESULT	Load(void);			//テクスチャ読み込み
	static void		Unload(void);		//テクスチャの破棄

	HRESULT			Init(void);			//初期化処理
	void			Uninit(void);		//終了処理
	void			Update(void);		//更新処理
	void			Draw(void);			//描画処理
	bool			Window(void);				
private:
	static char					*m_pcTexture[WINDOW_TYPE_MAX];		//テキスト名
	static LPDIRECT3DTEXTURE9	m_Texture[WINDOW_TYPE_MAX];			//テクスチャのポインタ
	static bool					m_Window[WINDOW_TYPE_MAX];			//使用状況
	D3DXVECTOR3					m_pos;				//ウィンドウ座標
	D3DXVECTOR3					m_size;				//ウィンドウサイズ
};
#endif
