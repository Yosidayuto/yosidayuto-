//=============================================================================
//
//	���U���g�w�i[result bg.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _RESULT_BG_H_
#define _RESULT_BG_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "bg.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CResultBg :public CBgc
{
public:
	CResultBg(int nPriorit = PRIORITY_SCENE);	//�R���X�g���N�^
	~CResultBg();								//�f�X�g���N�^

	static HRESULT		Load(void);		//�e�N�X�`���ǂݍ���
	static void			Unload(void);	//�e�N�X�`���̔j��
	static CResultBg*		Create(void);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��

private:
	static TEXTURE_DATA	m_TextureData;	//�e�N�X�`���f�[�^

};
#endif