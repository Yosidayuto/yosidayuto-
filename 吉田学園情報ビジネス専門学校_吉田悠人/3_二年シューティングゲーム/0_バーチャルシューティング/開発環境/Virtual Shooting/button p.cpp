//=============================================================================
//
//	�{�^���i���j[button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "button p.h"
#include "renderer.h"
#include "manager.h"
#include "inputmouse.h"
#include "scene2d.h"
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CButtonp::m_TextureData[BUTTON_MAX] =
{	NULL,"data/TEXTURE/buttonA.png",
	NULL,"data/TEXTURE/buttonC_over.png"	};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CButtonp::CButtonp(int nPriorit)
{
	m_pScene2d = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CButtonp::~CButtonp()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CButtonp::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCountBotton = 0; nCountBotton<BUTTON_MAX; nCountBotton++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			m_TextureData[nCountBotton].m_cFileName,
			&m_TextureData[nCountBotton].m_pTexture);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CButtonp::Unload(void)
{
	for (int nCountBotton = 0; nCountBotton < BUTTON_MAX; nCountBotton++)
	{
		//�e�N�X�`���̔j��
		if (m_TextureData[nCountBotton].m_pTexture != NULL)
		{
			m_TextureData[nCountBotton].m_pTexture->Release();
			m_TextureData[nCountBotton].m_pTexture = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CButtonp::Init(void)
{
	//�ʒu�ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z);
	//�T�C�Y�ݒ�
	D3DXVECTOR3 size = D3DXVECTOR3(GetSize().x, GetSize().y, GetSize().z);

	m_pScene2d = CScene2d::Create(pos, size,0.0f, m_TextureData[BUTTON_NORMAL].m_pTexture,1);
	//�I�u�W�F�N�g2D������
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CButtonp::Uninit(void)
{
	//�I�u�W�F�N�g2D�I��
	CScene2d::Uninit();
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CButtonp::Update(void)
{
	//�I�u�W�F�N�g2D�X�V
	CScene2d::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CButtonp::Draw(void)
{
	//�I�u�W�F�N�g2D�`��
	CScene2d::Draw();
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
bool CButtonp::Hit(void)
{
	//�}�E�X�|�C���^�擾
	CInihMouse *pMouse = CManager::GetMouse();	
	//�}�E�X�ʒu�擾
	D3DXVECTOR3 MousePos = D3DXVECTOR3((float)pMouse->GetMousePos().x, (float)pMouse->GetMousePos().y, 0.0f);
	//�{�^���ʒu�擾
	D3DXVECTOR3 ButtonPos = m_pScene2d->GetPos();
	//�{�^���T�C�Y�擾
	D3DXVECTOR3 ButtonSize = m_pScene2d->GetSize();
	//����
	bool		bButton;

	//�����蔻��
	if (MousePos.x > ButtonPos.x - ButtonSize.x / 2
		&& MousePos.x  < ButtonPos.x + ButtonSize.x / 2
		&& MousePos.y > ButtonPos.y - ButtonSize.y / 2
		&& MousePos.y < ButtonPos.y + ButtonSize.y / 2)
	{
		//����������
		m_pScene2d->BindTexture(m_TextureData[BUTTON_PUSH].m_pTexture);
		bButton = true;
	}
	else
	{
		//�������ĂȂ��Ƃ�
		m_pScene2d->BindTexture(m_TextureData[BUTTON_NORMAL].m_pTexture);
		bButton = false;
	}
	return bButton;
}
