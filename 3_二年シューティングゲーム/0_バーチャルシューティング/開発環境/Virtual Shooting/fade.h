#ifndef _FADE_H
#define _FADE_H
//------------------------------------
//インクルードファイル
//------------------------------------
#include"main.h"
#include"manager.h"
//----------------------------------------------
//シーンクラス
//----------------------------------------------
class CFade
{
public:
	CFade();
	~CFade();
	typedef enum
	{
		FADE_NONE = 0,		//何もない状態
		FADE_IN,			//フェード処理
		FADE_OUT,			//フェードアウト処理
		FADE_MAX
	}FADE;

	//static CFade *Create(CManager::GAME_MODE modeNext);	//生成処理

	HRESULT Init(/*CManager::GAME_MODE modeNext*/void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Set(CManager::GAME_MODE modeNext);
	FADE Get(void);
private:

	FADE						m_Fade;					//フェード状態
	D3DXCOLOR					m_Color;				//フェード色
	CManager::GAME_MODE			m_ModeNext;				//次の画面（モード）
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				//頂点バッファへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture;	//テクスチャのポインタ
	bool						m_bFade;

};

#endif