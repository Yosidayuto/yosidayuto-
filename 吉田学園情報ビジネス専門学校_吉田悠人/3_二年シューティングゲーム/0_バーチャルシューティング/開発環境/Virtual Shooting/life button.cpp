//=============================================================================
//
//	���C�t�{�^��[life button.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "life button.h"
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
TEXTURE_DATA CLifeButton::m_TextureData = { NULL,	"data/TEXTURE/Text_Life.png", };
int CLifeButton::m_nScoreCount[PLAYER_LIFE_UP]=
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
CLifeButton::CLifeButton(int nPriorit) :CButton(nPriorit)
{
	m_LifeCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLifeButton::~CLifeButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CLifeButton::Load(void)
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
void CLifeButton::Unload(void)
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
CLifeButton * CLifeButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CLifeButton *pLifeButton;
	pLifeButton = new CLifeButton;

	//�ʒu�ݒ�
	pLifeButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
	//�T�C�Y�ݒ�
	pLifeButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
	//�e�N�X�`���ݒ�
	pLifeButton->BindTexture(m_TextureData.m_Texture);
	//����������
	pLifeButton->Init();

	return pLifeButton;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLifeButton::Init(void)
{
	//�{�^���̏���������
	CButton::Init();
	//�ʒu�ݒ�
	SetPos(D3DXVECTOR3(GetPos().x + 85, GetPos().y, 0.0f));
	//������
	m_LifeCount = CManager::GetPlayer()->GetLifeData();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLifeButton::Uninit(void)
{
	CButton::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLifeButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLifeButton::Draw(void)
{

	CButton::Draw();
}

//=============================================================================
// �}�E�X�I�[�o�[����
//=============================================================================
void CLifeButton::MouseOver(void)
{
	//�X�R�A�����ʎ擾
	CScore*		pMinusScore = CSelect::GetMinusScore();
	//�e���b�v�|�C���^
	CTelop*		pTelop = CSelect::GetTelop();
	
	//����X�R�A�\��
	if (CManager::GetPlayer()->GetLifeData() <= PLAYER_LIFE_UP)
	{
		pMinusScore->SetScore(m_nScoreCount[m_LifeCount]);
	}

	//�e���b�v�ؑ�
	if (pTelop->GetTelopType() != TELOP_TYPE_LIFEUP)
	{
		pTelop->TypeChange(TELOP_TYPE_LIFEUP);
	}
}

//=============================================================================
// �v�b�V�����菈��
//=============================================================================
void CLifeButton::Push(void)
{
	//�}�E�X�|�C���^�擾
	CInihMouse* pMouse		= CManager::GetMouse();
	//�X�R�A
	CScore*		Score		= CSelect::GetScore();
	//���C�t�������l�p�i���o�[�擾
	CUiCount*	pNumber		= CSelect::GetNumber(CSelect::NUMBER_TYPE_LIEF);
	
	//���N���b�N
	if (pMouse->GetClickTrigger(CLICK_LEFT) == true)
	{
		//���C�t�A�b�v����
		if (LifeUp())
		{
			//���C�t�J�E���^�[�ɔ��f
			pNumber->SetCount(m_LifeCount + 1);
			//�X�R�A�̌���
			Score->AddScore(-m_nScoreCount[m_LifeCount]);
			//�����񐔐ݒ�
			m_LifeCount = CManager::GetPlayer()->GetLifeData();
		}
	}
	//�E�N���b�N
	else if (pMouse->GetClickTrigger(CLICK_RIGHT) == true)
	{
		//���C�t�_�E������
		if (LifeDown())
		{
			//���C�t�J�E���^�[�ɔ��f
			pNumber->SetCount(m_LifeCount-1);
			//�X�R�A�̉��Z
			Score->AddScore(m_nScoreCount[m_LifeCount-1]);
			//�����񐔐ݒ�
			m_LifeCount = CManager::GetPlayer()->GetLifeData();

		}
	}



}

//=============================================================================
// ���C�t��������
//=============================================================================
bool CLifeButton::LifeUp(void)
{
	//�T�E���h�擾
	CSound*		pSound = CManager::GetSound();
	//�擾�X�R�A�f�[�^�擾
	int			nScore = CSelect::GetScore()->GetScore();
	// ���C�t�擾
	int			nLife = CManager::GetPlayer()->GetLifeData();
	//���C�t�A�b�v�ł�����
	bool		bLifeUp = false;

	// ���C�t���ő勭������Ă��邩
	if (nLife<PLAYER_LIFE_UP
		&& nScore>m_nScoreCount[m_LifeCount])
	{
		//�N���b�N��SE
		pSound->Play(CSound::LABEL_SE_CLICK);
		//���C�t�A�b�v
		nLife++;
		//�v���C���[�f�[�^�ɔ��f
		CManager::GetPlayer()->SetLifeData(nLife);
		//���C�t�A�b�v
		bLifeUp = true;
	}
	return bLifeUp;
}

//=============================================================================
// ���C�t��������
//=============================================================================
bool CLifeButton::LifeDown(void)
{	//�T�E���h�擾
	CSound*		pSound = CManager::GetSound();
	// ���C�t�擾
	int			nLife = CManager::GetPlayer()->GetLifeData();
	//���C�t�_�E���ł�����
	bool		bLifeDown = false;
	// ���C�t����x�ł���������Ă��邩
	if (nLife>0)
	{
		//�N���b�N��SE
		pSound->Play(CSound::LABEL_SE_CANCEL);
		//���C�t�_�E��
		nLife--;
		//�v���C���[�f�[�^�ɔ��f
		CManager::GetPlayer()->SetLifeData(nLife);
		//���C�t�_�E��
		bLifeDown = true;
	}
	return bLifeDown;
}
