#ifndef _TELOP_TEXT_H_
#define _TELOP_TEXT_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene.h"
//----------------------------------------------
//�}�N����`
//----------------------------------------------

//----------------------------------------------
//�O�u����
//----------------------------------------------
class CScene2d;
//------------------------------------
//�N���X����
//------------------------------------
class CTelopText :public CScene
{
public:
	typedef enum  //�e�L�X�g���
	{
		TEXT_TYPE_TUTORIAL = 0,		//�`���[�g���A��
		TEXT_TYPE_LIFE,				//���C�t
		TEXT_TYPE_SPEED,			//�X�s�[�h
		TEXT_TYPE_BULLET,			//�o���b�g
		TEXT_TYPE_LASER,			//���[�U�[
		TEXT_TYPE_HOMING,			//�z�[�~���O
		TEXT_TYPE_MAX
	}TEXT_TYPE;


	CTelopText(int nPriorit = 4);					//�R���X�g���N�^
	~CTelopText();									//�f�X�g���N�^
	static HRESULT	Load(void);						//�e�N�X�`���ǂݍ���
	static void		Unload(void);					//�e�N�X�`���̔j��
	static CTelopText	*Create(void);	//��������
	HRESULT			Init(void);						//����������
	void			Uninit(void);					//�I������
	void			Update(void);					//�X�V����
	void			Draw(void);						//�`�揈��
	void			TypeChange(TEXT_TYPE Type);		//�e�L�X�g�ύX
	TEXT_TYPE		GetType(void) { return m_Type; }
private:
	static LPDIRECT3DTEXTURE9	m_apTexture[TEXT_TYPE_MAX];		//�e�N�X�`���ւ̃|�C���^
	static char					*m_pText[TEXT_TYPE_MAX];		//�e�L�X�g�l�[��
	CScene2d					*m_apScene2D;					//2D�|���S���̐�
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;						//���_�o�b�t�@�ւ̃|�C���^
	int							m_nCounterAnim;					//�A�j���[�V�����J�E���^�[
	int							m_nPatternAnim;					//�A�j���[�V�����p�^�[��No
	TEXT_TYPE					m_Type;							//�^�C�v
	D3DXVECTOR3					m_pos;							//�ʒu
};
#endif