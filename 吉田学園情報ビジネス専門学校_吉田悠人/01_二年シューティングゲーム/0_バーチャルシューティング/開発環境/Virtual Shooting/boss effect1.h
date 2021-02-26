//=============================================================================
//
// �{�X�G�t�F�N�g1���� [boss effect1.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _BOSS_EFFECT_1_H_
#define _BOSS_EFFECT_1_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "boss effect base.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CBossEffectType1 :public CBossEffectBase
{
public:
	CBossEffectType1();								//�R���X�g���N�^
	~CBossEffectType1();							//�f�X�g���N�^	
		
	static HRESULT				Load(void);			//�e�N�X�`���ǂݍ���
	static void					Unload(void);		//�e�N�X�`���̔j��
	static CBossEffectType1*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//��������

	HRESULT Init(void);			//����������
	void	Uninit(void);		//�I������
	void	Update(void);		//�X�V����
	void	Draw(void);			//�`�揈��

private:
	static TEXTURE_DATA		m_TextureData;	// �e�N�X�`���f�[�^

};
#endif