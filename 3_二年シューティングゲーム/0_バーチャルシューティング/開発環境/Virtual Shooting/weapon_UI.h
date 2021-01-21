#ifndef  _WEAPON_UI_H
#define  _WEAPON_UI_H
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "main.h"
#include "scene2d.h"
#include "player.h"
//----------------------------------------------
//マクロ定義
//----------------------------------------------
#define MAX_BUTTON_TEXTURE 2
//------------------------------------
//前置処理
//------------------------------------
class CUi;
//------------------------------------
//クラス処理
//------------------------------------
class CWeapon_Ui :public CScene2d
{
public:
	CWeapon_Ui(int nPriorit = 3);			//コンストラクタ
	~CWeapon_Ui();			//デストラクタ


	static CWeapon_Ui*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, WEAPON_MODE Type);	//生成処理
	static HRESULT		Load(void);				//テクスチャ読み込み
	static void			Unload(void);			//テクスチャの破棄


	HRESULT Init(void);		//初期化処理
	void	Uninit(void);	//終了処理
	void	Update(void);	//更新処理
	void	Draw(void);		//描画処理
	void	SetUI(WEAPON_MODE Type);
private:
	static LPDIRECT3DTEXTURE9	m_Texture;	//テクスチャのポインタ
	WEAPON_MODE			m_Type;
	D3DXVECTOR3			m_pos;				//位置
	D3DXVECTOR3			m_size;				//サイズ
	CUi					*m_pUi;				//UI
};
#endif