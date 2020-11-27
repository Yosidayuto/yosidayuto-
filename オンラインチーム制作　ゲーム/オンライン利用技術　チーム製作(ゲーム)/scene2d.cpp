//=============================================================================
//
// �|���S��2D���� [scene2d.cpp]
// Author : �U�J �����Y
//
//=============================================================================
#include "scene2d.h"
#include "input_keyboard.h"
#include "manager.h"
//#include "sound.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_fAngle = 0;
	m_fAngle1 = 0;
	m_fDiagonal = 0;
	m_fChange = 0;
	m_fAdd = 0;
	m_fAngleChane = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D ::~CScene2D()
{
}

//=============================================================================
// �|���S���쐬����
//=============================================================================
CScene2D * CScene2D::Create(D3DXVECTOR3 size)
{
	CScene2D *pScene2D;
	//�C���X�^���X����
	pScene2D = new CScene2D;

	//����������
	if (pScene2D != NULL)
	{
		pScene2D->Init(size);
	}

	return pScene2D;
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 size)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//pD3DDevice=GetRenderer()->GetDevice();	//��ɂ܂Ƃ߂邱�Ƃ��ł���@

	// ���_�o�b�t�@�̐���
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//(�Œ�)
		&m_pVtxBuff,
		NULL);

	m_fDiagonal = sqrtf((size.x / 2)*(size.x / 2) + (size.y / 2)*(size.y / 2));
	m_fAngle = atan2f((size.y / 2), (size.x / 2));
	m_fAngle1 = atan2f((size.y / 2), (size.x / 2));
	m_fChange = 1.0f;
	m_fAdd = 0.01f;
	m_fAngleChane = 0.01f;


	m_size = size;

	// ���_����ݒ�
	VERTEX_2D*pVtx;

	//���_�f�[�^�͈̔͂����b�N�����_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�(�E���Őݒ肷��)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	//rhw�̐ݒ�(�l��1.0�ŌŒ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;
	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;

}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// �ݒu����
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// ���_����ݒ�
	VERTEX_2D*pVtx;

	//���_�f�[�^�͈̔͂����b�N�����_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�(�E���Őݒ肷��)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	//pVtx += 4;

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

}

//=============================================================================
// �e�N�X�`�����W�擾
//=============================================================================
void CScene2D::SetTexPosition(int nCount, float nPattern)
{
	// ���_����ݒ�
	VERTEX_2D*pVtx;

	//���_�f�[�^�͈̔͂����b�N�����_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(nCount*nPattern, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(nCount*nPattern + nPattern, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(nCount*nPattern, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(nCount*nPattern + nPattern, 1.0f);

	pVtx[0].tex = D3DXVECTOR2((nPattern) / nCount, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPattern + 1) / nCount, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nPattern) / nCount, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nPattern + 1) / nCount, 1.0f);


	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();


}


//=============================================================================
// �ʒu���擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// �e�N�X�`���̊��蓖��
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// �J���[���擾
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�f�[�^�����b�N
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	m_pVtxBuff->Unlock();						//���_�f�[�^���A�����b�N����
}

//=============================================================================
// �p�x���擾
//=============================================================================
void CScene2D::SetRotate(float fAngle)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�f�[�^�����b�N

	pVtx[0].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)*cosf(fAngle)), (m_pos.y - (m_size.y / 2)*sinf(fAngle)), 0);
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)*cosf(fAngle)), (m_pos.y - (m_size.y / 2)*sinf(fAngle)), 0);
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)*cosf(fAngle)), (m_pos.y + (m_size.y / 2)*sinf(fAngle)), 0);
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)*cosf(fAngle)), (m_pos.y + (m_size.y / 2)*sinf(fAngle)), 0);

	m_pVtxBuff->Unlock();						//���_�f�[�^���A�����b�N����

}

//=============================================================================
// �A�j���[�V�������擾
//=============================================================================
void CScene2D::SetAnimation(float nPattern, int nMaxAnimation)
{
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

	pVtx[0].tex = D3DXVECTOR2(nPattern*(1.0f / nMaxAnimation), 0);
	pVtx[1].tex = D3DXVECTOR2((nPattern *(1.0f / nMaxAnimation)) + (1.0f / nMaxAnimation), 0);
	pVtx[2].tex = D3DXVECTOR2(nPattern*(1.0f / nMaxAnimation), 1);
	pVtx[3].tex = D3DXVECTOR2((nPattern*(1.0f / nMaxAnimation)) + (1.0f / nMaxAnimation), 1);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �T�C�Y���擾
//=============================================================================
void CScene2D::SetSize(D3DXVECTOR3 size)
{
	// ���_����ݒ�
	VERTEX_2D*pVtx;

	//���_�f�[�^�͈̔͂����b�N�����_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�(�E���Őݒ肷��)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (size.x / 2), m_pos.y - (size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (size.x / 2), m_pos.y - (size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (size.x / 2), m_pos.y + (size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (size.x / 2), m_pos.y + (size.y / 2), 0.0f);

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}
