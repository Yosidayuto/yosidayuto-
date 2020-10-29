#ifndef _WARNING_H_
#define _WARNING_H_
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include"main.h"
#include"scene2d.h"

//----------------------------------------------
//クラス
//----------------------------------------------
class CWarning :public CScene2d
{
public:
	CWarning(int nPriorit = 4);			//コンストラクタ
	~CWarning();			//デストラクタ	

	static CWarning*Create(D3DXVECTOR3 Pos, D3DXVECTOR3 size);	//生成処理
	static HRESULT Load(void);		//テクスチャ読み込み
	static void Unload(void);		//テクスチャの破棄


	HRESULT Init(D3DXVECTOR3 size);				//初期化処理
	void	Uninit(void);			//終了処理
	void	Update(void);			//更新処理
	void	Draw(void);				//描画処理

private:
	typedef struct
	{
		LPDIRECT3DTEXTURE9	pTexture;			//テクスチャのポインタ
		char				*pTextName;			//テキスト名
		int					MaxCount;			//テクスチャの最大コマ数
		int					nCountAnime;		//
		bool				bLoop;				//ループするか
	}ANIME_DATA;
	int						nStopCount;
	static ANIME_DATA		WarningAnim;		//ボスアニメ
	int m_nCounterAnim;							//アニメーションカウンター
	int m_nPatternAnimX;						//アニメーションパターンNo


};
#endif