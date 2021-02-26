//=============================================================================
//
// �G�l�~�[�o���b�g���� [enemy bullet.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _ENEMY_BULLET_H_
#define _ENEMY_BULLET_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "bullet base.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CEnemyBullet :public CBulletBase
{
public:
	CEnemyBullet();						//�R���X�g���N�^
	~CEnemyBullet();					//�f�X�g���N�^	
	static HRESULT		 Load(void);	//�e�N�X�`���ǂݍ���
	static void			 Unload(void);	//�e�N�X�`���̔j��
	static CEnemyBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//��������

	HRESULT Init(void);				// ����������
	void	Uninit(void);			// �I������
	void	Update(void);			// �X�V����
	void	Draw(void);				// �`�揈��
	void	Move(void);				// �ړ�����
	void	Bullet(CScene* pObj);	// �o���b�g����
private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
};
#endif