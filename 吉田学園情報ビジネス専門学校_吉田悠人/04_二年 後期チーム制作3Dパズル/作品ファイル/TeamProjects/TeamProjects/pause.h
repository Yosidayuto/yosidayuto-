//=============================================================================
//
// ポーズ [pause.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"
#include "object.h"
//=============================================================================
//前方宣言
//=============================================================================
class CObject2D;
class CPauseButtonManager;
class CPauseBg;
//=============================================================================
//クラス定義
//=============================================================================
class CPause
{
public:
	CPause();
	~CPause();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void	Delete(void);	//ポーズを終了
	bool	GetPause(void);	//ポーズ状況ゲッター
private:
	CPauseButtonManager *pButtonManager;	// ポーズのボタンマネージャーポインタ
	CPauseBg* m_pPauseBg;					// ポーズ背景ポインタ
	bool bPause;							// ポーズ状態かどうか
};
#endif
