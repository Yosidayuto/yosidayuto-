//=============================================================================
//
//	�X�^�[�g�{�^��[start button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _START_BUTTON_H_
#define _START_BUTTON_H_

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
class CStartButton :public CButtonp
{
public:

	CStartButton(int nPriorit = 0);			//�R���X�g���N�^
	~CStartButton();						//�f�X�g���N�^
	static HRESULT			Load(void);
	static void				Unload(void);
	static CStartButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��
private:
	static TEXTURE_DATA	m_TextureData;	//�e�N�X�`���f�[�^
	CNumber*			m_pNumber;		//�i���o�[

};
#endif
