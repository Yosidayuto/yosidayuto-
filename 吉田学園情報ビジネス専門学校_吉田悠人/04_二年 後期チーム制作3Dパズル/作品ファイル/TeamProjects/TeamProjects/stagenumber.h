//=============================================================================
//
//	stagenumberヘッダ [stagenumber.h]
//	Author : 筒井　俊稀
//
//=============================================================================

//二重インクルード防止
#ifndef _STAGENUMBER_H_
#define _STAGENUMBER_H_

//====================================
//インクルード
//====================================
#include "main.h"
#include "ui.h"

//====================================
// マクロ定義
//====================================
#define MAX_STAGENUMBER STAGE_NUM_MAX

//====================================
// クラス定義
//====================================

//UIクラス
class CStageNumber : public CUi
{
public:
	// 会話UIの種類
	typedef enum
	{
		STAGE_NUM_1 = 0,
		STAGE_NUM_2,
		STAGE_NUM_3,
		STAGE_NUM_MAX
	}STAGE_NUM;
	CStageNumber();
	~CStageNumber();

	static CStageNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, STAGE_NUM type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_STAGENUMBER];


};
#endif // !_UI_H_
