//=============================================================================
//
// �ؔ� [woodenbox.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "woodenbox.h"
#include "manager.h"
#include "renderer.h"
//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
CModel::MODELDATA CWoodenBox::m_modeldata = {};
D3DXMATERIAL * CWoodenBox::m_pMat = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWoodenBox::CWoodenBox()
{
	m_pModel = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetObjType(OBJTYPE_OBSTACLE);					//�I�u�W�F�N�g�^�C�v�ݒ�
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWoodenBox::~CWoodenBox()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CWoodenBox::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("Data/Model/woodenbox.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

	m_pMat = (D3DXMATERIAL *)m_modeldata.pBuffMat->GetBufferPointer();

	for (int nCountMat = 0; nCountMat < (int)m_modeldata.nNumMat; nCountMat++)
	{
		D3DXCreateTextureFromFile(pDevice, m_pMat[nCountMat].pTextureFilename, &m_modeldata.pTexture[nCountMat]);
	}
	return S_OK;
}

//=============================================================================
// ���f���j���֐�
//=============================================================================
void CWoodenBox::Unload(void)
{
	if (m_modeldata.pBuffMat != NULL)
	{
		m_modeldata.pBuffMat->Release();
	}

	if (m_modeldata.pMesh != NULL)
	{
		m_modeldata.pMesh->Release();
	}

	for (int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
	{
		if (m_modeldata.pTexture[nCountTex] != NULL)
		{
			m_modeldata.pTexture[nCountTex]->Release();
		}
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CWoodenBox * CWoodenBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CWoodenBox* pWoodenBox = NULL;
	pWoodenBox = new CWoodenBox;
	pWoodenBox->m_pos = pos;
	pWoodenBox->m_rot = rot;
	pWoodenBox->m_size = size;
	pWoodenBox->Init();

	return pWoodenBox;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CWoodenBox::Init(void)
{
	//���f������
	m_pModel = CModel::Create(NULL, this, m_modeldata, m_pos, m_rot, m_size);
	SetCollisionBullet(true);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CWoodenBox::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
	}
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CWoodenBox::Update(void)
{
}

//=============================================================================
// �`��֐�
//=============================================================================
void CWoodenBox::Draw(void)
{
}

//=============================================================================
// �ʒu�擾�֐�
//=============================================================================
D3DXVECTOR3 CWoodenBox::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �����擾�֐�
//=============================================================================
D3DXVECTOR3 CWoodenBox::GetRot(void)
{
	return m_rot;
}
