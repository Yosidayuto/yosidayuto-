//=============================================================================
//
//	�Z���N�g�w�i[select bg.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _SELECT_BG_H_
#define _SELECT_BG_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "bg.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CSelectBg :public CBgc
{
public:
	CSelectBg(int nPriorit = 0);			//�R���X�g���N�^
	~CSelectBg();							//�f�X�g���N�^

	static HRESULT		Load(void);		//�e�N�X�`���ǂݍ���
	static void			Unload(void);	//�e�N�X�`���̔j��
	static CSelectBg*	Create(void);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��

private:
	static TEXTURE_DATA	m_TextureData;	//�e�N�X�`���f�[�^

};
#endif