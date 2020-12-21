//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "manager.h"		//�}�l�[�W���[�t�@�C��
#include "renderer.h"		//�����_�����O�t�@�C��	
#include "scene2d.h"		//�V�[���QD�i2D�|���S���j�t�@�C��
#include "scene.h"			//�V�[���i�|���S���̐e�j�t�@�C��
#include "input.h"			//���͏����t�@�C��
#include "inihkeyboard.h"	//�L�[�{�[�h���͏����t�@�C��
#include "inputmouse.h"		//�}�E�X���͏����t�@�C��
#include "sound.h"			//���y�t�@�C��
#include "title.h"			//�^�C�g���t�@�C��
#include "score.h"			//�X�R�A�t�@�C��
#include "number.h"			//�i���o�[�t�@�C��
#include "fade.h"			//�t�F�[�h�A�E�g�t�@�C��
#include "ui.h"				//UI�t�@�C��
#include "game.h"			//�Q�[���w�b�_�[
#include "select.h"			//�Z���N�g�w�b�_�[
#include "text.h"			//�e�L�X�g�w�b�_�[
#include "window.h"			//�E�B���h�E�w�b�_�[
#include "player.h"			//�v���C���[�w�b�_�[
#include "button.h"			//�{�^���w�b�_�[
#include "clear.h"			//�Q�[���N���A�w�b�_�[
#include "telop_bar.h"		//�e���b�v�o�[�w�b�_�[
#include "mouse pointer.h"	//�}�E�X�|�C���^�[
#include "telop_text.h"		//�e���b�v�e�L�X�g�w�b�_�[
#include "tutorial.h"		//�`���[�g���A���w�b�_�[
//----------------------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------------------
CRenderer *CManager::m_pRenderer = NULL;
CInihKeyboard *CManager::m_pInput = NULL;
CInihMouse *CManager::m_pInihMouse = NULL;
CSound *CManager::m_pSound = NULL;
CManager::GAME_MODE CManager::m_Mode= GAME_MODE_TITLE;
CScene *CManager::m_pScene = NULL;
CTitle *CManager::m_pTitle = NULL;
CFade *CManager::m_pFade = NULL;
CGame *CManager::m_pGame = NULL;
CSelect *CManager::m_pSelect = NULL;
int CManager::m_nScore = 10000;
CManager::PLAYER_DATA CManager::m_Player = { 0,0,{ CPlayer::WEAPONS_MODE_BUTTOL , CPlayer::WEAPONS_MODE_NONE } };
CTutorial *CManager::m_pTutorial = NULL;

//---------------------------------
//�R���X�g���N�^
//---------------------------------
CManager::CManager()
{

}

//---------------------------------
//�f�X�g���N�^
//---------------------------------
CManager::~CManager()
{
}

//---------------------------------
//����������
//---------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�C���v�b�g(�L�[�{�[�h)����
	m_pInput = new CInihKeyboard;
	m_pInput->Init(hInstance, hWnd);
	
	//�C���v�b�g(�}�E�X)����
	m_pInihMouse = new CInihMouse;
	m_pInihMouse->Init(hInstance, hWnd);
	
	//�����_�����O����
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//�t�F�C�h�A�E�g����
	m_pFade = new CFade;
	m_pFade->Init();

	//�T�E���h����
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	//�e�N�X�`���̓ǂݍ���
	CClear::Load();			//�N���A
	CTitle::Load();			//�^�C�g��
	CNumber::Load();		//�i���o�[
	CUi::Load();			//UI
	CText::Load();			//�e�L�X�g
	CWindow::Load();		//�E�B���h�E
	CButton::Load();		//�{�^��
	CTelopBer::Load();		//�e���b�v�o�[
	CTelopText::Load();		//�e���b�v�e�L�X�g
	CPointer::Load();		//�}�E�X�|�C���^�[
	CTutorial::Load();		//�`���[�g���A��
	//�I�u�W�F�N�g�N���X����
	SetMode(m_Mode);
	return S_OK;
}

