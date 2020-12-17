#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
typedef struct
{
	char *pFilename;	// �t�@�C����
}FILE_TITLE;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_TEXTURE_MAX] = {};//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle[TITLE_TEXTURE_MAX] = {};//�o�b�t�@�ւ̃|�C���^�[
TITLE g_Title[TITLE_TEXTURE_MAX];
int g_nSelectTitle;
FILE_TITLE g_File[TITLE_TEXTURE_MAX] =
{
	{ "�摜/�����Ƃ���.png" },
	{ "�摜/title.png" },
	{ "�摜/titleback.png" },
	{ "�摜/" },
};

/*---------------------------------------------------*/
/*����������										*/
/*-------------------------------------------------*/
void InintTitle(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nTitle = 0; nTitle < TITLE_TEXTURE_MAX; nTitle++)
	{
		/*�ʒu�̏�����*/
		g_Title[nTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_nSelectTitle = 0;
		//�e�N�X�`���̓ǂݍ���	
		D3DXCreateTextureFromFile(pDevice, g_File[nTitle].pFilename, &g_pTextureTitle[nTitle]);
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,//�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,//(�Œ�)
			FVF_VERTEX_2D,//���_�t�H�[�}�b�g
			D3DPOOL_MANAGED,//�i�Œ�j
			&g_pVtxBuffTitle[nTitle],//�ϐ������ς��ƕύX���K�v
			NULL);

		g_pVtxBuffTitle[nTitle]->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
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
		g_pVtxBuffTitle[nTitle]->Unlock();
	}

}
void UninitTitle(void)
{
	for (int nTitle = 0; nTitle < TITLE_TEXTURE_MAX; nTitle++)
	{
		//�e�N�X�`���̐ݒ�
		if (g_pTextureTitle[nTitle] != NULL)
		{
			g_pTextureTitle[nTitle]->Release();
			g_pTextureTitle[nTitle] = NULL;
		}
		//���_�o�b�t�@�̊J��
		if (g_pVtxBuffTitle[nTitle] != NULL)
		{
			g_pVtxBuffTitle[nTitle]->Release();
			g_pVtxBuffTitle[nTitle] = NULL;
		}
	}
	


}
void UpdateTitle(void)
{
	/*���_���ւ̃|�C���^�[*/
	VERTEX_2D *pVtx;
	/*�R���g���[���[�̏���*/
	JOYINFOEX JOYPAD;
	/*�W���C�p�b�g�̓���*/
	JOYPAD.dwSize = sizeof(JOYINFOEX);
	JOYPAD.dwFlags = JOY_RETURNALL; // �S�Ă̏����擾

	/*�w�i*/
	g_pVtxBuffTitle[0]->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_Title[0].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Title[0].pos.x + -SCREEN_WIDTH / 2, g_Title[0].pos.y + -SCREEN_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Title[0].pos.x + SCREEN_WIDTH / 2, g_Title[0].pos.y + -SCREEN_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Title[0].pos.x + -SCREEN_WIDTH / 2, g_Title[0].pos.y + SCREEN_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Title[0].pos.x + SCREEN_WIDTH / 2, g_Title[0].pos.y + SCREEN_HEIGHT / 2, 0.0f);
	g_pVtxBuffTitle[0]->Unlock();
	/*�X�^�[�g�R�}���h*/
	g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);
	/*�ʒu�ݒ�*/
	g_Title[1].pos = D3DXVECTOR3(920.0f, 400.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Title[1].pos.x + -TITLE_COMMAND_SIZE_X / 2, g_Title[1].pos.y + -TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Title[1].pos.x + TITLE_COMMAND_SIZE_X / 2, g_Title[1].pos.y + -TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Title[1].pos.x + -TITLE_COMMAND_SIZE_X / 2, g_Title[1].pos.y + TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Title[1].pos.x + TITLE_COMMAND_SIZE_X / 2, g_Title[1].pos.y + TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	/*�J���[�ݒ�*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pVtxBuffTitle[1]->Unlock();
	/*�I���R�}���h*/
	g_pVtxBuffTitle[2]->Lock(0, 0, (void**)&pVtx, 0);
	/*�ʒu�ݒ�*/
	g_Title[2].pos = D3DXVECTOR3(920.0f, 500.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Title[2].pos.x + -TITLE_COMMAND_SIZE_X / 2, g_Title[2].pos.y + -TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Title[2].pos.x + TITLE_COMMAND_SIZE_X / 2, g_Title[2].pos.y + -TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Title[2].pos.x + -TITLE_COMMAND_SIZE_X / 2, g_Title[2].pos.y + TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Title[2].pos.x + TITLE_COMMAND_SIZE_X / 2, g_Title[2].pos.y + TITLE_COMMAND_SIZE_Y / 2, 0.0f);
	/*�J���[�ݒ�*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pVtxBuffTitle[2]->Unlock();
	/*�^�C�g�����S*/
	//g_pVtxBuffTitle[3]->Lock(0, 0, (void**)&pVtx, 0);
	///*�ʒu�ݒ�*/
	//g_Title[3].pos = D3DXVECTOR3(640.0f, 260.0f, 0.0f);
	//pVtx[0].pos = D3DXVECTOR3(g_Title[3].pos.x + -TITLE_LOGO_SIZE_X / 2, g_Title[3].pos.y + -TITLE_LOGO_SIZE_Y / 2, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_Title[3].pos.x + TITLE_LOGO_SIZE_X / 2, g_Title[3].pos.y + -TITLE_LOGO_SIZE_Y / 2, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_Title[3].pos.x + -TITLE_LOGO_SIZE_X / 2, g_Title[3].pos.y + TITLE_LOGO_SIZE_Y / 2, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_Title[3].pos.x + TITLE_LOGO_SIZE_X / 2, g_Title[3].pos.y + TITLE_LOGO_SIZE_Y / 2, 0.0f);
	///*�J���[�ݒ�*/
	//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//g_pVtxBuffTitle[3]->Unlock();
	/*�I������*/
	if (joyGetPosEx(JOYSTICKID1, &JOYPAD) == JOYERR_NOERROR)
	{
	
		if (JOYPAD.dwYpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
		{
			g_nSelectTitle = 1;
		}
		if (JOYPAD.dwYpos < 0x7FFF - 0x4000)//�O�ɓ|���X�e�B�b�N
		{
			g_nSelectTitle = 0;
		}
	
		if (JOYPAD.dwButtons & JOY_BUTTON1&&g_nSelectTitle == 0)
		{
			SetFade(MODE_TUTORIAL);
		}
		else if (JOYPAD.dwButtons& JOY_BUTTON1&&g_nSelectTitle == 1)
		{
			exit(1);
		}

	}
	/*if (GetKeyboardTrigger(DIK_UP))
	{
		
		g_nSelectTitle = 0;
	}
	else if (GetKeyboardTrigger(DIK_DOWN))
	{
		
		g_nSelectTitle = 1;
	}*/

	/*�I����Ԃ�UI*/
	if (g_nSelectTitle == 0)
	{
		g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);
		/*�ʒu�ݒ�*/
	/*	pVtx[0].pos = D3DXVECTOR3((g_Title[1].pos.x + -TITLE_COMMAND_SIZE_X / 2) + 10, (g_Title[1].pos.y + -TITLE_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_Title[1].pos.x + TITLE_COMMAND_SIZE_X / 2) - 10, (g_Title[1].pos.y + -TITLE_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_Title[1].pos.x + -TITLE_COMMAND_SIZE_X / 2) + 10, (g_Title[1].pos.y + TITLE_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_Title[1].pos.x + TITLE_COMMAND_SIZE_X / 2) - 10, (g_Title[1].pos.y + TITLE_COMMAND_SIZE_Y / 2) - 10, 0.0f);*/
		/*�J���[�ݒ�*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_pVtxBuffTitle[1]->Unlock();
	}
	else
	{
		g_pVtxBuffTitle[2]->Lock(0, 0, (void**)&pVtx, 0);
		/*�ʒu�ݒ�*/
	/*	pVtx[0].pos = D3DXVECTOR3((g_Title[2].pos.x + -TITLE_COMMAND_SIZE_X / 2) + 10, (g_Title[2].pos.y + -TITLE_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_Title[2].pos.x + TITLE_COMMAND_SIZE_X / 2) - 10, (g_Title[2].pos.y + -TITLE_COMMAND_SIZE_Y / 2) + 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_Title[2].pos.x + -TITLE_COMMAND_SIZE_X / 2) + 10, (g_Title[2].pos.y + TITLE_COMMAND_SIZE_Y / 2) - 10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_Title[2].pos.x + TITLE_COMMAND_SIZE_X / 2) - 10, (g_Title[2].pos.y + TITLE_COMMAND_SIZE_Y / 2) - 10, 0.0f);*/
		/*�J���[�ݒ�*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_pVtxBuffTitle[2]->Unlock();
	}

	if (GetKeyboardTrigger(DIK_RETURN) && g_nSelectTitle == 0)
	{
		SetFade(MODE_TUTORIAL);
	}
	else if (GetKeyboardTrigger(DIK_RETURN) && g_nSelectTitle == 1)
	{
		exit(1);
	}
}
void DrawTitle(void)
{
	for (int nTitle = 0; nTitle < TITLE_TEXTURE_MAX; nTitle++)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxBuffTitle[nTitle], 0, sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nTitle]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}
