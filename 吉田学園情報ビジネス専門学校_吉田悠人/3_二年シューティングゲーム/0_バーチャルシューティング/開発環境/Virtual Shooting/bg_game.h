#ifndef _BG_GEAM_H_
#define _BG_GEAM_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define MAX_BG_GA 2
#define MAX_PATTERN 2	//�A�j���[�V�����̍ő喇��

//------------------------------------
//�N���X����
//------------------------------------
class CBgGame :public CScene2d
{
public:
	CBgGame(int nPriorit = 4);			//�R���X�g���N�^
	~CBgGame();							//�f�X�g���N�^

	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);	//�e�N�X�`���̔j��
	static CBgGame*	Create(void);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��

private:
	static LPDIRECT3DTEXTURE9	m_apTexture;					//�e�N�X�`���ւ̃|�C���^
	CScene2d					*m_apScene2D;					//2D�|���S���̐�
};
#endif