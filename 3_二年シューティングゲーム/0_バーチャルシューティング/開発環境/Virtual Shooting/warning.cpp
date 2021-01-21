//�x��
#include "renderer.h"
#include "manager.h"
#include "warning.h"
#include "sound.h"
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
CWarning::ANIME_DATA CWarning::WarningAnim =
{
	NULL,"data/TEXTURE/Warning.png",20,2,false,
};

//----------------------------------
//�R���X�g���N�^
//----------------------------------
CWarning::CWarning(int nPriorit)
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_nCounterAnim = 0;
	m_nPatternAnimX = 0;
	nStopCount = 0;
}

//----------------------------------
//�f�X�g���N�^
//----------------------------------
CWarning::~CWarning()
{
}


//----------------------------------
//��������
//----------------------------------
CWarning * CWarning::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 size)
{
	CWarning *pWarning;

	pWarning = new CWarning;
	pWarning->SetPos(Pos);
	pWarning->Init(size);

	return pWarning;
}

//----------------------------------
//�e�N�X�`���ǂݍ��ݏ���
//----------------------------------
HRESULT CWarning::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, WarningAnim.pTextName, &WarningAnim.pTexture);
	return S_OK;

}

//----------------------------------
//�e�N�X�`���j������
//----------------------------------
void CWarning::Unload(void)
{
	//�e�N�X�`���̔j��
	if (WarningAnim.pTexture != NULL)
	{
		WarningAnim.pTexture->Release();
		WarningAnim.pTexture = NULL;
	}

}

HRESULT CWarning::Init(D3DXVECTOR3 size)
{
	CSound *pSound = CManager::GetSound();	//�T�E���h�擾
	//�T�E���h�Đ�
	pSound->Play(CSound::LABEL_SE_WARNING);

	D3DXVECTOR2 Texture[4];
	//�T�C�Y
	SetSize(D3DXVECTOR3(size.x, size.y, 0.0f));

	//����������
	CScene2d::Init();
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 0.0f);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 0.0f);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 1.0f);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 1.0f);

	TextureAnim(Texture);

	//�e�N�X�`���̐ݒ�
	BindTexture(WarningAnim.pTexture);

	return S_OK;
}

//----------------------------------
//����������
//----------------------------------
void CWarning::Uninit(void)
{
	//�I������
	CScene2d::Uninit();
}

//----------------------------------
//�I������
//----------------------------------
void CWarning::Update(void)
{
	D3DXVECTOR2 Texture[4];

	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 0);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 0);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 1);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 1);

	TextureAnim(Texture);
	//�A�j���[�V�����J�E���g
	m_nCounterAnim++;
	if (m_nCounterAnim >= WarningAnim.nCountAnime)
	{
		//�A�j���[�V�����̊G�����̊G�ɕς���
		m_nCounterAnim = 0;
		
		if (m_nPatternAnimX !=14)
		{
			m_nPatternAnimX++;
		}
		else
		{
			nStopCount++;
			if (nStopCount >= 50)
			{
				m_nPatternAnimX++;
			}
		}
		if (m_nPatternAnimX == WarningAnim.MaxCount)
		{
			m_nPatternAnimX = 0;
			if (WarningAnim.bLoop == false)
			{
				Uninit();
			}
		}
	}

}

//----------------------------------
//�X�V����
//----------------------------------
void CWarning::Draw(void)
{
	//�`�揈��
	CScene2d::Draw();
}
