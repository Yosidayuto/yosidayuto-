//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "scene2d.h"	//�V�[���QD�i2D�|���S���j�t�@�C��
#include "manager.h"	//�}�l�[�W���[�t�@�C��
#include "renderer.h"	//�����_�����O�t�@�C��	
#include "inputmouse.h"	//�}�E�X���̓t�@�C��
#include "fade.h"		//�t�F�[�h�A�E�g�t�@�C��
#include "clear.h"
//----------------------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------------------
LPDIRECT3DTEXTURE9 CClear::m_apTexture[MAX_ClEAR] = {};

//------------------------------------
//�R���X�g���N�^
//------------------------------------
CClear::CClear()
{
	//�|���S���̏�����
	for (int nCount = 0; nCount < MAX_ClEAR; nCount++)
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
CClear::~CClear()
{
}

//------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------
HRESULT CClear::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Result.png", &m_apTexture[0]);

	return S_OK;
}

//------------------------------------
//�e�N�X�`���̔j��
//------------------------------------
void CClear::Unload(void)
{
	for (int nCount = 0; nCount < MAX_ClEAR; nCount++)
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
CClear * CClear::Create(void)
{
	CClear *pClear;
	pClear = new CClear;
	pClear->Init();
	return pClear;
}

//------------------------------------
//����������
//------------------------------------
HRESULT CClear::Init(void)
{
	//�ǉ��}�E�X�J�[�\����\��
	ShowCursor(true);

	for (int nCount = 0; nCount < MAX_ClEAR; nCount++)
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
void CClear::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_ClEAR; nCount++)
	{
		m_apScene2D[nCount]->CScene2d::Uninit();
	}
	Release();
}

//------------------------------------
//�X�V����
//------------------------------------
void CClear::Update(void)
{
	CInihMouse *pMouse = CManager::GetMouse();			//�}�E�X�擾
	CFade *pFade = CManager::GetFade();
	if (pMouse->GetClickTrigger(0) == true)
	{
		pFade->Set(CManager::GAME_MODE_TITLE);
	}
	for (int nCount = 0; nCount < MAX_ClEAR; nCount++)
	{
		m_apScene2D[nCount]->CScene2d::Update();
	}

}

//------------------------------------
//�`�揈��
//------------------------------------
void CClear::Draw(void)
{
	for (int nCount = 0; nCount < MAX_ClEAR; nCount++)
	{
		m_apScene2D[nCount]->CScene2d::Draw();
	}
}
