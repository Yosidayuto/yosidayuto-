//=============================================================================
//
//	�X�s�[�h�{�^��[speed button.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "speed button.h"
#include "renderer.h"
#include "manager.h"
#include "score.h"
#include "select.h"
#include "sound.h"
#include "player data.h"
#include "ui count.h"
#include "telop.h"
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CSpeedButton::m_TextureData = { NULL,	"data/TEXTURE/Text_Speed.png", };
int CSpeedButton::m_nScoreCount[PLAYER_LIFE_UP] =
{
	4000,
	5000,
	6000,
	7000,
	8000,
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSpeedButton::CSpeedButton(int nPriorit) :CButton(nPriorit)
{
	m_SpeedCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSpeedButton::~CSpeedButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CSpeedButton::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CSpeedButton::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
}

//=============================================================================
// ��������
//=============================================================================
CSpeedButton * CSpeedButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CSpeedButton *pLifeButton = NULL;
	pLifeButton = new CSpeedButton;

	//NULL�`�F�b�N
	if (pLifeButton != NULL)
	{
		//�ʒu�ݒ�
		pLifeButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//�T�C�Y�ݒ�
		pLifeButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//�e�N�X�`���ݒ�
		pLifeButton->BindTexture(m_TextureData.m_Texture);
		//����������
		pLifeButton->Init();

	}
	return pLifeButton;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSpeedButton::Init(void)
{
	//�{�^���̏���������
	CButton::Init();
	//�ʒu�ݒ�
	SetPos(D3DXVECTOR3(GetPos().x + 85, GetPos().y, 0.0f));
	//������
	m_SpeedCount = (int)(CManager::GetPlayer()->GetSpeedData());

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSpeedButton::Uninit(void)
{
	CButton::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSpeedButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSpeedButton::Draw(void)
{
	CButton::Draw();
}

//=============================================================================
// �}�E�X�I�[�o�[����
//=============================================================================
void CSpeedButton::MouseOver(void)
{
	//�X�R�A�����ʎ擾
	CScore*		pMinusScore = CSelect::GetMinusScore();
	//�e���b�v�|�C���^
	CTelop*		pTelop = CSelect::GetTelop();

	//����X�R�A�\��
	if (CManager::GetPlayer()->GetSpeedData() <= PLAYER_SPEED_UP)
	{
		//����X�R�A���f
		pMinusScore->SetScore(m_nScoreCount[m_SpeedCount]);
	}
	//�e���b�v�ؑ�
	if (pTelop->GetTelopType() != TELOP_TYPE_SPEEDUP)
	{
		pTelop->TypeChange(TELOP_TYPE_SPEEDUP);
	}
}

//=============================================================================
// �v�b�V�����菈��
//=============================================================================
void CSpeedButton::Push(void)
{
	//�}�E�X�|�C���^�擾
	CInihMouse* pMouse		= CManager::GetMouse();
	//�X�R�A
	CScore*		Score		= CSelect::GetScore();
	//���C�t�������l�p�i���o�[�擾
	CUiCount*	pNumber		= CSelect::GetNumber(CSelect::NUMBER_TYPE_SPEED);


	//���N���b�N
	if (pMouse->GetClickTrigger(CLICK_LEFT) == true)
	{
		//�X�s�[�h�A�b�v����
		if (SpeedUp())
		{
			//�X�s�[�h�J�E���^�[�ɔ��f
			pNumber->SetCount(m_SpeedCount + 1);
			//�X�R�A�̌���
			Score->AddScore(-m_nScoreCount[m_SpeedCount]);
			//�����񐔐ݒ�
			m_SpeedCount = (int)(CManager::GetPlayer()->GetSpeedData());
		}
	}
	//�E�N���b�N
	else if (pMouse->GetClickTrigger(CLICK_RIGHT) == true)
	{
		//�X�s�[�h�_�E������
		if (SpeedDown())
		{
			//�X�s�[�h�J�E���^�[�ɔ��f
			pNumber->SetCount(m_SpeedCount - 1);
			//�X�R�A�̉��Z
			Score->AddScore(m_nScoreCount[m_SpeedCount - 1]);
			//�����񐔐ݒ�
			m_SpeedCount = (int)(CManager::GetPlayer()->GetSpeedData());

		}
	}
}

//=============================================================================
// �X�s�[�h��������
//=============================================================================
bool CSpeedButton::SpeedUp(void)
{
	//�T�E���h�擾
	CSound*		pSound = CManager::GetSound();
	//�擾�X�R�A�f�[�^�擾
	int			nScore = CSelect::GetScore()->GetScore();
	// �X�s�[�h�擾
	float		fSpeed = CManager::GetPlayer()->GetSpeedData();
	//�X�s�[�h�A�b�v�ł�����
	bool		bSpeedUp = false;

	// �X�s�[�h���ő勭������Ă��邩
	if (fSpeed<PLAYER_SPEED_UP
		&& nScore>m_nScoreCount[m_SpeedCount])
	{
		//�N���b�N��SE
		pSound->Play(CSound::LABEL_SE_CLICK);
		//�X�s�[�h�A�b�v
		fSpeed++;
		//�v���C���[�f�[�^�ɔ��f
		CManager::GetPlayer()->SetSpeedData(fSpeed);
		//���C�t�A�b�v
		bSpeedUp = true;
	}
	return bSpeedUp;
}

//=============================================================================
// �X�s�[�h��������
//=============================================================================
bool CSpeedButton::SpeedDown(void)
{	//�T�E���h�擾
	CSound*		pSound = CManager::GetSound();
	//�X�s�[�h�擾
	float		fSpeed = CManager::GetPlayer()->GetSpeedData();
	//���C�t�_�E���ł�����
	bool		bSpeedDown = false;
	if (fSpeed>0.0f)
	{
		//�N���b�N��SE
		pSound->Play(CSound::LABEL_SE_CANCEL);
		//���C�t�_�E��
		fSpeed--;
		//�v���C���[�f�[�^�ɔ��f
		CManager::GetPlayer()->SetSpeedData(fSpeed);
		//���C�t�_�E��
		bSpeedDown = true;
	}
	return bSpeedDown;
}
