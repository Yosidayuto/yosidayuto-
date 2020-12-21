//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "Background.h"	//�w�i�t�@�C��
#include "scene2d.h"	//�V�[���QD�i2D�|���S���j�t�@�C��
#include "manager.h"	//�}�l�[�W���[�t�@�C��
#include "renderer.h"	//�����_�����O�t�@�C��	

//----------------------------------
//�}�N����`
//----------------------------------

//----------------------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------------------
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};
CBg::DATA CBg::m_Data[MAX_BG] =
{
	{ D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f),D3DXVECTOR3(800, SCREEN_HEIGHT , 0.0f) },
	{ D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f),D3DXVECTOR3(800, SCREEN_HEIGHT , 0.0f) },

};
char *CBg::m_dTexture[MAX_BG]=
{
	"data/TEXTURE/background_game_0.png",
	"data/TEXTURE/background_game_1.png",
};
//------------------------------------
//�R���X�g���N�^
//------------------------------------
CBg::CBg(int nPriorit) :CScene(nPriorit)
{
	//�A�j���[�V�����p�^�[���̏�����
	for (int nCountBg = 0; nCountBg < MAX_PATTERN; nCountBg++)
	{
		m_nPatternAnim[nCountBg] = 0;		
	}
	//�|���S���̏�����
	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		m_apScene2D[nCountBg] = NULL;		
	}
	//�A�j���[�V�����J�E���g������
	m_nCounterAnim = 0;		

	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);


}

//------------------------------------
//�f�X�g���N�^
//------------------------------------
CBg::~CBg()
{
}

//------------------------------------
//�e�N�X�`���ǂݍ���
//------------------------------------
HRESULT CBg::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	for (int nCont = 0; nCont < MAX_BG; nCont++)
	{
		D3DXCreateTextureFromFile(pDevice, m_dTexture[nCont], &m_apTexture[nCont]);
	}
	return S_OK;
}

//------------------------------------
//�e�N�X�`���̔j��
//------------------------------------
void CBg::Unload(void)
{
	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCountBg] != NULL)
		{
			m_apTexture[nCountBg]->Release();
			m_apTexture[nCountBg] = NULL;
		}
	}
}

//------------------------------------
//��������
//------------------------------------
CBg * CBg::Create(void)
{
	CBg *pBg;
	pBg = new CBg;
	pBg->Init();
	return pBg;
}

//------------------------------------
//����������
//------------------------------------
HRESULT CBg::Init(void)
{
	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		//�������m��
		m_apScene2D[nCountBg] = new CScene2d (0);
		//�ʒu
		m_apScene2D[nCountBg]->SetPosition(m_Data[nCountBg].m_Pos);
		//�T�C�Y
		m_apScene2D[nCountBg]->SetSizeition(m_Data[nCountBg].m_Size);
		//����������
		m_apScene2D[nCountBg]->CScene2d::Init();
		//�e�N�X�`���̐ݒ�
		m_apScene2D[nCountBg]->BindTexture(m_apTexture[nCountBg]);
	}

	return S_OK;
}

//------------------------------------
//�I������
//------------------------------------
void CBg::Uninit(void)
{
	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		if (m_apScene2D[nCountBg] != NULL)
		{
			m_apScene2D[nCountBg]->CScene2d::Uninit();
		}
	}
	Release();
}

//------------------------------------
//�X�V����
//------------------------------------
void CBg::Update(void)
{
	D3DXVECTOR2 Texture1[4];
	D3DXVECTOR2 Texture2[4];
	Texture1[0] = D3DXVECTOR2(0.0f, ((float)-m_nPatternAnim[0] * 0.01f)*(1.0f / 1.0f));
	Texture1[1] = D3DXVECTOR2(1.0f, ((float)-m_nPatternAnim[0] * 0.01f)*(1.0f / 1.0f));
	Texture1[2] = D3DXVECTOR2(0.0f, ((float)-m_nPatternAnim[0] * 0.01f)*(1.0f / 1.0f)+ (1.0f / 1.0f));
	Texture1[3] = D3DXVECTOR2(1.0f, ((float)-m_nPatternAnim[0] * 0.01f)*(1.0f / 1.0f)+ (1.0f / 1.0f));
	
	Texture2[0] = D3DXVECTOR2(0.0f, ((float)-m_nPatternAnim[1] * 0.001f)*(1.0f / 1.0f));
	Texture2[1] = D3DXVECTOR2(1.0f, ((float)-m_nPatternAnim[1] * 0.001f)*(1.0f / 1.0f));
	Texture2[2] = D3DXVECTOR2(0.0f, ((float)-m_nPatternAnim[1] * 0.001f)*(1.0f / 1.0f) + (1.0f / 1.0f));
	Texture2[3] = D3DXVECTOR2(1.0f, ((float)-m_nPatternAnim[1] * 0.001f)*(1.0f / 1.0f) + (1.0f / 1.0f));





	m_apScene2D[0]->TextureAnim(Texture1);
	m_apScene2D[1]->TextureAnim(Texture2);
	
	//�A�j���[�V�����J�E���g
	m_nCounterAnim++;
	if (m_nCounterAnim % 2)
	{
		//�A�j���[�V�����̊G�����̊G�ɕς���
		m_nPatternAnim[0]++;
		m_nPatternAnim[1]++;

		m_nCounterAnim = 0;
		if (m_nPatternAnim[0] >= 100)
		{
			m_nPatternAnim[0] = 0;
		}
		if (m_nPatternAnim[1] >= 1000)
		{
			m_nPatternAnim[1] = 0;
		}
	}


	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		m_apScene2D[nCountBg]->CScene2d::Update();
	}
}

//------------------------------------
//�`�揈��
//------------------------------------
void CBg::Draw(void)
{
	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		m_apScene2D[nCountBg]->CScene2d::Draw();
	}
}

