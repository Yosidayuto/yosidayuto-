//=============================================================================
//
//	�e���b�v[telop.h]
//	Author:�g�c�@�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "telop.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "telop tutorial.h"
#include "telop life.h"
#include "telop speed.h"
#include "telop bullet.h"
#include "telop laser.h"
#include "telop homing.h"

//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CTelop::m_TextureData = {NULL,"data/TEXTURE/Telop.png" };

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CTelop::CTelop(int nPriorit) :CScene2d(nPriorit)
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_pTelop = NULL;
	m_TelopType = TELOP_TYPE_TUTORIAL;
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CTelop::~CTelop()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CTelop::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, 
		m_TextureData.m_cFileName, 
		&m_TextureData.m_Texture);
	//�e���b�v���[�h
	TelopLoad();
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CTelop::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
	//�e���b�v�A�����[�h
	TelopUnload();
}

//=============================================================================
//��������
//=============================================================================
CTelop * CTelop::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CTelop *pTelopBer = NULL;
	pTelopBer = new CTelop;
	
	//NULL�`�F�b�N
	if (pTelopBer != NULL)
	{
		//�ʒu
		pTelopBer->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 425, 25, 0.0f));
		//�T�C�Y
		pTelopBer->SetSize(D3DXVECTOR3(850, 50, 0.0f));
		//�e�N�X�`���ݒ�
		pTelopBer->BindTexture(m_TextureData.m_Texture);
		//����������
		pTelopBer->Init();

	}
	return pTelopBer;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CTelop::Init(void)
{
	//����������
	CScene2d::Init();
	//�e���b�v����
	m_pTelop = CTelopTutorial::Create(GetPos(), GetSize());
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CTelop::Uninit(void)
{
	CScene2d::Uninit();
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CTelop::Update(void)
{
	CScene2d::Update();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CTelop::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// �e���b�v�ؑ֏���
//=============================================================================
TELOP_TYPE CTelop::GetTelopType(void)
{
	return m_TelopType;
}

//=============================================================================
// �e���b�v�ؑ֏���
//=============================================================================
void CTelop::TypeChange(TELOP_TYPE Type)
{
	//���݂̃e���b�v�I������
	if (m_pTelop!=NULL)
	{
		m_pTelop->Uninit();
		m_pTelop = NULL;
	}

	//�^�C�v�ύX
	m_TelopType = Type;

	//�e���b�v����
	switch (m_TelopType)
	{
	case TELOP_TYPE_TUTORIAL:
		m_pTelop = CTelopTutorial::Create(GetPos(), GetSize());
		break;
	case TELOP_TYPE_LIFEUP:
		m_pTelop = CTelopLife::Create(GetPos(),GetSize());
		break;
	case TELOP_TYPE_SPEEDUP:
		m_pTelop = CTelopSpeed::Create(GetPos(), GetSize());
		break;
	case TELOP_TYPE_BUTTOL:
		m_pTelop = CTelopBullet::Create(GetPos(), GetSize());
		break;
	case TELOP_TYPE_LASER:
		m_pTelop = CTelopLaser::Create(GetPos(), GetSize());
		break;
	case TELOP_TYPE_HOMING:
		m_pTelop = CTelopHoming::Create(GetPos(), GetSize());
		break;
	}
}
//=============================================================================
// �e���b�v���[�h����
//=============================================================================
void CTelop::TelopLoad(void)
{
	CTelopTutorial::Load();
	CTelopLife::Load();
	CTelopSpeed::Load();
	CTelopBullet::Load();
	CTelopLaser::Load();
	CTelopHoming::Load();
}

//=============================================================================
// �e���b�v�A�����[�h����
//=============================================================================
void CTelop::TelopUnload(void)
{
	CTelopTutorial::Unload();
	CTelopLife::Unload();
	CTelopSpeed::Unload();
	CTelopBullet::Unload();
	CTelopLaser::Unload();
	CTelopHoming::Unload();
}
