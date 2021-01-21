#ifndef  _TEXT_H
#define  _TEXT_H
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene2d.h"

//----------------------------------------------
//�}�N����`
//----------------------------------------------

//------------------------------------
//�N���X����
//------------------------------------
class CText
{
public:

	CText();		//�R���X�g���N�^
	~CText();		//�f�X�g���N�^
	typedef enum
	{
		TEXT_START = 0,
		TEXT_START_LAST,
		TEXT_LIFE,
		TEXT_SPEED,
		TEXT_BULLET,
		TEXT_LASER,
		TEXT_HOMING,
		TEXT_MAX
	}TEXT_TYPE;

	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);	//�e�N�X�`���̔j��
	static CText*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size , TEXT_TYPE Text);	//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXT_TYPE Text);				//����������
	void	Uninit(void);			//�I������
	void	Update(void);			//�X�V����
	void	Draw(void);				//�`�揈��
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[TEXT_MAX];		//�e�N�X�`���ւ̃|�C���^
	static char						*m_cTexture[TEXT_MAX];		//�e�N�X�`����
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^
	TEXT_TYPE						m_Type;						//�^�C�v
};




#endif