#ifndef  _BUTTON_H
#define  _BUTTON_H
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "main.h"
#include "scene2d.h"
//----------------------------------------------
//マクロ定義
//----------------------------------------------
#define MAX_BUTTON_TEXTURE 2
//------------------------------------
//前置処理
//------------------------------------
class CUi;
class CText;
class CNumber;
//------------------------------------
//クラス処理
//------------------------------------
class CButton :public CScene2d
{
public:
	CButton(int nPriorit = 3);			//コンストラクタ
	~CButton();			//デストラクタ
	typedef enum
	{
		BUTTON_TYPE_1 = 0,
		BUTTON_TYPE_2,
		BUTTON_TYPE_3,
		BUTTON_TYPE_4,
		BUTTON_TYPE_5,
		BUTTON_TYPE_6,
		BUTTON_TYPE_MAX

	}BUTTON_TYPE;

	static CButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int m_Type);	//生成処理
	static HRESULT	Load(void);				//テクスチャ読み込み
	static void		Unload(void);			//テクスチャの破棄


	HRESULT Init(void);		//初期化処理
	void	Uninit(void);	//終了処理
	void	Update(void);	//更新処理
	void	Draw(void);		//描画処理

private:
	typedef enum  //ボタンテクスチャ種類
	{
		BUTTON_TYPE_TEXTURE_1 = 0,
		BUTTON_TYPE_TEXTURE_2,
		BUTTON_TYPE_TEXTURE_MAX
	}BUTTON_TYPE_TEXTURE;
	/*構造体*/
	typedef struct
	{
		char				*pTexture;			//ボタンテキスト名
		char				*pTextureOver;		//ボタンオーバーテキスト名
		LPDIRECT3DTEXTURE9	m_Texture;			//テクスチャのポインタ
		LPDIRECT3DTEXTURE9	m_TextureOver;		//テクスチャ(オーバー)のポインタ
	}BUTTON_DATA;

	static BUTTON_DATA			ButtonData[BUTTON_TYPE_TEXTURE_MAX];
	static BUTTON_TYPE_TEXTURE	TypeTextureData[BUTTON_TYPE_MAX];
	bool						Hit(D3DXVECTOR3 pos, int nType);	//当たり判定
	static int					nCountSpeed;
	D3DXVECTOR3			m_pos;					//位置
	D3DXVECTOR3			m_size;					//サイズ
	BUTTON_TYPE			m_Type;					//タイプ
	bool				m_Text;
	CNumber				*m_pNumber;				//ナンバー
	CText				*m_pText;				//テキスト
	CUi					*m_pUi;					//UI
};
#endif