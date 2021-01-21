//=============================================================================
//
//	�{�^���i���j[button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================
#ifndef _LIFE_UI_H_
#define _LIFE_UI_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene2d.h"
//=============================================================================
//�O���錾
//=============================================================================
class CUi;
//------------------------------------
//�N���X����
//------------------------------------
class CLifeUi :public CScene2d
{
public:
	CLifeUi(int nPriorit = 3);		//�R���X�g���N�^
	~CLifeUi();						//�f�X�g���N�^

	static HRESULT	Load(void);					//�e�N�X�`���ǂݍ���
	static void		Unload(void);				//�e�N�X�`���̔j��
	static CLifeUi*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��
private:
	static TEXTURE_DATA	m_TextureData;	//�e�N�X�`���f�[�^
};



#endif
