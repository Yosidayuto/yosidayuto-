#include "main.h"
#include "gameover.h"
#include "input.h"
#include "fade.h"
#include "Game.h"
#include "sound.h"
/*�O���[�o���ϐ�*/
LPDIRECT3DTEXTURE9 g_pTextureGameover[GAMEOVER_TEXTURE_MAX] = {};//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxGameover[GAMEOVER_TEXTURE_MAX] = {};//�o�b�t�@�ւ̃|�C���^�[
GAMEOVER g_Gameover[GAMEOVER_TEXTURE_MAX];
int g_nSelectGameover;	//�I��
typedef struct
{
	char *pFilename;	// �t�@�C����
}FILE_GAMEOVER;
/*�t�@�C��*/
FILE_GAMEOVER g_File[GAMEOVER_TEXTURE_MAX] =
{
	{ "data/image/GameOver.png" },
	{ "data/image/RestartButton.png" },
	{ "data/image/ShutDownButton.png" },

};

/*---------------------------------------------------*/
/*����������										*/
/*-------------------------------------------------*/
void InintGameover(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nGameover = 0; nGameover < GAMEOVER_TEXTURE_MAX; nGameover++)
	{
		/*�ʒu�̏�����*/
		g_Gameover[nGameover].pos= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*�I�������̏�����*/
		g_nSelectGameover = 0;
		//�e�N�X�`���̓ǂݍ���	
		D3DXCreateTextureFromFile(pDevice, g_File[nGameover].pFilename, &g_pTextureGameover[nGameover]);
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX * 3,//�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,//(�Œ�)
			FVF_VERTEX_2D,//���_�t�H�[�}�b�g
			D3DPOOL_MANAGED,//�i�Œ�j
			&g_pVtxGameover[nGameover],//�ϐ������ς��ƕύX���K�v
			NULL);
		g_pVtxGameover[nGameover]->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
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
		g_pVtxGameover[nGameover]->Unlock();
	}
	
}
void UpdateGameover(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	/*�w�i*/
	g_pVtxGameover[0]->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_Gameover[0].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Gameover[0].pos.x + -SCREEN_WIDTH / 2, g_Gameover[0].pos.y + -SCREEN_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Gameover[0].pos.x + SCREEN_WIDTH / 2, g_Gameover[0].pos.y + -SCREEN_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Gameover[0].pos.x + -SCREEN_WIDTH / 2, g_Gameover[0].pos.y + SCREEN_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Gameover[0].pos.x + SCREEN_WIDTH / 2, g_Gameover[0].pos.y + SCREEN_HEIGHT / 2, 0.0f);
	g_pVtxGameover[0]->Unlock();
	/*���X�^�[�g�R�}���h*/
	g_pVtxGameover[1]->Lock(0, 0, (void**)&pVtx, 0);
	/*�ʒu�ݒ�*/
	g_Gameover[1].pos = D3DXVECTOR3(425.0f, 540.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Gameover[1].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[1].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Gameover[1].pos.x + GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[1].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Gameover[1].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[1].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Gameover[1].pos.x + GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[1].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	/*�J���[�ݒ�*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	g_pVtxGameover[1]->Unlock();
	/*�I���R�}���h*/
	g_pVtxGameover[2]->Lock(0, 0, (void**)&pVtx, 0);
	/*�ʒu�ݒ�*/
	g_Gameover[2].pos = D3DXVECTOR3(850.0f, 540.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Gameover[2].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[2].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Gameover[2].pos.x + GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[2].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Gameover[2].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[2].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Gameover[2].pos.x + GAMEOVER_COMMAND_SIZE_X / 2, g_Gameover[2].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2, 0.0f);
	/*�J���[�ݒ�*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pVtxGameover[2]->Unlock();
	/*�I������*/
	if (GetKeyboardTrigger(DIK_RIGHT))
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectGameover = 1;
	}
	else if (GetKeyboardTrigger(DIK_LEFT))
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectGameover = 0;
	}
	/*�I����Ԃ�UI*/
	if (g_nSelectGameover == 0)
	{
		g_pVtxGameover[1]->Lock(0, 0, (void**)&pVtx, 0);
		/*�ʒu�ݒ�*/
		pVtx[0].pos = D3DXVECTOR3((g_Gameover[1].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2) + 10, (g_Gameover[1].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_Gameover[1].pos.x + GAMEOVER_COMMAND_SIZE_X / 2) - 10, (g_Gameover[1].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_Gameover[1].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2) + 10, (g_Gameover[1].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_Gameover[1].pos.x + GAMEOVER_COMMAND_SIZE_X / 2) - 10, (g_Gameover[1].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		/*�J���[�ݒ�*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_pVtxGameover[1]->Unlock();
	}
	else
	{
		g_pVtxGameover[2]->Lock(0, 0, (void**)&pVtx, 0);
		/*�ʒu�ݒ�*/
		pVtx[0].pos = D3DXVECTOR3((g_Gameover[2].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2) + 10, (g_Gameover[2].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_Gameover[2].pos.x + GAMEOVER_COMMAND_SIZE_X / 2) - 10, (g_Gameover[2].pos.y + -GAMEOVER_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_Gameover[2].pos.x + -GAMEOVER_COMMAND_SIZE_X / 2) + 10, (g_Gameover[2].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_Gameover[2].pos.x + GAMEOVER_COMMAND_SIZE_X / 2) - 10, (g_Gameover[2].pos.y + GAMEOVER_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		/*�J���[�ݒ�*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_pVtxGameover[2]->Unlock();
	}
	if (GetKeyboardTrigger(DIK_RETURN) && g_nSelectGameover == 0)
	{
		PlaySound(SOUND_LABEL_SE_DECIDED);
	
		SetFade(MODE_TITLE);
	}
	else if (GetKeyboardTrigger(DIK_RETURN) && g_nSelectGameover == 1)
	{
		PlaySound(SOUND_LABEL_SE_DECIDED);
		exit(1);
	}

}
void UninitGameover(void)
{
	for (int nGameover = 0; nGameover < GAMEOVER_TEXTURE_MAX; nGameover++)
	{
		//�e�N�X�`���̐ݒ�
		if (g_pTextureGameover != NULL)
		{
			g_pTextureGameover[nGameover]->Release();
			g_pTextureGameover[nGameover] = NULL;
		}

		//���_�o�b�t�@�̊J��
		if (g_pVtxGameover[nGameover] != NULL)
		{
			g_pVtxGameover[nGameover]->Release();
			g_pVtxGameover[nGameover] = NULL;
		}
	}
}
void DrawGameover(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nGameover = 0; nGameover < GAMEOVER_TEXTURE_MAX; nGameover++)
	{
		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxGameover[nGameover], 0, sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureGameover[nGameover]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}