#pragma once
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include"main.h"	//���C���w�b�_�[
#include"scene.h"	//�V�[���t�@�C��
//----------------------------------------------
//�N���X
//----------------------------------------------
class CScene2d :public CScene
{
public:
	
	CScene2d(int nPriorit = 3);						//�R���X�g���N�^
	~CScene2d();					//�f�X�g���N�^
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//�e�N�X�`���̓ǂݍ��ݏ���
	static CScene2d*
		Create(D3DXVECTOR3 Pos);	//��������
	HRESULT Init(void);				//����������
	void	Uninit(void);			//�I������
	void	Update(void);			//�X�V����
	void	Draw(void);				//�`�揈��
	void	Set(D3DXVECTOR3 Pos);	//�ݒu�ʒu

	void	TextureAnim(D3DXVECTOR2 *Texture);	//�e�N�X�`���A�j���[�V����
	void	SetRotate(void);			//�|���S����]

	void	SetPosition(D3DXVECTOR3 pos) { m_posPolygon = pos; }		//�ʒu�ݒu
	D3DXVECTOR3 GetPosition(void) { return m_posPolygon; }				//�ʒu�擾


	void	SetSizeition(D3DXVECTOR3 size) { m_sizePolygon = size; }	//�T�C�Y�Z�b�g
	D3DXVECTOR3 GetSizeition(void) { return m_sizePolygon; }			//�T�C�Y�擾

	void	ColChange(D3DXCOLOR col);									//�J���[�Z�b�g

private:

	D3DXVECTOR3				m_posPolygon;	// �|���S���̈ʒu
	D3DXVECTOR3				m_sizePolygon;	// �|���S���̑傫��

	float					m_fLengthpos;	//���_�܂ł̒���	
	float					m_fAngle;		//���S���璸�_�܂ł̊p�x

	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

};