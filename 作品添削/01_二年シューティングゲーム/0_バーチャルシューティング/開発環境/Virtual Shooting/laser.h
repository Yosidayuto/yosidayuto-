//=============================================================================
//
// ���[�U�[���� [laser.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _LASER_H_
#define _LASER_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"scene2d.h"
#include "bullet base.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define HIT_ENEMI (10)	//���[�U�[������������
//=============================================================================
// �N���X��`
//=============================================================================
class CLaser :public CBulletBase
{
public:
	CLaser();						//�R���X�g���N�^
	~CLaser();						//�f�X�g���N�^	
	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);	//�e�N�X�`���̔j��
	static CLaser* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//��������

	HRESULT Init(void);				// ����������
	void	Uninit(void);			// �I������
	void	Update(void);			// �X�V����
	void	Draw(void);				// �`�揈��
	void	Move(void);				// �ړ�����
	void	Bullet(CScene* pObj);	// �o���b�g����
private:
	static TEXTURE_DATA	m_TextureData;		// �e�N�X�`���f�[�^
	bool				m_bHit[HIT_ENEMI];	// �q�b�g�m�F
	int					m_nHitCount;		// �q�b�g�J�E���g
};	
#endif