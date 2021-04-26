//=============================================================================
//
// �`���C���h���� [child.cpp]
// Author : ���V ����
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "child.h"
#include "manager.h"
#include "inputcontroller.h"
#include "inputkeyboard.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"
#include "game.h"
#include "player.h"
#include "item block base.h"
#include "stage1.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define OBJECT_FILE		("Data/Model/Player/player.x")	// �t�@�C����
#define OBJECT_HEIGHT   (50.0f)                             // ���� 

//=============================================================================
// �ÓI�����o�ϐ�������
//=============================================================================
CModel::MODELDATA CChild::m_modeldata = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CChild::CChild()
{
	//���f���f�[�^�̏�����
	SetObjType(OBJTYPE_PLAYER);
	m_model = NULL;
	m_modelPearent = NULL;
	m_bActive = false;
	m_bFlag = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CChild::~CChild()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CChild::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat = NULL;

	D3DXLoadMeshFromX(OBJECT_FILE, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

	if (m_modeldata.pBuffMat != NULL)
	{
		pMat = (D3DXMATERIAL *)m_modeldata.pBuffMat->GetBufferPointer();

		for (int nCountMat = 0; nCountMat < (int)m_modeldata.nNumMat; nCountMat++)
		{
			D3DXCreateTextureFromFile(pDevice, pMat[nCountMat].pTextureFilename, &m_modeldata.pTexture[nCountMat]);
		}
	}

	//���[���h�ϊ��s��̏�����
	D3DXMatrixIdentity(&m_modeldata.mtxWorld);

	return S_OK;
}

//=============================================================================
// ���f���j���֐�
//=============================================================================
void CChild::Unload(void)
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
CChild * CChild::Create(CModel* modelPearent, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CChild* pChild = NULL;
	pChild = new CChild;

	//NULL�`�F�b�N
	if (pChild != NULL)
	{
		//�ʒu�ݒ�
		pChild->SetPosition(D3DXVECTOR3(0.0f,OBJECT_HEIGHT, 0.0f));
		//�����ݒ�
		pChild->SetRotation(rot);
		//�J���[�ݒ�
		pChild->SetScale(size);
		// �e���f���̓o�^
		pChild->m_modelPearent = modelPearent;
		//����������
		pChild->Init();
	}

	return pChild;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CChild::Init(void)
{
	// ���f������
	m_model = new CModel;
	if (m_model != NULL)
	{
		m_model->SetPosition(GetPosition());
		m_model->SetRotation(GetRotation());
		m_model->SetScale(GetScale());
		m_model->Init();
	}

	SetPriority(PRIORITY_OBJECT_CHILD);
	m_model->SetPriority(PRIORITY_OBJECT_CHILD);

	m_bActive = false;

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CChild::Uninit(void)
{
	//NULL�`�F�b�N
	if (m_model != NULL)
	{
		m_model->Uninit();
	}

	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CChild::Update(void)
{
	// �A�C�e���Ƃ̓����蔻��
	if (!m_bActive && !CPlayer::GetPlayer()->IsActiveMove()) CollisionItem();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CChild::Draw(void)
{
	if (m_modelPearent != NULL)
	{// �e���f����NULL����Ȃ��Ƃ�

		//�f�o�C�X���̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		D3DXMATRIX mtxRot, mtxTrans, mtxScail;
		D3DMATERIAL9 matDef;	//���݂̃}�e���A���ێ��p
		D3DXMATERIAL*pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

		CModel::MODELDATA modelData = m_model->GetModelData();

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&modelData.mtxWorld);

		//�T�C�Y�𔽉f
		D3DXMatrixScaling(&mtxScail, m_model->GetScale().x, m_model->GetScale().y, m_model->GetScale().z);
		D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &mtxScail);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_model->GetRotation().y, m_model->GetRotation().x, m_model->GetRotation().z);
		D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_model->GetPosition().x, m_model->GetPosition().y, m_model->GetPosition().z);
		D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &mtxTrans);

		CModel::MODELDATA modelDataPearent = m_modelPearent->GetModelData();
		// �e�̃��[���h�}�g���b�N�X��������
		D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &modelDataPearent.mtxWorld);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &modelData.mtxWorld);

		//���݂̃}�e���A�����擾����
		pDevice->GetMaterial(&matDef);

		if (modelData.pBuffMat != NULL)
		{
			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)modelData.pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)modelData.nNumMat; nCntMat++)
			{
				//�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
				//pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �e�N�X�`��
				pDevice->SetTexture(0, modelData.pTexture[nCntMat]);
				//���f���p�[�c�̕`��
				modelData.pMesh->DrawSubset(nCntMat);
			}
		}

		m_model->SetModelData(modelData);
	}
}

////=============================================================================
//// �f�o�b�N����ŋ�����
////=============================================================================
//void CChild::FadeTalk(void)
//{
//	//if (CTalkbase::GetTalk() == CTalkbase::TALK_3)
//	//{
//	//	if (m_bFlag == true)
//	//	{
//	//		if (CStage1::GetTalkStage1() != nullptr)
//	//		{
//	//			CStage1::GetTalkStage1()->SetFlagTex(CTalkbase::TALK_4);
//	//		}
//	//	}
//	//}
//}



//=============================================================================
// �A�C�e���Ƃ̓����蔻��
//=============================================================================
void CChild::CollisionItem(void)
{
	// ���[���h���W�̎擾
	CModel::MODELDATA modelData = m_model->GetModelData();
	D3DXVECTOR3 worldPos = D3DXVECTOR3(modelData.mtxWorld._41, modelData.mtxWorld._42, modelData.mtxWorld._43);

	CItemBlockBase * pItem = (CItemBlockBase*)(GetTop()[PRIORITY_OBJECT_ITEM]);

	while (pItem != NULL)
	{
		// �A�C�e���̍��W�̎擾
		D3DXVECTOR3 itemPos = pItem->GetPosition();
		// �����̌v�Z
		float fDitanse = sqrtf(powf(itemPos.x - worldPos.x, 2) + powf(itemPos.y - worldPos.y, 2) + powf(itemPos.z - worldPos.z, 2));
		// ���̓����蔻��*���a�҂����肾�Ƃ�����ƃo�O��̂ŏ����߂ɔ�������(1.9f)
		if (fDitanse <= ITEM_HEIGHT *1.9f)
		{
			// �L���t���O�𗧂Ă�
			m_bActive = true;
			// �A�C�e���̃��f���f�[�^�����g�̃��f���f�[�^�ɓ����
			m_model->SetModelData(pItem->GetModel()->GetModelData());
			// �A�C�e���͏���
			pItem->Uninit();
			//�A�C�e���^�C�v�ɂȂ�
			SetObjType(OBJTYPE_ITEM);
			// ���[�v���甲����
			break;
		}
		pItem  = (CItemBlockBase*)(pItem->GetNext());
	}
}

