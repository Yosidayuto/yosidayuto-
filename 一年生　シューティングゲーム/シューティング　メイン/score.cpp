#include"main.h"
#include"score.h"
#include"enemy.h"
LPDIRECT3DTEXTURE9 g_pTexturScore = NULL;//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;//�o�b�t�@�ւ̃|�C���^�[
/*���U���g��ʃX�R�A�J���[*/
int nCutScorecol01;
int nCutScorecol02;
/*�X�R�A�A�b�v�̌v�Z*/
int Score1 = 0;
int Score2 = 0;
int Score3 = 0;


SCORE g_aScore[MAX_SCORE];
void InintScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	int nCntScore;
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		g_aScore[nCntScore].pos= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore[nCntScore].col= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aScore[nCntScore].bUse = false;
		g_aScore[nCntScore].nScoreCnt = 0;
	}

					
	D3DXCreateTextureFromFile(pDevice, "number000.png", &g_pTexturScore);//�e�N�X�`���̓ǂݍ���	
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_SCORE,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffScore,//�ϐ������ς��ƕύX���K�v
		NULL);

	

	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore= nCntScore+4)
	{
		/*���_���W�̐ݒ�i�E���Őݒ肷��*/
		pVtx[0+ nCntScore].pos = D3DXVECTOR3((-SCORE_SION_X / 2), (-SCORE_SION_Y / 2), 0.0f);
		pVtx[1+ nCntScore].pos = D3DXVECTOR3((SCORE_SION_X / 2), (-SCORE_SION_Y / 2), 0.0f);
		pVtx[2+ nCntScore].pos = D3DXVECTOR3((-SCORE_SION_X / 2), (SCORE_SION_Y / 2), 0.0f);
		pVtx[3+ nCntScore].pos = D3DXVECTOR3((SCORE_SION_X / 2), (SCORE_SION_Y / 2), 0.0f);

		/*rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j*/
		pVtx[0+ nCntScore].rhw = 1.0f;
		pVtx[1+ nCntScore].rhw = 1.0f;
		pVtx[2+ nCntScore].rhw = 1.0f;
		pVtx[3+ nCntScore].rhw = 1.0f;

		/*���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j*/
		pVtx[0+ nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1+ nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2+ nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3+ nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0+ nCntScore].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1+ nCntScore].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2+ nCntScore].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3+ nCntScore].tex = D3DXVECTOR2(0.1f, 1.0);
		
	}
	//���_�f�[�^���A�����b�N����
	g_pVtxBuffScore->Unlock();
	
}

