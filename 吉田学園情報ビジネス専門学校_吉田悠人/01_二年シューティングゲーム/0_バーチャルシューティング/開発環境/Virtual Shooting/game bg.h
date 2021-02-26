//=============================================================================
//
//	�Q�[���w�i[game bg.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _GAME_BG_H_
#define _GAME_BG_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "bg.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CGameBg :public CBgc
{
public:
	CGameBg(int nPriorit = PRIORITY_SCENE);	//�R���X�g���N�^
	~CGameBg();								//�f�X�g���N�^

	static HRESULT		Load(void);		//�e�N�X�`���ǂݍ���
	static void			Unload(void);	//�e�N�X�`���̔j��
	static CGameBg*		Create(void);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��

private:
	static TEXTURE_DATA	m_TextureData;	//�e�N�X�`���f�[�^

};
#endif