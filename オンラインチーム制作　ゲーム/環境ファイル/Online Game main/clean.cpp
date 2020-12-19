//=============================================
//
// �������G�t�F�N�g���� [clean.cpp]
// Author : ��R���H
//
//=============================================
//=============================================
// �w�b�_�[�t�@�C��
//=============================================
#include "clean.h"
#include "main.h"
#include "manager.h"

//=============================================
//�ÓI�����o�ϐ��錾
//=============================================
LPDIRECT3DTEXTURE9 CClean::m_pTexture = NULL;
//=============================================
//�C���X�^���X
//=============================================
CClean::CClean()
{
	m_nCountAnime = 0;
	m_nPatternAnime = 0;
}
//=============================================
//�f�X�g���N�^
//=============================================
CClean::~CClean()
{

}
//=============================================
// ��������
//=============================================
CClean * CClean::Create(D3DXVECTOR3 size)
{

	CClean *pClean;
	//�C���X�^���X����
	pClean = new CClean;
	//����������
	pClean->Init(size);
	return pClean;
}
//=============================================
// ����������
//=============================================
HRESULT CClean::Init(D3DXVECTOR3 size)
{
	CScene2D::Init(size);
	//�e�N�X�`���ʒu�ݒ�
	CScene2D::SetAnimation((float)m_nPatternAnime, MAX_ANIMATION);
	//�e�N�X�`���Z�b�g
	BindTexture(m_pTexture);

	return S_OK;
}

//=============================================
// �I������
//=============================================
void CClean::Uninit()
{
	CScene2D::Uninit();
}

//=============================================
// �X�V����
//=============================================
void CClean::Update()
{

	m_nCountAnime++;
	//�A�j���[�V�������x
	if (m_nCountAnime >= 4.5f)
	{
		//�e�N�X�`���A�j���[�V�����Z�b�g
		CScene2D::SetAnimation((float)m_nPatternAnime, MAX_ANIMATION);

		m_nPatternAnime++;

		m_nCountAnime = 0;

		if (m_nPatternAnime >= MAX_ANIMATION)
		{
			Uninit();
		}
	}
}

//=============================================
// �`�揈��
//=============================================
void CClean::Draw()
{
	CScene2D::Draw();
}

//=============================================
// �ǂݍ��ݏ���
//=============================================
HRESULT CClean::Load()
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		CLEAN_TEXTURE,//�t�@�C���̖��O
		&m_pTexture);

	return S_OK;
}

//=============================================
// �ǂݍ��ݔj������
//=============================================
void CClean::Unload()
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}