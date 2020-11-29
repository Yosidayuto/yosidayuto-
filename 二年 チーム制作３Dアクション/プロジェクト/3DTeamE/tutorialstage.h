//=============================================================================
//
// チュートリアルステージ [tutorialstage.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _TUTORIALSTAGE_H_
#define _TUTORIALSTAGE_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTutorialStage : public CObject
{
public:
	CTutorialStage();
	~CTutorialStage();
	static HRESULT Load(void);
	static void Unload(void);
	static CTutorialStage* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CModel* GetModel(void);
private:
	static CModel::MODELDATA m_modeldata;
	static D3DXMATERIAL *m_pMat;
	CModel* m_pModel;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
};
#endif