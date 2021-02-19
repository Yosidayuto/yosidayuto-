//=============================================================================
//
// ボスアニメーション処理 [boss_anime.cpp]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _BOSS_ANIME_H_
#define _BOSS_ANIME_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
#include"scene2d.h"


//=============================================================================
// クラス定義
//=============================================================================
class CBossAnime :public CScene2d
{
public:
	CBossAnime(int nPriorit = PRIORITY_OBJECT_1);	//コンストラクタ
	~CBossAnime();									//デストラクタ	
	typedef enum  //アニメ種類
	{
		BOSS_ANIME_1 = 0,
		BOSS_ANIME_2,
		BOSS_ANIME_3,
		BOSS_ANIME_4,
		BOSS_ANIME_5,
		BOSS_ANIME_6,

		BOSS_ANIME_MAX
	}BOSS_ANIME;

	static CBossAnime*Create(D3DXVECTOR3 Pos, D3DXVECTOR3 size, BOSS_ANIME Type);	//生成処理
	static HRESULT Load(void);		//テクスチャ読み込み
	static void Unload(void);		//テクスチャの破棄


	HRESULT Init(D3DXVECTOR3 size);	//初期化処理
	void	Uninit(void);			//終了処理
	void	Update(void);			//更新処理
	void	Draw(void);				//描画処理

private:
	typedef struct
	{
		int					MaxCount;			// テクスチャの最大コマ数
		int					nCountAnime;		// アニメーションカウント
		bool				bLoop;				// ループするか
	}ANIME_DATA;
	BOSS_ANIME				m_Type;							// タイプ
	static ANIME_DATA		BossAnim[BOSS_ANIME_MAX];		// ボスアニメ
	static TEXTURE_DATA		m_TextureData[BOSS_ANIME_MAX];	// テクスチャデータ
	int						m_nCounterAnim;					// アニメーションカウンター
	int						m_nPatternAnimX;				// アニメーションパターンNo
			

};
#endif