 //=============================================================================
//
//	stagenumber�w�b�_ [stagenumber.cpp]
//	Author : ����@�r�H
//
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "stagenumber.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_PATH_STAGENUMBER_1 "Data/Texture/stage/stage1.png"
#define TEXTURE_PATH_STAGENUMBER_2 "Data/Texture/stage/stage2.png"
#define TEXTURE_PATH_STAGENUMBER_3 "Data/Texture/stage/stage3.png"

//=============================================================================
// �ÓI�����o�ϐ��錾������
//=============================================================================
LPDIRECT3DTEXTURE9 CStageNumber::m_apTexture[STAGE_NUM_MAX] = {};

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
CStageNumber::CStageNumber()
{

}

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
CStageNumber::~CStageNumber()
{
}

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
CStageNumber * CStageNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, STAGE_NUM type)
{
	// �������̊m��
	CStageNumber * pStageNumber = new CStageNumber;

	if (pStageNumber != NULL)
	{
		// ���W��set
		pStageNumber->SetPos(pos);
		// �T�C�Y��set
		pStageNumber->SetSize(size);
		// �e�N�X�`���w��
		pStageNumber->BindTexture(m_apTexture[type]);
		// ����������
		pStageNumber->Init();
	}

	return pStageNumber;
}

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
HRESULT CStageNumber::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_STAGENUMBER_1, &m_apTexture[STAGE_NUM_1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_STAGENUMBER_2, &m_apTexture[STAGE_NUM_2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_STAGENUMBER_3, &m_apTexture[STAGE_NUM_3]);

	return S_OK;
}

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
void CStageNumber::Unload(void)
{
	for (int nCount = STAGE_NUM_1; nCount < STAGE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
HRESULT CStageNumber::Init()
{
	CUi::Init();
	return S_OK;
}

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
void CStageNumber::Uninit(void)
{
	CUi::Uninit();
}

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
void CStageNumber::Update(void)
{
	CUi::Update();
}

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
void CStageNumber::Draw(void)
{
	CUi::Draw();
}
