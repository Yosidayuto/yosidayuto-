#include"explosion.h"
#include"manager.h"
#include"renderer.h"
//----------------------------------
//�}�N����`
//----------------------------------
#define EXPLOSION_SIZE 150	//�}�b�N�X�T�C�Y
#define MAX_PATTERN 8		//�A�j���[�V�����̍ő喇��
#define MAX_PATTERN_X 2		//�A�j���[�V�������̍ő喇��
#define MAX_PATTERN_Y 5		//�A�j���[�V�����c�̍ő喇��

//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
TEXTURE_DATA CExplosion::m_TextureData = {NULL,"data/TEXTURE/Explosion.png" };
//----------------------------------
//�R���X�g���N�^
//----------------------------------
CExplosion::CExplosion(int nPriorit) :CScene2d(nPriorit)
{
	//����������
	m_nCounterAnim = 0;
	m_nPatternAnimX = 0;
	m_nPatternAnimY = 0;

	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);

}

//----------------------------------
//�f�X�g���N�^
//----------------------------------
CExplosion::~CExplosion()
{
}

//----------------------------------
//����������
//----------------------------------
HRESULT CExplosion::Init(void)
{
	D3DXVECTOR2 Texture[4];

	//�T�C�Y
	SetSize(D3DXVECTOR3(EXPLOSION_SIZE / 2, EXPLOSION_SIZE / 2, 0.0f));

	//����������
	CScene2d::Init();
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y));
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X) + (1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y));
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y) + (1.0f / (float)MAX_PATTERN_Y));
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X) + (1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y) + (1.0f / (float)MAX_PATTERN_Y));
	TextureAnim(Texture);

	//�e�N�X�`���̐ݒ�
	BindTexture(m_TextureData.m_Texture);

	return S_OK;
}

//----------------------------------
//�I������
//----------------------------------
void CExplosion::Uninit(void)
{
	//�I������
	CScene2d::Uninit();
}

//----------------------------------
//�X�V����
//----------------------------------
void CExplosion::Update(void)
{
	D3DXVECTOR2 Texture[4];

	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y));
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X)+ (1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y));
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y) + (1.0f / (float)MAX_PATTERN_Y));
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X)+ (1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y) + (1.0f / (float)MAX_PATTERN_Y));

	TextureAnim(Texture);
	//�A�j���[�V�����J�E���g
	m_nCounterAnim++;
	if (m_nCounterAnim %2)
	{
		//�A�j���[�V�����̊G�����̊G�ɕς���
		m_nPatternAnimX++;
		m_nCounterAnim = 0;
		if (m_nPatternAnimX == MAX_PATTERN_X)
		{
			m_nPatternAnimX = 0;
			m_nPatternAnimY++;
			if (m_nPatternAnimY == MAX_PATTERN_Y)
			{
				m_nPatternAnimY = 0;
				Uninit();
			}
		}
	}
	
}

//----------------------------------
//�`�揈��
//----------------------------------
void CExplosion::Draw(void)
{
	//�`�揈��
	CScene2d::Draw();
}

//----------------------------------
//�ݒu�ʒu
//----------------------------------
void CExplosion::Set(D3DXVECTOR3 Pos)
{
	//�Z�b�g����
	CScene2d::SetPos(Pos);
}

//----------------------------------
//��������
//----------------------------------
CExplosion * CExplosion::Create(D3DXVECTOR3 Pos)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion;
	pExplosion->Set(Pos);
	pExplosion->Init();
	return pExplosion;
}

//----------------------------------
//�e�N�X�`���ǂݍ��ݏ���
//----------------------------------
HRESULT CExplosion::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, m_TextureData.m_cFileName, &m_TextureData.m_Texture);
	return S_OK;
}

//----------------------------------
//�e�N�X�`���j������
//----------------------------------
void CExplosion::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_TextureData.m_Texture!= NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
}

