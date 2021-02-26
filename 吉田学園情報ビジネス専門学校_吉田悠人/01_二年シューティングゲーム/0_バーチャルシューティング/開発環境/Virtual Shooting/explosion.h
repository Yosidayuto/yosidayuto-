//=============================================================================
//
// �G�N�X�v���[�W�������� [explosion.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"scene2d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CExplosion :public CScene2d
{
public:
	CExplosion(int nPriorit= PRIORITY_OBJECT_1);	//�R���X�g���N�^
	~CExplosion();									//�f�X�g���N�^	

	static HRESULT		Load(void);					//�e�N�X�`���ǂݍ���
	static void			Unload(void);				//�e�N�X�`���̔j��
	static CExplosion*	Create(D3DXVECTOR3 Pos);	//��������

	HRESULT Init(void);				//����������
	void	Uninit(void);			//�I������
	void	Update(void);			//�X�V����
	void	Draw(void);				//�`�揈��


private:
	static TEXTURE_DATA	m_TextureData;		// �e�N�X�`���f�[�^
	int					m_nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int					m_nPatternAnimX;	// �A�j���[�V�����p�^�[��No
	int					m_nPatternAnimY;	// �A�j���[�V�����p�^�[��No

};
#endif