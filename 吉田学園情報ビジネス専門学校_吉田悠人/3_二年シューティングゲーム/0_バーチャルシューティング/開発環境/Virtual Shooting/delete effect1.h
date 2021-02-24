//=============================================================================
//
// �{�X�f���[�g�G�t�F�N�g1���� [delete effect1.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _DELETE_EFFECT_1_H_
#define _DELETE_EFFECT_1_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "boss effect base.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CDeleteEffect1 :public CBossEffectBase
{
public:
	CDeleteEffect1();						//�R���X�g���N�^
	~CDeleteEffect1();						//�f�X�g���N�^	

	static HRESULT			Load(void);		//�e�N�X�`���ǂݍ���
	static void				Unload(void);	//�e�N�X�`���̔j��
	static CDeleteEffect1*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//��������

	HRESULT Init(void);			//����������
	void	Uninit(void);		//�I������
	void	Update(void);		//�X�V����
	void	Draw(void);			//�`�揈��

private:
	static TEXTURE_DATA		m_TextureData;	// �e�N�X�`���f�[�^

};
#endif