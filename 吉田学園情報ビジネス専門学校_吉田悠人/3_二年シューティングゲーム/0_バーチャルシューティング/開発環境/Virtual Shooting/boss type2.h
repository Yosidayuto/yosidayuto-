//=============================================================================
//
// �{�X�^�C�v2���� [boss type2.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _BOSS_TYPE_2_H_
#define _BOSS_TYPE_2_H_

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
class CBossType2 :public CBossBase
{
public:
	CBossType2();	//�R���X�g���N�^
	~CBossType2();									//�f�X�g���N�^	

	static HRESULT		Load(void);					// �e�N�X�`���ǂݍ���
	static void			Unload(void);				// �e�N�X�`���̔j��
	static CBossType2*	Create(D3DXVECTOR3 pos);	// ��������

	HRESULT Init(void);			// ����������
	void	Uninit(void)	;	// �I������
	void	Update(void)	;	// �X�V����
	void	Draw(void);			// �`�揈��
	void	Effect(void);		//�G�t�F�N�g����
	void	DisEffect(void);	//�|���ꂽ�Ƃ��̃G�t�F�N�g����

private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
	CBossEffectBase*	m_Effect;		// �G�t�F�N�g�|�C���^

};
#endif