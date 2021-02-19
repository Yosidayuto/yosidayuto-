//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "ui.h"
#include "manager.h"
#include "renderer.h"

//----------------------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------------------
LPDIRECT3DTEXTURE9 CUi::m_pTexture[TEXTURE_TYPE_MAX] = {};
char * CUi::pTexture[TEXTURE_TYPE_MAX] =
{
	"data/TEXTURE/UI_score.png",
	"data/TEXTURE/UI_Life.png",
	"data/TEXTURE/UI_Bullet.png",
	"data/TEXTURE/UI_Laser.png",
	"data/TEXTURE/UI_Homing.png",
};
//------------------------------------
//�R���X�g���N�^
//------------------------------------
CUi::CUi()
{
	m_nTexture = NULL;
	m_pVtxBuff = NULL;
}

//------------------------------------
//�f�X�g���N�^
//------------------------------------
CUi::~CUi()
{
}

//------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------
HRESULT CUi::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < TEXTURE_TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, pTexture[nCount], &m_pTexture[nCount]);
	}
	return S_OK;
}

//------------------------------------
//�e�N�X�`���̔j��
//------------------------------------
void CUi::Unload(void)
{
	for (int nCount = 0; nCount < TEXTURE_TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{			  
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}

	}
}

//------------------------------------
//��������
//------------------------------------
CUi * CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTexture)
{
	CUi *pUi;
	pUi = new CUi;
	pUi->Init(pos, size, nTexture);
	return pUi;
}

//------------------------------------
//����������
//------------------------------------
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTexture)
{
	m_nTexture = nTexture;
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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;

}

//------------------------------------
//�I������
//------------------------------------
void CUi::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//------------------------------------
//�X�V����
//------------------------------------
void CUi::Update(void)
{
}

//------------------------------------
//�`�揈��
//------------------------------------
void CUi::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture[m_nTexture]);
	
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

