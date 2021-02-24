//=============================================================================
//
// �{�X�G�t�F�N�g�x�[�X���� [boss effect base.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "boss effect base.h"
#include "boss effect1.h"
#include "boss effect2.h"
#include "boss effect3.h"
#include "delete effect1.h"
#include "delete effect2.h"
#include "delete effect3.h"

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CBossEffectBase::CBossEffectBase(int nPriorit):CScene2d(nPriorit)
{
	m_nMaxCount			= 0;
	m_nMaxCountAnime	= 0;
	m_nCounterAnim		= 0;
	m_nPatternAnimX		= 0;
	m_bLoop				= false;
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CBossEffectBase::~CBossEffectBase()
{
}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CBossEffectBase::Load(void)
{
	CBossEffectType1::Load();
	CBossEffectType2::Load();
	CBossEffectType3::Load();
	CDeleteEffect1::Load();
	CDeleteEffect2::Load();
	CDeleteEffect3::Load();

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CBossEffectBase::Unload(void)
{
	CBossEffectType1::Unload();
	CBossEffectType2::Unload();
	CBossEffectType3::Unload();
	CDeleteEffect1::Unload();
	CDeleteEffect2::Unload();
	CDeleteEffect3::Unload();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossEffectBase::Init(void)
{
	//�e�N�X�`���p
	D3DXVECTOR2 Texture[4];
	//����������
	CScene2d::Init();
	//�e�N�X�`���ݒ�
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount), 0.0f);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount) + (1.0f / (float)m_nMaxCount), 0.0f);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount), 1.0f);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount) + (1.0f / (float)m_nMaxCount), 1.0f);
	//�e�N�X�`���A�j���ݒ�
	TextureAnim(Texture);
	
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CBossEffectBase::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossEffectBase::Update(void)
{
	//�e�N�X�`���p
	D3DXVECTOR2 Texture[4];

	//�e�N�X�`���ݒ�
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount), 0.0f);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount) + (1.0f / (float)m_nMaxCount), 0.0f);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount), 1.0f);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount) + (1.0f / (float)m_nMaxCount), 1.0f);

	//�e�N�X�`���A�j���ݒ�
	TextureAnim(Texture);
	//�A�j���[�V�����J�E���g
	m_nCounterAnim++;
	if (m_nCounterAnim >= m_nMaxCountAnime)
	{
		//�A�j���[�V�����̊G�����̊G�ɕς���
		m_nCounterAnim = 0;
		m_nPatternAnimX++;
		if (m_nPatternAnimX == m_nMaxCount)
		{
			m_nPatternAnimX = 0;
			if (m_bLoop == false)
			{
				Uninit();
				return;
			}
		}
	}

	CScene2d::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBossEffectBase::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// �e�N�X�`���̍ő�R�}���Z�b�^�[
//=============================================================================
void CBossEffectBase::SetMaxTexture(int nMaxTexture)
{
	m_nMaxCount = nMaxTexture;
}

//=============================================================================
// �e�N�X�`���̍ő�R�}���Q�b�^�[
//=============================================================================
int CBossEffectBase::GetMaxTexture(void)
{
	return m_nMaxCount;
}

//=============================================================================
// �A�j���[�V�����J�E���g�Z�b�^�[
//=============================================================================
void CBossEffectBase::SetCountAnime(int nCountAnime)
{
	m_nMaxCountAnime = nCountAnime;
}

//=============================================================================
// �A�j���[�V�����J�E���^�Q�b�^�[
//=============================================================================
int CBossEffectBase::GetCountAnime(void)
{
	return m_nMaxCountAnime;
}

//=============================================================================
// ���[�v�Q�b�^�[
//=============================================================================
void CBossEffectBase::SetLoop(bool bLoop)
{
	m_bLoop = bLoop;
}

//=============================================================================
// ���[�v�Z�b�^�[
//=============================================================================
bool CBossEffectBase::GetLoop(void)
{
	return m_bLoop;
}
