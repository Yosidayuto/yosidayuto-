//=============================================================================
//�w�b�_�[�t�@�C��
//=============================================================================
#include "score.h"		
#include "manager.h"	
#include "scene2d.h"	
#include "renderer.h"	
#include "number.h"		
#include "score bar.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_TEXTURE 10
#define NUMBER_SIZE_X (200.0f,20.0f)
#define NUMBER_SIZE_Y 45.0f

//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriorit) :CScene(nPriorit)
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_pScoreBar = NULL;
	UiSwitch = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScore::~CScore()
{

}
//=============================================================================
//��������
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, bool UI, PRIORITY priority)
{
	CScore *pScore;
	pScore = new CScore(priority);
	pScore->m_pos = pos;
	pScore->m_size = size;
	pScore->UiSwitch = UI;
	pScore->Init();
	return pScore;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CScore::Init()
{

	m_nScore = 0;
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create
		(D3DXVECTOR3(
			(nCount*m_size.x + m_size.x / 2) + m_pos.x,
			(m_pos.y + m_size.y /1.5f),
			0.0f),
			D3DXVECTOR3(m_size.x, m_size.y, 0.0f));
	}
	if (UiSwitch == true)
	{
		m_pScoreBar = CScoreBar::Create
		(D3DXVECTOR3(m_pos.x + (m_size.x*(float)(MAX_SCORE) / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f),
			D3DXVECTOR3(m_size.x*((float)(MAX_SCORE)*1.5f), m_size.y*1.5f, 0.0f));
	}

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Uninit();
		}
	}
	if (m_pScoreBar != NULL)
	{
		m_pScoreBar->Uninit();
	}

	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CScore::Update(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Update();
		}
	}
	if (m_pScoreBar != NULL)
	{
		m_pScoreBar->Update();
	}

}

//=============================================================================
//�`�揈��
//=============================================================================
void CScore::Draw(void)
{
	if (m_pScoreBar != NULL)
	{
		m_pScoreBar->Draw();
	}

	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Draw();

		}
	}


}

void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
	float fIndex;			//�w���@(�X�R�A�\���p)
	float fRadix = 10.0f;	//��@(�X�R�A�\���p)
	int nCount = 0;
	for (fIndex = 0; fIndex < MAX_SCORE; fIndex++)
	{
		int nScore = (int)powf(fRadix, MAX_SCORE - fIndex);
		int nScore2 = (int)powf(fRadix, MAX_SCORE - fIndex - 1);
		int nAnswer = m_nScore % nScore / nScore2;

		m_apNumber[(int)fIndex]->SetNumber(nAnswer);
	}
}

void CScore::ColChange(D3DXCOLOR col)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		m_apNumber[nCount]->ColChange(col);
	}
}

void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
	float fIndex;			//�w���@(�X�R�A�\���p)
	float fRadix = 10.0f;	//��@(�X�R�A�\���p)
	int nCount = 0;
	for (fIndex = 0; fIndex < MAX_SCORE; fIndex++)
	{
		int nScore = (int)powf(fRadix, MAX_SCORE - fIndex);
		int nScore2 = (int)powf(fRadix, MAX_SCORE - fIndex - 1);
		int nAnswer = m_nScore % nScore / nScore2;

		m_apNumber[(int)fIndex]->SetNumber(nAnswer);
	}
}

int CScore::GetScore(void)
{
	return m_nScore;
}
