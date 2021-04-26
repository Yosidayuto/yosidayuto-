//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff		= NULL;
	m_color			= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fade			= FADE_NONE;
	m_ManagerMode	= CManager::MODE_TITLE;
	m_StageMode		= CGame::MAP_TYPE_1;
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
	//�������m��
	CFade* pFade = NULL;
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
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();
	//���_�o�b�t�@����
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���K��
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�i�E���Őݒ肷��j
	pVtx[0].pos = D3DXVECTOR3(00.0f, 00.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 00.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(00.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�i�l��1.0�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	//������
	m_fade = FADE_NONE;

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
	
	//�t�F�[�h����
	Fadeout();

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���K��
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, NULL);

	//�|���S���`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// �Ó]����
//=============================================================================
void CFade::Fadeout(void)
{
	//�t�F�[�h������
	if (m_fade != FADE_NONE)
	{
		//�t�F�[�h�C������
		if (m_fade == FADE_IN)
		{
			m_color.a -= FADE_RATE;//���l�����Z���Č��̉�ʂ𕂂��オ�点��

			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				//�t�F�[�h�����I��
				m_fade = FADE_NONE;
			}
		}
		//�t�F�[�h�A�E�g����
		else if (m_fade == FADE_OUT)
		{
			m_color.a += FADE_RATE;//���l�����Z���Č��̉�ʂ������Ă���

			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;
				//�t�F�[�h�C�������ɐ؂�ւ�
				m_fade = FADE_IN;

				//���[�h��ݒ�
				switch (m_FadeType)
				{
				case FADE_TYPE_MANAGER:
					CManager::SetMode(m_ManagerMode);

					break;
				case FADE_TYPE_STAGE:
					CGame::SetMapMode(m_StageMode);

					break;

				}
			}
		}
	}

}

//=============================================================================
// �u���b�N�A�E�g����
//=============================================================================
void CFade::SetBlackout(CManager::MODE mode)
{
	if (m_fade == FADE_NONE)
	{
		m_color			= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);// ������ʁi�s�����j
		m_fade			= FADE_OUT;							// �t�F�[�h�󋵐ݒ�
		m_ManagerMode	= mode;								// �t�F�[�h�A�E�g������
		m_FadeType		= FADE_TYPE_MANAGER;						// �t�F�[�h���郂�[�h
	}
}


//=============================================================================
// �z���C�g�A�E�g����
//=============================================================================
void CFade::SetWhiteout(CGame::MAP_TYPE mode)
{
	if (m_fade == FADE_NONE)
	{
		m_color		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);// ������ʁi�s�����j
		m_fade		= FADE_OUT;							// �t�F�[�h�󋵐ݒ�
		m_StageMode = mode;								// �t�F�[�h�A�E�g������
		m_FadeType	= FADE_TYPE_STAGE;						// �t�F�[�h���郂�[�h
	}
}
