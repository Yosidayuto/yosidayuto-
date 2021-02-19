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
CScene* CScene::m_pTop[PRIORITY_MAX] = {};
CScene* CScene::m_pCur[PRIORITY_MAX] = {};


//=============================================================================
//�R���X�g���N�g
//=============================================================================
CScene::CScene(int nPriority)
{
	//����������
	m_bDestroy = false;
	//���X�g�\���ɒǉ�
	m_nPriority = nPriority;
	if (m_pTop[nPriority] != NULL)
	{
		m_pCur[nPriority]->m_pNext = this;
	}
	else
	{
		m_pTop[nPriority] = this;
	}
	this->m_pPrev		= m_pCur[nPriority];
	this->m_pNext		= NULL;
	m_pCur[nPriority]	= this;

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
	CScene* pNext = NULL;
	CScene* pNextBuff = NULL;
	int ObjectCount = 0;
	//���X�g�Ɋ܂܂��I�u�W�F�N�g���X�V
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//NULL�`�F�b�N
		if (m_pTop[nCount] != NULL)
		{
			pNext = m_pTop[nCount];
			//NULL�`�F�b�N
			while (pNext != NULL && !pNext->m_bDestroy)
			{
				pNextBuff = pNext->m_pNext;
				pNext->Update();
				pNext = pNextBuff;
				ObjectCount++;
			}
		}
	}

	//���S�t���O�����Ă�������
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//NULL�`�F�b�N
		if (m_pTop[nCount] != NULL)
		{
			pNext = m_pTop[nCount];
			//NULL�`�F�b�N
			while (pNext != NULL)
			{
				pNextBuff = pNext->m_pNext;
				if (pNext->m_bDestroy == true)
				{
					pNext->Death();
				}
				pNext = pNextBuff;
			}
		}
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	CScene* pNext = NULL;
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//NULL�`�F�b�N
		if (m_pTop[nCount] != NULL)
		{
			pNext = m_pTop[nCount];
			while (pNext != NULL)
			{
				pNext->Draw();
				pNext = pNext->m_pNext;
			}
		}
	}
}

//=============================================================================
//�S�J������
//=============================================================================
void CScene::ReleaseAll(void)
{
	CScene* pNext = NULL;
	CScene* pNextBuff = NULL;
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//NULL�`�F�b�N
		if (m_pTop[nCount] != NULL)
		{
			pNext = m_pTop[nCount];
			while (pNext != NULL)
			{
				pNextBuff = pNext->m_pNext;
				pNext->Uninit();
				delete pNext;
				pNext = pNextBuff;
			}
		}
		m_pTop[nCount] = NULL;
		m_pCur[nCount] = NULL;
	}
}

//=============================================================================
//�Z�b�g�^�C�v ���[�h����
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}
//=============================================================================
//�^�C�v�Q�b�g����
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
//�I�u�W�F�N�g�g�b�v�Q�b�^�[
//=============================================================================
CScene** CScene::GetTop(void)
{
	return m_pTop;
}

//=============================================================================
// ���̃I�u�W�F�N�g�Q�b�^�[
//=============================================================================
CScene* CScene::GetNext(void)
{
	return m_pNext;
}

//=============================================================================
// �O�̃I�u�W�F�N�g�Q�b�^�[
//=============================================================================
CScene* CScene::GetPrev(void)
{
	return m_pPrev;
}

//=============================================================================
//�V�[���j������
//=============================================================================
void CScene::Release(void)
{
	//���S�t���O�𗧂Ă�
	m_bDestroy = true;
}

//=============================================================================
//���X�g����������Ď��g�������鏈��
//=============================================================================
void CScene::Death(void)
{
	//������Ƃ��̏���
	if (this == m_pTop[m_nPriority])
	{
		m_pTop[m_nPriority] = m_pNext;
	}
	if (this == m_pCur[m_nPriority])
	{
		m_pCur[m_nPriority] = m_pPrev;
	}
	if (m_pNext != NULL)
	{
		m_pNext->m_pPrev = m_pPrev;
	}
	if (m_pPrev != NULL)
	{
		m_pPrev->m_pNext = m_pNext;
	}
	delete this;
}


