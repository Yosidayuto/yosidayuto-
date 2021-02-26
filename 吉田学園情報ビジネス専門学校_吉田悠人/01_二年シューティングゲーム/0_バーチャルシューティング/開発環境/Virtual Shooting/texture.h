
//=============================================================================
//	
//	�e�N�X�`��[texture.h]
//	�e�L�X�g�摜��UI�A�C�R���Ȃǂ̕\��
//	Author:�g�c�@�I�l
//
//=============================================================================
#ifndef  _TEXTURE_H
#define  _TEXTURE_H
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
//=============================================================================
// �O���錾
//=============================================================================
typedef struct
{
	LPDIRECT3DTEXTURE9	m_Texture;	// �e�N�X�`���ւ̃|�C���^
	char*				m_cFileName;// �t�@�C���̖��O
} TEXTURE_ICON;
//=============================================================================
// �N���X��`
//=============================================================================
class CTexture
{
public:
	CTexture();				// �R���X�g���N�^
	~CTexture();			// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void	Uninit(void);	// �I������
	void	Update(void);	// �X�V����
	void	Draw(void);		// �`�揈��

	void	SetPos(D3DXVECTOR3 pos);	// �ʒu�Z�b�^�[
	void	SetSize(D3DXVECTOR3 size);	// �T�C�Y�Z�b�^�[

	D3DXVECTOR3	GetPos(void);			// �ʒu�Q�b�^�[
	D3DXVECTOR3 GetSize(void);			// �T�C�Y�Q�b�^�[
	
	void	BindTexture(LPDIRECT3DTEXTURE9 pTexture);	// �e�N�X�`���̓ǂݍ��ݏ���
	void	TextureAnim(D3DXVECTOR2 *Texture);			// �e�N�X�`���A�j���[�V��������
private:
	LPDIRECT3DTEXTURE9			m_Texture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_pos;		// �ʒu
	D3DXVECTOR3					m_size;		// �T�C�Y

};
#endif