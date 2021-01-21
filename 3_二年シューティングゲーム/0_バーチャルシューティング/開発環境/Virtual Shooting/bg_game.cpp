//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "bg_game.h"
#include "renderer.h"
//----------------------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------------------
LPDIRECT3DTEXTURE9 CBgGame::m_apTexture = NULL;
//------------------------------------
//�R���X�g���N�^
//------------------------------------
CBgGame::CBgGame(int nPriorit)
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//------------------------------------
//�f�X�g���N�^
//------------------------------------
CBgGame::~CBgGame()
{
}

//------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------
HRESULT CBgGame::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/background_gameoutside_0.png", &m_apTexture);
	return S_OK;
}

//------------------------------------
//�e�N�X�`���̔j��
//------------------------------------
void CBgGame::Unload(void)
{
		//�e�N�X�`���̔j��
		if (m_apTexture != NULL)
		{
			m_apTexture->Release();
			m_apTexture = NULL;
		}

}

//------------------------------------
//��������
//------------------------------------
CBgGame * CBgGame::Create(void)
{
	CBgGame *pBgGame;
	pBgGame = new CBgGame;
	pBgGame->Init();
	return pBgGame;
}

//------------------------------------
//����������
//------------------------------------
HRESULT CBgGame::Init(void)
{
	////�ʒu
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	////�T�C�Y
	SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	//�e�N�X�`���̐ݒ�
	BindTexture(m_apTexture);
	//����������
	CScene2d::Init();

	return S_OK;

}

//------------------------------------
//�I������
//------------------------------------
void CBgGame::Uninit(void)
{
	CScene2d::Uninit();
}

//------------------------------------
//�X�V����
//------------------------------------
void CBgGame::Update(void)
{
}

//------------------------------------
//�`�揈��
//------------------------------------
void CBgGame::Draw(void)
{
	CScene2d::Draw();
}