//---------------------------------
//�I������
//---------------------------------
void CManager::Uninit(void)
{
	//�L�[�{�[�h�j��
	if (m_pInput != NULL)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = NULL;

	}
	//�}�E�X�j��
	if (m_pInihMouse != NULL)
	{
		m_pInihMouse->Uninit();
		delete m_pInihMouse;
		m_pInihMouse = NULL;

	}
	//�T�E���h�j��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	//�t�F�[�h�A�E�g�j��
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}
	
	//�e�N�X�`���̔j��
	CClear::Unload();			//�N���A
	CButton::Unload();			//�{�^��
	CTitle::Unload();			//�^�C�g��
	CNumber::Unload();			//�i���o�[
	CUi::Unload();				//UI
	CText::Unload();			//�e�L�X�g
	CWindow::Unload();			//�E�B���h�E
	CTelopBer::Unload();		//�e���b�v�o�[
	CTelopText::Unload();		//�e���b�v�e�L�X�g
	CPointer::Unload();			//�}�E�X�|�C���^�[
	CTutorial::Unload();			//�`���[�g���A��

	//�����_�����O�N���X�̔j��
	if (m_pRenderer != NULL)	//���������m�ۂ���Ă��邩
	{
		//�����_�����O �I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

}

//---------------------------------
//�X�V����
//---------------------------------
void CManager::Update()
{
	m_pInihMouse->Update();		//�}�E�X�X�V
	m_pInput->Update();			//�L�[�{�[�h�X�V (�ŏ��ɍs��)
	m_pRenderer->Update();		//�����_�����O�X�V����
	m_pFade->Update();			//�t�F�[�h�A�E�g�X�V����

	switch (m_Mode)
	{
	case GAME_MODE_TITLE:
		break;
	case GAME_MODE_SELECT:
		m_pSelect->Update();
		break;
	case GAME_MODE_STAGE:
		m_pGame->Update();
		break;
	}

}

//---------------------------------
//�`�揈��
//---------------------------------
void CManager::Draw(void)
{
	m_pRenderer->Draw();				// �����_�����O�`�揈��
}

//---------------------------------
//�Q�[�����[�h�Z�b�g����
//---------------------------------
void CManager::SetMode(GAME_MODE mode)
{
	m_Mode = mode;
	//����������
	switch (m_Mode)
	{
	case GAME_MODE_TITLE:
		//�V�[���j��
		CScene::ReleaseAll();
		//�T�E���h��~
		m_pSound->Stop();

		//�^�C�g������
		m_pTitle = CTitle::Create();
		//�T�E���h�Đ�
		m_pSound->Play(CSound::LABEL_BGM_TITLE);
		break;
	case GAME_MODE_TUTORIAL:
		//�V�[���j��
		CScene::ReleaseAll();
		//�`���[�g���A������
		m_pTutorial= CTutorial::Create();

		break;
	case GAME_MODE_SELECT:
		//�V�[���j��
		CScene::ReleaseAll();
		//�T�E���h��~
		m_pSound->Stop();

		//�Z���N�g��������
		m_pSelect = CSelect::Create();
		//�T�E���h�Đ�
		m_pSound->Play(CSound::LABEL_BGM_SELECT);

		break;
	case GAME_MODE_STAGE:
		//�V�[���j��
		CScene::ReleaseAll();
		//�T�E���h��~
		m_pSound->Stop();

		//�Q�[����������
		m_pGame = CGame::Create();

		break;
	case GAME_MODE_CLEAR:
		m_Player = { 0,0,{ CPlayer::WEAPONS_MODE_BUTTOL , CPlayer::WEAPONS_MODE_NONE } };
		m_nScore = 10000;
		//�V�[���j��
		CScene::ReleaseAll();
		//�T�E���h��~
		m_pSound->Stop();

		//�Q�[���N���A
		CClear::Create();
		//�T�E���h�Đ�
		m_pSound->Play(CSound::LABEL_SE_RESULT);

		break;

	}

}

CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CInihKeyboard * CManager::GetKeyboard(void)
{
	return m_pInput;
}

CInihMouse * CManager::GetMouse(void)
{
	return m_pInihMouse;
}

CSound * CManager::GetSound(void)
{
	return m_pSound;
}

CFade * CManager::GetFade(void)
{
	return m_pFade;
}

int  CManager::GetScore(void)
{
	return m_nScore;
}

int CManager::GetPlayer(int nPlayerData)
{
	if (nPlayerData == 0)
	{
		return m_Player.m_nLife;
	}
	else
	{
		return m_Player.m_nSpeed;
	}
}

void CManager::SetPlayer(int nLife, int nSpeed)
{
	m_Player.m_nLife = nLife;
	m_Player.m_nSpeed = nSpeed;
}

void CManager::SetWeapon(CPlayer::WEAPON_MODE nWeaponData1, CPlayer::WEAPON_MODE nWeaponData2)
{
	m_Player.m_nWeapon[0] = nWeaponData1;
	m_Player.m_nWeapon[1] = nWeaponData2;
}




