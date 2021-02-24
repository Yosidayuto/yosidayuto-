//=============================================================================
//
//	�Q�[���X�N���[���w�i[game scroll bg.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _GAME_SCROLL_BG_H_
#define _GAME_SCROLL_BG_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "bg.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CGameScrollBg :public CBgc
{
public:
	CGameScrollBg(int nPriorit = PRIORITY_BG_0);//�R���X�g���N�^
	~CGameScrollBg();							//�f�X�g���N�^

	static HRESULT			Load(void);		//�e�N�X�`���ǂݍ���
	static void				Unload(void);	//�e�N�X�`���̔j��
	static CGameScrollBg*	Create(void);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��

private:
	static TEXTURE_DATA	m_TextureData;	//�e�N�X�`���f�[�^

};
#endif