//=============================================================================
//
//	stagenumber�w�b�_ [stagenumber.h]
//	Author : ����@�r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _STAGENUMBER_H_
#define _STAGENUMBER_H_

//====================================
//�C���N���[�h
//====================================
#include "main.h"
#include "ui.h"

//====================================
// �}�N����`
//====================================
#define MAX_STAGENUMBER STAGE_NUM_MAX

//====================================
// �N���X��`
//====================================

//UI�N���X
class CStageNumber : public CUi
{
public:
	// ��bUI�̎��
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
