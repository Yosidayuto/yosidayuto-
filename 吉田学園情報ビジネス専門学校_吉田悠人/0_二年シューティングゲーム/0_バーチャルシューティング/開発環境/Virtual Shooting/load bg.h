//=============================================================================
//
//	���[�h�w�i[load bg.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _LOAD_BG_H_
#define _LOAD_BG_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "bg.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CLoadBg :public CBgc
{
public:
	CLoadBg();	//�R���X�g���N�^
	~CLoadBg();								//�f�X�g���N�^

	static HRESULT		Load(void);		//�e�N�X�`���ǂݍ���
	static void			Unload(void);	//�e�N�X�`���̔j��
	static CLoadBg*		Create(void);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��

private:
	static TEXTURE_DATA	m_TextureData;	//�e�N�X�`���f�[�^

};
#endif