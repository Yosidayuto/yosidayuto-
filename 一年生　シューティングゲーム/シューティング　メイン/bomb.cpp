#include"main.h"
#include"bomb.h"
#include"player.h"
#include"enemy.h"
LPDIRECT3DTEXTURE9 g_pTexturBomb = NULL;//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBomb = NULL;//�o�b�t�@�ւ̃|�C���^�[

BOMB g_aBomb[MAX_BOMB];

int nCntAnime = 0;
int nPatternAnimX = 0;
int nPatternAnimY = 0;
void InintBomb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	int nCntBomb;
	for (nCntBomb = 0; nCntBomb< MAX_BOMB; nCntBomb++)
	{
		g_aBomb[nCntBomb].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBomb[nCntBomb].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBomb[nCntBomb].bUse = false;
	}


	D3DXCreateTextureFromFile(pDevice, "120b99a08cce763536914aee77045be5.png", &g_pTexturBomb);//�e�N�X�`���̓ǂݍ���	
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_BOMB,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffBomb,//�ϐ������ς��ƕύX���K�v
		NULL);



	g_pVtxBuffBomb->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb ++)
	{
		/*���_���W�̐ݒ�i�E���Őݒ肷��*/
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		/*rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j*/
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
		pVtx[0 ].tex = D3DXVECTOR2(0, 0);
		pVtx[1 ].tex = D3DXVECTOR2(1, 0);
		pVtx[2 ].tex = D3DXVECTOR2(0, 1);
		pVtx[3 ].tex = D3DXVECTOR2(1, 1);

	}
	pVtx += 4;
	//���_�f�[�^���A�����b�N����
	g_pVtxBuffBomb->Unlock();
}
void UninitBomb(void)
{
	//�e�N�X�`���̐ݒ�
	if (g_pTexturBomb != NULL)
	{
		g_pTexturBomb->Release();
		g_pTexturBomb = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBomb != NULL)
	{
		g_pVtxBuffBomb->Release();
		g_pVtxBuffBomb = NULL;
	}
}
void UpdateBomb(void)
{
	VERTEX_2D*pVtx;
	PLAYER *pPlayer;
	ENEMY*pEnemy;

	int nCntBomb;
	g_pVtxBuffBomb->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb++)
	{ 
		if (g_aBomb[nCntBomb].bUse == true)//�{�����g�p����Ă���		
		{
		
				nCntAnime++;//�J�E���^�[�v�Z
				if (nCntAnime == 15)
				{
					nCntAnime = 0;//�J�E���^�[�������l�ɖ߂�
					nPatternAnimX++;
				
					if (nPatternAnimX == 5)
					{
						nPatternAnimY++;
						nPatternAnimX = 0;
					}
					if (nPatternAnimY == 3)
					{
						
						for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
						{
							pEnemy = GetEnemy();
							if (pEnemy[nCntEnemy].bUse == true)
							{
								HitEnemy(nCntEnemy, 10);
							}
						}
						g_aBomb[nCntBomb].bUse = false;
					}
				}
				pPlayer = GatPlayer();
				//�e�N�X�`���̍��W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(nPatternAnimX*0.2f,		 nPatternAnimY*0.325f);
				pVtx[1].tex = D3DXVECTOR2(nPatternAnimX*0.2f+0.2f,	 nPatternAnimY*0.325f);
				pVtx[2].tex = D3DXVECTOR2(nPatternAnimX*0.2f,		 nPatternAnimY*0.325f+0.325f);
				pVtx[3].tex = D3DXVECTOR2(nPatternAnimX*0.2f+0.2f,	 nPatternAnimY*0.325f+0.325f);

				pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x + (-BOMB_SION / 2)*nPatternAnimX*2, pPlayer->pos.y + (-BOMB_SION / 2)*nPatternAnimX*2, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x + (BOMB_SION / 2)*nPatternAnimX*2, pPlayer->pos.y + (-BOMB_SION / 2)*nPatternAnimX*2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x + (-BOMB_SION / 2)*nPatternAnimX*2, pPlayer->pos.y + (BOMB_SION / 2)*nPatternAnimX*2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + (BOMB_SION / 2)*nPatternAnimX*2, pPlayer->pos.y + (BOMB_SION / 2)*nPatternAnimX*2, 0.0f);

		}
	}
	//���_�f�[�^���A�����b�N����
	g_pVtxBuffBomb->Unlock();
}
void DrawBomb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBomb;
	/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h*/
	pDevice->SetStreamSource(0, g_pVtxBuffBomb, 0, sizeof(VERTEX_2D));
	/*���_�t�H�[�}�b�g�̐ݒ�*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*�e�N�X�`���̐ݒ�*/
	pDevice->SetTexture(0, g_pTexturBomb);


	/*�|���S���̕`��*/
	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb++)
	{
		if (g_aBomb[nCntBomb].bUse == true)
		{
			/*�e���g�p���Ȃ�`��*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBomb * 4, NUM_POLYGON);
		}
	}
}
void SetBomb(D3DXVECTOR3 pos)
{
	int nCntBomb;
	VERTEX_2D*pVtx;
	g_pVtxBuffBomb->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBomb = 0; nCntBomb < MAX_BOMB; nCntBomb++)
	{

		if (g_aBomb[nCntBomb].bUse == false)					//�e���g�p����Ă��Ȃ��ꍇ
		{
			/*�ʒu�ݒ�*/
			g_aBomb[nCntBomb].pos = pos;
			
			/*���_���W�̐ݒ�*/
			pVtx[0].pos = D3DXVECTOR3(g_aBomb[nCntBomb].pos.x + (-BOMB_SION / 2), g_aBomb[nCntBomb].pos.y + (-BOMB_SION / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBomb[nCntBomb].pos.x + (BOMB_SION / 2), g_aBomb[nCntBomb].pos.y + (-BOMB_SION / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBomb[nCntBomb].pos.x + (-BOMB_SION / 2), g_aBomb[nCntBomb].pos.y + (BOMB_SION / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBomb[nCntBomb].pos.x + (BOMB_SION / 2), g_aBomb[nCntBomb].pos.y + (BOMB_SION / 2), 0.0f);


			/*�g�p���Ă����Ԃɂ���*/
			g_aBomb[nCntBomb].bUse = true;
			break;
		}
		pVtx += 4;													//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	g_pVtxBuffBomb->Unlock();
}