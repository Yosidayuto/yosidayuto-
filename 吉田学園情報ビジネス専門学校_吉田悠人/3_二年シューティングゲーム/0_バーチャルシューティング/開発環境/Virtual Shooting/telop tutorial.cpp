//=============================================================================
//
//	�`���[�g���A���e���b�v[telop tutorial.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "telop tutorial.h"
#include "telop.h"
#include "manager.h"
#include "renderer.h"


//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CTelopTutorial::m_TextureData = { NULL,"data/TEXTURE/Telop_Normal.png" };
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CTelopTutorial::CTelopTutorial(int nPriorit) :CScene2d(nPriorit)
{
	m_nPatternAnim = NULL;
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CTelopTutorial::~CTelopTutorial()
{

}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CTelopTutorial::Load(void)
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
// �e�N�X�`���j������
//=============================================================================
void CTelopTutorial::Unload(void)
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
CTelopTutorial * CTelopTutorial::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CTelopTutorial* pTelopText = NULL;
	pTelopText = new CTelopTutorial;

	//NULL�`�F�b�N
	if (pTelopText != NULL)
	{
		//�ʒu�ݒ�
		pTelopText->SetPos(D3DXVECTOR3(pos.x - TELOP_X_SIZE / 2, pos.y, pos.z));
		//�T�C�Y�ݒ�
		pTelopText->SetSize(D3DXVECTOR3(size.x - TELOP_X_SIZE, size.y - TELOP_Y_SIZE, size.z));
		//����������
		pTelopText->Init();
	}

	return pTelopText;
}


//=============================================================================
// ����������
//=============================================================================
HRESULT CTelopTutorial::Init(void)
{
	//�e�N�X�`���ݒ�
	BindTexture(m_TextureData.m_Texture);
	//�A�C�R���̏���������
	CScene2d::Init();
	TelopMove();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTelopTutorial::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTelopTutorial::Update(void)
{
	CScene2d::Update();
	TelopMove();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTelopTutorial::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// �e���b�v���񂷏���
//=============================================================================
void CTelopTutorial::TelopMove(void)
{
	// �e�N�X�`���̃A�j���[�V���������p
	D3DXVECTOR2 Texture[4];
	//�A�j���[�V�����J�E���g
	static int nCounterAnim = 0;
	//�A�j���[�V�����J�E���g���Z
	nCounterAnim++;
	//���̐��l�ɂȂ�����
	if (nCounterAnim%2)
	{
		//�A�j���[�V������������
		m_nPatternAnim++;
		//���l�̏�����
		nCounterAnim = 0;
		if (m_nPatternAnim>= 10000)
		{
			//�A�j���[�V�����̏�����
			m_nPatternAnim = 0;
		}
	}

	Texture[0] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f), 0.0f);
	Texture[1] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f) + (1.0f / 6.0f), 0.0f);
	Texture[2] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f), 1.0f);
	Texture[3] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f) + (1.0f / 6.0f), 1.0f);

	//�A�j���[�V�����̈ړ��ʂ̃Z�b�g
	TextureAnim(Texture);
}
