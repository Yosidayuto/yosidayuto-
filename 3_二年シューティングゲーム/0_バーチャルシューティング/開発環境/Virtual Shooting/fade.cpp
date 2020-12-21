#include"fade.h"
#include"manager.h"
#include"renderer.h"
//----------------------------------
//�}�N����`
//----------------------------------
#define FADE_RATE (0.01f)
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
LPDIRECT3DTEXTURE9 CFade::m_pTexture = NULL;

//----------------------------------
//�R���X�g���N�^
//----------------------------------
CFade::CFade()
{
	//�t�F�[�h���[�h
	m_Fade = FADE_OUT;
	//������ʁi�����j
	m_Color= D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	

}

//----------------------------------
//�f�X�g���N�^
//----------------------------------
CFade::~CFade()
{
}


//----------------------------------
//����������
//----------------------------------
HRESULT CFade::Init(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();


	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&m_pVtxBuff,//�ϐ������ς��ƕύX���K�v
		NULL);
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH , 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH , SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`���̐���
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);


	// ���_����ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	
	//rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;


}

//----------------------------------
//�I������
//----------------------------------
void CFade::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//----------------------------------
//�X�V����
//----------------------------------
void CFade::Update(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	if (m_Fade != FADE_NONE)
	{//�t�F�[�h������
		if (m_Fade == FADE_IN)
		{//�t�F�[�h�C������
			m_Color.a -= FADE_RATE;			//a�l�����Z���Č��̉�ʂ𕂂��オ�点��
			if (m_Color.a <= 0.0f)
			{
				/*�t�F�[�h�����I��*/
				m_Color.a = 0.0f;
				m_Fade = FADE_NONE;
			}
		}
		else if (m_Fade == FADE_OUT)
		{//�t�F�[�h�A�E�g����
			m_Color.a += FADE_RATE;			//a�l�����Z���Č��̉�ʂ������Ă���
			if (m_Color.a >= 1.0f)
			{
				/*�t�F�[�h�C�������ɐ؂�ւ�*/
				m_Color.a = 1.0f;
				m_Fade = FADE_IN;
				/*���[�h��ݒ�*/
				CManager::SetMode(m_ModeNext);
			}
		}

	}

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();


}

//----------------------------------
//�`�揈��
//----------------------------------
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
//----------------------------------
//�t�F�[�h�̏�Ԑݒ�
//----------------------------------
bool CFade::Set(CManager::GAME_MODE modeNext)
{
	if (m_Fade == FADE_NONE)
	{
		m_Fade = FADE_OUT;
		m_ModeNext = modeNext;
		m_bFade = true;
		return true;
	}
	return false;
}

CFade::FADE CFade::Get(void)
{
	return m_Fade;
}
