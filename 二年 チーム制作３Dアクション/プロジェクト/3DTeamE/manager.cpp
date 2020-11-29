//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	manager.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "manager.h"

#include "Obstacle.h"
#include "animation.h"
#include "assaultbutton.h"
#include "bullet_ui.h"
#include "camera.h"
#include "clear.h"
#include "computer.h"
#include "continuebutton.h"
#include "crosshair.h"
#include "damage_ui.h"
#include "debug.h"
#include "exclamationmark.h"
#include "explosion.h"
#include "explosion2.h"
#include "fade.h"
#include "handgunbutton.h"
#include "heavy_enemy.h"
#include "hiteffect.h"
#include "input.h"
#include "inputjoystick.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "item.h"
#include "item_ui.h"
#include "light.h"
#include "light_enemy.h"
#include "map01.h"
#include "map02.h"
#include "map03.h"
#include "map04.h"
#include "mission.h"
#include "model.h"
#include "monitor.h"
#include "muzzleflash.h"
#include "object.h"
#include "object2d.h"
#include "object3d.h"
#include "pause.h"
#include "player.h"
#include "polygon3d.h"
#include "question.h"
#include "renderer.h"
#include "result.h"
#include "resultscene.h"
#include "retrybutton.h"
#include "returntitlebutton.h"
#include "sound.h"
#include "stage01.h"
#include "stage02.h"
#include "stage03.h"
#include "stage04.h"
#include "startbutton.h"
#include "title.h"
#include "titlelogo.h"
#include "trap.h"
#include "tutorial.h"
#include "tutorialbutton.h"
#include "tutorialstage.h"
#include "uav.h"
#include "weapons_ui.h"
#include "weaponselect.h"
#include "weaponselectscene.h"
#include "woodenbox.h"
#include "number.h"
#include "countdown.h"
#include "blood.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRenderer* CManager::m_pRenderer               = NULL;
CInput* CManager::m_pInputKey                  = NULL;
CInput* CManager::m_pInputMou                  = NULL;
CCamera* CManager::m_pCamera                   = NULL;
CPlayer* CManager::m_pPlayer                   = NULL;
CModel* CManager::m_pStageModel                = NULL;
CFade* CManager::m_pFade                       = NULL;
CManager::MODE CManager::m_mode                = {};
CSound* CManager::m_pSound                     = NULL;
CTitle* CManager::m_pTitle                     = NULL;
CTutorial* CManager::m_pTutorial               = NULL;
CMap01* CManager::m_pMap01                     = NULL;
CMap02* CManager::m_pMap02                     = NULL;
CMap03* CManager::m_pMap03                     = NULL;
CMap04* CManager::m_pMap04					   = NULL;
CResult* CManager::m_pResult                   = NULL;
CManager::WEAPONS_MODE CManager::m_WeaponsMode = WEAPONS_MODE_NONE;
CInputJoystick* CManager::m_pInputJoystick     = NULL;
CWeaponSelect* CManager::m_pWeaponSelect       = NULL;
CPause* CManager::m_pPause                     = NULL;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CManager::CManager()
{
    m_pRenderer   = NULL;
    m_WeaponsMode = WEAPONS_MODE_AR;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CManager::~CManager()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�������֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CManager::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
    HRESULT hResult = NULL;
    m_pRenderer     = new CRenderer;                    //�����_���𐶐�
    hResult         = m_pRenderer->Init(hWnd, true);    //�����_����������

    CLight* pLight = NULL;    //���C�g�̐���
    pLight         = new CLight;
    pLight->Init();
    m_pInputKey = new CInputKeyboard;    //�L�[�{�[�h����
    m_pInputKey->Init(hInstance, hWnd);
    m_pInputMou = new CInputMouse;    //�}�E�X����
    m_pInputMou->Init(hInstance, hWnd);

    //�T�E���h�̐���
    if(m_pSound == NULL)
    {
        m_pSound = new CSound;
    }

    //�T�E���h�̏�����
    m_pSound->Init(hWnd);

    m_pFade = CFade::Create();
    LoadFile();        //�t�@�C���ǂݍ���
    CDebug::Init();    //�f�o�b�O���̏����������i����FPS�̂݁j
                       //m_pTitle = new CTitle;
    m_pTitle        = new CTitle;
    m_pTutorial     = new CTutorial;
    m_pMap01        = new CMap01;
    m_pMap02        = new CMap02;
    m_pMap03        = new CMap03;
	m_pMap04		= new CMap04;
    m_pResult       = new CResult;
    m_pWeaponSelect = new CWeaponSelect;

    return hResult;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Uninit(void)
{
    //�V�[���̏I��
    CObject::ReleaseAll();

    //�f�o�b�O���̏I��
    CDebug::Uninit();

    //�t�F�[�h�I��
    if(m_pFade != NULL)
    {
        m_pFade->Uninit();
        delete m_pFade;
        m_pFade = NULL;
    }

    //���͂̏I��
    m_pInputKey->Uninit();
    delete m_pInputKey;
    m_pInputKey = NULL;

    m_pInputMou->Uninit();
    delete m_pInputMou;
    m_pInputMou = NULL;
    //�J�����̏I��
    m_pCamera->Uninit();
    delete m_pCamera;
    m_pCamera = NULL;

    //�����_���̏I��
    m_pRenderer->Uninit();
    delete m_pRenderer;
    m_pRenderer = NULL;

    //�T�E���h�̒�~
    m_pSound->StopSound();

    //�T�E���h�̔j��
    if(m_pSound != NULL)
    {
        m_pSound->Uninit();
        delete m_pSound;
        m_pSound = NULL;
    }

    //�ǂݍ��񂾃t�@�C���̃A�����[�h
    UnloadFiles();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Update(void)
{
    //���͂̍X�V
    if(m_pInputKey != NULL)
    {
        m_pInputKey->Update();
    }
    if(m_pInputMou != NULL)
    {
        m_pInputMou->Update();
    }
    //�����_���̍X�V
	if (m_pRenderer != NULL && m_pPause == NULL)
	{
		m_pRenderer->Update();
	}
    //�t�F�[�h�X�V
    if(m_pFade != NULL)
    {
        m_pFade->Update();
    }
    if(m_mode != MODE_TITLE && m_mode != MODE_WEAPONSELECT && m_mode != MODE_RESULT && ((CInputKeyboard*)m_pInputKey)->GetKeyTrigger(DIK_ESCAPE) && m_pPause == NULL&&m_pPlayer->GetLife() > 0)
    {
        m_pPause = CPause::Create();
    }
	else if(((CInputKeyboard*)m_pInputKey)->GetKeyTrigger(DIK_ESCAPE))
	{
		DestroyWindow(FindWindow(CLASS_NAME,NULL));
	}

    if(m_pPause != NULL)
    {
        m_pPause->Update();
    }
    else
    {
        switch(m_mode)
        {
            case MODE_TITLE:
                m_pTitle->Update();
                break;
            case MODE_TUTORIAL:
                m_pTutorial->Update();
                break;
            case MODE_WEAPONSELECT:
                m_pWeaponSelect->Update();
                break;
            case MODE_MAP01:
                m_pMap01->Update();
                break;
            case MODE_MAP02:
                m_pMap02->Update();
                break;
            case MODE_MAP03:
                m_pMap03->Update();
                break;
			case MODE_MAP04:
				m_pMap04->Update();
				break;
            case MODE_RESULT:
                m_pResult->Update();
                break;
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Draw(void)
{
    switch(m_mode)
    {
        case MODE_TITLE:
            m_pTitle->Draw();
            break;
        case MODE_TUTORIAL:
            m_pTutorial->Draw();
            break;
        case MODE_WEAPONSELECT:
            m_pWeaponSelect->Draw();
            break;
        case MODE_MAP01:
            m_pMap01->Draw();
            break;
        case MODE_MAP02:
            m_pMap02->Draw();
            break;
        case MODE_MAP03:
            m_pMap03->Draw();
            break;
		case MODE_MAP04:
			m_pMap04->Draw();
			break;
        case MODE_RESULT:
            m_pResult->Draw();
            break;
    }
    //�����_���̕`��
    if(m_pRenderer != NULL)
    {
        m_pRenderer->Draw();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRenderer* CManager::GetRenderer(void)
{
    return m_pRenderer;
}

CInput* CManager::GetInputKey(void)
{
    return m_pInputKey;
}

CInput* CManager::GetInputMou(void)
{
    return m_pInputMou;
}

CInputJoystick* CManager::GetInputJoystick(void)
{
    return m_pInputJoystick;
}

CCamera* CManager::GetCamera(void)
{
    return m_pCamera;
}

CPlayer* CManager::GetPlayer(void)
{
    return m_pPlayer;
}

CModel* CManager::GetStageModel(void)
{
    return m_pStageModel;
}
CManager::WEAPONS_MODE CManager::GetWeaponsMode(void)
{
    return m_WeaponsMode;
}
void CManager::SetWeaponsMode(WEAPONS_MODE WeaponsMode)
{
    m_WeaponsMode = WeaponsMode;
}
void CManager::SetStageModel(CModel* pModel)
{
    m_pStageModel = pModel;
}
void CManager::SetPlayer(CPlayer* pPlayer)
{
    m_pPlayer = pPlayer;
}

void CManager::BindCamera(CCamera* pCamera)
{
    m_pCamera = pCamera;
}
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���̃��[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::LoadFile(void)
{
    CWeapons_ui::Load();
    CPlayer::Load();
    CCrosshair::Load();
    CLightEnemy::Load();
    CTutorialStage::Load();
    CItem::Load();
    CWoodenBox::Load();
    CAnimation::Load();
    CComputer::Load();
    CExplosion::Load();
    CExplosion2::Load();
    CComputer::Load();
    CMonitor::Load();
    CExclamationMark::Load();
    CQuestion::Load();
    CUav::Load();
    CStage01::Load();
    CStage02::Load();
    CStage03::Load();
	CStage04::Load();
    CTitleLogo::Load();
    CHeavyEnemy::Load();
    CMuzzleflash::Load();
    CHitEffect::Load();
    CItem_ui::Load();
    CDamage_ui::Load();
    CBullet_ui::Load();
    CStartButton::Load();
    CTutorialButton::Load();
    CAssaultButton::Load();
    CHandgunButton::Load();
    CWeaponSelectScene::Load();
    CResultScene::Load();
    CObstacle::Load();
    CReturnTitleButton::Load();
    CRetryButton::Load();
    CMission::Load();
    CClear::Load();
    CContinueButton::Load();
	CNumber::Load();
	CCountDown::Load();
	CTutorial::Load();
	CBlood::Load();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���̃A�����[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::UnloadFiles(void)
{
    CWeapons_ui::Unload();
    CPlayer::Unload();
    CLightEnemy::Unload();
    CTutorialStage::Unload();
    CItem::Unload();
    CWoodenBox::Unload();
    CComputer::Unload();
    CExplosion::Unload();
    CExplosion2::Unload();
    CMonitor::Unload();
    CExclamationMark::Unload();
    CQuestion::Unload();
    CUav::Unload();
    CStage01::Unload();
    CStage02::Unload();
    CStage03::Unload();
	CStage04::Unload();
    CTitleLogo::Unload();
    CHeavyEnemy::Unload();
    CMuzzleflash::Unload();
    CHitEffect::Unload();
    CItem_ui::Unload();
    CDamage_ui::Unload();
    CBullet_ui::Unload();
    CStartButton::Unload();
    CTutorialButton::Unload();
    CAssaultButton::Unload();
    CHandgunButton::Unload();
    CWeaponSelectScene::Unload();
    CResultScene::Unload();
    CObstacle::Unload();
    CReturnTitleButton::Unload();
    CRetryButton::Unload();
    CMission::Unload();
    CClear::Unload();
    CContinueButton::Unload();
	CNumber::Unload();
	CCountDown::Unload();
	CCrosshair::Unload();
	CTutorial::Unload();
	CBlood::Unload();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���[�h�ؑ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::SetMode(MODE mode)
{
    CSound* pSound = CManager::GetSound();    //�T�E���h�̎擾
    if(m_pPause != NULL)
    {
        m_pPause->Uninit();
        m_pPause = NULL;
    }
    //�I������
    switch(m_mode)
    {
        case MODE_TITLE:
            //�T�E���h�I��
            pSound->StopSound();
            //�V�[���I��
            m_pTitle->Uninit();
            break;
        case MODE_TUTORIAL:
            //�T�E���h�I��
            pSound->StopSound();
            //�V�[���I��
            m_pTutorial->Uninit();
            break;
        case MODE_WEAPONSELECT:
            //�T�E���h�I��
            pSound->StopSound();
            //�V�[���I��
            m_pWeaponSelect->Uninit();
            break;
        case MODE_MAP01:
            //�T�E���h�I��
            pSound->StopSound();
            //�V�[���I��
            m_pMap01->Uninit();
            break;
        case MODE_MAP02:
            //�T�E���h�I��
            pSound->StopSound();
            //�V�[���I��
            m_pMap02->Uninit();
            break;
        case MODE_MAP03:
            //�T�E���h�I��
            pSound->StopSound();
            //�V�[���I��
            m_pMap03->Uninit();
            break;
		case MODE_MAP04:
			//�T�E���h�I��
			pSound->StopSound();
			//�V�[���I��
			m_pMap03->Uninit();
			break;
        case MODE_RESULT:
            //�T�E���h�I��
            pSound->StopSound();
            //�V�[���I��
            m_pResult->Uninit();
            break;
    }

    m_mode = mode;

    switch(m_mode)
    {
        case MODE_TITLE:
            m_pTitle->Init();
            break;
        case MODE_TUTORIAL:
            m_pTutorial->Init();
            break;
        case MODE_WEAPONSELECT:
            m_pWeaponSelect->Init();
            break;
        case MODE_MAP01:
            m_pMap01->Init();
            break;
        case MODE_MAP02:
            m_pMap02->Init();
            break;
        case MODE_MAP03:
            m_pMap03->Init();
            break;
		case MODE_MAP04:
			m_pMap04->Init();
			break;
        case MODE_RESULT:
            m_pResult->Init();
            break;
    }
}

CManager::MODE CManager::GetMode(void)
{
    return m_mode;
}

void CManager::EndPause(void)
{
    if(m_pPause != NULL)
    {
        m_pPause->Uninit();
        m_pPause = NULL;
    }
}
