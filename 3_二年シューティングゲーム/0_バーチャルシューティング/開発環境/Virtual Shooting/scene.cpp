//=============================================================================
// �w�b�_�t�@�C��
//=============================================================================
#include "scene.h"
#include <typeinfo.h>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "manager.h"
#include "inputmouse.h"
#include "inihkeyboard.h"

//=============================================================================
//�ÓI�����o�[�ϐ��錾
//=============================================================================
CScene * CScene::m_apScene[MAX_DRAW][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;
bool CScene::bPause = true;
//CPause * CScene::m_pPause = NULL;
//=============================================================================
//�R���X�g���N�g
//=============================================================================
CScene::CScene(int nPriorit)
{
	for (int nCutScene = 0; nCutScene < MAX_SCENE; nCutScene++)
	{
		if (m_apScene[nPriorit][nCutScene] == NULL)
		{
			m_nID = nCutScene;
			m_apScene[nPriorit][nCutScene] = this;
			m_nPiority= nPriorit;
			m_nNumAll++;
			break;
		}
	}

}
//=============================================================================
//�f�X�g���N�g
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
//�X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCut = 0; nCut < MAX_DRAW; nCut++)
	{
		for (int nCutScene = 0; nCutScene < MAX_SCENE; nCutScene++)
		{
			if (m_apScene[nCut][nCutScene] != NULL && typeid(*m_apScene[nCut][nCutScene]) != typeid(CScene2d))
			{
				m_apScene[nCut][nCutScene]->Update();
			}
		}
	}
}
//=============================================================================
//�`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCut = 0; nCut < MAX_DRAW; nCut++)
	{
		for (int nCutScene = 0; nCutScene < MAX_SCENE; nCutScene++)
		{
			if (m_apScene[nCut][nCutScene] != NULL && typeid(*m_apScene[nCut][nCutScene]) != typeid(CScene2d))
			{
				m_apScene[nCut][nCutScene]->Draw();
			}
		}
	}
}

//=============================================================================
//�I������
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCut = 0; nCut < MAX_DRAW; nCut++)
	{
		for (int nCutScene = 0; nCutScene < MAX_SCENE; nCutScene++)
		{
			if (m_apScene[nCut][nCutScene] != NULL)
			{
				m_apScene[nCut][nCutScene]->Uninit();	
			}
		}
	}
}

//=============================================================================
//�Z�b�g�^�C�v ���[�h����
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_nType = objType;
}

//=============================================================================
//�^�C�v�Q�b�g����
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_nType;
}

//=============================================================================
//�V�[���Q�b�g����
//=============================================================================
CScene * CScene::GetScene(int nPriorty, int nCntScene)
{
	return m_apScene[nPriorty][nCntScene];
}

//=============================================================================
//�V�[���j������
//=============================================================================
void CScene::Release(void)
{
		if (m_apScene[m_nPiority][m_nID] != NULL)
		{
			int nID = m_nID;
			int nPiority = m_nPiority;
			delete m_apScene[nPiority][nID];
			m_apScene[nPiority][nID] = NULL;
			m_nNumAll--;
		}

}