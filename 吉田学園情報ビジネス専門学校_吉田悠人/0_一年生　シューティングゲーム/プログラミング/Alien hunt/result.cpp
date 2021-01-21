#include "main.h"
#include "result.h"
#include "score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;//�o�b�t�@�ւ̃|�C���^�[

LPDIRECT3DTEXTURE9 g_pTextureResultRogo = NULL;//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultRogo = NULL;//�o�b�t�@�ւ̃|�C���^�[


int nCutScore01 = 0;
int nCutScore02 = 0;
/*---------------------------------------------------*/
/*����������										*/
/*-------------------------------------------------*/
void InintResult(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(pDevice, "TEXTURE/bg000.png", &g_pTextureResult);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*2,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffResult,//�ϐ������ς��ƕύX���K�v
		NULL);
	
	/*-----------------------------------------------------------------------------------------------------------------------*/

	D3DXCreateTextureFromFile(pDevice, "TEXTURE/gameover_logo.png", &g_pTextureResultRogo);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*2,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffResultRogo,//�ϐ������ς��ƕύX���K�v
		NULL);

	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾

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
	g_pVtxBuffResult->Unlock();

	/*------------------------------------------------------------------------------------------------------------------------------------*/

	g_pVtxBuffResultRogo->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾

	pVtx[4].pos = D3DXVECTOR3(-SCREEN_WIDTH/3, -SCREEN_HEIGHT/5, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH/3, -SCREEN_HEIGHT/5, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-SCREEN_WIDTH/3, SCREEN_HEIGHT/5, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH/3, SCREEN_HEIGHT/5, 0.0f);
	//rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;
	//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`���̍��W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0, 0);
	pVtx[5].tex = D3DXVECTOR2(1, 0);
	pVtx[6].tex = D3DXVECTOR2(0, 1);
	pVtx[7].tex = D3DXVECTOR2(1, 1);
	//���_�f�[�^���A�����b�N����
	g_pVtxBuffResultRogo->Unlock();
	
}
void UpdateResult(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	g_pVtxBuffResultRogo->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾

	pVtx[4].pos = D3DXVECTOR3(650+(-SCREEN_WIDTH / 3), 300+(-SCREEN_HEIGHT / 5), 0.0f);
	pVtx[5].pos = D3DXVECTOR3(650+( SCREEN_WIDTH / 3), 300+(-SCREEN_HEIGHT / 5), 0.0f);
	pVtx[6].pos = D3DXVECTOR3(650+(-SCREEN_WIDTH / 3), 300+( SCREEN_HEIGHT / 5), 0.0f);
	pVtx[7].pos = D3DXVECTOR3(650+( SCREEN_WIDTH / 3), 300+( SCREEN_HEIGHT / 5), 0.0f);
	
	for (int nCnt = 0; nCnt < 255; nCnt++)
	{
		nCutScore01++;
		if (nCutScore01 == 500)
		{
			nCutScore01 = 0;//�J�E���^�[�������l�ɖ߂�
			nCutScore02++;
			if (nCutScore02 >= 255)
			{
				nCutScore02 = 255;
			}
		}
	}
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, nCutScore02);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, nCutScore02);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, nCutScore02);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, nCutScore02);

	g_pVtxBuffResultRogo->Unlock();//���_�f�[�^���A�����b�N����

}
void UninitResult(void)
{
//�e�N�X�`���̐ݒ�
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}
void DrawResult(void) 
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	/*----------------------------------------------------------------------*/
	
	
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffResultRogo, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResultRogo);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, NUM_POLYGON);
}