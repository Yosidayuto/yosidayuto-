//=============================================================================
//
// 2D�V�[�� [scene2d.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include"main.h"	//���C���w�b�_�[
#include"scene.h"	//�V�[���t�@�C��
//=============================================================================
// �O���錾
//=============================================================================
typedef struct
{
	LPDIRECT3DTEXTURE9	m_Texture;	// �e�N�X�`���ւ̃|�C���^
	char*				m_cFileName;// �t�@�C���̖��O
} TEXTURE_DATA;

//=============================================================================
//�N���X��`
//=============================================================================
class CScene2d :public CScene
{
public:
	
	CScene2d(int nPriorit = 3);					//�R���X�g���N�^
	~CScene2d();								//�f�X�g���N�^
	static CScene2d*	Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const float frot, const LPDIRECT3DTEXTURE9 pTexture, const int nPriority);    // �|���S����������
	HRESULT Init(void);							//����������
	void	Uninit(void);						//�I������
	void	Update(void);						//�X�V����
	void	Draw(void);							//�`�揈��
	

	void	SetPos(D3DXVECTOR3 pos); 	//�ʒu�ݒu
	void	SetRot(float frot);			//�����ݒ�
	void	SetSize(D3DXVECTOR3 size);	//�T�C�Y�Z�b�g
	void	SetCol(D3DXCOLOR col);		//�J���[�Z�b�g

	D3DXVECTOR3 GetPos(void);			//�ʒu�擾
	D3DXVECTOR3 GetSize(void);			//�T�C�Y�擾
	float		GetRot(void);			//�����擾
	D3DXCOLOR	GetCol(void);			//�J���[�擾

	void	BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//�e�N�X�`���̓ǂݍ��ݏ���
	void	TextureAnim(D3DXVECTOR2 *Texture);			//�e�N�X�`���A�j���[�V����
private:
	LPDIRECT3DTEXTURE9		m_Texture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_size;			// �|���S���̑傫��
	D3DCOLOR				m_col;			// �|���S���̃J���[
	float					m_fRot;			// �|���S���̌���
};
#endif
