#include "boss_anime.h"
#include "manager.h"
#include "renderer.h"
//----------------------------------
//�}�N����`
//----------------------------------
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
CBossAnime::ANIME_DATA CBossAnime::BossAnim[BOSS_ANIME_MAX] = 
{
	45,2,true,
	45,2,false,

	50,2,true,
	60,3,false,
	
	60,2,true,
	90,2,false,
};
TEXTURE_DATA CBossAnime::m_TextureData[BOSS_ANIME_MAX] =
{ { NULL,"data/TEXTURE/BossAnime_0.png" },
{ NULL,"data/TEXTURE/DeleteEffect_0.png" },
{ NULL,"data/TEXTURE/BossAnime_1.png" } ,
{ NULL,"data/TEXTURE/DeleteEffect_1.png" },
{ NULL,"data/TEXTURE/BossAnime_2.png" } ,
{ NULL,"data/TEXTURE/DeleteEffect_2.png" } };

//----------------------------------
//�R���X�g���N�^
//----------------------------------
CBossAnime::CBossAnime(int nPriorit)
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_nCounterAnim = 0;
	m_nPatternAnimX = 0;
}

//----------------------------------
//�f�X�g���N�^
//----------------------------------
CBossAnime::~CBossAnime()
{
}


//----------------------------------
//��������
//----------------------------------
CBossAnime * CBossAnime::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 size, BOSS_ANIME Type)
{
	CBossAnime *pBossAnime;

	pBossAnime = new CBossAnime;
	pBossAnime->m_Type = Type;
	pBossAnime->SetPos(Pos);
	pBossAnime->Init(size);
	
	return pBossAnime;
}

//----------------------------------
//�e�N�X�`���ǂݍ��ݏ���
//----------------------------------
HRESULT CBossAnime::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < BOSS_ANIME_MAX; nCount++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, m_TextureData[nCount].m_cFileName, &m_TextureData[nCount].m_Texture);

	}
	return S_OK;
}

//----------------------------------
//�e�N�X�`���j������
//----------------------------------
void CBossAnime::Unload(void)
{
	for (int nCount = 0; nCount < BOSS_ANIME_MAX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_TextureData[nCount].m_Texture != NULL)
		{
			m_TextureData[nCount].m_Texture->Release();
			m_TextureData[nCount].m_Texture = NULL;
		}


	}
}

//----------------------------------
//����������
//----------------------------------
HRESULT CBossAnime::Init(D3DXVECTOR3 size)
{
	D3DXVECTOR2 Texture[4];
	//�T�C�Y
	SetSize(D3DXVECTOR3(size.x, size.y, 0.0f));

	//����������
	CScene2d::Init();
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount), 0.0f);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount) + (1.0f / (float)BossAnim[m_Type].MaxCount), 0.0f);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount), 1.0f);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount) + (1.0f / (float)BossAnim[m_Type].MaxCount), 1.0f);
	
	TextureAnim(Texture);
	//�e�N�X�`���̐ݒ�
	BindTexture(m_TextureData[m_Type].m_Texture);

	return S_OK;
}

//----------------------------------
//�I������
//----------------------------------
void CBossAnime::Uninit(void)
{
	//�I������
	CScene2d::Uninit();

}

//----------------------------------
//�X�V����
//----------------------------------
void CBossAnime::Update(void)
{
	D3DXVECTOR2 Texture[4];

	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount), 0);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount) + (1.0f / (float)BossAnim[m_Type].MaxCount), 0);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount), 1);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)BossAnim[m_Type].MaxCount) + (1.0f / (float)BossAnim[m_Type].MaxCount), 1);

	TextureAnim(Texture);
	//�A�j���[�V�����J�E���g
	m_nCounterAnim++;
	if (m_nCounterAnim>= BossAnim[m_Type].nCountAnime)
	{
		//�A�j���[�V�����̊G�����̊G�ɕς���
		m_nCounterAnim = 0;
		m_nPatternAnimX++;
		if (m_nPatternAnimX == BossAnim[m_Type].MaxCount)
		{
			m_nPatternAnimX = 0;
			if (BossAnim[m_Type].bLoop == false)
			{
				Uninit();
			}
		}
	}

}

//----------------------------------
//�`�揈��
//----------------------------------
void CBossAnime::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	/*�����_�����O�X�e�[�g(���Z��������)*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`�揈��
	CScene2d::Draw();

	/*�����_�[�X�e�[�g*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

