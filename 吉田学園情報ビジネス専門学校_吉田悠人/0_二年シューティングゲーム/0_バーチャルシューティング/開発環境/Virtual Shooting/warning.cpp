//=============================================================================
//
// �{�X���o�̃��[�j���O���� [warning.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "renderer.h"
#include "manager.h"
#include "warning.h"
#include "sound.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define SIZE_X (800)	//X�����̃T�C�Y
#define SIZE_Y (200)	//Y�����̃T�C�Y

//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
CWarning::ANIME_DATA CWarning::WarningAnim =
{
	NULL,"data/TEXTURE/Warning.png",20,2,false,
};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CWarning::CWarning(int nPriorit)
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_nCounterAnim	= 0;
	m_nPatternAnimX = 0;
	nStopCount		= 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CWarning::~CWarning()
{
}



//=============================================================================
//�e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CWarning::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, WarningAnim.pTextName, &WarningAnim.pTexture);
	return S_OK;

}

//=============================================================================
//�e�N�X�`���j������
//=============================================================================
void CWarning::Unload(void)
{
	//�e�N�X�`���̔j��
	if (WarningAnim.pTexture != NULL)
	{
		WarningAnim.pTexture->Release();
		WarningAnim.pTexture = NULL;
	}

}

//=============================================================================
//��������
//=============================================================================
CWarning * CWarning::Create(D3DXVECTOR3 Pos)
{
	//�������m��
	CWarning *pWarning = NULL;
	pWarning = new CWarning;

	//NULL�`�F�b�N
	if (pWarning != NULL)
	{
		//�ʒu�ݒ�
		pWarning->SetPos(Pos);
		//�T�C�Y�ݒ�
		pWarning->SetSize(D3DXVECTOR3(SIZE_X, SIZE_Y, 0.0f));
		//����������
		pWarning->Init();
	}

	return pWarning;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWarning::Init(void)
{
	//�T�E���h�|�C���^�擾
	CSound *pSound = CManager::GetSound();	
	//�T�E���h�Đ�
	pSound->Play(CSound::LABEL_SE_WARNING);

	//�e�N�X�`���ݒ�p�ϐ�
	D3DXVECTOR2 Texture[4];

	//����������
	CScene2d::Init();
	//�e�N�X�`���A�j���[�V�����ݒ�
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 0.0f);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 0.0f);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 1.0f);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 1.0f);
	//�e�N�X�`���A�j���[�V�����Z�b�g
	TextureAnim(Texture);

	//�e�N�X�`���̐ݒ�
	BindTexture(WarningAnim.pTexture);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWarning::Uninit(void)
{
	//�I������
	CScene2d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CWarning::Update(void)
{
	//�A�j���[�V�����ϐ�
	D3DXVECTOR2 Texture[4];
	//����
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 0);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 0);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 1);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 1);
	//�e�N�X�`���Z�b�g
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

//=============================================================================
// �`�揈��
//=============================================================================
void CWarning::Draw(void)
{
	//�`�揈��
	CScene2d::Draw();
}
