#ifndef _Bakground_H_
#define _Bakground_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene.h"
#include "manager.h"
//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define MAX_BG 2
#define MAX_PATTERN 2	//�A�j���[�V�����̍ő喇��

//----------------------------------------------
//�O�u����
//----------------------------------------------
class CScene2d;
//------------------------------------
//�N���X����
//------------------------------------
class CBg :public CScene
{
public:
	CBg(int nPriorit = 1);			//�R���X�g���N�^
	~CBg();							//�f�X�g���N�^

	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);	//�e�N�X�`���̔j��
	static CBg*		Create(void);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��

private:

	static LPDIRECT3DTEXTURE9	m_apTexture[MAX_BG];	//�e�N�X�`���ւ̃|�C���^
	CScene2d					*m_apScene2D[MAX_BG];	//2D�|���S���̐�
	typedef struct
	{
		D3DXVECTOR3			m_Pos;			//�ʒu
		D3DXVECTOR3			m_Size;			//�T�C�Y
	}DATA;
	static char			*m_dTexture[MAX_BG];			//�e�N�X�`����
	static DATA		m_Data[MAX_BG];					//�w�i�f�[�^
	int					m_nCounterAnim;					//�A�j���[�V�����J�E���^�[
	int					m_nPatternAnim[MAX_PATTERN];	//�A�j���[�V�����p�^�[��No
};
#endif