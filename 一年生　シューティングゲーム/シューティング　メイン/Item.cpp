
#include"main.h"
#include"Item.h"
#include"player.h"
#include"enemy.h"
/*�}�N����`*/
#define MAX_ITEM (128)							//�A�C�e���̍ő吔

/*�O���[�o���ϐ�*/
LPDIRECT3DTEXTURE9 g_apTextureItem = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem= NULL;		//���_�o�b�t�@�ւ̃|�C���^
ITEM g_aItem[MAX_ITEM];
int nCntType;
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntItem;
	/*�G�̏���������*/
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].nType = 0;
		g_aItem[nCntItem].bUse = false;
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	/*�e�N�X�`���̓ǂݍ���*/
	D3DXCreateTextureFromFile(pDevice, "yajirusi0101.png", &g_apTextureItem);//�e�N�X�`���̓ǂݍ���

	pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_ITEM,		//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,											//(�Œ�)
		FVF_VERTEX_2D,												//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,											//�i�Œ�j
		&g_pVtxBuffItem,											//�ϐ������ς��ƕύX���K�v
		NULL);
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		/*���_���W�̐ݒ�*/
		pVtx[0].pos = D3DXVECTOR3(-MAX_ITEM_SIZ / 2, -MAX_ITEM_SIZ / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_ITEM_SIZ / 2, -MAX_ITEM_SIZ / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_ITEM_SIZ / 2, MAX_ITEM_SIZ / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_ITEM_SIZ / 2, MAX_ITEM_SIZ / 2, 0.0f);
		/*rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j*/
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		/*���_�J���[�̐ݒ�*/
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		/*�e�N�X�`���̍��W�̐ݒ�*/
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		///*���_�f�[�^�̃|�C���^��4��*/
		pVtx += 4;
	}
	/*���_�f�[�^���A�����b�N*/
	g_pVtxBuffItem->Unlock();

}



void UninitItem(void)
{
	
	if (g_apTextureItem!= NULL)
	{
		g_apTextureItem->Release();
		g_apTextureItem = NULL;
	}

	/*���_�o�b�t�@�̊J��*/
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

void UpdaItem(void)
{

	VERTEX_2D*pVtx;
	PLAYER *pPlayer;
	int nCntPlayer;

	int nCntItem;
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)//�A�C�e�����g�p����Ă���					//�e���g�p����Ă���
		{
			pPlayer = GatPlayer();
		
			if (pPlayer->pos.x + 30 >= g_aItem[nCntItem].pos.x
				&&pPlayer->pos.x - 30 <= g_aItem[nCntItem].pos.x
				&&pPlayer->pos.y + 30 >= g_aItem[nCntItem].pos.y
				&&pPlayer->pos.y - 30 <= g_aItem[nCntItem].pos.y)
			{
				switch (g_aItem[nCntItem].nType)
				{
				case 0:
					if (pPlayer->nBulletType<6)
					{
						pPlayer->nBulletType = 1 + pPlayer->nBulletType;
					}
				
					break;
				case 1:
					if (pPlayer->nLife < 5)
					{
						pPlayer->nLife = 1 + pPlayer->nLife;
					}
					break;
				case 2:
					if (pPlayer->nBomb < 3)
					{
						pPlayer->nBomb = 1 + pPlayer->nBomb;
					}
					break;
				case 3:
					break;
				case 4:
					break;
				}
				g_aItem[nCntItem].bUse = false;//�g�p���Ȃ���Ԃɂ���
			}
			
			/*�ʒu�X�V*/
			g_aItem[nCntItem].pos += g_aItem[nCntItem].move*0.3;

		

			/*���_���W�̐ݒ�*/
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (-MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (-MAX_ITEM_SIZ / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (-MAX_ITEM_SIZ / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (-MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (MAX_ITEM_SIZ / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (MAX_ITEM_SIZ / 2), 0.0f);

			

			if (g_aItem[nCntItem].pos.y>SCREEN_HEIGHT ||
				g_aItem[nCntItem].pos.y<0 ||
				g_aItem[nCntItem].pos.x> SCREEN_WIDTH ||
				g_aItem[nCntItem].pos.x<0)
			{
				g_aItem[nCntItem].bUse = false;
			}
		}
		pVtx += 4;													//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	g_pVtxBuffItem->Unlock();
}
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntItem;
	/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h*/
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));
	/*���_�t�H�[�}�b�g�̐ݒ�*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*�|���S���̕`��*/
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, NUM_POLYGON);

		}
	}
}

void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move/*�ړ���*/, D3DXCOLOR col)
{
	
	VERTEX_2D*pVtx;
  	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	int nCntItem;
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)					//�e���g�p����Ă��Ȃ��ꍇ
		{
			/*�ʒu�ݒ�*/
			g_aItem[nCntItem].pos = pos;
			/*�ړ��ʂ�ݒ�*/
			g_aItem[nCntItem].move = move;
			/*�F*/
			g_aItem[nCntItem].col = col;
			/*���_���W�̐ݒ�*/
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (-MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (-MAX_ITEM_SIZ / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (-MAX_ITEM_SIZ / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (-MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (MAX_ITEM_SIZ / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + (MAX_ITEM_SIZ / 2), g_aItem[nCntItem].pos.y + (MAX_ITEM_SIZ / 2), 0.0f);
			nCntType = rand() % 2;
			switch (nCntType)
			{
			case 0://�o���b�g����
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				g_aItem[nCntItem].nType = 0;
				break;
			case 1://�̗͉�
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
				g_aItem[nCntItem].nType = 1;
				break;
			case 2://�{���ǉ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				g_aItem[nCntItem].nType = 2;
				break;
				/*case 3:
				pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				g_aItem[nCntItem].nType = 3;
				break;
			case 4:
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				g_aItem[nCntItem].nType = 4;
				break;*/
			}

			/*�g�p���Ă����Ԃɂ���*/
			g_aItem[nCntItem].bUse = true;
			break;
		}
		pVtx += 4;													//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	g_pVtxBuffItem->Unlock();
}
