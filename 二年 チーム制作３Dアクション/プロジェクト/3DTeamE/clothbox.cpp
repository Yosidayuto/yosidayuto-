//=============================================================================
//
// �z�t�������� [clothbox.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "clothbox.h"
#include "manager.h"
#include "renderer.h"
//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
CModel::MODELDATA CClothBox::m_modeldata = {};
D3DXMATERIAL * CClothBox::m_pMat = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CClothBox::CClothBox()
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
CClothBox::~CClothBox()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CClothBox::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("Data/Model/clothbox.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

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
void CClothBox::Unload(void)
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
CClothBox * CClothBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CClothBox* pClothBox = NULL;
	pClothBox = new CClothBox;
	pClothBox->m_pos = pos;
	pClothBox->m_rot = rot;
	pClothBox->m_size = size;
	pClothBox->Init();

	return pClothBox;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CClothBox::Init(void)
{
	//���f������
	m_pModel = CModel::Create(NULL, this, m_modeldata, m_pos, m_rot, m_size);
	SetCollisionBullet(true);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CClothBox::Uninit(void)
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
void CClothBox::Update(void)
{
}

//=============================================================================
// �`��֐�
//=============================================================================
void CClothBox::Draw(void)
{
}

//=============================================================================
// �ʒu�擾�֐�
//=============================================================================
D3DXVECTOR3 CClothBox::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �����擾�֐�
//=============================================================================
D3DXVECTOR3 CClothBox::GetRot(void)
{
	return m_rot;
}
