#include "telop_text.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

//----------------------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------------------
LPDIRECT3DTEXTURE9 CTelopText::m_apTexture[TEXT_TYPE_MAX] = {};
char *CTelopText::m_pText[TEXT_TYPE_MAX]=
{
	"data/TEXTURE/Telop_Normal.png",
	"data/TEXTURE/Telop_LifeUp.png",
	"data/TEXTURE/Telop_SpeedUp.png",
	"data/TEXTURE/Telop_Bullet.png",
	"data/TEXTURE/Telop_Laser.png",
	"data/TEXTURE/Telop_Homing.png",
};
//------------------------------------
//�R���X�g���N�^
//------------------------------------
CTelopText::CTelopText(int nPriorit) :CScene(nPriorit)
{
	//�|���S���̏�����
	m_apScene2D = NULL;
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_Type = TEXT_TYPE_TUTORIAL;
	m_nPatternAnim = 0;
	m_nCounterAnim = 0;
}

//------------------------------------
//�f�X�g���N�^
//------------------------------------
CTelopText::~CTelopText()
{
}

//------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------
HRESULT CTelopText::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < TEXT_TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, m_pText[nCount], &m_apTexture[nCount]);
	}

	return S_OK;
}

//------------------------------------
//�e�N�X�`���̔j��
//------------------------------------
void CTelopText::Unload(void)
{
	for (int nCount = 0; nCount < TEXT_TYPE_MAX; nCount++)
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
CTelopText * CTelopText::Create(void)
{
	CTelopText *pCelopText;
	pCelopText = new CTelopText;
	pCelopText->Init();
	return pCelopText;
}

//------------------------------------
//����������
//------------------------------------
HRESULT CTelopText::Init(void)
{
	//�������m��
	m_apScene2D = new CScene2d;
	//�ʒu
	m_apScene2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 455, 20, 0.0f));
	//�T�C�Y
	m_apScene2D->SetSize(D3DXVECTOR3(775, 40, 0.0f));
	//����������
	m_apScene2D->CScene2d::Init();
	//�e�N�X�`���̐ݒ�
	m_apScene2D->BindTexture(m_apTexture[m_Type]);
	return S_OK;
}

//------------------------------------
//�I������
//------------------------------------
void CTelopText::Uninit(void)
{
	Release();
}

//------------------------------------
//�X�V����
//------------------------------------
void CTelopText::Update(void)
{
	D3DXVECTOR2 Texture[4];
	m_apScene2D->CScene2d::Update();
	if (m_Type == TEXT_TYPE_TUTORIAL)
	{
		Texture[0] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f),0.0f);
		Texture[1] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f) + (1.0f / 6.0f), 0.0f);
		Texture[2] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f), 1.0f);
		Texture[3] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f) + (1.0f / 6.0f), 1.0f);
		m_apScene2D->TextureAnim(Texture);
		//�A�j���[�V�����J�E���g
		m_nCounterAnim++;
		if (m_nCounterAnim >=1)
		{
			//�A�j���[�V�����̊G�����̊G�ɕς���
			m_nPatternAnim++;

			m_nCounterAnim = 0;
			if (m_nPatternAnim >= 10000)
			{
				m_nPatternAnim = 0;
			}
		}
	}
}

//------------------------------------
//�`�揈��
//------------------------------------
void CTelopText::Draw(void)
{
	m_apScene2D->CScene2d::Draw();
}

//------------------------------------
//�e�L�X�g�ύX
//------------------------------------
void CTelopText::TypeChange(TEXT_TYPE Type)
{
	D3DXVECTOR2 Texture[4];
	m_Type = Type;

	
	
	if (m_Type == TEXT_TYPE_TUTORIAL)
	{
		Texture[0] = D3DXVECTOR2(((float)m_nPatternAnim * 0.01f)*(1.0f / 6.0f), 0.0f);
		Texture[1] = D3DXVECTOR2(((float)m_nPatternAnim * 0.01f)*(1.0f / 6.0f) + (1.0f / 6.0f), 0.0f);
		Texture[2] = D3DXVECTOR2(((float)m_nPatternAnim * 0.01f)*(1.0f / 6.0f), 1.0f);
		Texture[3] = D3DXVECTOR2(((float)m_nPatternAnim * 0.01f)*(1.0f / 6.0f) + (1.0f / 6.0f), 1.0f);
	}
	else
	{
		Texture[0] = D3DXVECTOR2(((float)0 * 0.01f)*(1.0f / 1.0f), 0.0f);
		Texture[1] = D3DXVECTOR2(((float)0 * 0.01f)*(1.0f / 1.0f) + (1.0f / 1.0f), 0.0f);
		Texture[2] = D3DXVECTOR2(((float)0 * 0.01f)*(1.0f / 1.0f), 1.0f);
		Texture[3] = D3DXVECTOR2(((float)0 * 0.01f)*(1.0f / 1.0f) + (1.0f / 1.0f), 1.0f);
	}

	//�e�N�X�`���̐ݒ�
	m_apScene2D->BindTexture(m_apTexture[m_Type]);

	//�e�N�X�`���̐ݒ�
	m_apScene2D->TextureAnim(Texture);


}
