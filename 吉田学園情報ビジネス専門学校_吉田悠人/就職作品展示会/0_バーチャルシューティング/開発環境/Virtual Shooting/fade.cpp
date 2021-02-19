//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : �g�c�I�l
//
//=============================================================================

#include"fade.h"
#include"manager.h"
#include"renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff	= NULL;
	m_ModeNext	= GAME_MODE_TITLE;
	m_Fade		= FADE_NONE;
	m_Color		= D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// �쐬����
//=============================================================================
CFade * CFade::Create(void)
{
	CFade *pFade;
	//�C���X�^���X����
	pFade = new CFade;
	//����������
	if (pFade != NULL)
	{
		pFade->Init();
	}

	return pFade;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFade::Init(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//���_���ւ̃|�C���^�[
	VERTEX_2D *pVtx;
	
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//������ʁi�s�����j


	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�i�E���Őݒ肷��j
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	
	//rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_����ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	
	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;


}

//=============================================================================
// �I������
//=============================================================================
void CFade::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CFade::Update(void)
{
	//���_���ւ̃|�C���^�[
	VERTEX_2D *pVtx;

	//�t�F�[�h������
	if (m_Fade != FADE_NONE)
	{
		//�t�F�[�h�C������
		if (m_Fade == FADE_IN)
		{
			m_Color.a -= FADE_RATE;//���l�����Z���Č��̉�ʂ𕂂��オ�点��

			if (m_Color.a <= 0.0f)
			{
				m_Color.a = 0.0f;
				//�t�F�[�h�����I��
				m_Fade = FADE_NONE;
			}
		}
		//�t�F�[�h�A�E�g����
		else if (m_Fade == FADE_OUT)
		{
			m_Color.a += FADE_RATE;//���l�����Z���Č��̉�ʂ������Ă���

			if (m_Color.a >= 1.0f)
			{
				m_Color.a = 1.0f;
				//�t�F�[�h�C�������ɐ؂�ւ�
				m_Fade = FADE_IN;
				//���[�h��ݒ�
				CManager::SetMode(m_ModeNext);
			}
		}
	}
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���K��
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, 0);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(GAME_MODE mode)
{
	m_Fade = FADE_OUT;
	m_ModeNext = mode;
}
