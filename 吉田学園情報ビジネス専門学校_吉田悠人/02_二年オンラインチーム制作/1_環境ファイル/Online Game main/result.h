//=============================================================================
//
// ���U���g���� [result.h]
// Author : �U�J �����Y
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_RESULT	(2)
#define RESULT_TEXTURE	"data/TEXTURE/result001.png"	// �e�N�X�`���p�X(���U���g)

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// ���U���g�N���X
//*****************************************************************************
class CResult : public CScene
{
public:
	typedef enum
	{
		RESULT_WINNER = 0,					// �������
		RESULT_LOSER,						// ���S���
		RESULT_MAX
	}RESULT;

	CResult();								// �R���X�g���N�^
	~CResult();								// �f�X�g���N�^
	static HRESULT Load(void);				// �e�N�X�`���ǂݍ���
	static void Unload(void);				// �e�N�X�`���j��
	static CResult*Create(D3DXVECTOR3 size);// �쐬����
	HRESULT Init(D3DXVECTOR3 size);			// ����������
	void Uninit(void);						// �I������
	void Update(void);						// �X�V����
	void Draw(void);						// �`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_apTexture;	// �e�N�X�`���̃|�C���^
	CScene2D *m_apScene2D;					// Scene2D�̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu
	static RESULT m_ResultType;				// ���U���g�^�C�v
};

#endif 

