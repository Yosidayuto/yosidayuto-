#ifndef  SCORE_H
#define  SCORE_H
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "main.h"
#include "scene2d.h"

//----------------------------------------------
//マクロ定義
//----------------------------------------------
#define MAX_SCORE 8//スコアパネルの最大数

class CUi;
class CNumber;
//------------------------------------
//クラス処理
//------------------------------------
class CScore :public CScene
{
public:
	CScore(int nPriorit = 5);			//コンストラクタ
	~CScore();			//デストラクタ


	static CScore*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,bool UI);	//生成処理


	HRESULT Init(void);		//初期化処理
	void	Uninit(void);	//終了処理
	void	Update(void);	//更新処理
	void	Draw(void);		//描画処理

	void	SetScore(int nScore);
	void	ColChange(D3DXCOLOR col);
	void	AddScore(int nValue);
	int		GetScore(void);

	//void ScoreEffect(int nScore);

private:
	bool						UiSwitch;
	CUi							*m_apUi;
	CNumber						*m_apNumber[MAX_SCORE];
	int							m_nScore;
	D3DXVECTOR3					m_pos;
	D3DXVECTOR3					m_size;
};
#endif