//=============================================================================
//
// �z�[�~���O�e���� [homing.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _HOMING_H_
#define _HOMING_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"scene2d.h"
#include "bullet base.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CHoming :public CBulletBase
{
public:
	CHoming();						//�R���X�g���N�^
	~CHoming();						//�f�X�g���N�^	
	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);	//�e�N�X�`���̔j��
	static CHoming* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//��������

	HRESULT Init(void);				// ����������
	void	Uninit(void);			// �I������
	void	Update(void);			// �X�V����
	void	Draw(void);				// �`�揈��
	void	Move(void);				// �ړ�����
	void	Bullet(CScene* pObj);	// �o���b�g����
	void	LockOn(D3DXVECTOR3 pos, D3DXVECTOR3 EnemyPos);		// �^�[�Q�b�g�擾
	void	TargetMove(D3DXVECTOR3 pos, D3DXVECTOR3 EnemyPos);	// �^�[�Q�b�g�Ɍ��������߂�move�擾
private:
	static TEXTURE_DATA	m_TextureData;		// �e�N�X�`���f�[�^
	int					m_nRange;			// �z�[�~���O�͈͕ۊǕϐ�
};
#endif