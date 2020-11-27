//=============================================================================
//
// �v�Z���� [polygon.cpp]
// Author : �U�J �����Y
//
//=============================================================================

#include "polygon.h"
#include "tooth.h"
#include "manager.h"
#include "input_mouse.h"
#include "clean.h"
#include "game.h"
#include "communication.h"
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
int CPolygon::nCountTooth = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPolygon::CPolygon()
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apTooth[nCount] != NULL)
		{
			m_apTooth[nCount] = NULL;
		}
	}
	nCountTooth = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{
}

//=============================================================================
// �쐬����
//=============================================================================
CPolygon * CPolygon::Create(D3DXVECTOR3 size)
{
	CPolygon *pPolygon;
	//�C���X�^���X����
	pPolygon = new CPolygon;

	//����������
	if (pPolygon != NULL)
	{
		pPolygon->Init(size);
	}

	return pPolygon;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPolygon::Init(D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apTooth[nCount] == NULL)
		{
			//����5��,�E��5��,��10��
			if (nCount < 5)
			{															//�����m�̊Ԋu	�@X��											 �@Y��
				m_apTooth[nCount] = CTooth::Create(D3DXVECTOR3(nCount + (50 * nCount) + 390.0f, -5 * ((nCount*nCount) - (5 * nCount) + 9) + 395.0f, 0.0f), size);	//���j���㕔�� (U���^)
			}
			else if (nCount >= 5 && nCount < 10)
			{
				m_apTooth[nCount] = CTooth::Create(D3DXVECTOR3((nCount - 5) + (50 * (nCount - 5)) + 680.0f, -4 * (((nCount - 5)*(nCount - 5)) - (3 * (nCount - 5)) + 9) + 405.0f, 0.0f), size);	//���j�E�㕔�� (U���^)
			}
			else if (nCount >= 10 && nCount < MAX_NUMBER)
			{
				m_apTooth[nCount] = CTooth::Create(D3DXVECTOR3((nCount - 10) + (50 * (nCount - 10)) + 410.0f, -3 * ((nCount - 10)*(nCount - 10) - (9 * (nCount - 10)) + 30.0f) + 580.0f, 0.0f), D3DXVECTOR3(80.0f, 65.0f, 0.0f)); //���j������ U���^
				m_apTooth[nCount]->SetRotation(180);
			}
			nCountTooth += 1;
		}
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPolygon::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apTooth[nCount] != NULL)
		{
			m_apTooth[nCount]->Uninit();
			m_apTooth[nCount] = NULL;
		}
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPolygon::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CPolygon::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apTooth[nCount] != NULL)
		{
			m_apTooth[nCount]->Draw();
		}
	}
}

//=============================================================================
// �^�b�`����
//=============================================================================
int CPolygon::Touch(void)
{
	//�}�E�X�擾
	CInhMouse *pMouse = CManager::GetMouse();

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apTooth[nCount] != NULL)
		{
			D3DXVECTOR3 MousePos = D3DXVECTOR3(pMouse->GetMousePos().x, pMouse->GetMousePos().y, 0.0f);

			m_pos = m_apTooth[nCount]->GetPosition();
			if (MousePos.x >= m_pos.x - (TEXTURE_WIDTH / 2) &&
				MousePos.x < m_pos.x + (TEXTURE_WIDTH / 2) &&
				MousePos.y >= m_pos.y - (TEXTURE_HEIGHT / 2) &&
				MousePos.y < m_pos.y + (TEXTURE_HEIGHT / 2))
			{
				if (pMouse->GetClickTrigger(0) == true)
				{
					CClean::Create(D3DXVECTOR3(100, 100, 100))->SetPosition(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f));
					m_apTooth[nCount]->Color();
					nCountTooth -= 1;
					return nCount;
				}
			}
		}
	}
	return 0;
}

//=============================================================================
// �J���[����
//=============================================================================
void CPolygon::TouchCol(int nTooth)
{
	m_apTooth[nTooth]->Color();
}



