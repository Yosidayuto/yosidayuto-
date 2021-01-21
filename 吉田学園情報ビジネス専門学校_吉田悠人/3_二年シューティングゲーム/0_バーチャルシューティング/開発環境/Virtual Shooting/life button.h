//=============================================================================
//
//	���C�t�{�^��[life button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _LIFE_BUTTON_H_
#define _LIFE_BUTTON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "button p.h"

//=============================================================================
//�O���錾
//=============================================================================
class CNumber;

//=============================================================================
// �N���X��`
//=============================================================================
class CLifeButton :public CButtonp
{
public:

	CLifeButton(int nPriorit = 0);			//�R���X�g���N�^
	~CLifeButton();						//�f�X�g���N�^
	static HRESULT			Load(void);
	static void				Unload(void);
	static CLifeButton*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��
private:
	static TEXTURE_DATA	m_TextureData;	//�e�N�X�`���f�[�^

};
#endif
