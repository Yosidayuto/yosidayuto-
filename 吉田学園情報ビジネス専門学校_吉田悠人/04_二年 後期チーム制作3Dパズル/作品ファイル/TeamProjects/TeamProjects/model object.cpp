//=============================================================================
//
//	���f���I�u�W�F�N�g[model object.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "model object.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModelObject::CModelObject()
{
	//���f���f�[�^�̏�����
	SetObjType(OBJTYPE_NONE);
	ZeroMemory(&m_ModelData, sizeof(m_ModelData));

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModelObject::~CModelObject()
{

}

//=============================================================================
// ��������
//=============================================================================
CModelObject * CModelObject::Create(MODELDATA Data, CObject * pParentObject, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// �������̊m��
	CModelObject* pModelObje = NULL;
	pModelObje = new CModelObject;

	if (pModelObje != NULL)
	{
		//�e����̐ݒ�
		pModelObje->SetPosition(pos);
		pModelObje->SetRotation(rot);
		pModelObje->SetScale(size);
		pModelObje->m_ModelData = Data;
		// ����������
		pModelObje->Init();
	}

	return pModelObje;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CModelObject::Init(void)
{
	CModel::Init();
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CModelObject::Uninit(void)
{
	CModel::Uninit();
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CModelObject::Update(void)
{
}

//=============================================================================
//�`�揈��
//=============================================================================
void CModelObject::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�s��v�Z�p
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	//���[���h�ϊ��s��̏�����
	D3DXMatrixIdentity(&m_ModelData.mtxWorld);

	//�g��k���s��̐����ƌv�Z
	D3DXMatrixScaling(&mtxScale, GetScale().x, GetScale().y, GetScale().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);

	//��]�s��̐����ƌv�Z
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRotation().y, GetRotation().x, GetRotation().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);

	//���s�ړ��s��̐����ƌv�Z
	D3DXMatrixTranslation(&mtxTrans, GetPosition().x, GetPosition().y, GetPosition().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);
	
	//�v�Z���ʂ�K�p
	pDevice->SetTransform(D3DTS_WORLD, &m_ModelData.mtxWorld);

	SetModelData(m_ModelData);

	//�`�揈��
	CModel::Draw();
}
