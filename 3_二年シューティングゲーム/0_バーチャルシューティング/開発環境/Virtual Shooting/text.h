#ifndef  _TEXT_H
#define  _TEXT_H
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "main.h"
#include "scene2d.h"

//----------------------------------------------
//マクロ定義
//----------------------------------------------

//------------------------------------
//クラス処理
//------------------------------------
class CText
{
public:

	CText();		//コンストラクタ
	~CText();		//デストラクタ
	typedef enum
	{
		TEXT_START = 0,
		TEXT_START_LAST,
		TEXT_LIFE,
		TEXT_SPEED,
		TEXT_BULLET,
		TEXT_LASER,
		TEXT_HOMING,
		TEXT_MAX
	}TEXT_TYPE;

	static HRESULT	Load(void);		//テクスチャ読み込み
	static void		Unload(void);	//テクスチャの破棄
	static CText*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size , TEXT_TYPE Text);	//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXT_TYPE Text);				//初期化処理
	void	Uninit(void);			//終了処理
	void	Update(void);			//更新処理
	void	Draw(void);				//描画処理
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[TEXT_MAX];		//テクスチャへのポインタ
	static char						*m_cTexture[TEXT_MAX];		//テクスチャ名
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;					//頂点バッファへのポインタ
	TEXT_TYPE						m_Type;						//タイプ
};




#endif