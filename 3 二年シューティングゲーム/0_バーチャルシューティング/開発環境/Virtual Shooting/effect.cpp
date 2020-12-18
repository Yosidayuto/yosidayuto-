//�A�b�v�f�[�g�ő傫���F�i���l�j��ύX
//�`�揈���ŉ��Z���v�̐ݒ�(DESTBLEND��ONE)���Ă���QD�̕`�揈�����Ă�
//���̂��Ƃɉ��Z���v�̐ݒ�(DESTBLEND��INVSRCALPHA)�����ɖ߂�
//

//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include"renderer.h"		//�����_�����O
#include"manager.h"			//�}�l�[�W���[
#include "effect.h"
//----------------------------------
//�}�N����`
//----------------------------------
#define EFFECT_LIFE 8		//�o���b�g�̎˒�����
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
LPDIRECT3DTEXTURE9 CEffect::m_pTexture[EFFECT_TYPE_MAX] = {};
char * CEffect::pTexture[EFFECT_TYPE_MAX]=
{
	"data/TEXTURE/Bullet.png",
	"data/TEXTURE/Laser.png"
};

CEffect::CEffect(int nPriorit):CScene2d(nPriorit)
{
	nLife = 0;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);

}

CEffect::~CEffect()
{
}

CEffect * CEffect::Create(D3DXVECTOR3 Pos, D3DXCOLOR col, D3DXVECTOR3 size ,EFFECT_TYPE type)
{
	CEffect *pEffect;
	pEffect = new CEffect;
	pEffect->Set(Pos);
	pEffect->m_Type=type;
	pEffect->Init(size, col);

	return pEffect;
}

void CEffect::Unload(void)
{
	for (int nCount = 0; nCount < EFFECT_TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}

	}
}

HRESULT CEffect::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < EFFECT_TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, pTexture[nCount], &m_pTexture[nCount]);

	}
	return S_OK;
}

HRESULT CEffect::Init(D3DXVECTOR3 size, D3DXCOLOR col)
{
	//�˒�����
	nLife = EFFECT_LIFE;
	//�J���[
	m_col = col;
	//�T�C�Y
	SetSizeition(D3DXVECTOR3(size.x, size.y, 0.0f));
	//�e�N�X�`���̐ݒ�
	BindTexture(m_pTexture[m_Type]);
	//����������
	CScene2d::Init();

	return S_OK;
}

void CEffect::Uninit(void)
{
	//�I������
	CScene2d::Uninit();

}

void CEffect::Update(void)
{
	//�G�t�F�N�g�̑���
	nLife--;

	switch (m_Type)
	{
	case EFFECT_TYPE_BULLET:
		//�傫���̎擾
		m_size = GetSizeition();
		//�傫���̏���
		m_size -= D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		//�|���S���̑傫����n��
		SetSizeition(m_size);
		break;
	}
	m_col = D3DXCOLOR(m_col.r - 0.05f, m_col.g - 0.05f, m_col.b - 0.05f, m_col.a-0.05f);
	//�J���[�Z�b�g
	ColChange(m_col);

	//�X�V����
	CScene2d::Update();
	//�G�t�F�N�g�̏I������
	if (nLife<0)
	{
		Uninit();	//�I������
	}

}

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
