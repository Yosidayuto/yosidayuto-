//=============================================================================
//
// �{�X�^�C�v3���� [boss type3.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _BOSS_TYPE_3_H_
#define _BOSS_TYPE_3_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "boss base.h"
//=============================================================================
//�O���錾
//=============================================================================
class CBossEffectBase;
//=============================================================================
// �N���X��`
//=============================================================================
class CBossType3 :public CBossBase
{
public:
	CBossType3(int nPriorit = PRIORITY_OBJECT_1);	//�R���X�g���N�^
	~CBossType3();									//�f�X�g���N�^	

	static HRESULT		Load(void);					// �e�N�X�`���ǂݍ���
	static void			Unload(void);				// �e�N�X�`���̔j��
	static CBossType3*	Create(D3DXVECTOR3 pos);	// ��������

	HRESULT Init(void);			// ����������
	void	Uninit(void);		// �I������
	void	Update(void);		// �X�V����
	void	Draw(void);			// �`�揈��

	void	Effect(void);		//�G�t�F�N�g����
	void	DisEffect(void);	//�|���ꂽ�Ƃ��̃G�t�F�N�g����

private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
	CBossEffectBase*	m_Effect;		// �G�t�F�N�g�|�C���^

};
#endif