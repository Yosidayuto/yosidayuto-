//=============================================================================
//
// ���[�h��ʏ��� [load.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "load.h"
#include "renderer.h"
#include "sound.h"
#include "manager.h"
#include "load bg.h"
#include "clear.h"
#include "number.h"
#include "telop.h"
#include "mouse pointer.h"
#include "title bg.h"
#include "tutorial bg.h"
#include "select bg.h"
#include "life ui.h"
#include "weapon manager.h"
#include "button manager.h"
#include "result bg.h"
#include "score bar.h"
#include "stage.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLoad::CLoad()
{
	m_bLoad = false;
	m_pLoadBg = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLoad::~CLoad()
{

}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CLoad::Load(void)
{
	CLoadBg::Load();
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CLoad::Unload(void)
{
	CLoadBg::Unload();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLoad::Init(void)
{
	//�T�E���h�擾
	CSound*	pSound = CManager::GetSound();
	//�T�E���h�Đ�
	pSound->Play(CSound::LABEL_BGM_LOAD);
	//�w�i����
	m_pLoadBg = CLoadBg::Create();

	//�A�b�v�f�[�g�i�}���`�X���b�h�j
	std::thread LoadUpdate(&CLoad::Update,this);
	//�`��i�}���`�X���b�h�j
	std::thread LoadDraw(&CLoad::Draw, this);
	//�t�@�C�����[�h(�}���`�X���b�h)
	std::thread Load(&CLoad::FileLoad, this);

	//�X���b�h���I������܂őҋ@����
	LoadUpdate.join();
	LoadDraw.join();
	Load.join();
	//�����܂�
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLoad::Uninit(void)
{
	//�V�[���j��
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLoad::Update(void)
{

	while (!m_bLoad)
	{
		//�����_���[�|�C���^�擾
		CRenderer* Renderer = NULL;
		Renderer = CManager::GetRenderer();

		//NULL�`�F�b�N
		if (Renderer != NULL)
		{
			std::lock_guard<std::mutex> lock(m_mtx_);
			Renderer->Update();
		}
	}

}

//=============================================================================
// �`��֐�
//=============================================================================
void CLoad::Draw(void)
{

	while (!m_bLoad)
	{
		//�����_���[�|�C���^�擾
		CRenderer* Renderer = NULL;
		Renderer = CManager::GetRenderer();


		//NULL�`�F�b�N
		if (Renderer != NULL)
		{
			std::lock_guard<std::mutex> lock(m_mtx_);
			Renderer->Draw();
		}

	}
}

void CLoad::FileLoad(void)
{
	std::lock_guard<std::mutex> lock(m_mtx_);
	
	//�e�N�X�`���̓ǂݍ���
	CClear::Load();
	CNumber::Load();
	CTelop::Load();
	CPointer::Load();
	CTitleBg::Load();
	CTutorialBg::Load();
	CSelectBg::Load();
	CLifeUi::Load();
	CWeaponManager::Load();
	CButtonManager::Load();
	CGame::Load();
	CResultBg::Load();
	CScoreBar::Load();
	//�e�L�X�g�ǂݍ���
	CStage::LoadFile();
	
	//�ǂݏI������
	m_bLoad = true;
}
