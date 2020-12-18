#include "telop_bar.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

//----------------------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------------------
LPDIRECT3DTEXTURE9 CTelopBer::m_apTexture= {};

//------------------------------------
//�R���X�g���N�^
//------------------------------------
CTelopBer::CTelopBer()
{
	//�|���S���̏�����
	m_apScene2D = NULL;
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//------------------------------------
//�f�X�g���N�^
//------------------------------------
CTelopBer::~CTelopBer()
{
}

//------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------
HRESULT CTelopBer::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Telop.png", &m_apTexture);

	return S_OK;
}

//------------------------------------
//�e�N�X�`���̔j��
//------------------------------------
void CTelopBer::Unload(void)
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
CTelopBer * CTelopBer::Create(void)
{
	CTelopBer *pTelopBer;
	pTelopBer = new CTelopBer;
	pTelopBer->Init();
	return pTelopBer;
}

//------------------------------------
//����������
//------------------------------------
HRESULT CTelopBer::Init(void)
{
	//�������m��
	m_apScene2D = new CScene2d;
	//�ʒu
	m_apScene2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH-425, 25, 0.0f));
	//�T�C�Y
	m_apScene2D->SetSizeition(D3DXVECTOR3(850, 50, 0.0f));
	//����������
	m_apScene2D->CScene2d::Init();
	//�e�N�X�`���̐ݒ�
	m_apScene2D->BindTexture(m_apTexture);
	return S_OK;
}

//------------------------------------
//�I������
//------------------------------------
void CTelopBer::Uninit(void)
{
	m_apScene2D->CScene2d::Uninit();
	Release();
}

//------------------------------------
//�X�V����
//------------------------------------
void CTelopBer::Update(void)
{
	m_apScene2D->CScene2d::Update();
}

//------------------------------------
//�`�揈��
//------------------------------------
void CTelopBer::Draw(void)
{
	m_apScene2D->CScene2d::Draw();
}
