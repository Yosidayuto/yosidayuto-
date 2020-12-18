#ifndef  _BUTTON_H
#define  _BUTTON_H
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene2d.h"
//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define MAX_BUTTON_TEXTURE 2
//------------------------------------
//�O�u����
//------------------------------------
class CUi;
class CText;
class CNumber;
//------------------------------------
//�N���X����
//------------------------------------
class CButton :public CScene2d
{
public:
	CButton(int nPriorit = 3);			//�R���X�g���N�^
	~CButton();			//�f�X�g���N�^
	typedef enum
	{
		BUTTON_TYPE_1 = 0,
		BUTTON_TYPE_2,
		BUTTON_TYPE_3,
		BUTTON_TYPE_4,
		BUTTON_TYPE_5,
		BUTTON_TYPE_6,
		BUTTON_TYPE_MAX

	}BUTTON_TYPE;

	static CButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int m_Type);	//��������
	static HRESULT	Load(void);				//�e�N�X�`���ǂݍ���
	static void		Unload(void);			//�e�N�X�`���̔j��


	HRESULT Init(void);		//����������
	void	Uninit(void);	//�I������
	void	Update(void);	//�X�V����
	void	Draw(void);		//�`�揈��

private:
	typedef enum  //�{�^���e�N�X�`�����
	{
		BUTTON_TYPE_TEXTURE_1 = 0,
		BUTTON_TYPE_TEXTURE_2,
		BUTTON_TYPE_TEXTURE_MAX
	}BUTTON_TYPE_TEXTURE;
	/*�\����*/
	typedef struct
	{
		char				*pTexture;			//�{�^���e�L�X�g��
		char				*pTextureOver;		//�{�^���I�[�o�[�e�L�X�g��
		LPDIRECT3DTEXTURE9	m_Texture;			//�e�N�X�`���̃|�C���^
		LPDIRECT3DTEXTURE9	m_TextureOver;		//�e�N�X�`��(�I�[�o�[)�̃|�C���^
	}BUTTON_DATA;

	static BUTTON_DATA			ButtonData[BUTTON_TYPE_TEXTURE_MAX];
	static BUTTON_TYPE_TEXTURE	TypeTextureData[BUTTON_TYPE_MAX];
	bool						Hit(D3DXVECTOR3 pos, int nType);	//�����蔻��
	static int					nCountSpeed;
	D3DXVECTOR3			m_pos;					//�ʒu
	D3DXVECTOR3			m_size;					//�T�C�Y
	BUTTON_TYPE			m_Type;					//�^�C�v
	bool				m_Text;
	CNumber				*m_pNumber;				//�i���o�[
	CText				*m_pText;				//�e�L�X�g
	CUi					*m_pUi;					//UI
};
#endif