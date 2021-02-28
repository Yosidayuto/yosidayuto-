//=============================================================================
//
// �G�l�~�[�^�C�v2���� [enemy type2.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _ENEMY_TYPE_2_H_
#define _ENEMY_TYPE_2_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "enemy base.h"
//=============================================================================
//�O���錾
//=============================================================================

//=============================================================================
// �N���X��`
//=============================================================================
class CEnemyType2 :public CEnemyBase
{
public:
	CEnemyType2(int nPriorit = PRIORITY_OBJECT_1);	//�R���X�g���N�^
	~CEnemyType2();									//�f�X�g���N�^	

	static HRESULT		Load(void);					// �e�N�X�`���ǂݍ���
	static void			Unload(void);				// �e�N�X�`���̔j��
	static CEnemyType2*	Create(ENEMY_MOVE_PATTERN MoveType,		// �s���p�^�[��
								ENEMY_ATTACK_PATTERN AttackType,	// �U���p�^�[��
								int nInTime,						// �o���^�C��
								int nActionTime,					// �A�N�V�����^�C��
								int nAttacTime,						// �A�^�b�N�^�C��
								int nReturnTime,					// ���^�[���^�C��
								D3DXVECTOR3 pos,					// �o���ʒu
								float fSpeed,						// �X�s�[�h
								int nLife);							// ���C�t

	HRESULT Init(void);				// ����������
	void	Uninit(void);			// �I������
	void	Update(void);			// �X�V����
	void	Draw(void);				// �`�揈��
private:
	static TEXTURE_DATA	m_TextureData;					// �e�N�X�`���f�[�^

};
#endif