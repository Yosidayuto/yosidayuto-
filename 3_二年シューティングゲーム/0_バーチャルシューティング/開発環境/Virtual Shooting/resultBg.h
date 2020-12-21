#ifndef _RESULT_BG_H_
#define _RESULT_BG_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene2d.h"
//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define MAX_BG_GA 2
#define MAX_PATTERN 2	//�A�j���[�V�����̍ő喇��

//------------------------------------
//�N���X����
//------------------------------------
class CResultBg :public CScene2d
{
public:
	CResultBg(int nPriorit = 5);			//�R���X�g���N�^
	~CResultBg();							//�f�X�g���N�^

	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);	//�e�N�X�`���̔j��
	static CResultBg*	Create(void);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��

private:
	static LPDIRECT3DTEXTURE9	m_apTexture;					//�e�N�X�`���ւ̃|�C���^
	CScene2d					*m_apScene2D;					//2D�|���S���̐�
};
#endif