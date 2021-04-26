//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : �g�c �I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "score.h"		
#include "manager.h"	
#include "object2d.h"	
#include "renderer.h"	
#include "number.h"		
//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_TEXTURE 10
#define NUMBER_SIZE_X (200.0f,20.0f)
#define NUMBER_SIZE_Y 45.0f

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriorit) :CObject2D(nPriorit)
{
	//�^�C�v����
	CObject2D::SetObjType(CObject2D::OBJTYPE_NONE);
	m_nScore = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{

}
//=============================================================================
// ��������
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CScore *pScore = NULL;
	pScore = new CScore();

	if (pScore != NULL)
	{
		//�ʒu����
		pScore->SetPos(pos);
		//�T�C�Y����
		pScore->SetSize(size);
		//����������
		pScore->Init();
	}
	
	return pScore;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScore::Init()
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	//�i���o�[����
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create
		(D3DXVECTOR3(
			(nCount*size.x + size.x / 2) + pos.x,pos.y,0.0f),
			D3DXVECTOR3(size.x, size.y, 0.0f));
	}
	return S_OK;
}

//=============================================================================
// �I������
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

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScore::Update(void)
{
	//�i���o�[�̍X�V����
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Update();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScore::Draw(void)
{
	//�i���o�[�̕`�揈��
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Draw();

		}
	}


}

//=============================================================================
// �X�R�A�Z�b�^�[
//=============================================================================
void CScore::SetScore(int nScore)
{
	//���݂̃X�R�A
	m_nScore = nScore;
	//�w���@(�X�R�A�\���p)
	float fIndex;			
	//��@(�X�R�A�\���p)
	float fRadix = 10.0f;	

	for (fIndex = 0; fIndex < MAX_SCORE; fIndex++)
	{
		int nScore = (int)powf(fRadix, MAX_SCORE - fIndex);
		int nScore2 = (int)powf(fRadix, MAX_SCORE - fIndex - 1);
		int nAnswer = m_nScore % nScore / nScore2;
		m_apNumber[(int)fIndex]->SetNumber(nAnswer);
	}
}

//=============================================================================
// �J���[�`�F���W
//=============================================================================
void CScore::ColChange(D3DXCOLOR col)
{
	//�i���o�[�̃J���[�`�F���W
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		m_apNumber[nCount]->ColChange(col);
	}
}

//=============================================================================
// �X�R�A���Z
//=============================================================================
void CScore::AddScore(int nValue)
{
	//�X�R�A���Z
	m_nScore += nValue;
	//�w���@(�X�R�A�\���p)
	float fIndex;			
	//��@(�X�R�A�\���p)
	float fRadix = 10.0f;	

	for (fIndex = 0; fIndex < MAX_SCORE; fIndex++)
	{
		int nScore = (int)powf(fRadix, MAX_SCORE - fIndex);
		int nScore2 = (int)powf(fRadix, MAX_SCORE - fIndex - 1);
		int nAnswer = m_nScore % nScore / nScore2;
		m_apNumber[(int)fIndex]->SetNumber(nAnswer);
	}
}

//=============================================================================
// �X�R�A�Q�b�^�[
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}
