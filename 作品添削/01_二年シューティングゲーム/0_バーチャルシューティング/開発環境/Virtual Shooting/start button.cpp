//=============================================================================
//
//	�X�^�[�g�{�^��[start button.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "start button.h"
#include "renderer.h"
#include "manager.h"
#include "fade.h"
#include "number.h"
#include "sound.h"
#include "game.h"
#include "player.h"
#include "player data.h"
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CStartButton::m_TextureData = {NULL,	"data/TEXTURE/Text_Start.png",};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStartButton::CStartButton(int nPriorit):CButton(nPriorit)
{
	m_pNumber = NULL;
	m_bPush = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStartButton::~CStartButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CStartButton::Load(void)
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
void CStartButton::Unload(void)
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
CStartButton * CStartButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nStage)
{
	//�������m��
	CStartButton *pStartButton = NULL;
	pStartButton = new CStartButton;
	
	//NULL�`�F�b�N
	if (pStartButton != NULL)
	{
		//�ʒu�ݒ�
		pStartButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//�T�C�Y�ݒ�
		pStartButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//�e�N�X�`���ݒ�
		pStartButton->BindTexture(m_TextureData.m_Texture);
		//�X�e�[�W�ݒ�
		pStartButton->SetStage(nStage+1);
		//����������
		pStartButton->Init();

	}
	return pStartButton;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CStartButton::Init(void)
{
	//���݂̃X�e�[�W�ԍ�
	m_pNumber = CNumber::Create(D3DXVECTOR3(GetPos().x + 65, GetPos().y, 0.0f), D3DXVECTOR3(25.0f, GetSize().y, 0.0f));
	m_pNumber->SetNumber(nStage);
	
	//�{�^���̏���������
	CButton::Init();
	
	//�����̈ʒu����
	SetPos(D3DXVECTOR3(GetPos().x + 20, GetPos().y,0.0f));
	SetSize(D3DXVECTOR3(GetSize().x-100, GetSize().y,0.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CStartButton::Uninit(void)
{
	//NULL�`�F�b�N
	if (m_pNumber != NULL)
	{
		m_pNumber->Uninit();
	}
	//�I������
	CButton::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CStartButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CStartButton::Draw(void)
{
	//NULL�`�F�b�N
	if (m_pNumber != NULL)
	{
		m_pNumber->Draw();
	}

	CButton::Draw();
}

//=============================================================================
// �X�e�[�W�ԍ��Q�b�^�[
//=============================================================================
void CStartButton::SetStage(int stage)
{
	nStage = stage;
}

//=============================================================================
// �}�E�X�I�[�o�[����
//=============================================================================
void CStartButton::MouseOver(void)
{

}

//=============================================================================
// �v�b�V�����菈��
//=============================================================================
void CStartButton::Push()
{
	//�}�E�X�|�C���^�擾
	CInihMouse *pMouse = CManager::GetMouse();
	//�T�E���h�擾
	CSound*		pSound = CManager::GetSound();	
	//�t�F�C�h�擾
	CFade*		pFade = CManager::GetFade();	
	//�v���C���[�E�F�|���擾
	WEAPON_DATA nPlayerWeapon = CManager::GetPlayer()->GetWeaponData();

	//���N���b�N
	if (pMouse->GetClickTrigger(CLICK_LEFT) == true)
	{
		//�{�^������������
		if (m_bPush == false)
		{
			//�������ǂ�����������Ă��邩
			if (nPlayerWeapon.Left != WEAPONS_MODE_NONE
				|| nPlayerWeapon.Right != WEAPONS_MODE_NONE)
			{
				//SE��
				pSound->Play(CSound::LABEL_SE_START);
				//�t�F�C�h�A�E�g����
				pFade->SetFade(GAME_MODE_STAGE);
				//�{�^����������
				m_bPush = true;
			}
		}
	}
}
