//----------------------------------
//�w�b�_�t�@�C��
//----------------------------------
#include "life.h"		//���C�t�t�@�C��
#include "scene2d.h"	//�V�[���QD�i2D�|���S���j�t�@�C��
#include "manager.h"	//�}�l�[�W���[�t�@�C��
#include "renderer.h"	//�����_�����O�t�@�C��	
#include "ui.h"			//UI�t�@�C��
//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define LIFE_SIZE_X (200.0f,20.0f)
#define LIFE_SIZE_Y 30.0f

//----------------------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------------------
LPDIRECT3DTEXTURE9 CLife::m_apTexture = NULL;

//----------------------------------
//�R���X�g���N�^
//----------------------------------
CLife::CLife(int nPriorit) :CScene(nPriorit)
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	nLife = 0;
}

//----------------------------------
//�f�X�g���N�^
//----------------------------------
CLife::~CLife()
{
}

//----------------------------------
//�e�N�X�`���ǂݍ��ݏ���
//----------------------------------
HRESULT CLife::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Life_UI.png", &m_apTexture);
	return S_OK;

}

//----------------------------------
//�e�N�X�`���j������
//----------------------------------
void CLife::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_apTexture != NULL)
	{
		m_apTexture->Release();
		m_apTexture = NULL;
	}
}

//----------------------------------
//��������
//----------------------------------
CLife * CLife::Create(D3DXVECTOR3 pos)
{
	CLife *pLife;
	pLife = new CLife;
	pLife->SetPos(pos);			//���C�t�̈ʒu
	pLife->Init();
	return pLife;
}

//----------------------------------
//����������
//----------------------------------
HRESULT CLife::Init(void)
{
	for (int nCount = 0; nCount < MAX_LIFE; nCount++)
	{
		//�������m��
		m_apScene2D[nCount] = new CScene2d(PRIORIT_LIFE);
		//�ʒu
		m_apScene2D[nCount]->SetPosition(D3DXVECTOR3((nCount*LIFE_SIZE_X + LIFE_SIZE_X/2)+ pos.x,(pos.y - LIFE_SIZE_Y / 2),0.0f));
		//�T�C�Y
		m_apScene2D[nCount]->SetSizeition(D3DXVECTOR3(LIFE_SIZE_X, LIFE_SIZE_Y, 0.0f));
		//����������
		m_apScene2D[nCount]->CScene2d::Init();
		//�e�N�X�`���̐ݒ�
		m_apScene2D[nCount]->BindTexture(m_apTexture);
	}
	m_Ui = CUi::Create(D3DXVECTOR3(LIFE_SIZE_X*(MAX_LIFE/2)+ pos.x, pos.y - LIFE_SIZE_Y / 2,0.0f), D3DXVECTOR3(LIFE_SIZE_X*(MAX_LIFE*1.5), LIFE_SIZE_Y*1.5,0.0f), CUi::TEXTURE_TYPE_LIFE);
	return S_OK;

}

//----------------------------------
//�I������
//----------------------------------
void CLife::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_LIFE; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount]->CScene2d::Uninit();
		}
	}
	if (m_Ui != NULL)
	{
		m_Ui->Uninit();
	}
	Release();
}

//----------------------------------
//�X�V����
//----------------------------------
void CLife::Update(void)
{

}

//----------------------------------
//�`�揈��
//----------------------------------
void CLife::Draw(void)
{
	if (m_Ui != NULL)
	{
		m_Ui->Draw();
	}

	for (int nCount = 0; nCount < nLife; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount]->CScene2d::Draw();
		}
	}

}

void CLife::SetLife(int nLifeNumber)
{
	nLife = nLifeNumber;
}

void CLife::SetPos(D3DXVECTOR3 Lifepos)
{
	pos = Lifepos;
}

void CLife::DownLife(int nLifeDown)
{
	nLife -= nLifeDown;
}
