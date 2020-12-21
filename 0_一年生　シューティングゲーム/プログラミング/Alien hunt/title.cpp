#include "main.h"
#include "title.h"
#include"fade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//�o�b�t�@�ւ̃|�C���^�[

LPDIRECT3DTEXTURE9 g_pTextureTitlerogo = NULL;//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlerogo = NULL;//�o�b�t�@�ւ̃|�C���^�[

LPDIRECT3DTEXTURE9 g_pTextureTitlePusy = NULL;//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlePusy = NULL;//�o�b�t�@�ւ̃|�C���^�[


TITLE g_Title;
float nCountercol2 = 0.0f;
int nCountercol = 0;
int nSwitch=0;
int siltuti = 0;
/*---------------------------------------------------*/
/*����������										*/
/*-------------------------------------------------*/
void InintTitle(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntTitle = 4; nCntTitle < 7; nCntTitle++)
	{
		g_Title.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Title.move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_Title.bUse = false;
	}
	
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(pDevice, "TEXTURE/bg000.png", &g_pTextureTitle);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX *3,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffTitle,//�ϐ������ς��ƕύX���K�v
		NULL);
	
	D3DXCreateTextureFromFile(pDevice, "TEXTURE/title_logo.png", &g_pTextureTitlerogo);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX *3,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffTitlerogo,//�ϐ������ς��ƕύX���K�v
		NULL);

	D3DXCreateTextureFromFile(pDevice, "TEXTURE/press_enter.png", &g_pTextureTitlePusy);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX * 3,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffTitlePusy,//�ϐ������ς��ƕύX���K�v
		NULL);

	
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾

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
	g_pVtxBuffTitle->Unlock();

	
	g_pVtxBuffTitlerogo->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtx[4].pos = D3DXVECTOR3(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 4, 0.0f);
	pVtx[5].pos = D3DXVECTOR3( SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 4, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 4, 0.0f);
	pVtx[7].pos = D3DXVECTOR3( SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 4, 0.0f);

	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[4].tex = D3DXVECTOR2(0, 0);
	pVtx[5].tex = D3DXVECTOR2(1, 0);
	pVtx[6].tex = D3DXVECTOR2(0, 1);
	pVtx[7].tex = D3DXVECTOR2(1, 1);
	g_pVtxBuffTitlerogo->Unlock();


	g_pVtxBuffTitlePusy->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtx[8].pos = D3DXVECTOR3(-SCREEN_WIDTH / 3, -SCREEN_HEIGHT / 10, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH / 3, -SCREEN_HEIGHT / 10, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(-SCREEN_WIDTH / 3, SCREEN_HEIGHT / 10, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 10, 0.0f);

	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[8].tex = D3DXVECTOR2(0, 0);
	pVtx[9].tex = D3DXVECTOR2(1, 0);
	pVtx[10].tex = D3DXVECTOR2(0, 1);
	pVtx[11].tex = D3DXVECTOR2(1, 1);
	g_pVtxBuffTitlePusy->Unlock();
}
void UpdateTitle(void)
{

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	g_pVtxBuffTitlerogo->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	if (g_Title.bUse == true)
	{
		g_Title.pos += g_Title.move*0.5f;
		pVtx[4].pos = D3DXVECTOR3(g_Title.pos.x + (-SCREEN_WIDTH / 3), g_Title.pos.y + (-SCREEN_HEIGHT / 5), 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_Title.pos.x + (SCREEN_WIDTH / 3), g_Title.pos.y + (-SCREEN_HEIGHT / 5), 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_Title.pos.x + (-SCREEN_WIDTH / 3), g_Title.pos.y + (SCREEN_HEIGHT / 5), 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_Title.pos.x + (SCREEN_WIDTH / 3), g_Title.pos.y + (SCREEN_HEIGHT / 5), 0.0f);
		/*�G����ʊO�ɍs������*/
		if (g_Title.pos.y >=300 )
		{
			/*�g��Ȃ�����*/
			g_Title.pos -= g_Title.move;
		}
	}
	g_pVtxBuffTitlerogo->Unlock();
	g_pVtxBuffTitlePusy->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtx[8].pos = D3DXVECTOR3(650+(-SCREEN_WIDTH / 5), 500 + ( -SCREEN_HEIGHT / 12), 0.0f);
	pVtx[9].pos = D3DXVECTOR3(650+(SCREEN_WIDTH / 5), 500 + (-SCREEN_HEIGHT / 12), 0.0f);
	pVtx[10].pos = D3DXVECTOR3(650+ (-SCREEN_WIDTH /5), 500 + (SCREEN_HEIGHT / 12), 0.0f);
	pVtx[11].pos = D3DXVECTOR3(650+(SCREEN_WIDTH / 5), 500 + (SCREEN_HEIGHT / 12), 0.0f);
	for (int nCnt = 0; nCnt < 1000; nCnt++)
	{
		
		nCountercol++;
		if (nCountercol >= 1000)
		{
			nCountercol = 0;//�J�E���^�[�������l�ɖ߂�

			
			switch (nSwitch)
			{
			case 0:
				nCountercol2+=0.01f;
				if (nCountercol2 >= 1.0f)
				{
					nSwitch = 1;
				}
				break;
			case 1:
				nCountercol2-=0.01f;
				if (nCountercol2 <= 0.0f)
				{
					nSwitch = 0;
				}
				break;
				
			}
		
		}
	}
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, nCountercol2);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, nCountercol2);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, nCountercol2);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, nCountercol2);

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		siltuti++;
	}
	if (siltuti >= 1)
	{
		for (int nCnt = 0; nCnt < 255; nCnt++)
		{

			nCountercol += 1;
			if (nCountercol >= 0)
			{
				nCountercol = 0;//�J�E���^�[�������l�ɖ߂�


				switch (nSwitch)
				{
				case 0:
					nCountercol2 += 0.5f;
					if (nCountercol2 >= 1.0f)
					{
						nSwitch = 1;
					}
					break;
				case 1:
					nCountercol2 -= 0.1f;
					if (nCountercol2 <= 0.0f)
					{
						nSwitch = 0;
					}
					break;

				}

			}
		}
	}
	if (GetKeyboarRelease(DIK_RETURN))	//�G���^�[�L�[�������Ɛi��
	{
		SetFade(MODE_GAME);
	}
	g_pVtxBuffTitlePusy->Unlock();
}
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitle);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTitlerogo, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitlerogo);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, NUM_POLYGON);



	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTitlePusy, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitlePusy);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, NUM_POLYGON);

}
void UninitTitle(void)
{
	//�e�N�X�`���̐ݒ�
	if (g_pTextureTitle!= NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle= NULL;
	}
	
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle= NULL;
	}
	
	
}

void SetTitle(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	g_pVtxBuffTitlerogo->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾

	g_Title.pos = pos;
	

	if (g_Title.bUse == false)
	{
		pVtx[4].pos = D3DXVECTOR3(g_Title.pos.x + (-SCREEN_WIDTH / 2), g_Title.pos.y + (-SCREEN_HEIGHT / 4), 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_Title.pos.x + (SCREEN_WIDTH / 2), g_Title.pos.y + (-SCREEN_HEIGHT / 4), 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_Title.pos.x + (-SCREEN_WIDTH / 2), g_Title.pos.y + (SCREEN_HEIGHT / 4), 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_Title.pos.x + (SCREEN_WIDTH / 2), g_Title.pos.y + (SCREEN_HEIGHT / 4), 0.0f);

		g_Title.bUse = true;
	}
	g_pVtxBuffTitlerogo->Unlock();
}
