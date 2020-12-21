#ifndef _WINDOW_H_
#define _WINDOW_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include"main.h"
#include"scene2d.h"
//------------------------------------
//�O�u����
//------------------------------------
class CButton;
class CScore;
//----------------------------------------------
//�N���X
//----------------------------------------------
class CWindow :public CScene2d
{
public:

	CWindow(int nPriorit = 4);			//�R���X�g���N�^
	~CWindow();						//�f�X�g���N�^	
	typedef enum
	{
		WINDOW_TYPE_SELECT = 0,
		WINDOW_TYPE_MAX
	}WINDOW_TYPE;

	static CWindow*	Create(D3DXVECTOR3 Pos, D3DXVECTOR3 size, WINDOW_TYPE Type);//��������
	static HRESULT	Load(void);			//�e�N�X�`���ǂݍ���
	static void		Unload(void);		//�e�N�X�`���̔j��

	HRESULT			Init(void);			//����������
	void			Uninit(void);		//�I������
	void			Update(void);		//�X�V����
	void			Draw(void);			//�`�揈��
	bool			Window(void);				
private:
	static char					*m_pcTexture[WINDOW_TYPE_MAX];		//�e�L�X�g��
	static LPDIRECT3DTEXTURE9	m_Texture[WINDOW_TYPE_MAX];			//�e�N�X�`���̃|�C���^
	static bool					m_Window[WINDOW_TYPE_MAX];			//�g�p��
	D3DXVECTOR3					m_pos;				//�E�B���h�E���W
	D3DXVECTOR3					m_size;				//�E�B���h�E�T�C�Y
};
#endif
