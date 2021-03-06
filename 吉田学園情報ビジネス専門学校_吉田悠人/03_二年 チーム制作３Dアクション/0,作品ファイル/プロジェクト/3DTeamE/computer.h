//=============================================================================
//
// コンピュータ [computer.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _COMPUTER_H_
#define _COMPUTER_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COMPUTER_PARTS 2
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CComputer : public CObject
{
public:
	CComputer();
	~CComputer();
	static HRESULT Load(void);
	static void Unload(void);
	static CComputer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetRot(void);
private:
	static CModel::MODELDATA m_modeldata;
	static D3DXMATERIAL *m_pMat;
	CModel* m_pModel;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	bool m_bUse;
};
#endif