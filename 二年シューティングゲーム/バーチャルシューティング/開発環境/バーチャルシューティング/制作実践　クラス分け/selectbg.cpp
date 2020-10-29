//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "selectbg.h"	//�Z���N�g�w�i�t�@�C��
#include "scene2d.h"	//�V�[���QD�i2D�|���S���j�t�@�C��
#include "manager.h"	//�}�l�[�W���[�t�@�C��
#include "renderer.h"	//�����_�����O�t�@�C��	

//----------------------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------------------
LPDIRECT3DTEXTURE9 CSelectBg::m_apTexture[MAX_SELECT_BG] = {};
CSelectBg::SELECT_DATA CSelectBg::m_Data[MAX_SELECT_BG] =
{
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT , 0.0f) },
	{ D3DXVECTOR3(SCREEN_WIDTH /2+150, SCREEN_HEIGHT / 2, 0.0f),D3DXVECTOR3(SCREEN_WIDTH-320, SCREEN_HEIGHT -220, 0.0f) },
};
char *CSelectBg::m_dTexture[MAX_SELECT_BG] =
{
	"data/TEXTURE/background_Select.png",
	"data/TEXTURE/Select_status.png",
};

//------------------------------------
//�R���X�g���N�^
//------------------------------------
CSelectBg::CSelectBg(int nPriorit) :CScene(nPriorit)
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//------------------------------------
//�f�X�g���N�^
//------------------------------------
CSelectBg::~CSelectBg()
{
}

//------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------
HRESULT CSelectBg::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	for (int nCont = 0; nCont < MAX_SELECT_BG; nCont++)
	{
		D3DXCreateTextureFromFile(pDevice, m_dTexture[nCont], &m_apTexture[nCont]);
	}
	return S_OK;
}

//------------------------------------
//�e�N�X�`���̔j��
//------------------------------------
void CSelectBg::Unload(void)
{
	for (int nCountBg = 0; nCountBg < MAX_SELECT_BG; nCountBg++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCountBg] != NULL)
		{
			m_apTexture[nCountBg]->Release();
			m_apTexture[nCountBg] = NULL;
		}
	}

}

//------------------------------------
//��������
//------------------------------------
CSelectBg * CSelectBg::Create(void)
{
	CSelectBg *pSelectBg;
	pSelectBg = new CSelectBg;
	pSelectBg->Init();
	return pSelectBg;
}

//------------------------------------
//����������
//------------------------------------
HRESULT CSelectBg::Init(void)
{
	for (int nCountBg = 0; nCountBg < MAX_SELECT_BG; nCountBg++)
	{
		//�������m��
		m_apScene2D[nCountBg] = new CScene2d(0);
		//�ʒu
		m_apScene2D[nCountBg]->SetPosition(m_Data[nCountBg].m_Pos);
		//�T�C�Y
		m_apScene2D[nCountBg]->SetSizeition(m_Data[nCountBg].m_Size);
		//����������
		m_apScene2D[nCountBg]->CScene2d::Init();
		//�e�N�X�`���̐ݒ�
		m_apScene2D[nCountBg]->BindTexture(m_apTexture[nCountBg]);
	}

	return S_OK;
}

//------------------------------------
//�I������
//------------------------------------
void CSelectBg::Uninit(void)
{
	for (int nCountBg = 0; nCountBg < MAX_SELECT_BG; nCountBg++)
	{
		if (m_apScene2D[nCountBg] != NULL)
		{
			m_apScene2D[nCountBg]->CScene2d::Uninit();
			m_apScene2D[nCountBg] = NULL;
		}
	}
	Release();
}

//------------------------------------
//�X�V����
//------------------------------------
void CSelectBg::Update(void)
{
	for (int nCountBg = 0; nCountBg < MAX_SELECT_BG; nCountBg++)
	{
		m_apScene2D[nCountBg]->CScene2d::Update();
	}

}

//------------------------------------
//�`�揈��
//------------------------------------
void CSelectBg::Draw(void)
{
	for (int nCountBg = 0; nCountBg < MAX_SELECT_BG; nCountBg++)
	{
		if (m_apScene2D[nCountBg] != NULL)
		{
			m_apScene2D[nCountBg]->CScene2d::Draw();
		}
	}

}
