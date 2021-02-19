//=============================================================================
//
//	�z�[�~���O�e���b�v[telop homing.h]
//	Author:�g�c�@�I�l
//
//=============================================================================
#ifndef  _TELOP_HOMING_H
#define  _TELOP_HOMING_H
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
//=============================================================================
// �O���錾
//=============================================================================
//=============================================================================
// �N���X��`
//=============================================================================
class CTelopHoming :public CScene2d
{
public:
	CTelopHoming(int nPriorit = PRIORITY_UI_1);			// �R���X�g���N�^
	~CTelopHoming();		// �f�X�g���N�^

	static HRESULT		Load(void);
	static void			Unload(void);
	static CTelopHoming*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(void);		// ����������
	void	Uninit(void);	// �I������
	void	Update(void);	// �X�V����
	void	Draw(void);		// �`�揈��
private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^

};
#endif