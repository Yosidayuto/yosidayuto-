#include "main.h"
#include "bg.h"

/*�}�N����`*/
#define MAX_BG (128)
/*�\����*/
typedef struct
{
	int nCounterAnim;//�J�E���^�[
	int nPtternAnim;//�p�^�[��No
}BG;
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePolygonBg = NULL;//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonbg = NULL;//�o�b�t�@�ւ̃|�C���^�[

BG g_aBg[MAX_BG];
/*����������*/
void InintPolygonbg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(pDevice, "TEXTURE/bg100.png", &g_pTexturePolygonBg);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffPolygonbg,//�ϐ������ς��ƕύX���K�v
		NULL);

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾

	g_pVtxBuffPolygonbg->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

													  //���_���W�̐ݒ�i�E���Őݒ肷��j

	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	//rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`���̍��W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);
	//���_�f�[�^���A�����b�N����
	g_pVtxBuffPolygonbg->Unlock();

}

void UninitPolygonbg(void)
{



	//�e�N�X�`���̐ݒ�
	if (g_pTexturePolygonBg != NULL)
	{
		g_pTexturePolygonBg->Release();
		g_pTexturePolygonBg = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygonbg != NULL)
	{
		g_pVtxBuffPolygonbg->Release();
		g_pVtxBuffPolygonbg = NULL;
	}
}
void UpdatePolygonbg(void)
{
	VERTEX_2D*pVtx;
	int  nCntBg;
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBuffPolygonbg->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		g_aBg[nCntBg].nCounterAnim++;
		if (g_aBg[nCntBg].nCounterAnim == 5)
		{
			g_aBg[nCntBg].nCounterAnim = 0;//�J�E���^�[�������l�ɖ߂�
			g_aBg[nCntBg].nPtternAnim++;
			if (g_aBg[nCntBg].nPtternAnim == 1000)
			{
				g_aBg[nCntBg].nPtternAnim = 0;

			}

		}
		pVtx[0].tex = D3DXVECTOR2(0.0f, g_aBg[nCntBg].nPtternAnim*0.99f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, g_aBg[nCntBg].nPtternAnim*0.99f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, g_aBg[nCntBg].nPtternAnim*0.99f + 0.99f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, g_aBg[nCntBg].nPtternAnim*0.99f + 0.99f);


	}
	/*���_�f�[�^���A�����b�N*/
	g_pVtxBuffPolygonbg->Unlock();
}
//�`�揈��
void DrawPolygonbg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonbg, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygonBg);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}
