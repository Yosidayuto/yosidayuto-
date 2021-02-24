//=============================================================================
//
//	�`���[�g���A���w�i[tutorial bg.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _TUTORIAL_BG_H_
#define _TUTORIAL_BG_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "bg.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CTutorialBg :public CBgc
{
public:

	CTutorialBg(int nPriorit = 0);			//�R���X�g���N�^
	~CTutorialBg();							//�f�X�g���N�^
	static HRESULT			Load(void);
	static void				Unload(void);
	static CTutorialBg*		Create(void);

	HRESULT	Init(void);			//����������
	void	Uninit(void);		//�I������
	void	Update(void);		//�X�V����
	void	Draw(void);			//�`�揈��

	void	TextureMove(bool bScroll);	//�e�N�X�`���̈ړ�
private:
	static TEXTURE_DATA	m_TextureData;	//�e�N�X�`���f�[�^
	float				m_fTexture;		//�e�N�X�`���̃X�N���[���l
};
#endif
