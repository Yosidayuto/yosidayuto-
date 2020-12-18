#ifndef _TELOP_TEXT_H_
#define _TELOP_TEXT_H_
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
class CTelopText :public CScene
{
public:
	typedef enum  //テキスト種類
	{
		TEXT_TYPE_TUTORIAL = 0,		//チュートリアル
		TEXT_TYPE_LIFE,				//ライフ
		TEXT_TYPE_SPEED,			//スピード
		TEXT_TYPE_BULLET,			//バレット
		TEXT_TYPE_LASER,			//レーザー
		TEXT_TYPE_HOMING,			//ホーミング
		TEXT_TYPE_MAX
	}TEXT_TYPE;


	CTelopText(int nPriorit = 4);					//コンストラクタ
	~CTelopText();									//デストラクタ
	static HRESULT	Load(void);						//テクスチャ読み込み
	static void		Unload(void);					//テクスチャの破棄
	static CTelopText	*Create(void);	//生成処理
	HRESULT			Init(void);						//初期化処理
	void			Uninit(void);					//終了処理
	void			Update(void);					//更新処理
	void			Draw(void);						//描画処理
	void			TypeChange(TEXT_TYPE Type);		//テキスト変更
	TEXT_TYPE		GetType(void) { return m_Type; }
private:
	static LPDIRECT3DTEXTURE9	m_apTexture[TEXT_TYPE_MAX];		//テクスチャへのポインタ
	static char					*m_pText[TEXT_TYPE_MAX];		//テキストネーム
	CScene2d					*m_apScene2D;					//2Dポリゴンの数
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;						//頂点バッファへのポインタ
	int							m_nCounterAnim;					//アニメーションカウンター
	int							m_nPatternAnim;					//アニメーションパターンNo
	TEXT_TYPE					m_Type;							//タイプ
	D3DXVECTOR3					m_pos;							//位置
};
#endif