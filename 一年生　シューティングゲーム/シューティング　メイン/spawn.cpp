#include"spawn.h"
#include"enemy.h"
#include <time.h>
LPDIRECT3DTEXTURE9 g_pTextureSpawn= NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxSpawn= NULL;		//���_�o�b�t�@�ւ̃|�C���^
SPAWN g_aSpawn[MAX_SPAWN];
void InitSpawn(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntSpawn;
	for (nCntSpawn = 0; nCntSpawn < MAX_SPAWN; nCntSpawn++)
	{
		g_aSpawn[nCntSpawn].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSpawn[nCntSpawn].move= D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		g_aSpawn[nCntSpawn].bUse= false;
		srand(time(NULL));
	}
	
	D3DXCreateTextureFromFile(pDevice, "thWEFU39RJ.png", &g_pTextureSpawn);//�e�N�X�`���̓ǂݍ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_SPAWN,		//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,											//(�Œ�)
		FVF_VERTEX_2D,												//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,											//�i�Œ�j
		&g_pVtxSpawn,												//�ϐ������ς��ƕύX���K�v
		NULL);
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxSpawn->Lock(0, 0, (void**)&pVtx, 0);

	
		/*���_���W�̐ݒ�*/
		pVtx[0].pos = D3DXVECTOR3(-SPAWN_SIZE / 2, -SPAWN_SIZE / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( SPAWN_SIZE / 2, -SPAWN_SIZE / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAWN_SIZE / 2,  SPAWN_SIZE / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3 (SPAWN_SIZE / 2,  SPAWN_SIZE / 2, 0.0f);
		/*rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j*/
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		/*���_�J���[�̐ݒ�*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		/*�e�N�X�`���̍��W�̐ݒ�*/
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		/*���_�f�[�^�̃|�C���^��4��*/
		pVtx += 4;
	
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxSpawn->Unlock();
}
void UninitSpawn(void)
{
	//�e�N�X�`���̐ݒ�
	if (g_pTextureSpawn != NULL)
	{
		g_pTextureSpawn->Release();
		g_pTextureSpawn = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxSpawn != NULL)
	{
		g_pVtxSpawn->Release();
		g_pVtxSpawn = NULL;
	}
}
void UpdateSpawn(void)
{
	VERTEX_2D*pVtx;
	int nCntSpawn;
	int g_nCntSpawn=30;
	
	
	g_pVtxSpawn->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntSpawn = 0; nCntSpawn < MAX_SPAWN; nCntSpawn++)
	{
		if (g_aSpawn[nCntSpawn].bUse == true)
		{
			pVtx[0].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x + (-SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y + (-SPAWN_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x + (SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y + (-SPAWN_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x + (-SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y + (SPAWN_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x + (SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y + (SPAWN_SIZE / 2), 0.0f);
			g_aSpawn[nCntSpawn].pos += g_aSpawn[nCntSpawn].move;
			
			if ((rand() % ((g_nCntSpawn) * 20)) <= 0)
			{
				SetEnemy(g_aSpawn[nCntSpawn].pos, 0);
			}
			if (g_aSpawn[nCntSpawn].pos.x<0 + (SPAWN_SIZE / 2) || g_aSpawn[nCntSpawn].pos.x>SCREEN_WIDTH - (SPAWN_SIZE / 2))
			{
				g_aSpawn[nCntSpawn].move *= -1;
				g_nCntSpawn--;
			}

		}
	}
	g_pVtxSpawn->Unlock();
}
void DrawWpawn(void)
{
	int  nCntSpawn;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h*/
	pDevice->SetStreamSource(0, g_pVtxSpawn, 0, sizeof(VERTEX_2D));
	/*���_�t�H�[�}�b�g�̐ݒ�*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*�e�N�X�`���̐ݒ�*/
	pDevice->SetTexture(0, g_pTextureSpawn);
	/*�|���S���̕`��*/
	for (nCntSpawn = 0; nCntSpawn < MAX_SPAWN; nCntSpawn++)
	{
		if (g_aSpawn[nCntSpawn].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
		}
	}
}
void SetWpawn(D3DXVECTOR3 pos)
{

	int nCntSpawn;
	VERTEX_2D*pVtx;
	g_pVtxSpawn->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntSpawn = 0; nCntSpawn < MAX_SPAWN; nCntSpawn++)
	{

		if (g_aSpawn[nCntSpawn].bUse == false)					//�G���g�p����Ă��Ȃ��ꍇ
		{
			/*�ʒu�ݒ�*/
			g_aSpawn[nCntSpawn].pos = pos;

			pVtx[0].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x+(-SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y+(-SPAWN_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x+( SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y+(-SPAWN_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x+(-SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y+( SPAWN_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSpawn[nCntSpawn].pos.x+( SPAWN_SIZE / 2), g_aSpawn[nCntSpawn].pos.y+( SPAWN_SIZE / 2), 0.0f);

			/*�g�p���Ă����Ԃɂ���*/
			g_aSpawn[nCntSpawn].bUse = true;

			break;
		}
		pVtx += 4;
	}
	g_pVtxSpawn->Unlock();
}