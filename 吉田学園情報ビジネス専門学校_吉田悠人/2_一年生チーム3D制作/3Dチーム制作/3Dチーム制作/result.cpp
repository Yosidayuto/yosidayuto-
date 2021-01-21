#include "main.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "time.h"

typedef struct
{
	char *pFilename;	// �t�@�C����

}FILE_RESULT;

/*�O���[�o���ϐ�*/

LPDIRECT3DTEXTURE9 g_pTextureResult[RESULT_TEXTURE_MAX] = {};//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxResult[RESULT_TEXTURE_MAX] = {};//�o�b�t�@�ւ̃|�C���^�[
RESULT g_Result[RESULT_TEXTURE_MAX];
int g_nSelectResult;	//�I��
/*�t�@�C��*/
FILE_RESULT g_File[RESULT_TEXTURE_MAX] =
{
	{ "�摜/���U���g���.png" },
	{ "�摜/���U���g.png" },
	{ "�摜/back.png" },
};

/*---------------------------------------------------*/
/*����������										*/
/*-------------------------------------------------*/
void InintResult(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nResult = 0; nResult < RESULT_TEXTURE_MAX; nResult++)
	{
		/*�ʒu�̏�����*/
		g_Result[nResult].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*�I�������̏�����*/
		g_nSelectResult = 0;											//0���I�����X�^�[�g
		//�e�N�X�`���̓ǂݍ���	
		D3DXCreateTextureFromFile(pDevice, g_File[nResult].pFilename, &g_pTextureResult[nResult]);
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,//�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,//(�Œ�)
			FVF_VERTEX_2D,//���_�t�H�[�}�b�g
			D3DPOOL_MANAGED,//�i�Œ�j
			&g_pVtxResult[nResult],//�ϐ������ς��ƕύX���K�v
			NULL);

		g_pVtxResult[nResult]->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
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
		g_pVtxResult[nResult]->Unlock();
	}
}
void UpdateResult(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	/*�R���g���[���[�̏���*/
	JOYINFOEX JOYPAD;

	/*�W���C�p�b�g�̓���*/
	JOYPAD.dwSize = sizeof(JOYINFOEX);
	JOYPAD.dwFlags = JOY_RETURNALL; // �S�Ă̏����擾

	/*�w�i*/
	g_pVtxResult[0]->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_Result[0].pos= D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Result[0].pos.x + - SCREEN_WIDTH/2, g_Result[0].pos.y + -SCREEN_HEIGHT/2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Result[0].pos.x + SCREEN_WIDTH/2, g_Result[0].pos.y + -SCREEN_HEIGHT/2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Result[0].pos.x +  -SCREEN_WIDTH/2, g_Result[0].pos.y + SCREEN_HEIGHT/2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Result[0].pos.x + SCREEN_WIDTH/2, g_Result[0].pos.y + SCREEN_HEIGHT/2, 0.0f);
	g_pVtxResult[0]->Unlock();
	/*���X�^�[�g�R�}���h*/
	g_pVtxResult[1]->Lock(0, 0, (void**)&pVtx, 0);
	/*�ʒu�ݒ�*/
	g_Result[1].pos = D3DXVECTOR3(425.0f, 640.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Result[1].pos.x + -RESULT_COMMAND_SIZE_X /2, g_Result[1].pos.y + -RESULT_COMMAND_SIZE_Y /2,0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Result[1].pos.x + RESULT_COMMAND_SIZE_X /2, g_Result[1].pos.y + -RESULT_COMMAND_SIZE_Y /2,0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Result[1].pos.x + -RESULT_COMMAND_SIZE_X /2, g_Result[1].pos.y + RESULT_COMMAND_SIZE_Y /2,0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Result[1].pos.x + RESULT_COMMAND_SIZE_X /2, g_Result[1].pos.y + RESULT_COMMAND_SIZE_Y /2,0.0f);
	/*�J���[�ݒ�*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	g_pVtxResult[1]->Unlock();
	/*�I���R�}���h*/
	g_pVtxResult[2]->Lock(0, 0, (void**)&pVtx, 0);
	/*�ʒu�ݒ�*/
	g_Result[2].pos = D3DXVECTOR3(850.0f, 640.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Result[2].pos.x + -RESULT_COMMAND_SIZE_X / 2, g_Result[2].pos.y + -RESULT_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Result[2].pos.x + RESULT_COMMAND_SIZE_X / 2, g_Result[2].pos.y + -RESULT_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Result[2].pos.x + -RESULT_COMMAND_SIZE_X / 2, g_Result[2].pos.y + RESULT_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Result[2].pos.x + RESULT_COMMAND_SIZE_X / 2, g_Result[2].pos.y + RESULT_COMMAND_SIZE_Y / 2, 0.0f);
	/*�J���[�ݒ�*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	g_pVtxResult[2]->Unlock();

	/*�I������*/
	if (joyGetPosEx(JOYSTICKID1, &JOYPAD) == JOYERR_NOERROR)
	{
		if (JOYPAD.dwXpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
		{
			g_nSelectResult = 1;
		}
		if(JOYPAD.dwXpos < 0x7FFF - 0x4000)//�E�ɓ|���X�e�B�b�N
		{
			g_nSelectResult = 0;
		}

		if (JOYPAD.dwButtons & JOY_BUTTON1&&g_nSelectResult == 0)
		{
			SetFade(MODE_TITLE);
		}
		else if (JOYPAD.dwButtons& JOY_BUTTON1&&g_nSelectResult == 1)
		{
			exit(1);
		}

	}
	/*if (GetKeyboardTrigger(DIK_RIGHT))
	{
		
		g_nSelectResult = 1;
	}
	else if (GetKeyboardTrigger(DIK_LEFT))
	{

		g_nSelectResult = 0;
	}*/
	/*�I����Ԃ�UI*/
	if (g_nSelectResult ==0)
	{
		g_pVtxResult[1]->Lock(0, 0, (void**)&pVtx, 0);
		/*�ʒu�ݒ�*/
		/*pVtx[0].pos = D3DXVECTOR3((g_Result[1].pos.x + -RESULT_COMMAND_SIZE_X / 2) + 10, (g_Result[1].pos.y + -RESULT_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_Result[1].pos.x + RESULT_COMMAND_SIZE_X / 2) - 10, (g_Result[1].pos.y + -RESULT_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_Result[1].pos.x + -RESULT_COMMAND_SIZE_X / 2) + 10, (g_Result[1].pos.y + RESULT_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_Result[1].pos.x + RESULT_COMMAND_SIZE_X / 2) - 10, (g_Result[1].pos.y + RESULT_COMMAND_SIZE_Y / 2) - 10, 0.0f);*/
		/*�J���[�ݒ�*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_pVtxResult[1]->Unlock();
	}
	else
	{
		g_pVtxResult[2]->Lock(0, 0, (void**)&pVtx, 0);
		/*�ʒu�ݒ�*/
		/*pVtx[0].pos = D3DXVECTOR3((g_Result[2].pos.x + -RESULT_COMMAND_SIZE_X / 2)+10, (g_Result[2].pos.y + -RESULT_COMMAND_SIZE_Y / 2)+10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_Result[2].pos.x + RESULT_COMMAND_SIZE_X / 2)-10, (g_Result[2].pos.y + -RESULT_COMMAND_SIZE_Y / 2)+10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_Result[2].pos.x + -RESULT_COMMAND_SIZE_X / 2)+10, (g_Result[2].pos.y + RESULT_COMMAND_SIZE_Y / 2)-10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_Result[2].pos.x + RESULT_COMMAND_SIZE_X / 2)-10, (g_Result[2].pos.y + RESULT_COMMAND_SIZE_Y / 2)-10, 0.0f);*/
		/*�J���[�ݒ�*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_pVtxResult[2]->Unlock();										  
	}
	if (GetKeyboardTrigger(DIK_RETURN)&& g_nSelectResult == 0)
	{
		SetFade(MODE_TITLE);
	}
	else if (GetKeyboardTrigger(DIK_RETURN) && g_nSelectResult == 1)
	{
		exit(1);
	}

}
void UninitResult(void)
{
	for (int nResult = 0; nResult < RESULT_TEXTURE_MAX; nResult++)
	{
		//�e�N�X�`���̐ݒ�
		if (g_pTextureResult[nResult] != NULL)
		{
			g_pTextureResult[nResult]->Release();
			g_pTextureResult[nResult] = NULL;
		}
		//���_�o�b�t�@�̊J��
		if (g_pVtxResult[nResult] != NULL)
		{
			g_pVtxResult[nResult]->Release();
			g_pVtxResult[nResult] = NULL;
		}
	}
}
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nResult = 0; nResult < RESULT_TEXTURE_MAX; nResult++)
	{
		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxResult[nResult], 0, sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[nResult]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
	DrawTime();
}