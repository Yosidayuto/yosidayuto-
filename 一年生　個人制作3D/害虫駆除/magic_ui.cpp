#include"main.h"
#include"model.h"
#include"magic_ui.h"
typedef struct
{
	char *pFilename;	// �t�@�C����
}FILE_MAGIC_UI;
/*�O���[�o���ϐ�*/
//�o�b�t�@�ւ̃|�C���^�[
LPDIRECT3DTEXTURE9 g_pTexturMafic_Ui[MAGIC_UI_TEXTURE_MAX] = {};
/*���_�o�b�t�@�ւ̃|�C���^*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMafic_Ui[MAGIC_UI_TEXTURE_MAX] = {};//�o�b�t�@�ւ̃|�C���^�[
MAGIC_UI g_aMafic_Ui[MAGIC_UI_TEXTURE_MAX];
FILE_MAGIC_UI g_FileMafic_Ui[MAGIC_UI_TEXTURE_MAX] =
{
	{ "data/image/UI_Magic.png" },
	{ "data/image/Water.png" },
	{ "data/image/Phlogistic.png" },
	{ "data/image/Grass.png" },
	{ "data/image/star.png" },
	{ "data/image/UI_MagicCover.png" },
	{ "data/image/UI_Magic2.png" },
	{ "data/image/Number.png" },
	{ "data/image/UI_MagicCover,png" },
};
MAGIC_NUMBER g_Magic;
void InintMafic_Ui(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	for (int i = 0; i < 4; i++)
	{
		g_Magic.Number[i] = 9;
	}
	for (int nMafic = 0; nMafic < MAGIC_UI_TEXTURE_MAX; nMafic++)
	{
		g_aMafic_Ui[nMafic].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMafic_Ui[nMafic].bUse = false;
		/*�e�N�X�`���̓ǂݍ���*/
		D3DXCreateTextureFromFile(pDevice, g_FileMafic_Ui[nMafic].pFilename, &g_pTexturMafic_Ui[nMafic]);
		/*���_�o�b�t�@�̐���*/
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,//�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMafic_Ui[nMafic],
			NULL);
		g_pVtxBuffMafic_Ui[nMafic]->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
															/*���_���W�̐ݒ�i�E���Őݒ肷��*/
		pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		//rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		/*���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j*/
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
		g_pVtxBuffMafic_Ui[nMafic]->Unlock();
	}
}
void UninitMafic_Ui(void)
{
	for (int nMafic = 0; nMafic < MAGIC_UI_TEXTURE_MAX; nMafic++)
	{
		//�e�N�X�`���̐ݒ�
		if (g_pTexturMafic_Ui[nMafic] != NULL)
		{
			g_pTexturMafic_Ui[nMafic]->Release();
			g_pTexturMafic_Ui[nMafic] = NULL;
		}
		//���_�o�b�t�@�̊J��
		if (g_pVtxBuffMafic_Ui[nMafic] != NULL)
		{
			g_pVtxBuffMafic_Ui[nMafic]->Release();
			g_pVtxBuffMafic_Ui[nMafic] = NULL;
		}
	}

}
void UpdateMafic_Ui(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	PLAYER *pPlayer = GetPlayer();
	g_aMafic_Ui[0].bUse = true;
	g_aMafic_Ui[5].bUse = true;
	g_aMafic_Ui[6].bUse = true;
	g_aMafic_Ui[7].bUse = true;
	g_aMafic_Ui[8].bUse = true;
	/*�}�W�b�NUI�w�i*/
	g_pVtxBuffMafic_Ui[0]->Lock(0, 0, (void**)&pVtx, 0);
	g_aMafic_Ui[0].pos = D3DXVECTOR3(60, 40, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aMafic_Ui[0].pos.x + (-MAGIC_UI_SION / 2), g_aMafic_Ui[0].pos.y + (-MAGIC_UI_SION / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMafic_Ui[0].pos.x + (MAGIC_UI_SION / 2), g_aMafic_Ui[0].pos.y + (-MAGIC_UI_SION / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMafic_Ui[0].pos.x + (-MAGIC_UI_SION / 2), g_aMafic_Ui[0].pos.y + (MAGIC_UI_SION / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMafic_Ui[0].pos.x + (MAGIC_UI_SION / 2), g_aMafic_Ui[0].pos.y + (MAGIC_UI_SION / 2), 0.0f);
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffMafic_Ui[0]->Unlock();
	/*���@UI*/
	g_pVtxBuffMafic_Ui[1]->Lock(0, 0, (void**)&pVtx, 0);
	g_aMafic_Ui[1].pos = D3DXVECTOR3(60, 50, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aMafic_Ui[1].pos.x + (-MAGIC_UI_SION_WATER / 2) , g_aMafic_Ui[1].pos.y + (-MAGIC_UI_SION_WATER / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMafic_Ui[1].pos.x + (MAGIC_UI_SION_WATER / 2) , g_aMafic_Ui[1].pos.y + (-MAGIC_UI_SION_WATER / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMafic_Ui[1].pos.x + (-MAGIC_UI_SION_WATER / 2) , g_aMafic_Ui[1].pos.y + (MAGIC_UI_SION_WATER / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMafic_Ui[1].pos.x + (MAGIC_UI_SION_WATER / 2) , g_aMafic_Ui[1].pos.y + (MAGIC_UI_SION_WATER / 2), 0.0f);
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffMafic_Ui[1]->Unlock();
	/*���@UI*/
	g_pVtxBuffMafic_Ui[2]->Lock(0, 0, (void**)&pVtx, 0);
	g_aMafic_Ui[2].pos = D3DXVECTOR3(60, 50, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aMafic_Ui[2].pos.x + (-MAGIC_UI_SION_FIRE / 2), g_aMafic_Ui[2].pos.y + (-MAGIC_UI_SION_FIRE / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMafic_Ui[2].pos.x + (MAGIC_UI_SION_FIRE / 2), g_aMafic_Ui[2].pos.y + (-MAGIC_UI_SION_FIRE / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMafic_Ui[2].pos.x + (-MAGIC_UI_SION_FIRE / 2), g_aMafic_Ui[2].pos.y + (MAGIC_UI_SION_FIRE / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMafic_Ui[2].pos.x + (MAGIC_UI_SION_FIRE / 2), g_aMafic_Ui[2].pos.y + (MAGIC_UI_SION_FIRE / 2), 0.0f);
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffMafic_Ui[2]->Unlock();
	/*���@UI*/
	g_pVtxBuffMafic_Ui[3]->Lock(0, 0, (void**)&pVtx, 0);
	g_aMafic_Ui[3].pos = D3DXVECTOR3(60, 50, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aMafic_Ui[3].pos.x + (-MAGIC_UI_SION_GRASS / 2), g_aMafic_Ui[3].pos.y + (-MAGIC_UI_SION_GRASS / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMafic_Ui[3].pos.x + (MAGIC_UI_SION_GRASS / 2), g_aMafic_Ui[3].pos.y + (-MAGIC_UI_SION_GRASS / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMafic_Ui[3].pos.x + (-MAGIC_UI_SION_GRASS / 2), g_aMafic_Ui[3].pos.y + (MAGIC_UI_SION_GRASS / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMafic_Ui[3].pos.x + (MAGIC_UI_SION_GRASS / 2), g_aMafic_Ui[3].pos.y + (MAGIC_UI_SION_GRASS / 2), 0.0f);
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffMafic_Ui[3]->Unlock();
	/*���@UI*/
	g_pVtxBuffMafic_Ui[4]->Lock(0, 0, (void**)&pVtx, 0);
	g_aMafic_Ui[4].pos = D3DXVECTOR3(60, 50, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aMafic_Ui[4].pos.x + (-MAGIC_UI_SION_SRAR / 2), g_aMafic_Ui[4].pos.y + (-MAGIC_UI_SION_SRAR / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMafic_Ui[4].pos.x + (MAGIC_UI_SION_SRAR / 2), g_aMafic_Ui[4].pos.y + (-MAGIC_UI_SION_SRAR / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMafic_Ui[4].pos.x + (-MAGIC_UI_SION_SRAR / 2), g_aMafic_Ui[4].pos.y + (MAGIC_UI_SION_SRAR / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMafic_Ui[4].pos.x + (MAGIC_UI_SION_SRAR / 2), g_aMafic_Ui[4].pos.y + (MAGIC_UI_SION_SRAR / 2), 0.0f);
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffMafic_Ui[4]->Unlock();
	/*UI�@�J�o�[*/
	g_pVtxBuffMafic_Ui[5]->Lock(0, 0, (void**)&pVtx, 0);
	g_aMafic_Ui[5].pos = D3DXVECTOR3(60, 40, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aMafic_Ui[5].pos.x + (-MAGIC_UI_SION / 2), g_aMafic_Ui[5].pos.y + (-MAGIC_UI_SION / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMafic_Ui[5].pos.x + (MAGIC_UI_SION / 2), g_aMafic_Ui[5].pos.y + (-MAGIC_UI_SION / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMafic_Ui[5].pos.x + (-MAGIC_UI_SION / 2), g_aMafic_Ui[5].pos.y + (MAGIC_UI_SION / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMafic_Ui[5].pos.x + (MAGIC_UI_SION / 2), g_aMafic_Ui[5].pos.y + (MAGIC_UI_SION / 2), 0.0f);
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffMafic_Ui[5]->Unlock();
	/*�}�W�b�NUI2�w�i*/
	g_pVtxBuffMafic_Ui[6]->Lock(0, 0, (void**)&pVtx, 0);
	g_aMafic_Ui[6].pos = D3DXVECTOR3(170, 107, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aMafic_Ui[6].pos.x + (-MAGIC_UI_SION2 / 2), g_aMafic_Ui[6].pos.y + (-MAGIC_UI_SION2 / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMafic_Ui[6].pos.x + (MAGIC_UI_SION2/ 2), g_aMafic_Ui[6].pos.y + (-MAGIC_UI_SION2 / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMafic_Ui[6].pos.x + (-MAGIC_UI_SION2 / 2), g_aMafic_Ui[6].pos.y + (MAGIC_UI_SION2 / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMafic_Ui[6].pos.x + (MAGIC_UI_SION2 / 2), g_aMafic_Ui[6].pos.y + (MAGIC_UI_SION2 / 2), 0.0f);
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffMafic_Ui[6]->Unlock();
	/*�}�W�b�NUI2�@����*/
	g_pVtxBuffMafic_Ui[7]->Lock(0, 0, (void**)&pVtx, 0);
	g_aMafic_Ui[7].pos = D3DXVECTOR3(170, 107, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aMafic_Ui[7].pos.x + (-MAGIC_UI_SION2 / 2), g_aMafic_Ui[7].pos.y + (-MAGIC_UI_SION2 / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMafic_Ui[7].pos.x + (MAGIC_UI_SION2 / 2), g_aMafic_Ui[7].pos.y + (-MAGIC_UI_SION2 / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMafic_Ui[7].pos.x + (-MAGIC_UI_SION2 / 2), g_aMafic_Ui[7].pos.y + (MAGIC_UI_SION2 / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMafic_Ui[7].pos.x + (MAGIC_UI_SION2 / 2), g_aMafic_Ui[7].pos.y + (MAGIC_UI_SION2 / 2), 0.0f);
	//�e�N�X�`���̍��W�̐ݒ�
	if (g_Magic.Number[pPlayer->nMagic] == 0)
	{
		pVtx[0].tex = D3DXVECTOR2(0.8f, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.8f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	else if(g_Magic.Number[pPlayer->nMagic]<=5)
	{
		pVtx[0].tex = D3DXVECTOR2(0.2f*(g_Magic.Number[pPlayer->nMagic] - 1), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.2f*(g_Magic.Number[pPlayer->nMagic] - 1) + 0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.2f*(g_Magic.Number[pPlayer->nMagic] - 1), 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.2f*(g_Magic.Number[pPlayer->nMagic] - 1) + 0.2f, 0.5f);
	}
	else
	{
		pVtx[0].tex = D3DXVECTOR2(0.2f*(g_Magic.Number[pPlayer->nMagic] - 1), 0.5f);
		pVtx[1].tex = D3DXVECTOR2(0.2f*(g_Magic.Number[pPlayer->nMagic] - 1) + 0.2f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.2f*(g_Magic.Number[pPlayer->nMagic] - 1), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.2f*(g_Magic.Number[pPlayer->nMagic] - 1) + 0.2f, 1.0f);	
	}
	if (g_Magic.Number[pPlayer->nMagic] > 9)
	{
		g_Magic.Number[pPlayer->nMagic] = 9;
	}
	else if (g_Magic.Number[pPlayer->nMagic] < 0)
	{
		g_Magic.Number[pPlayer->nMagic] = 0;
	}
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffMafic_Ui[7]->Unlock();

	/*�}�W�b�NUI2�@�����J�o�[*/
	g_pVtxBuffMafic_Ui[8]->Lock(0, 0, (void**)&pVtx, 0);
	g_aMafic_Ui[8].pos = D3DXVECTOR3(170, 107, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aMafic_Ui[8].pos.x + (-MAGIC_UI_SION2 / 2), g_aMafic_Ui[8].pos.y + (-MAGIC_UI_SION2 / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMafic_Ui[8].pos.x + (MAGIC_UI_SION2 / 2), g_aMafic_Ui[8].pos.y + (-MAGIC_UI_SION2 / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMafic_Ui[8].pos.x + (-MAGIC_UI_SION2 / 2), g_aMafic_Ui[8].pos.y + (MAGIC_UI_SION2 / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMafic_Ui[8].pos.x + (MAGIC_UI_SION2 / 2), g_aMafic_Ui[8].pos.y + (MAGIC_UI_SION2 / 2), 0.0f);
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffMafic_Ui[8]->Unlock();
	switch (pPlayer->nMagic)
	{
	case 0:
		g_aMafic_Ui[1].bUse = true;
		g_aMafic_Ui[2].bUse = false;
		g_aMafic_Ui[3].bUse = false;
		g_aMafic_Ui[4].bUse = false;
		break;
	case 1:
		g_aMafic_Ui[2].bUse = true;
		g_aMafic_Ui[1].bUse = false;
		g_aMafic_Ui[3].bUse = false;
		g_aMafic_Ui[4].bUse = false;
		break;
	case 2:
		g_aMafic_Ui[3].bUse = true;
		g_aMafic_Ui[1].bUse = false;
		g_aMafic_Ui[2].bUse = false;
		g_aMafic_Ui[4].bUse = false;
		break;
	case 3:
		g_aMafic_Ui[4].bUse = true;
		g_aMafic_Ui[1].bUse = false;
		g_aMafic_Ui[2].bUse = false;
		g_aMafic_Ui[3].bUse = false;
		break;
	}

}
void Magic_Number(int Magic_Number, int Magic)
{
	g_Magic.Number[Magic] += Magic_Number;
}
void DrawMafic_Ui(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nMafic = 0; nMafic < MAGIC_UI_TEXTURE_MAX; nMafic++)
	{
		if (g_aMafic_Ui[nMafic].bUse)
		{
			/*�A���t�@�e�X�g��L����*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			/*�A���t�@�e�X�g��l�̐ݒ�*/
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			/*�A���t�@�e�X�g�̔�r���@�̐ݒ�*/
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffMafic_Ui[nMafic], 0, sizeof(VERTEX_2D));
			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturMafic_Ui[nMafic]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
			/*�A���t�@�e�X�g�𖳌���*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
	}
}


MAGIC_NUMBER*GetMagic_Number()
{
	return &g_Magic;
}
