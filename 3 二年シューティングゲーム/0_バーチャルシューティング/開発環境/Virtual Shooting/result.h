#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"
#include "game.h"
//------------------------------------
//マクロ定義
//------------------------------------
#define MAX_RANKING 9

//------------------------------------
//前置処理
//------------------------------------
class CScore;
class CNumber;
//------------------------------------
//クラス処理
//------------------------------------
class CResult :public CScene
{
public:
	CResult(int nPriorit = 5);	//コンストラクタ
	~CResult();	//デストラクタ


	static CResult*	Create(void);	//生成処理

	HRESULT			Init(void);				//初期化処理
	void			Uninit(void);			//終了処理
	void			Update(void);			//更新処理
	void			Draw(void);				//描画処理
	void			ReadFile(CGame::STAGE_TYPE Stage);			//ランキングデータ読み込み
	void			WriteFile(CGame::STAGE_TYPE Stage);		//ランキングデータ書き込み
	int				SetRanking(int nScore, CGame::STAGE_TYPE Stage);	//スコアを照らし合わせる

private:
	CScore	*m_Score[MAX_RANKING];				//スコアクラス
	CNumber *m_pNumber[MAX_RANKING];			//ナンバークラス
	int nScoreData[MAX_RANKING];				//記録されたスコア
	int nScore;									//現在のスコア
	static char *pTexture[CGame::STAGE_TYPE_MAX];	//テキスト名
};


#endif