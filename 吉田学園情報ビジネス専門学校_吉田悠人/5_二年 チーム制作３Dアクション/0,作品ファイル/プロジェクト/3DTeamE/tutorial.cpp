//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	tutorial.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "tutorial.h"

#include "bullet_ui.h"
#include "camera.h"
#include "computer.h"
#include "crosshair.h"
#include "damage_ui.h"
#include "exclamationmark.h"
#include "fade.h"
#include "goal.h"
#include "heavy_enemy.h"
#include "hiteffect.h"
#include "inputkeyboard.h"
#include "item.h"
#include "item_ui.h"
#include "light.h"
#include "light_enemy.h"
#include "manager.h"
#include "player.h"
#include "polygon3d.h"
#include "sound.h"
#include "stage01.h"
#include "stage02.h"
#include "stage03.h"
#include "titlelogo.h"
#include "trap.h"
#include "tutorialstage.h"
#include "uav.h"
#include "weapons_ui.h"
#include "woodenbox.h"
#include "Obstacle.h"
#include "countdown.h"
#include "renderer.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

LPDIRECT3DTEXTURE9 CTutorial::m_apTexture[13] = {};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
    //����������
    m_pCamera        = NULL;
    m_pPlayer        = NULL;
    m_pTutorialStage = NULL;
    m_pCrosshair     = NULL;
    m_pWoodenBox     = NULL;
    m_pClothBox      = NULL;
    m_pComputer      = NULL;
    m_pWeaponsUi     = NULL;
    m_pIronBox       = NULL;
    m_pStage01       = NULL;
    m_pStage02       = NULL;
    m_pStage03       = NULL;
    m_pTitleLogo     = NULL;
    m_pItemUi        = NULL;
    m_pDamageUi      = NULL;
    m_pBulletUi      = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init(void)
{
    D3DXVECTOR3 vec = D3DXVECTOR3(0, 0, 0);    //�x�N�g����`
    CLightEnemy *test = NULL;
	CUav* pUav = NULL;
	CPolygon3D* pGuide[13] = {};
	ZeroMemory(pGuide, sizeof(pGuide));
    //�T�E���h�̎擾
    CSound *pSound = CManager::GetSound();
    pSound->StopSound();
    pSound->PlaySound(CSound::SOUND_LABEL_BGM_MAP);
    SetCursorPos(((int)SCREEN_WIDTH / 2), ((int)SCREEN_HEIGHT / 2));

    //-----------------
    //�I�u�W�F�N�g����
    //-----------------

	m_pCamera = new CCamera;
	//�J��������������
	m_pCamera->Init();
    //�`���[�g���A������
    m_pTutorialStage = CTutorialStage::Create(D3DXVECTOR3(0, 0, 0), vec, D3DXVECTOR3(2.0f, 1.75f, 2.0f));
    //�v���C���[����
    m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -800.0f), D3DXVECTOR3(45, 180, 0), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
    //�G�l�~�[����

    test = CLightEnemy::Create(D3DXVECTOR3(90.0f, 0.0f, 375.0f), vec);
	test->SetTour(1, D3DXVECTOR3(90.0f, 0.0f, 375.0f));
	test->SetTour(2, D3DXVECTOR3(-90.0f, 0.0f, 375.0f));
	//HeavyEnemy = CHeavyEnemy::Create(D3DXVECTOR3(100, 0.0f, 50.0f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	//HeavyEnemy->SetTour(1, D3DXVECTOR3(200, 0.0f, 50.0f));
	//UAV ����
	pUav = CUav::Create(D3DXVECTOR3(0.0f, 0.0f, -175.0f), D3DXVECTOR3(0, 0, 0));
	pUav->SetTour(1, D3DXVECTOR3(90.0f, 0.0f, -175.0f));
	pUav->SetTour(2, D3DXVECTOR3(-90.0f, 0.0f, -175.0f));

	pGuide[0] = CPolygon3D::Create(D3DXVECTOR3(-50.0f, 60.0f, -700.0f), D3DXVECTOR3(90.0f, -90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[1] = CPolygon3D::Create(D3DXVECTOR3(-50.0f, 60.0f, -600.0f), D3DXVECTOR3(90.0f, -90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[2] = CPolygon3D::Create(D3DXVECTOR3(-50.0f, 60.0f, -500.0f), D3DXVECTOR3(90.0f, -90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[3] = CPolygon3D::Create(D3DXVECTOR3(50.0f, 60.0f, -700.0f), D3DXVECTOR3(90.0f, 90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[4] = CPolygon3D::Create(D3DXVECTOR3(50.0f, 60.0f, -600.0f), D3DXVECTOR3(90.0f, 90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[5] = CPolygon3D::Create(D3DXVECTOR3(50.0f, 60.0f, -500.0f), D3DXVECTOR3(90.0f, 90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[6] = CPolygon3D::Create(D3DXVECTOR3(0.0f, 60.0f, -450.0f), D3DXVECTOR3(90.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 20.0f, 0.0f));
	pGuide[7] = CPolygon3D::Create(D3DXVECTOR3(0.0f, 60.0f, -175.0f), D3DXVECTOR3(90.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 20.0f, 0.0f));
	pGuide[8] = CPolygon3D::Create(D3DXVECTOR3(0.0f, 60.0f, 375.0f), D3DXVECTOR3(90.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 20.0f, 0.0f));
	pGuide[9] = CPolygon3D::Create(D3DXVECTOR3(-50.0f, 60.0f, -50.0f), D3DXVECTOR3(90.0f, -90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[10] = CPolygon3D::Create(D3DXVECTOR3(-370.0f, 60.0f, 320.0f), D3DXVECTOR3(90.0f, 180.0f, 0.0f), D3DXVECTOR3(30.0f, 20.0f, 0.0f));
	pGuide[11] = CPolygon3D::Create(D3DXVECTOR3(-370.0f, 30.0f, 310.0f), D3DXVECTOR3(90.0f, 180.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[12] = CPolygon3D::Create(D3DXVECTOR3(-370.0f, 35.0f, 460.0f), D3DXVECTOR3(90.0f, 0.0f, 0.0f), D3DXVECTOR3(40.0f, 50.0f, 0.0f));
	for (int nCount = 0; nCount < 13; nCount++)
	{
		pGuide[nCount]->BindTexture(m_apTexture[nCount]);
	}
	//�A�C�e������
    CItem::Create(D3DXVECTOR3(-370, 25, 320), vec);
    m_Trap = CTrap::Create(D3DXVECTOR3(60.0f, 35.0f,-400.0f), D3DXVECTOR3(-60.0f, 35.0f, -400.0f));
    CGoal::Create(D3DXVECTOR3(-500.0f, 50.0f, 390.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.0f), CManager::MODE_TITLE);
    //�����܂�
    return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
{
#ifdef _DEBUG
	if (((CInputKeyboard *)CManager::GetInputKey())->GetKeyTrigger(DIK_RETURN))
    {
        CManager::GetFade()->SetFade(CManager::MODE_MAP01);
    }

    if(((CInputKeyboard *)CManager::GetInputKey())->GetKeyTrigger(DIK_O))
    {
        CLightEnemy::Create(D3DXVECTOR3(100, 0, 0), D3DXVECTOR3(0, 0, 0));

        CUav::Create(D3DXVECTOR3(100, 50, 0), D3DXVECTOR3(0, 0, 0));
    }

    if(((CInputKeyboard *)CManager::GetInputKey())->GetKeyTrigger(DIK_L))
    {
        CLightEnemy::Create(m_pPlayer->GetPos(), D3DXVECTOR3(0, 0, 0));
    }

	if (((CInputKeyboard *)CManager::GetInputKey())->GetKeyTrigger(DIK_P))
	{
		CItem::Create(D3DXVECTOR3(100, 25, 100), D3DXVECTOR3(0, 0, 0));
	}
    if(((CInputKeyboard *)CManager::GetInputKey())->GetKeyTrigger(DIK_M))
    {
        CHitEffect::HitEffectCreate(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(10, 10, 10), D3DCOLOR_RGBA(255, 0, 0, 255));
    }

#endif
    if(m_pCamera != NULL)
    {
        m_pCamera->Update();
    }
}

//=============================================================================
// �`��֐�
//=============================================================================
void CTutorial::Draw(void)
{
    if(m_pCamera != NULL)
    {
        m_pCamera->SetCamera();
    }
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
    CObject::ReleaseAll();
}

void CTutorial::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/WASD.png",								// �t�@�C���̖��O
		&m_apTexture[0]);		
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/Shift.png",								// �t�@�C���̖��O
		&m_apTexture[1]);	
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/Ctrl.png",								// �t�@�C���̖��O
		&m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/Mouse.png",								// �t�@�C���̖��O
		&m_apTexture[3]);
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/RClick.png",								// �t�@�C���̖��O
		&m_apTexture[4]);
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/LClick.png",								// �t�@�C���̖��O
		&m_apTexture[5]);
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/Trap.png",								// �t�@�C���̖��O
		&m_apTexture[6]);
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/teisatsuki.png",								// �t�@�C���̖��O
		&m_apTexture[7]);
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/chugataki.png",								// �t�@�C���̖��O
		&m_apTexture[8]);
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/R_Key.png",								// �t�@�C���̖��O
		&m_apTexture[9]);
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/recovery.png",								// �t�@�C���̖��O
		&m_apTexture[10]);
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/F_Key.png",								// �t�@�C���̖��O
		&m_apTexture[11]);
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/mission.png",								// �t�@�C���̖��O
		&m_apTexture[12]);
}

void CTutorial::Unload(void)
{
	for (int nCount = 0; nCount < 13; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}