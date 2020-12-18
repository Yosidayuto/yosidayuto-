//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "text.h"
#include "manager.h"
#include "renderer.h"
//----------------------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------------------
LPDIRECT3DTEXTURE9 CText::m_pTexture[TEXT_MAX] = {};
char * CText::m_cTexture[TEXT_MAX]=
{
	"data/TEXTURE/Text_Start.png",
	"data/TEXTURE/Text_Start_Last.png",
	"data/TEXTURE/Text_Life.png",
	"data/TEXTURE/Text_Speed.png",
	"data/TEXTURE/Text_Bullet.png",
	"data/TEXTURE/Text_Laser.png",
	"data/TEXTURE/Text_Homing.png",

};
//------------------------------------
//�R���X�g���N�^
//------------------------------------
CText::CText()
{
	m_pVtxBuff = NULL;
	
}

//------------------------------------
//�f�X�g���N�^
//------------------------------------
CText::~CText()
{
}

//------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------
HRESULT CText::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	for (int nCount = 0; nCount < TEXT_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_cTexture[nCount], &m_pTexture[nCount]);
	}
	return S_OK;
}

//------------------------------------
//�e�N�X�`���̔j��
//------------------------------------
void CText::Unload(void)
{
	for (int nCount = 0; nCount < TEXT_MAX; nCount++)
	{
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
CText * CText::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXT_TYPE Text)
{
	CText *pText;
	pText = new CText;
	pText->Init(pos, size, Text);
	return pText;
}

//------------------------------------
//����������
//------------------------------------
HRESULT CText::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXT_TYPE Text)
{
	m_Type = Text;
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
void CText::Uninit(void)
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
void CText::Update(void)
{
}

//------------------------------------
//�`�揈��
//------------------------------------
void CText::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture[m_Type]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}
