//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	model.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "model.h"

#include "inputkeyboard.h"
#include "inputmouse.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CModel::CModel()
{
    //���f���f�[�^�̏�����
    ZeroMemory(&m_ModelData, sizeof(m_ModelData));
    m_rotAnime      = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_posAnime      = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_pParentModel  = NULL;
    m_pParentObject = NULL;
    SetObjType(OBJTYPE_MODEL);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CModel::~CModel()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CModel::Init(void)
{
    CObject3D::Init();
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CModel::Uninit(void)
{
    CObject3D::Uninit();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CModel::Update(void)
{
    CObject3D::Update();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CModel::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DXMATRIX mtxRot, mtxTrans, mtxScale;
    D3DXMATRIX mtxParent;
    D3DMATERIAL9 matDef;
    D3DXMATERIAL* pMat;
    //���[���h�ϊ��s��̏�����
    D3DXMatrixIdentity(&m_ModelData.mtxWorld);

    //�g��k���s��̐����ƌv�Z
    D3DXMatrixScaling(&mtxScale, GetScale().x, GetScale().y, GetScale().z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);

    //��]�s��̐����ƌv�Z
    D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRotation().y, GetRotation().x, GetRotation().z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotAnime.y, m_rotAnime.x, m_rotAnime.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);

    //���s�ړ��s��̐����ƌv�Z
    D3DXMatrixTranslation(&mtxTrans, GetPosition().x, GetPosition().y, GetPosition().z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);
    D3DXMatrixTranslation(&mtxTrans, m_posAnime.x, m_posAnime.y, m_posAnime.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);

    if(m_pParentModel != NULL)
    {
        mtxParent = m_pParentModel->m_ModelData.mtxWorld;
        D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxParent);
    }

    //�v�Z���ʂ�K�p
    pDevice->SetTransform(D3DTS_WORLD, &m_ModelData.mtxWorld);

    //�}�e���A�����̎擾
    pDevice->GetMaterial(&matDef);
    if(m_ModelData.pBuffMat != NULL)
    {
        pMat = (D3DXMATERIAL*)m_ModelData.pBuffMat->GetBufferPointer();
    }

    //�}�e���A�����̐ݒ�ƃ}�e���A�����Ƃɕ`��
    for(int nCntMat = 0; nCntMat < (int)m_ModelData.nNumMat; nCntMat++)
    {
        pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
        pDevice->SetTexture(0, m_ModelData.pTexture[nCntMat]);
        m_ModelData.pMesh->DrawSubset(nCntMat);
    }
    //�}�e���A�����̃��Z�b�g
    pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 3D�I�u�W�F�N�g�̐���
//=============================================================================
CModel* CModel::Create(CModel* pParentModel, CObject* pParentObject, MODELDATA modeldata, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
    // �������̊m��
    CModel* pModel;
    pModel = new CModel;
    //�e����̐ݒ�
    pModel->SetPosition(pos);
    pModel->SetRotation(rot);
    pModel->SetScale(size);
    pModel->m_pParentModel  = pParentModel;
    pModel->m_ModelData     = modeldata;
    pModel->m_pParentObject = pParentObject;
    // ����������
    pModel->Init();

    return pModel;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���f���̊���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CModel::BindModel(MODELDATA modeldata)
{
    m_ModelData = modeldata;
}

CModel::MODELDATA CModel::GetModelData(void)
{
    return m_ModelData;
}

CObject* CModel::GetParentObject(void)
{
    return m_pParentObject;
}
