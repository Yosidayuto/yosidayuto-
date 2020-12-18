//=============================================================================
//
// ���̃e�N�X�`������ [tooth.cpp]
// Author : �U�J �����Y
//
//=============================================================================
#include "ui.h"
#include "manager.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CUi::m_pTexture[TEX_MAX] = {};
char *CUi::m_TextureName[TEX_MAX] =
{
	UI_TEXTURE_LOAD,
	UI_TEXTURE_DOG,
	UI_TEXTURE_CAT,
	UI_TEXTURE_USAGI,
	UI_TEXTURE_RISU,
	UI_TEXTURE_1P,
	UI_TEXTURE_2P,
	UI_TEXTURE_3P,
	UI_TEXTURE_4P,
	UI_TEXTURE_YOUTRUN,
	UI_TEXTURE_WAIT,
	UI_TEXTURE_DEATH,
	UI_TEXTURE_WINS_1P,
	UI_TEXTURE_WINS_2P,
	UI_TEXTURE_WINS_3P,
	UI_TEXTURE_WINS_4P,
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CUi::CUi()
{
	m_bBig = false;
	m_bLoad = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CUi::~CUi()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CUi::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		//�e�N�X�`��
		D3DXCreateTextureFromFile(pD3DDevice, m_TextureName[nCount], &m_pTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CUi::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//=============================================================================
// UI�쐬����
//=============================================================================

CUi * CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXTYPE TYPE)
{
	CUi *pUi;
	//�C���X�^���X����
	pUi = new CUi;

	//����������
	if (pUi != NULL)
	{
		pUi->GetTexType(TYPE);
		pUi->Init(pos, size);
	}
	return pUi;
}

CUi::TEXTYPE CUi::GetTexType(TEXTYPE TYPE)
{
	TexType = TYPE;
	return TexType;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{

	BindTexture(m_pTexture[TexType]);

	//����������
	CScene2D::Init(size);
	m_pos = pos;
	//�ʒu�ݒ�
	SetPosition(m_pos);
	//�T�C�Y���ۑ�
	m_size = size;
	m_Minsize = size;

	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void CUi::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CUi::Update(void)
{
	if (TexType == TEX_DEATH)
	{
		if (!m_bBig)
		{
			m_size = D3DXVECTOR3(m_Minsize.x * 3, m_Minsize.y * 3, 0.0f);
			m_bBig = true;
		}
		else
		{
			//�T�C�Y������������
			m_size += D3DXVECTOR3(-3.0f, -3.0f, 0.0f);

			//�T�C�Y���k�����~�߂�
			if (m_size.x <= m_Minsize.x && m_size.y <= m_Minsize.y)
			{
				m_size = m_Minsize;
			}
		}

		//�T�C�Y�X�V
		CScene2D::SetSize(m_size);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CUi::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ���[�hUI�̏���
//=============================================================================
void CUi::LoadPos(void)
{
	D3DXVECTOR3 LoadUiPos = GetPosition();
	if (m_bLoad == false)
	{
		if (LoadUiPos.y <= m_pos.y + 15.0f)
		{
			LoadUiPos.y += 0.4f;
			SetPosition(LoadUiPos);
		}
		else
		{
			m_bLoad = true;
		}
	}
	else
	{
		if (LoadUiPos.y >= m_pos.y)
		{
			LoadUiPos.y -= 0.5f;
			SetPosition(LoadUiPos);
		}
		else
		{
			m_bLoad = false;
		}
	}

}

