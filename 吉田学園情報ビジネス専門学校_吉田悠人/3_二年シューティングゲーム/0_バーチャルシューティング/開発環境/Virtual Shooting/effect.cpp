//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "renderer.h"	
#include "manager.h"	
#include "effect.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define EFFECT_LIFE (8)		//�o���b�g�̎˒�����

//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CEffect::m_TextureData[EFFECT_TYPE_MAX] =
{ {NULL,"data/TEXTURE/Bullet.png"},
{ NULL,	"data/TEXTURE/Laser.png"} };

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEffect::CEffect(int nPriorit):CScene2d(nPriorit)
{
	m_nLife = 0;
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CEffect::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < EFFECT_TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, m_TextureData[nCount].m_cFileName, &m_TextureData[nCount].m_Texture);

	}
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CEffect::Unload(void)
{
	for (int nCount = 0; nCount < EFFECT_TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_TextureData[nCount].m_Texture != NULL)
		{
			m_TextureData[nCount].m_Texture->Release();
			m_TextureData[nCount].m_Texture = NULL;
		}
	}
}

//=============================================================================
// ��������
//=============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 Pos, D3DXCOLOR col, D3DXVECTOR3 size, EFFECT_TYPE type)
{
	//�������m��
	CEffect *pEffect = NULL;
	pEffect = new CEffect;
	
	//NULL�`�F�b�N
	if (pEffect != NULL)
	{
		//�ʒu�Z�b�g
		pEffect->SetPos(Pos);
		//�T�C�Y�Z�b�g
		pEffect->SetSize(D3DXVECTOR3(size.x, size.y, 0.0f));
		//�^�C�v�Z�b�g
		pEffect->m_Type = type;
		//�J���[�Z�b�g
		pEffect->SetCol(col);
		//����������
		pEffect->Init();
	}
	return pEffect;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CEffect::Init(void)
{
	//�˒�����
	m_nLife = EFFECT_LIFE;
	//�e�N�X�`���̐ݒ�
	BindTexture(m_TextureData[m_Type].m_Texture);
	//����������
	CScene2d::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	//�I������
	CScene2d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	//�G�t�F�N�g����
	Effect();
	//�X�V����
	CScene2d::Update();
	//���C�t����
	LifeDown();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	/*�����_�����O�X�e�[�g(���Z��������)*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`�揈��
	CScene2d::Draw();

	/*�����_�[�X�e�[�g*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


}

//=============================================================================
// �G�t�F�N�g����
//=============================================================================
void CEffect::Effect(void)
{
	//�T�C�Y
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�J���[
	D3DXCOLOR col;

	switch (m_Type)
	{
	case EFFECT_TYPE_BULLET:
		//�傫���̎擾
		size = GetSize();
		//�傫���̏���
		size -= D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		//�|���S���̑傫����n��
		SetSize(size);
		break;
	}
	//�J���[�擾
	col = GetCol();
	//�J���[����
	col = D3DXCOLOR(col.r - 0.05f, col.g - 0.05f, col.b - 0.05f, col.a - 0.05f);
	//�J���[�Z�b�g
	SetCol(col);

}

//=============================================================================
//�`�揈��
//=============================================================================
void CEffect::LifeDown(void)
{
	//���C�t����
	m_nLife--;
	//�G�t�F�N�g�̏I������
	if (m_nLife<=0)
	{
		Uninit();	//�I������
	}

}
