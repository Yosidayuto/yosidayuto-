//=============================================================================
//
// ���\�[�X�}�l�[�W���[ [reource manager.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "renderer.h"
#include "resource manager.h"
#include <stdio.h>
#include "model.h"

#include "stage1.h"
#include "stage2.h"
#include "stage3.h"

#include "sea.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_DATA ("Data/Text/TextureData.csv")
#define MODEL_DATA ("Data/Text/ModelData.csv")

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResource::CResource()
{
	m_nMaxTexture	= 0;
	m_nMaxModel		= 0;
	m_npTexture		= NULL;
	m_npModel		= NULL;
	m_pTexture		= NULL;
	m_pModel		= NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResource::~CResource()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResource::Init(void)
{
	//�e�N�X�`�����[�h
	TextureFail();
	//���f���t�@�C�����[�h
	XFail();
	//�C�f�[�^���[�h
	CSea::Load();

	//�}�b�v�ǂݍ���
	CStage1::Load();
	CStage2::Load();
	CStage3::Load();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResource::Uninit(void)
{
	//�e�N�X�`���A�����[�h
	TextureUnLoad();
	//���f���A�����[�h
	ModelUnLoad();
	//�C�f�[�^�A�����[�h
	CSea::Unload();

}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
LPDIRECT3DTEXTURE9 CResource::TextureLoad(int nTexture)
{
	for (int nCountTexture = 0; nCountTexture < m_nMaxTexture; nCountTexture++)
	{
		//�e�N�X�`���ԍ�����v������
		if (m_npTexture[nCountTexture] == nTexture)
		{
			return m_pTexture[nCountTexture];
		}
	}
	return NULL;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CResource::TextureUnLoad(void)
{
	for (int nTexture = 0; nTexture < m_nMaxTexture; nTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nTexture] != NULL)
		{
			m_pTexture[nTexture]->Release();
			m_pTexture[nTexture] = NULL;
		}
	}
}

//=============================================================================
// �e�N�X�`���f�[�^�ǂݍ���
//=============================================================================
void CResource::TextureFail(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�t�@�C���|�C���^
	FILE*	pFile = NULL;
	//�ǂݍ��ݗp�f�[�^
	char cFileString[258];
	char aData[256] = {};
	//�s
	int nRow = 0;
	//������
	memset(cFileString, 0, sizeof(cFileString));

	//�t�@�C���ǂݍ���
	fopen_s(&pFile, TEXTURE_DATA, "r");

	if (pFile != NULL)
	{
		//�����ǂݍ���
		fscanf_s(pFile, "MAX_DATA,%d", &m_nMaxTexture);
		
		//�������m��
		m_npTexture = new int [m_nMaxTexture];
		m_pTexture = new LPDIRECT3DTEXTURE9 [m_nMaxTexture];
		//������
		for (int nTexture = 0; nTexture < m_nMaxTexture; nTexture++)
		{
			m_npTexture[nTexture] = NULL;
			m_pTexture[nTexture] = NULL;
		}

		//�s��ǂݔ�΂�
		while (fgetc(pFile) != '\n');

		while (fscanf(pFile, "%d,%[^,],%s\n", &m_npTexture[nRow], m_pcTextureName, aData) != EOF)
		{
			// �e�N�X�`���̐���
			D3DXCreateTextureFromFile(pDevice,
				m_pcTextureName,
				&m_pTexture[nRow]);
			//�s��i�߂�
			nRow++;
		}
		fclose(pFile);				//�t�@�C�������
	}

}

//=============================================================================
// ���f�����[�h
//=============================================================================
CModel::MODELDATA CResource::ModelLoad(int nModel)
{
	for (int nCountModel = 0; nCountModel < m_nMaxModel; nCountModel++)
	{
		//�e�N�X�`���ԍ�����v������
		if (m_npModel[nCountModel] == nModel)
		{
			return m_pModel[nCountModel];
		}
	}
	return CModel::MODELDATA();
}

//=============================================================================
// ���f���A�����[�h
//=============================================================================
void CResource::ModelUnLoad(void)
{
	for (int nCountModel = 0; nCountModel < m_nMaxModel; nCountModel++)
	{
		if (m_pModel[nCountModel].pBuffMat != NULL)
		{
			m_pModel[nCountModel].pBuffMat->Release();
		}

		if (m_pModel[nCountModel].pMesh != NULL)
		{
			m_pModel[nCountModel].pMesh->Release();
		}

		for (int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
		{
			if (m_pModel[nCountModel].pTexture[nCountTex] != NULL)
			{
				m_pModel[nCountModel].pTexture[nCountTex]->Release();
			}
		}

	}

}

//=============================================================================
// X�t�@�C���ǂݍ��݃t�@�C��
//=============================================================================
void CResource::XFail(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�t�@�C���|�C���^
	FILE*	pFile = NULL;
	//���f���e�N�X�`���p
	D3DXMATERIAL *pMat;
	//�ǂݍ��ݗp�f�[�^
	char cFileString[258];
	char aData[256] = {};
	//�s
	int nRow = 0;
	//������
	memset(cFileString, 0, sizeof(cFileString));

	//�t�@�C���ǂݍ���
	fopen_s(&pFile, MODEL_DATA, "r");

	if (pFile != NULL)
	{
		//�����ǂݍ���
		fscanf_s(pFile, "MAX_DATA,%d", &m_nMaxModel);

		//�������m��
		m_npModel = new int[m_nMaxModel];
		m_pModel = new CModel::MODELDATA[m_nMaxModel];
		//������
		for (int nModel = 0; nModel < m_nMaxModel; nModel++)
		{
			m_npModel[nModel] = NULL;
			ZeroMemory(&m_pModel[nModel], sizeof(m_pModel[nModel]));
		}

		//�s��ǂݔ�΂�
		while (fgetc(pFile) != '\n');

		while (fscanf(pFile, "%d,%[^,],%s\n", &m_npModel[nRow], m_pcTextureName, aData) != EOF)
		{
			// ���f���̐���
			D3DXLoadMeshFromX(m_pcTextureName,
				D3DXMESH_SYSTEMMEM, 
				pDevice,
				NULL,
				&m_pModel[nRow].pBuffMat,
				NULL, 
				&m_pModel[nRow].nNumMat,
				&m_pModel[nRow].pMesh);
			// ���f���̃e�N�X�`������
			if (m_pModel[nRow].pBuffMat != NULL)
			{
				pMat = (D3DXMATERIAL *)m_pModel[nRow].pBuffMat->GetBufferPointer();

				for (int nCountMat = 0; nCountMat < (int)m_pModel[nRow].nNumMat; nCountMat++)
				{
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCountMat].pTextureFilename,
						&m_pModel[nRow].pTexture[nCountMat]);
				}

			}

			//�s��i�߂�
			nRow++;
		}
		fclose(pFile);				//�t�@�C�������
	}

}

