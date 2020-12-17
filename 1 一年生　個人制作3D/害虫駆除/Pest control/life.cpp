#include"life.h"
#include"main.h"
#include"model.h"
#include"camera.h"
typedef struct
{
	char *pFilename;	// �t�@�C����
}FILE_LIFE;
/*�O���[�o���ϐ�*/
//�o�b�t�@�ւ̃|�C���^�[
LPDIRECT3DTEXTURE9 g_pTexturLife[LIFE_TEXTURE_MAX] = {};
/*���_�o�b�t�@�ւ̃|�C���^*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife[LIFE_TEXTURE_MAX] = {};//�o�b�t�@�ւ̃|�C���^�[
LIFE g_aLife[LIFE_TEXTURE_MAX];
FILE_LIFE g_File[LIFE_TEXTURE_MAX] =
{
	{ "data/image/Physical.png" },
	{ "data/image/PhysicalLeft.png" },
	{ "data/image/PhysicalCentral.png" },
	{ "data/image/PhysicalRight.png" },
};

void InintLife(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nLife = 0; nLife < LIFE_TEXTURE_MAX; nLife++)
	{
		
		g_aLife[nLife].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLife[nLife].bUse = true;
		/*�e�N�X�`���̓ǂݍ���*/	
		D3DXCreateTextureFromFile(pDevice, g_File[nLife].pFilename, &g_pTexturLife[nLife]);
		/*���_�o�b�t�@�̐���*/
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,//�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffLife[nLife],
			NULL);
		g_pVtxBuffLife[nLife]->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		/*���_���W�̐ݒ�i�E���Őݒ肷��*/
		pVtx[0].pos = D3DXVECTOR3((-LIFE1_SION_X / 2), (-LIFE1_SION_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3((LIFE1_SION_X / 2), (-LIFE1_SION_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3((-LIFE1_SION_X / 2), (LIFE1_SION_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3((LIFE1_SION_X / 2), (LIFE1_SION_Y / 2), 0.0f);
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
		g_pVtxBuffLife[nLife]->Unlock();
	}
}
void UninitLife(void)
{
	for (int nLife = 0; nLife < LIFE_TEXTURE_MAX; nLife++)
	{
		//�e�N�X�`���̐ݒ�
		if (g_pTexturLife[nLife] != NULL)
		{
			g_pTexturLife[nLife]->Release();
			g_pTexturLife[nLife] = NULL;
		}
		//���_�o�b�t�@�̊J��
		if (g_pVtxBuffLife[nLife] != NULL)
		{
			g_pVtxBuffLife[nLife]->Release();
			g_pVtxBuffLife[nLife] = NULL;
		}
	}
	
}
void UpdateLife(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	PLAYER *pPlayer = GetPlayer();
	
	g_pVtxBuffLife[0]->Lock(0, 0, (void**)&pVtx, 0);
	g_aLife[0].pos = D3DXVECTOR3(300,40,0);
	pVtx[0].pos = D3DXVECTOR3(g_aLife[0].pos.x + (-LIFE1_SION_X / 2), g_aLife[0].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aLife[0].pos.x + ( LIFE1_SION_X / 2), g_aLife[0].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aLife[0].pos.x + (-LIFE1_SION_X / 2), g_aLife[0].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aLife[0].pos.x + (LIFE1_SION_X / 2), g_aLife[0].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffLife[0]->Unlock();

	g_pVtxBuffLife[1]->Lock(0, 0, (void**)&pVtx, 0);
	g_aLife[1].pos = D3DXVECTOR3(200, 40, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aLife[1].pos.x + (-LIFE1_SION_X / 2)/3, g_aLife[1].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aLife[1].pos.x +  (LIFE1_SION_X / 2)/3, g_aLife[1].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aLife[1].pos.x + (-LIFE1_SION_X / 2)/3, g_aLife[1].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aLife[1].pos.x +  (LIFE1_SION_X / 2)/3, g_aLife[1].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffLife[1]->Unlock();

	g_pVtxBuffLife[2]->Lock(0, 0, (void**)&pVtx, 0);
	g_aLife[2].pos = D3DXVECTOR3(300, 40, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aLife[2].pos.x + (-LIFE1_SION_X / 2) / 3, g_aLife[2].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aLife[2].pos.x + (LIFE1_SION_X / 2) / 3, g_aLife[2].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aLife[2].pos.x + (-LIFE1_SION_X / 2) / 3, g_aLife[2].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aLife[2].pos.x + (LIFE1_SION_X / 2) / 3, g_aLife[2].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffLife[2]->Unlock();

	g_pVtxBuffLife[3]->Lock(0, 0, (void**)&pVtx, 0);
	g_aLife[3].pos = D3DXVECTOR3(400, 40, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aLife[3].pos.x + (-LIFE1_SION_X / 2) / 3, g_aLife[3].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aLife[3].pos.x + (LIFE1_SION_X / 2) / 3, g_aLife[3].pos.y + (-LIFE1_SION_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aLife[3].pos.x + (-LIFE1_SION_X / 2) / 3, g_aLife[3].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aLife[3].pos.x + (LIFE1_SION_X / 2) / 3, g_aLife[3].pos.y + (LIFE1_SION_Y / 2), 0.0f);
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffLife[3]->Unlock();

	switch (pPlayer->nLife)
	{
	case 3:

		break;
	case 2:
		g_aLife[3].bUse = false;
		break;
	case 1:
		g_aLife[2].bUse = false;
		break;
	case 0:
		g_aLife[1].bUse = false;
		break;
	}
}
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nLife = 0; nLife < LIFE_TEXTURE_MAX; nLife++)
	{
		if (g_aLife[nLife].bUse)
		{
			/*�A���t�@�e�X�g��L����*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			/*�A���t�@�e�X�g��l�̐ݒ�*/
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			/*�A���t�@�e�X�g�̔�r���@�̐ݒ�*/
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffLife[nLife], 0, sizeof(VERTEX_2D));
			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturLife[nLife]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
			/*�A���t�@�e�X�g�𖳌���*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
	}
}


