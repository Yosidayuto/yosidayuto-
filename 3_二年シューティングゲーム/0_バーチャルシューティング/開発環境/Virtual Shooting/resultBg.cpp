//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "resultBg.h"
#include "manager.h"
#include "renderer.h"
//----------------------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------------------
LPDIRECT3DTEXTURE9 CResultBg::m_apTexture = NULL;

//------------------------------------
//�R���X�g���N�^
//------------------------------------
CResultBg::CResultBg(int nPriorit)
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//------------------------------------
//�f�X�g���N�^
//------------------------------------
CResultBg::~CResultBg()
{
}

//------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------
HRESULT CResultBg::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ResultBg.png", &m_apTexture);
	return S_OK;
}

//------------------------------------
//�e�N�X�`���̔j��
//------------------------------------
void CResultBg::Unload(void)
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
CResultBg * CResultBg::Create(void)
{
	CResultBg *pResultBg;
	pResultBg = new CResultBg;
	pResultBg->Init();
	return pResultBg;
}

//------------------------------------
//����������
//------------------------------------
HRESULT CResultBg::Init(void)
{
	//�ʒu
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	//�T�C�Y
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
void CResultBg::Uninit(void)
{
	CScene2d::Uninit();
}

//------------------------------------
//�X�V����
//------------------------------------
void CResultBg::Update(void)
{
}

//------------------------------------
//�`�揈��
//------------------------------------
void CResultBg::Draw(void)
{
	CScene2d::Draw();
}
