//=============================================================================
//
// �Z���N�g���� [select.cpp]
// Author : �g�c �I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "select.h"		
#include "select bg.h"	
#include "fade.h"
#include "sound.h"
#include "inputmouse.h"
#include "select pointer.h"
#include "player data.h"
#include "button manager.h"
#include "ui count.h"
#include "telop.h"	
#include "weapon manager.h"
#include "score.h"		
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
CScore * CSelect::m_pScore = NULL;
CScore * CSelect::m_pMinusScore = NULL;
CTelop * CSelect::m_pTelop = NULL;
CUiCount *CSelect::Number[MAX_NUMBER]=
{
	NULL,NULL
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSelect::CSelect()
{
	ZeroMemory(Number, sizeof(Number));
	m_pTelop		= NULL;
	m_pMinusScore	= NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSelect::~CSelect()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSelect::Init(void)
{
	CSound*	pSound = CManager::GetSound();	//�T�E���h�擾
	//�T�E���h�Đ�
	pSound->Play(CSound::LABEL_BGM_SELECT);

	//�ǉ��}�E�X�J�[�\����\��
	ShowCursor(false);
	//�N���G�C�g����
	//�{�^������
	CButtonManager::Create();
	//�E�F�|���A�C�R��
	CWeaponManager::Create(D3DXVECTOR3(1000, 400, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	//�e���b�v����
	m_pTelop=CTelop::Create(D3DXVECTOR3(SCREEN_WIDTH - 425, 25, 0.0f), D3DXVECTOR3(850, 50, 0.0f));
	//�w�i����
	CSelectBg::Create();
	//�X�R�A
	m_pScore = CScore::Create(D3DXVECTOR3(35.0f, 585.0f, 0.0f), D3DXVECTOR3(25.0f, 35.0f, 0.0f), true);
	m_pScore->AddScore(CManager::GetScore());
	//�}�C�i�X�X�R�A
	m_pMinusScore = CScore::Create(D3DXVECTOR3(35.0f, 500.0f, 0.0f), D3DXVECTOR3(25.0f, 35.0f, 0.0f), true);
	m_pMinusScore->ColChange(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));
	//�}�E�X�|�C���^
	CSelectPointer::Create();
	
	//�i���o�[�Z�b�g
	Number[NUMBER_TYPE_LIEF] = CUiCount::Create(D3DXVECTOR3(580.0f, 225.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f));
	Number[NUMBER_TYPE_LIEF]->SetCount(CManager::GetPlayer()->GetLifeData());
	Number[NUMBER_TYPE_SPEED] = CUiCount::Create(D3DXVECTOR3(580.0f, 465.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f));
	Number[NUMBER_TYPE_SPEED]->SetCount(((int)(CManager::GetPlayer()->GetSpeedData())));

	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void CSelect::Uninit(void)
{
	//�T�E���h�擾
	CSound*	pSound = CManager::GetSound();
	//�T�E���h��~
	pSound->Stop();
	//�V�[���j��
	CScene::ReleaseAll();

}

//=============================================================================
// �X�V����
//=============================================================================
void CSelect::Update(void)
{

}

//=============================================================================
// �`��֐�
//=============================================================================
void CSelect::Draw(void)
{
}

//=============================================================================
// �i���o�[�Q�b�^�[
//=============================================================================
CUiCount * CSelect::GetNumber(NUMBER_TYPE NumberType)
{
	return Number[NumberType];
}

//=============================================================================
// �X�R�A�Q�b�^�[�Q�b�^�[
//=============================================================================
CScore * CSelect::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
//�@�}�C�i�X�X�R�A�Q�b�^�[
//=============================================================================
CScore * CSelect::GetMinusScore(void)
{
	return m_pMinusScore;
}

//=============================================================================
// �e���b�v�Q�b�^�[
//=============================================================================
CTelop * CSelect::GetTelop(void)
{
	return m_pTelop;
}


