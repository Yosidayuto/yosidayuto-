#include"bomuSaid.h"
#include"main.h"
#include"player.h"

LPDIRECT3DTEXTURE9 g_pTexturBomuSaid = NULL;//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBomuSaid = NULL;//�o�b�t�@�ւ̃|�C���^�[

BOMUSAID g_aBomuSaid[MAX_BOMUSAID];
void InintBomuSaid(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	int nCntBomuSaid;
	for (nCntBomuSaid = 0; nCntBomuSaid < MAX_BOMUSAID; nCntBomuSaid++)
	{
		g_aBomuSaid[nCntBomuSaid].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBomuSaid[nCntBomuSaid].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBomuSaid[nCntBomuSaid].bUse = false;
	}


	D3DXCreateTextureFromFile(pDevice, "TEXTURE/heart.png", &g_pTexturBomuSaid);//�e�N�X�`���̓ǂݍ���	
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_BOMUSAID,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBomuSaid,//�ϐ������ς��ƕύX���K�v
		NULL);



	g_pVtxBomuSaid->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	for (nCntBomuSaid = 0; nCntBomuSaid < MAX_BOMUSAID; nCntBomuSaid = nCntBomuSaid + 4)
	{
		/*���_���W�̐ݒ�i�E���Őݒ肷��*/
		pVtx[0 + nCntBomuSaid].pos = D3DXVECTOR3((-BOMUSAID_SION_X / 2), (-BOMUSAID_SION_Y / 2), 0.0f);
		pVtx[1 + nCntBomuSaid].pos = D3DXVECTOR3((BOMUSAID_SION_X / 2), (-BOMUSAID_SION_Y / 2), 0.0f);
		pVtx[2 + nCntBomuSaid].pos = D3DXVECTOR3((-BOMUSAID_SION_X / 2), (BOMUSAID_SION_Y / 2), 0.0f);
		pVtx[3 + nCntBomuSaid].pos = D3DXVECTOR3((BOMUSAID_SION_X / 2), (BOMUSAID_SION_Y / 2), 0.0f);

		/*rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j*/
		pVtx[0 + nCntBomuSaid].rhw = 1.0f;
		pVtx[1 + nCntBomuSaid].rhw = 1.0f;
		pVtx[2 + nCntBomuSaid].rhw = 1.0f;
		pVtx[3 + nCntBomuSaid].rhw = 1.0f;

		/*���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j*/
		pVtx[0 + nCntBomuSaid].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1 + nCntBomuSaid].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2 + nCntBomuSaid].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3 + nCntBomuSaid].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0 + nCntBomuSaid].tex = D3DXVECTOR2(0, 0);
		pVtx[1 + nCntBomuSaid].tex = D3DXVECTOR2(1, 0);
		pVtx[2 + nCntBomuSaid].tex = D3DXVECTOR2(0, 1);
		pVtx[3 + nCntBomuSaid].tex = D3DXVECTOR2(1, 1);

	}
	pVtx += 4;
	//���_�f�[�^���A�����b�N����
	g_pVtxBomuSaid->Unlock();
}
void UninitBomuSaid(void)
{
	//�e�N�X�`���̐ݒ�
	if (g_pTexturBomuSaid != NULL)
	{
		g_pTexturBomuSaid->Release();
		g_pTexturBomuSaid = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBomuSaid != NULL)
	{
		g_pVtxBomuSaid->Release();
		g_pVtxBomuSaid = NULL;
	}
}
void UpdateBomuSaid(void)
{
	int nCntBomuSaid;
	VERTEX_2D*pVtx;
	PLAYER *pPlayer;
	g_pVtxBomuSaid->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	for (nCntBomuSaid = 0; nCntBomuSaid < MAX_BOMUSAID; nCntBomuSaid++)
	{
		if (g_aBomuSaid[nCntBomuSaid].bUse == true)
		{
			pPlayer = GatPlayer();
			switch (pPlayer->nBomb)
			{
			case 2:
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
			case 1:
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
			case 0:
				pVtx[8].tex = D3DXVECTOR2(0, 0);
				pVtx[9].tex = D3DXVECTOR2(0, 0);
				pVtx[10].tex = D3DXVECTOR2(0, 0);
				pVtx[11].tex = D3DXVECTOR2(0, 0);
				break;
			}


		}

	}
	//���_�f�[�^���A�����b�N����
	g_pVtxBomuSaid->Unlock();
}
void DrawBomuSaid(void)
{
	int nCntBomuSaid;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBomuSaid, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturBomuSaid);
	for (nCntBomuSaid = 0; nCntBomuSaid < MAX_BOMUSAID; nCntBomuSaid++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBomuSaid * 4, NUM_POLYGON);
	}
}
void SetBomuSaid(D3DXVECTOR3 pos)
{
	int nCntBomuSaid;
	int nCntPos;
	int nCntzi = 0;
	VERTEX_2D*pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBomuSaid->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	for (nCntBomuSaid = 0; nCntBomuSaid < MAX_BOMUSAID; nCntBomuSaid++)
	{
		if (g_aBomuSaid[nCntBomuSaid].bUse == false)
		{
			g_aBomuSaid[nCntBomuSaid].pos = pos;
			for (nCntPos = 0; nCntPos < MAX_BOMUSAID; nCntPos = nCntPos + 4)
			{
				/*���_���W�̐ݒ�i�E���Őݒ肷��*/
				pVtx[0 + nCntPos].pos = D3DXVECTOR3(g_aBomuSaid[nCntBomuSaid].pos.x + (nCntzi)+(-BOMUSAID_SION_X / 2), g_aBomuSaid[nCntBomuSaid].pos.y + (-BOMUSAID_SION_Y / 2), 0.0f);
				pVtx[1 + nCntPos].pos = D3DXVECTOR3(g_aBomuSaid[nCntBomuSaid].pos.x + (nCntzi)+(BOMUSAID_SION_X / 2), g_aBomuSaid[nCntBomuSaid].pos.y + (-BOMUSAID_SION_Y / 2), 0.0f);
				pVtx[2 + nCntPos].pos = D3DXVECTOR3(g_aBomuSaid[nCntBomuSaid].pos.x + (nCntzi)+(-BOMUSAID_SION_X / 2), g_aBomuSaid[nCntBomuSaid].pos.y + (BOMUSAID_SION_Y / 2), 0.0f);
				pVtx[3 + nCntPos].pos = D3DXVECTOR3(g_aBomuSaid[nCntBomuSaid].pos.x + (nCntzi)+(BOMUSAID_SION_X / 2), g_aBomuSaid[nCntBomuSaid].pos.y + (BOMUSAID_SION_Y / 2), 0.0f);
				nCntzi += 50;
				/*�g�p���Ă����Ԃɂ���*/
				g_aBomuSaid[nCntPos].bUse = true;
			}
			break;

		}

		pVtx += 4;
	}

	g_pVtxBomuSaid->Unlock();	//���_�f�[�^���A�����b�N����
}

