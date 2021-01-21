//=============================================================================
//
//	�^�C�g���w�i[title bg.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _TITLE_BG_H_
#define _TITLE_BG_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "bg.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CTitleBg :public CBgc
{
public:

	CTitleBg(int nPriorit = 0);			//�R���X�g���N�^
	~CTitleBg();						//�f�X�g���N�^
	static HRESULT		Load(void);
	static void			Unload(void);
	static CTitleBg*	Create(void);


	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��
private:
	static TEXTURE_DATA	m_TextureData;	//�e�N�X�`���f�[�^
};
#endif
