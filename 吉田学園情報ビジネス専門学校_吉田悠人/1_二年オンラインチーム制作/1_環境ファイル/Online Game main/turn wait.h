//=============================================================================
//
// �^�[���҂����� [turn wait.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _TURN_WAIT_H_
#define _TURN_WAIT_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TURN_WAIT	(1)
#define TURN_WAIT_TEXTURE	"data/TEXTURE/matching.png"		// �ҋ@��ʂ̃e�N�X�`���p�X


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
// �^�C�g���N���X
//*****************************************************************************
class CTurnWait : public CScene
{
public:
	CTurnWait();											// �R���X�g���N�^
	~CTurnWait();											// �f�X�g���N�^
	static HRESULT Load(void);								// �e�N�X�`���ǂݍ���
	static void Unload(void);								// �e�N�X�`���j��
	static CTurnWait *Create(D3DXVECTOR3 size);				// �쐬����
	HRESULT Init(D3DXVECTOR3 size);							// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TURN_WAIT];	// �e�N�X�`���̃|�C���^
	CScene2D *m_apScene2D[MAX_TURN_WAIT];					// Scene2D�̃|�C���^
	D3DXVECTOR3 m_pos;										// �ʒu
};
#endif

