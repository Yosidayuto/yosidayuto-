#include"life.h"
#include"main.h"
#include"player.h"
LPDIRECT3DTEXTURE9 g_pTexturLife= NULL;//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife= NULL;//�o�b�t�@�ւ̃|�C���^�[

LIFE g_aLife[MAX_LIFE];

void InintLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	int nCntLife;
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		g_aLife[nCntLife].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLife[nCntLife].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aLife[nCntLife].bUse = false;
	}


	D3DXCreateTextureFromFile(pDevice, "TEXTURE/heart.png", &g_pTexturLife);//�e�N�X�`���̓ǂݍ���	
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_LIFE,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffLife,//�ϐ������ς��ƕύX���K�v
		NULL);



	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife = nCntLife + 4)
	{
		/*���_���W�̐ݒ�i�E���Őݒ肷��*/
		pVtx[0 + nCntLife].pos = D3DXVECTOR3((-LIFE_SION_X / 2), (-LIFE_SION_Y / 2), 0.0f);
		pVtx[1 + nCntLife].pos = D3DXVECTOR3((LIFE_SION_X / 2), (-LIFE_SION_Y / 2), 0.0f);
		pVtx[2 + nCntLife].pos = D3DXVECTOR3((-LIFE_SION_X / 2), (LIFE_SION_Y / 2), 0.0f);
		pVtx[3 + nCntLife].pos = D3DXVECTOR3((LIFE_SION_X / 2), (LIFE_SION_Y / 2), 0.0f);

		/*rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j*/
		pVtx[0 + nCntLife].rhw = 1.0f;
		pVtx[1 + nCntLife].rhw = 1.0f;
		pVtx[2 + nCntLife].rhw = 1.0f;
		pVtx[3 + nCntLife].rhw = 1.0f;

		/*���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j*/
		pVtx[0 + nCntLife].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1 + nCntLife].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2 + nCntLife].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3 + nCntLife].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0 + nCntLife].tex = D3DXVECTOR2(0, 0);
		pVtx[1 + nCntLife].tex = D3DXVECTOR2(1, 0);
		pVtx[2 + nCntLife].tex = D3DXVECTOR2(0, 1);
		pVtx[3 + nCntLife].tex = D3DXVECTOR2(1, 1);
	
	}
	pVtx += 4;
	//���_�f�[�^���A�����b�N����
	g_pVtxBuffLife->Unlock();
}
void UninitLife(void)
{
	//�e�N�X�`���̐ݒ�
	if (g_pTexturLife != NULL)
	{
		g_pTexturLife->Release();
		g_pTexturLife = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}
void UpdateLife(void)
{
	int nCntLife;
	VERTEX_2D*pVtx;
	PLAYER *pPlayer;
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{
			pPlayer = GatPlayer();
			switch (pPlayer->nLife)
			{
			case 5:
				if (pVtx[1].tex = D3DXVECTOR2(0, 0))
				{
					pVtx[0].tex = D3DXVECTOR2(0, 0);
					pVtx[1].tex = D3DXVECTOR2(1, 0);
					pVtx[2].tex = D3DXVECTOR2(0, 1);
					pVtx[3].tex = D3DXVECTOR2(1, 1);
				}
				break;
			case 4:
				
				pVtx[0].tex = D3DXVECTOR2(0, 0);
				pVtx[1].tex = D3DXVECTOR2(0, 0);
				pVtx[2].tex = D3DXVECTOR2(0, 0);
				pVtx[3].tex = D3DXVECTOR2(0, 0);
				if (pVtx[5].tex = D3DXVECTOR2(0, 0))
				{
					pVtx[4].tex = D3DXVECTOR2(0, 0);
					pVtx[5].tex = D3DXVECTOR2(1, 0);
					pVtx[6].tex = D3DXVECTOR2(0, 1);
					pVtx[7].tex = D3DXVECTOR2(1, 1);
				}
				break;
			case 3:
				pVtx[4].tex = D3DXVECTOR2(0, 0);
				pVtx[5].tex = D3DXVECTOR2(0, 0);
				pVtx[6].tex = D3DXVECTOR2(0, 0);
				pVtx[7].tex = D3DXVECTOR2(0, 0);
				if (pVtx[9].tex = D3DXVECTOR2(0, 0))
				{
					pVtx[8].tex = D3DXVECTOR2(0, 0);
					pVtx[9].tex = D3DXVECTOR2(1, 0);
					pVtx[10].tex = D3DXVECTOR2(0, 1);
					pVtx[11].tex = D3DXVECTOR2(1, 1);
				}
				break;
			case 2:
				pVtx[8].tex = D3DXVECTOR2(0, 0);
				pVtx[9].tex = D3DXVECTOR2(0, 0);
				pVtx[10].tex = D3DXVECTOR2(0, 0);
				pVtx[11].tex = D3DXVECTOR2(0, 0);
				if (pVtx[13].tex = D3DXVECTOR2(0, 0))
				{
					pVtx[12].tex = D3DXVECTOR2(0, 0);
					pVtx[13].tex = D3DXVECTOR2(1, 0);
					pVtx[14].tex = D3DXVECTOR2(0, 1);
					pVtx[15].tex = D3DXVECTOR2(1, 1);
				}
				break;
			case 1:
				pVtx[12].tex = D3DXVECTOR2(0, 0);
				pVtx[13].tex = D3DXVECTOR2(0, 0);
				pVtx[14].tex = D3DXVECTOR2(0, 0);
				pVtx[15].tex = D3DXVECTOR2(0, 0);
				if (pVtx[17].tex = D3DXVECTOR2(0, 0))
				{
					pVtx[16].tex = D3DXVECTOR2(0, 0);
					pVtx[17].tex = D3DXVECTOR2(1, 0);
					pVtx[18].tex = D3DXVECTOR2(0, 1);
					pVtx[19].tex = D3DXVECTOR2(1, 1);
				}
				break;
			case 0:
				pVtx[16].tex = D3DXVECTOR2(0, 0);
				pVtx[17].tex = D3DXVECTOR2(0, 0);
				pVtx[18].tex = D3DXVECTOR2(0, 0);
				pVtx[19].tex = D3DXVECTOR2(0, 0);
				break;
			}

			
		}
		
	}
	//���_�f�[�^���A�����b�N����
	g_pVtxBuffLife->Unlock();
}
void DrawLife(void)
{
	int nCntLife;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturLife);
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, NUM_POLYGON);
	}
}
void SetLife(D3DXVECTOR3 pos)
{
	int nCntLife;
	int nCntPos;
	int nCntzi = 0;
	VERTEX_2D*pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == false)
		{
			g_aLife[nCntLife].pos = pos;
			for (nCntPos = 0; nCntPos < MAX_LIFE; nCntPos = nCntPos + 4)
			{
				/*���_���W�̐ݒ�i�E���Őݒ肷��*/
				pVtx[0 + nCntPos].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x +(nCntzi)+(-LIFE_SION_X / 2), g_aLife[nCntLife].pos.y + (-LIFE_SION_Y / 2), 0.0f);
				pVtx[1 + nCntPos].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x +(nCntzi)+(LIFE_SION_X / 2), g_aLife[nCntLife].pos.y + (-LIFE_SION_Y / 2), 0.0f);
				pVtx[2 + nCntPos].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x +(nCntzi)+(-LIFE_SION_X / 2), g_aLife[nCntLife].pos.y + (LIFE_SION_Y / 2), 0.0f);
				pVtx[3 + nCntPos].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x +(nCntzi)+(LIFE_SION_X / 2), g_aLife[nCntLife].pos.y + (LIFE_SION_Y / 2), 0.0f);
				nCntzi += 50;
				/*�g�p���Ă����Ԃɂ���*/
				g_aLife[nCntPos].bUse = true;
			}
			break;
		
		}
	
		pVtx += 4;
	}
	
	g_pVtxBuffLife->Unlock();	//���_�f�[�^���A�����b�N����
}

