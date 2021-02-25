//=============================================================================
//
// ��Q�� [obstacle.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "obstacle.h"
#include "manager.h"
#include "renderer.h"
//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
CModel::MODELDATA CObstacle::m_modeldata = {};
D3DXMATERIAL * CObstacle::m_pMat = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObstacle::CObstacle()
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
CObstacle::~CObstacle()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CObstacle::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("Data/Model/gareki.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

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
void CObstacle::Unload(void)
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
CObstacle * CObstacle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CObstacle* pObstacle = NULL;
	pObstacle = new CObstacle;
	pObstacle->m_pos = pos;
	pObstacle->m_rot = rot;
	pObstacle->m_size = size;
	pObstacle->Init();

	return pObstacle;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CObstacle::Init(void)
{
	//���f������
	m_pModel = CModel::Create(NULL, this, m_modeldata, m_pos, m_rot, m_size);
	SetCollisionBullet(true);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CObstacle::Uninit(void)
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
void CObstacle::Update(void)
{
}

//=============================================================================
// �`��֐�
//=============================================================================
void CObstacle::Draw(void)
{
}

//=============================================================================
// �ʒu�擾�֐�
//=============================================================================
D3DXVECTOR3 CObstacle::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �����擾�֐�
//=============================================================================
D3DXVECTOR3 CObstacle::GetRot(void)
{
	return m_rot;
}
