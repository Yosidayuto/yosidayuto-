//=============================================================================
//	
//	�e�N�X�`��[texture.cpp]
//	�e�L�X�g�摜��UI�A�C�R���Ȃǂ̕\��
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CTexture::CTexture()
{
	m_Texture = NULL;
	memset(m_pos, 0, sizeof(m_pos));
	memset(m_size, 0, sizeof(m_size));
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTexture::Init(void)
{
	//���_���ւ̃|�C���^�[
	VERTEX_2D *pVtx;
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,			//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				//(�Œ�)
		FVF_VERTEX_2D,					//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				//�i�Œ�j
		&m_pVtxBuff,					//�ϐ������ς��ƕύX���K�v
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_����ݒ�
	pVtx[0].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)m_size.y / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)m_size.y / 2, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_����ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);    //a�͓����x
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);    //a�͓����x
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);    //a�͓����x
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);    //a�͓����x

														//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTexture::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CTexture::Update(void)
{
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�X�V
	pVtx[0].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)m_size.y / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)m_size.y / 2, 0.0f);

	m_pVtxBuff->Unlock();


}

//=============================================================================
// �`�揈��
//=============================================================================
void CTexture::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=============================================================================
// �ʒu�Z�b�^�[����
//=============================================================================
void CTexture::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �T�C�Y�Z�b�^�[����
//=============================================================================
void CTexture::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �ʒu�Q�b�^�[����
//=============================================================================
D3DXVECTOR3 CTexture::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �T�C�Y�Q�b�^�[����
//=============================================================================
D3DXVECTOR3 CTexture::GetSize(void)
{
	return m_size;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
void CTexture::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//�e�N�X�`���̊��蓖��
	m_Texture = pTexture;
}

//=============================================================================
// �e�N�X�`���A�j���[�V�����֐�
//=============================================================================
void CTexture::TextureAnim(D3DXVECTOR2 * Texture)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�f�[�^�����b�N

	pVtx[0].tex = Texture[0];
	pVtx[1].tex = Texture[1];
	pVtx[2].tex = Texture[2];
	pVtx[3].tex = Texture[3];

	m_pVtxBuff->Unlock();						//���_�f�[�^���A�����b�N����

}
