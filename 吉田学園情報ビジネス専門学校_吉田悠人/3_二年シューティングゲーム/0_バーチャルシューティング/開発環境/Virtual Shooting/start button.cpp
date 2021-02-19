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
int			CStartButton::m_StageNuber = 0;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStartButton::CStartButton(int nPriorit):CButton(nPriorit)
{
	m_pNumber = NULL;
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
CStartButton * CStartButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CStartButton *pStartButton;
	pStartButton = new CStartButton;

	//�ʒu�ݒ�
	pStartButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
	//�T�C�Y�ݒ�
	pStartButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
	//�e�N�X�`���ݒ�
	pStartButton->BindTexture(m_TextureData.m_Texture);
	//����������
	pStartButton->Init();
	return pStartButton;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CStartButton::Init(void)
{
	m_pNumber = CNumber::Create(D3DXVECTOR3(GetPos().x + 65, GetPos().y, 0.0f), D3DXVECTOR3(25.0f, GetSize().y, 0.0f));
	m_pNumber->SetNumber(m_StageNuber + 1);
	CButton::Init();
	SetPos(D3DXVECTOR3(GetPos().x + 20, GetPos().y,0.0f));
	SetSize(D3DXVECTOR3(GetSize().x-100, GetSize().y,0.0f));
	return E_NOTIMPL;
}

//=============================================================================
// �I������
//=============================================================================
void CStartButton::Uninit(void)
{
	if (m_pNumber != NULL)
	{
		m_pNumber->Uninit();
	}

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
	if (m_pNumber != NULL)
	{
		m_pNumber->Draw();
	}

	CButton::Draw();
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
	//�{�^������x�ł���������
	//static bool bPush = false;
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
		//if (bPush==false)
		{
			//�������ǂ�����������Ă��邩
			if (nPlayerWeapon.Left != WEAPONS_MODE_NONE
				|| nPlayerWeapon.Right != WEAPONS_MODE_NONE)
			{
				//SE��
				pSound->Play(CSound::LABEL_SE_START);
				//�t�F�C�h�A�E�g����
				pFade->SetFade(GAME_MODE_STAGE);
				//�X�e�[�W�ԍ���i�߂�
				m_StageNuber += 1;
				//�{�^����������
				//bPush = true;
			}

		}

	}
}
