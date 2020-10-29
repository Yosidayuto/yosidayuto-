#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "scene2d.h"
#include "main.h"

//------------------------------------
//�O�u����
//------------------------------------
class CBossAnime;
class CBullet;
//----------------------------------------------
//�N���X
//----------------------------------------------
class CTutorial :public CScene2d
{
public:

	CTutorial(int nPriorit = 3);		//�R���X�g���N�^
	~CTutorial();						//�f�X�g���N�^	


	static HRESULT		Load(void);				//�e�N�X�`���ǂݍ���
	static void			Unload(void);			//�e�N�X�`���̔j��
	static CTutorial*	Create(void);//��������

	HRESULT			Init(void);						//����������
	void			Uninit(void);					//�I������
	void			Update(void);					//�X�V����
	void			Draw(void);						//�`�揈��

private:
	static char					*pTexture;		//�e�L�X�g��
	static LPDIRECT3DTEXTURE9	m_Texture;		//�e�N�X�`���̃|�C���^

	int							m_nCountTexture;	//�e�N�X�`���̌��݂̖���
};
#endif
