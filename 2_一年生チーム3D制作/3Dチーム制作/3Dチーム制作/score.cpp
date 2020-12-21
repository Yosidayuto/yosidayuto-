#include "score.h"
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCORE (6)	//�X�R�A�̍ő包��
#define SCOREWIDTH (50.0f)
#define SCORE_SIZE (25.0f)
#define SCORE_NNMBER (9)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;					// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore[SCORE_NNMBER] = {};		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nScore[SCORE_NNMBER];					// �X�R�A
D3DXVECTOR3				g_pos[SCORE_NNMBER];					//�ʒu
D3DXVECTOR3				g_size[SCORE_NNMBER];					//�T�C�Y
//=============================================================================
// ����������
//=============================================================================

void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nScore = 0; nScore < SCORE_NNMBER; nScore++)
	{
		// �X�R�A�̏�����
		g_nScore[nScore] = 0;
	}/*�ʒu*/
	g_pos[0] = D3DXVECTOR3(1130, 530, 0);	//���v
	g_pos[1] = D3DXVECTOR3(860, 235, 0);	//�A�C�e�����C��
	g_pos[2] = D3DXVECTOR3(860, 278, 0);	//�A�C�e����
	g_pos[3] = D3DXVECTOR3(860, 320, 0);	//�A�C�e����
	g_pos[4] = D3DXVECTOR3(860, 360, 0);	//�A�C�e����

	g_pos[5] = D3DXVECTOR3(1100, 235, 0);	//-�A�C�e�����C��
	g_pos[6] = D3DXVECTOR3(1100, 278, 0);	//-�A�C�e����
	g_pos[7] = D3DXVECTOR3(1100, 320, 0);	//-�A�C�e����
	g_pos[8] = D3DXVECTOR3(1100, 360, 0);	//-�A�C�e����
	/*�T�C�Y*/
	g_size[0]= D3DXVECTOR3(80, 80, 0);		//���v
	g_size[1] = D3DXVECTOR3(30, 30, 0);		//�A�C�e�����C��
	g_size[2] = D3DXVECTOR3(30, 30, 0);		//�A�C�e����
	g_size[3] = D3DXVECTOR3(30, 30, 0);		//�A�C�e����
	g_size[4] = D3DXVECTOR3(30, 30, 0);		//�A�C�e����

	g_size[5] = D3DXVECTOR3(30, 30, 0);		//-�A�C�e�����C��
	g_size[6] = D3DXVECTOR3(30, 30, 0);		//-�A�C�e����
	g_size[7] = D3DXVECTOR3(30, 30, 0);		//-�A�C�e����
	g_size[8] = D3DXVECTOR3(30, 30, 0);		//-�A�C�e����
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		"�摜/�X�R�A2.png",		// �t�@�C���̖��O
		&g_pTextureScore);				// �e�N�X�`���ւ̃|�C���^
	// ���_���̍쐬
	MakeVertexScore(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	for (int nScore = 0; nScore < SCORE_NNMBER; nScore++)
	{
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffScore != NULL)
		{
			g_pVtxBuffScore[nScore]->Release();
			g_pVtxBuffScore[nScore] = NULL;
		}
	}
	
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	for (int nScore = 0; nScore < SCORE_NNMBER; nScore++)
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffScore[nScore], 0, sizeof(VERTEX_2D));	
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureScore);
		for (int nCntTex = 0; nCntTex < MAX_SCORE; nCntTex++)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTex, 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^
	for (int nScore = 0; nScore < SCORE_NNMBER; nScore++)
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffScore[nScore],
			NULL);

		//���_�����b�N���A���_�f�[�^�ւ̃|�C���^�擾
		g_pVtxBuffScore[nScore]->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntPos = 0; nCntPos < MAX_SCORE; nCntPos++, pVtx += 4)
		{
			if (nScore == 0)
			{
				//���_���̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(-g_size[nScore].x / 2 + g_pos[nScore].x, -g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * SCOREWIDTH, 0.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_size[nScore].x / 2 + g_pos[nScore].x, -g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * SCOREWIDTH, 0.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_size[nScore].x / 2 + g_pos[nScore].x, g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * SCOREWIDTH, 0.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_size[nScore].x / 2 + g_pos[nScore].x, g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * SCOREWIDTH, 0.0f, 0.0f);

			}
			else
			{
				//���_���̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(-g_size[nScore].x / 2 + g_pos[nScore].x, -g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * 30.0f, 0.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_size[nScore].x / 2 + g_pos[nScore].x, -g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * 30.0f, 0.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_size[nScore].x / 2 + g_pos[nScore].x, g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * 30.0f, 0.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_size[nScore].x / 2 + g_pos[nScore].x, g_size[nScore].y / 2 + g_pos[nScore].y, 0.0f) -= D3DXVECTOR3(nCntPos * 30.0f, 0.0f, 0.0f);

			}
		
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//�F�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffScore[nScore]->Unlock();
	}

}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddScore(int nValue, int nType)
{
	
	float fTex[MAX_SCORE][SCORE_NNMBER];
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^
	/*�X�R�A����*/
	if (nType == 1)
	{//���C���A�C�e��
		nValue *= 10000;
	}
	else if (nType == 2)
	{//�A�C�e����
		nValue *= 5000;
	}
	else if (nType == 3)
	{//�A�C�e����
		nValue *= 2500;
	}
	else if(nType == 4)
	{//�A�C�e����
		nValue *= 1000;
	}

	/*�}�C�i�X�X�R�A*/
	else if (nType == 5)
	{//���C���A�C�e��
		nValue *= 3000;
	}
	else if (nType == 6)
	{//�A�C�e����
		nValue *= 1000;
	}
	else if (nType == 7)
	{//�A�C�e����
		nValue *= 800;
	}
	else if (nType == 8)
	{//�A�C�e����
		nValue *= 200;
	}

	g_nScore[nType] += nValue;
	g_nScore[0] = g_nScore[1] + g_nScore[2] + g_nScore[3] + g_nScore[4];
	for (int nScore = 0; nScore < SCORE_NNMBER; nScore++)
	{
		fTex[0][nScore] = g_nScore[nScore] % 10 * 0.1f;
		fTex[1][nScore] = g_nScore[nScore] / 10 % 10 * 0.1f;
		fTex[2][nScore] = g_nScore[nScore] / 100 % 10 * 0.1f;
		fTex[3][nScore] = g_nScore[nScore] / 1000 % 10 * 0.1f;
		fTex[4][nScore] = g_nScore[nScore] / 10000 % 10 * 0.1f;
		fTex[5][nScore] = g_nScore[nScore] / 100000 % 10 * 0.1f;
		/*fTex[6][nScore] = g_nScore[nScore] / 1000000 % 10 * 0.1f;
		fTex[7][nScore] = g_nScore[nScore] / 10000000 % 10 * 0.1f;*/
		//���_�����b�N���A���_�f�[�^�ւ̃|�C���^�擾
		g_pVtxBuffScore[nScore]->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntPos = 0; nCntPos < MAX_SCORE; nCntPos++, pVtx += 4)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2((0.1f + fTex[nCntPos][nScore]) - 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((0.1f + fTex[nCntPos][nScore]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((0.1f + fTex[nCntPos][nScore]) - 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((0.1f + fTex[nCntPos][nScore]), 1.0f);
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffScore[nScore]->Unlock();
	}
	
}