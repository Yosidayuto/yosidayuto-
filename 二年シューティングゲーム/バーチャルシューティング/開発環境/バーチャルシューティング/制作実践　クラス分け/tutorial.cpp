#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "inputmouse.h"
#include "fade.h"
#include "sound.h"
//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define TEXTURE_X 0.25f

//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
LPDIRECT3DTEXTURE9 CTutorial::m_Texture = NULL;
char * CTutorial::pTexture = "data/TEXTURE/tutorial.png";

//----------------------------------
//�R���X�g���N�^
//----------------------------------
CTutorial::CTutorial(int nPriorit)
{
	m_nCountTexture = 0;
}

//----------------------------------
//�f�X�g���N�^
//----------------------------------
CTutorial::~CTutorial()
{
}

//----------------------------------
//��������
//----------------------------------
HRESULT CTutorial::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, pTexture, &m_Texture);

	return S_OK;
}

//----------------------------------
//�e�N�X�`���ǂݍ��ݏ���
//----------------------------------
void CTutorial::Unload(void)
{
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}

}

//----------------------------------
//�e�N�X�`���j������
//----------------------------------
CTutorial * CTutorial::Create(void)
{
	CTutorial *pTutorial;
	pTutorial = new CTutorial;
	pTutorial->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	pTutorial->SetSizeition(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f));
	
	pTutorial->Init();

	return pTutorial;
}

//----------------------------------
//����������
//----------------------------------
HRESULT CTutorial::Init(void)
{
	D3DXVECTOR2 Texture[4];
	//�e�N�X�`������
	Texture[0] = D3DXVECTOR2(0.0f, 0.0f);
	Texture[1] = D3DXVECTOR2(TEXTURE_X, 0.0f);
	Texture[2] = D3DXVECTOR2(0.0f, 1.0f);
	Texture[3] = D3DXVECTOR2(TEXTURE_X, 1.0f);

	BindTexture(m_Texture);
	//����������
	CScene2d::Init();


	TextureAnim(&Texture[0]);

	return S_OK;
}

//----------------------------------
//�I������
//----------------------------------
void CTutorial::Uninit(void)
{
	CScene2d::Uninit();
}

//----------------------------------
//�X�V����
//----------------------------------
void CTutorial::Update(void)
{
	CSound *pSound = CManager::GetSound();				//�T�E���h�擾
	CInihMouse *pMouse = CManager::GetMouse();			//�}�E�X�擾
	CFade *pFade = CManager::GetFade();					//�t�F�[�h�擾	
	D3DXVECTOR2 Texture[4];								//�e�N�X�`��

	if (pMouse->GetClickTrigger(0) == true)
	{
		if (m_nCountTexture < 3)
		{
			m_nCountTexture++;
			pSound->Play(CSound::LABEL_SE_CLICK);
		}
		else
		{
			if (pFade->Set(CManager::GAME_MODE_SELECT) == true)
			{
				pSound->Play(CSound::LABEL_SE_CLICK);
			}

		}

	}
	if (pMouse->GetClickTrigger(1) == true && m_nCountTexture>0)
	{
		m_nCountTexture--;
	}
	Texture[0] = D3DXVECTOR2(TEXTURE_X*m_nCountTexture, 0.0f);
	Texture[1] = D3DXVECTOR2(TEXTURE_X*m_nCountTexture + TEXTURE_X, 0.0f);
	Texture[2] = D3DXVECTOR2(TEXTURE_X*m_nCountTexture, 1.0f);
	Texture[3] = D3DXVECTOR2(TEXTURE_X*m_nCountTexture + TEXTURE_X, 1.0f);
	TextureAnim(&Texture[0]);
	
	CScene2d::Update();
}

//----------------------------------
//�`�揈��
//----------------------------------
void CTutorial::Draw(void)
{
	CScene2d::Draw();
}
