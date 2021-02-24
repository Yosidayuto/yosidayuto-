//=============================================================================
//
//	�X�s�[�h�e���b�v[telop speed.h]
//	Author:�g�c�@�I�l
//
//=============================================================================
#ifndef  _TELOP_SPEED_H
#define  _TELOP_SPEED_H
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
class CTelopSpeed :public CScene2d
{
public:
	CTelopSpeed(int nPriorit = PRIORITY_UI_1);	// �R���X�g���N�^
	~CTelopSpeed();	// �f�X�g���N�^

	static HRESULT		Load(void);
	static void			Unload(void);
	static CTelopSpeed*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(void);		// ����������
	void	Uninit(void);	// �I������
	void	Update(void);	// �X�V����
	void	Draw(void);		// �`�揈��
private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^

};
#endif