#ifndef _SELECTBG_H_
#define _SELECTBG_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene.h"
#include "manager.h"
//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define MAX_SELECT_BG 2
//----------------------------------------------
//�O�u����
//----------------------------------------------
class CScene2d;
//------------------------------------
//�N���X����
//------------------------------------
class CSelectBg :public CScene
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

	static LPDIRECT3DTEXTURE9	m_apTexture[MAX_SELECT_BG];	//�e�N�X�`���ւ̃|�C���^
	CScene2d					*m_apScene2D[MAX_SELECT_BG];	//2D�|���S���̐�
	typedef struct
	{
		D3DXVECTOR3			m_Pos;			//�ʒu
		D3DXVECTOR3			m_Size;			//�T�C�Y
	}SELECT_DATA;
	static char			*m_dTexture[MAX_SELECT_BG];			//�e�N�X�`����
	static SELECT_DATA		m_Data[MAX_SELECT_BG];					//�w�i�f�[�^
};
#endif