//=============================================================================
//�w�b�_�[�t�@�C��
//=============================================================================
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{
}
//=============================================================================
//�e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CNumber::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &m_pTexture);
	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CNumber::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//��������
//=============================================================================
CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CNumber *pNumber=NULL;
	pNumber = new CNumber;
	
	//NULL�`�F�b�N
	if (pNumber != NULL)
	{
		//�ʒu�ݒ�
		pNumber->pos = pos;
		//�T�C�Y�ݒ�
		pNumber->size = size;
		//����������
		pNumber->Init();

	}
	return pNumber;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CNumber::Init(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&m_pVtxBuff,//�ϐ������ς��ƕύX���K�v
		NULL);
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(-size.x / 2 + pos.x, -size.y / 2 + pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size.x / 2 + pos.x, -size.y / 2 + pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x / 2 + pos.x, size.y / 2 + pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size.x / 2 + pos.x, size.y / 2 + pos.y, 0.0f);

	// ���_����ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
	CNumber::SetNumber(0);

	return S_OK;

}

//=============================================================================
//�I������
//=============================================================================
void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CNumber::Update(void)
{
}

//=============================================================================
//�`�揈��
//=============================================================================
void CNumber::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=============================================================================
//�Z�b�g����
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�f�[�^�����b�N

	pVtx[0].tex = D3DXVECTOR2(0.0f+(0.1f* nNumber), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f+(0.1f* nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f+(0.1f* nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f+(0.1f* nNumber), 1.0f);

	m_pVtxBuff->Unlock();						//���_�f�[�^���A�����b�N����

}

//=============================================================================
// �J���[�`�F���W����
//=============================================================================
void CNumber::ColChange(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�f�[�^�����b�N

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();						//���_�f�[�^���A�����b�N����
}
