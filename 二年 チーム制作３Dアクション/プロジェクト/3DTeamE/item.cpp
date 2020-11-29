//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	item.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "item.h"

#include "inputkeyboard.h"
#include "inputmouse.h"
#include "main.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CModel::MODELDATA CItem::m_modelData = {};

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CItem::CItem()
{
    m_fFrameCounter = 0;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CItem::~CItem()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CItem::Init(void)
{
    CModel::Init();
    //���f���̊���
    BindModel(m_modelData);
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Uninit(void)
{
    //���f���̔j��
    CModel::Uninit();
    Release();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Update(void)
{
    CPlayer* pPlayer      = NULL;
    pPlayer               = CManager::GetPlayer();
    D3DXVECTOR3 playerPos = pPlayer->GetPos();
    //���������ɂӂ�ӂ킳���鏈��
    m_fFrameCounter += 0.05f;
    SetRotation(GetRotation() + D3DXVECTOR3(0, D3DXToRadian(1), 0));
    SetPosition(GetPosition() + D3DXVECTOR3(0, sinf(m_fFrameCounter) / 5, 0));
    CModel::Update();
    //��苗���܂ŋ߂Â�����A�C�e������肷�鏈��
    if(sqrt(pow(GetPosition().x - playerPos.x, 2.0f) + pow(GetPosition().z - playerPos.z, 2.0f)) < ITEM_OBTAIN_RANGE)
    {
        //���肵���Ƃ��̏���
		pPlayer->AddItem();
        Uninit();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Draw(void)
{
    CModel::Draw();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CItem* CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // �������̊m��
    CItem* pItem;
    pItem = new CItem;
    //�e����̐ݒ�
    pItem->SetPosition(pos);
    pItem->SetRotation(rot);
	pItem->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	// ����������
    pItem->Init();

    return pItem;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���f���ǂݍ���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DXLoadMeshFromX("Data\\Model\\Kaihuku.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modelData.pBuffMat, NULL, &m_modelData.nNumMat, &m_modelData.pMesh);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���f���j��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Unload(void)
{
    //���b�V���̔j��
    if(m_modelData.pMesh != NULL)
    {
        m_modelData.pMesh->Release();
    }
    //�}�e���A���̔j��
    if(m_modelData.pBuffMat != NULL)
    {
        m_modelData.pBuffMat->Release();
    }
}
