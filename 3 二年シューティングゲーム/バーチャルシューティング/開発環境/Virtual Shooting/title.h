#ifndef _TITLE_H_
#define _TITLE_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene.h"
//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define MAX_TITLE 1
#define MAX_PATTERN 2		//�A�j���[�V�����̍ő喇��

//----------------------------------------------
//�O�u����
//----------------------------------------------
class CScene2d;
//------------------------------------
//�N���X����
//------------------------------------
class CTitle :public CScene
{
public:
	CTitle();							//�R���X�g���N�^
	~CTitle();							//�f�X�g���N�^

	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);	//�e�N�X�`���̔j��
	static CTitle	*Create(void);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��

private:

	static LPDIRECT3DTEXTURE9	m_apTexture[MAX_TITLE];	//�e�N�X�`���ւ̃|�C���^
	CScene2d					*m_apScene2D[MAX_TITLE];	//2D�|���S���̐�
	
	//typedef struct
	//{
	//	D3DXVECTOR3				m_Pos;			//�ʒu
	//	D3DXVECTOR3				m_Size;			//�T�C�Y
	//}DATA;
	//static	DATA				m_Data[MAX_TITLE];	//�|���S���f�[�^
	
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	int							m_nCounterAnim;			//�A�j���[�V�����J�E���^�[
	int							m_nPatternAnim[MAX_PATTERN];			//�A�j���[�V�����p�^�[��No
	bool						m_bFade;
};



#endif