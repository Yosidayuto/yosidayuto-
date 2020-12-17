//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "scene2d.h"	//�V�[���QD�i2D�|���S���j�t�@�C��
#include "manager.h"	//�}�l�[�W���[�t�@�C��
#include "renderer.h"	//�����_�����O�t�@�C��	
#include "title.h"		//�^�C�g���t�@�C��
#include "inputmouse.h"	//�}�E�X���̓t�@�C��
#include "fade.h"		//�t�F�[�h�A�E�g�t�@�C��
#include "sound.h"		//�T�E���h

//----------------------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------------------
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[MAX_TITLE] = {};

//------------------------------------
//�R���X�g���N�^
//------------------------------------
CTitle::CTitle()
{
	//�|���S���̏�����
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_bFade = false;
}

//------------------------------------
//�f�X�g���N�^
//------------------------------------
CTitle::~CTitle()
{
}

//------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------
HRESULT CTitle::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title.png", &m_apTexture[0]);
	
	return S_OK;
}

//------------------------------------
//�e�N�X�`���̔j��
//------------------------------------
void CTitle::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//------------------------------------
//��������
//------------------------------------
CTitle * CTitle::Create(void)
{
	CTitle *pTitle;
	pTitle = new CTitle;
	pTitle->Init();
	return pTitle;
}

//------------------------------------
//����������
//------------------------------------
HRESULT CTitle::Init(void)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		//�������m��
		m_apScene2D[nCount] = new CScene2d;
		//�ʒu
		m_apScene2D[nCount]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		//�T�C�Y
		m_apScene2D[nCount]->SetSizeition(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		//����������
		m_apScene2D[nCount]->CScene2d::Init();
		//�e�N�X�`���̐ݒ�
		m_apScene2D[nCount]->BindTexture(m_apTexture[nCount]);
	}

	return S_OK;
}

//------------------------------------
//�I������
//------------------------------------
void CTitle::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		m_apScene2D[nCount]->CScene2d::Uninit();
	}
	Release();
}

//------------------------------------
//�X�V����
//------------------------------------
void CTitle::Update(void)
{
	CSound *pSound = CManager::GetSound();				//�T�E���h�擾
	CInihMouse *pMouse = CManager::GetMouse();			//�}�E�X�擾
	CFade *pFade = CManager::GetFade();
	if (pMouse->GetClickTrigger(0) == true)
	{
		if (pFade->Set(CManager::GAME_MODE_SELECT) == true)
		{
			pSound->Play(CSound::LABEL_SE_CLICK);
		}
	}
	else if (pMouse->GetClickTrigger(1) == true)
	{
		if (pFade->Set(CManager::GAME_MODE_TUTORIAL) == true)
		{
			pSound->Play(CSound::LABEL_SE_CLICK);
		}

	}
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		m_apScene2D[nCount]->CScene2d::Update();
	}

}

//------------------------------------
//�`�揈��
//------------------------------------
void CTitle::Draw(void)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		m_apScene2D[nCount]->CScene2d::Draw();
	}
}