void UninitScore(void)
{
	//�e�N�X�`���̐ݒ�
	if (g_pTexturScore != NULL)
	{
		g_pTexturScore->Release();
		g_pTexturScore = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
void UpdateScore(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	MODE mode;
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	/*���U���g��ʃX�R�A����*/
		mode = GetMode();
		if (mode == MODE_RESULE)
		{
			pVtx[0].pos = D3DXVECTOR3(550 + (-SCORE_SION_X*3), 500 + (-SCORE_SION_Y*2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(550 + ( SCORE_SION_X*3), 500 + (-SCORE_SION_Y*2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(550 + (-SCORE_SION_X*3), 500 + ( SCORE_SION_Y*2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(550 + ( SCORE_SION_X*3), 500 + ( SCORE_SION_Y*2), 0.0f);

			pVtx[4].pos = D3DXVECTOR3(650 + (-SCORE_SION_X*3), 500 + (-SCORE_SION_Y*2), 0.0f);
			pVtx[5].pos = D3DXVECTOR3(650 + ( SCORE_SION_X*3), 500 + (-SCORE_SION_Y*2), 0.0f);
			pVtx[6].pos = D3DXVECTOR3(650 + (-SCORE_SION_X*3), 500 + ( SCORE_SION_Y*2), 0.0f);
			pVtx[7].pos = D3DXVECTOR3(650 + ( SCORE_SION_X*3), 500 + ( SCORE_SION_Y*2), 0.0f);


			pVtx[8].pos = D3DXVECTOR3(750 + (-SCORE_SION_X*3), 500 + (-SCORE_SION_Y*2), 0.0f);
			pVtx[9].pos = D3DXVECTOR3(750 + ( SCORE_SION_X*3), 500 + (-SCORE_SION_Y*2), 0.0f);
			pVtx[10].pos= D3DXVECTOR3(750 + (-SCORE_SION_X*3), 500 + ( SCORE_SION_Y*2), 0.0f);
			pVtx[11].pos= D3DXVECTOR3(750 + ( SCORE_SION_X*3), 500 + ( SCORE_SION_Y*2), 0.0f);
		
			/*���U���g��ʃX�R�A�J���[����*/
			for (int nCnt = 0; nCnt < 255; nCnt++)
			{
				nCutScorecol01++;
				if (nCutScorecol01 == 500)
				{
					nCutScorecol01 = 0;//�J�E���^�[�������l�ɖ߂�
					nCutScorecol02++;
					if (nCutScorecol02 >= 255)
					{
						nCutScorecol02 = 255;
					}
				}
			}
			for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore = nCntScore + 4)
			{
				pVtx[0 + nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, nCutScorecol02);
				pVtx[1 + nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, nCutScorecol02);
				pVtx[2 + nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, nCutScorecol02);
				pVtx[3 + nCntScore].col = D3DCOLOR_RGBA(255, 255, 255, nCutScorecol02);
			}
		}

	g_pVtxBuffScore->Unlock();	//���_�f�[�^���A�����b�N����
}
void DrawScore(void)
{
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturScore);
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore*4, NUM_POLYGON);
	}
}
void SetScore(D3DXVECTOR3 pos)
{
	int nCntScore;
	int nCntPos;
	int nCntzi=1;
	VERTEX_2D*pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	for (nCntScore = 0; nCntScore < 1; nCntScore++)
	{
		if (g_aScore[nCntScore].bUse == false)
		{
			g_aScore[nCntScore].pos = pos;
			for (nCntPos = 0; nCntPos < MAX_SCORE; nCntPos = nCntPos + 4)
			{
				/*���_���W�̐ݒ�i�E���Őݒ肷��*/
				pVtx[0 + nCntPos].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x *(nCntzi)+ (-SCORE_SION_X / 2), g_aScore[nCntScore].pos.y + (-SCORE_SION_Y / 2), 0.0f);
				pVtx[1 + nCntPos].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x *(nCntzi)+ (SCORE_SION_X / 2), g_aScore[nCntScore].pos.y + (-SCORE_SION_Y / 2), 0.0f);
				pVtx[2 + nCntPos].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x *(nCntzi)+ (-SCORE_SION_X / 2), g_aScore[nCntScore].pos.y + (SCORE_SION_Y / 2), 0.0f);
				pVtx[3 + nCntPos].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x *(nCntzi)+ (SCORE_SION_X / 2), g_aScore[nCntScore].pos.y + (SCORE_SION_Y / 2), 0.0f);
				nCntzi++;
			}
			/*�g�p���Ă����Ԃɂ���*/
			g_aScore[nCntScore].bUse = true;

			break;
		}
	}

	g_pVtxBuffScore->Unlock();	//���_�f�[�^���A�����b�N����
}
void ScoreUp(int Score)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	
  	Score1 += Score;
 	if (Score1 >= 10)
	{
		Score1 = 0;
		Score2++;
	}
	if (Score2 >= 10)
	{
		Score2 = 0;
		Score3++;
	}
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].tex = D3DXVECTOR2(Score3*0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(Score3*0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(Score3*0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(Score3*0.1f + 0.1f, 1.0);

	pVtx[4].tex = D3DXVECTOR2(Score2*0.1f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(Score2*0.1f + 0.1f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(Score2*0.1f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(Score2*0.1f + 0.1f, 1.0);

	pVtx[8].tex = D3DXVECTOR2(Score1*0.1f	, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(Score1*0.1f+0.1f, 0.0f);
	pVtx[10].tex= D3DXVECTOR2(Score1*0.1f	, 1.0f);
	pVtx[11].tex= D3DXVECTOR2(Score1*0.1f+ 0.1f, 1.0);
	g_pVtxBuffScore->Unlock();
}