#include "enemy.h"
#include "main.h"
#include"explosion.h"
#include"bullet.h"
#include"score.h"
#include"Item.h"
#include"player.h"
#include <time.h>
/*�}�N����`*/
#define MAX_TYPE_ENEMY (100)

/*�O���[�o���ϐ�*/
LPDIRECT3DTEXTURE9 g_apTextureEnemy[MAX_TYPE_ENEMY] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;		//���_�o�b�t�@�ւ̃|�C���^
ENEMY g_aEnemy[MAX_ENEMY];

/*����������*/
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntEnemy;
	/*�G�̏���������*/
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nLife = 5;
		g_aEnemy[nCntEnemy].move= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		srand(time(NULL));
	}
	/*�e�N�X�`���̓ǂݍ���*/
	D3DXCreateTextureFromFile(pDevice, "TEXTURE/enemy000.png", &g_apTextureEnemy[0]);//�e�N�X�`���̓ǂݍ���

	pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_ENEMY,		//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,											//(�Œ�)
		FVF_VERTEX_2D,												//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,											//�i�Œ�j
		&g_pVtxBuffEnemy,											//�ϐ������ς��ƕύX���K�v
		NULL);
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		/*���_���W�̐ݒ�*/
		pVtx[0].pos = D3DXVECTOR3(-MAX_ENEMYSIZ / 2, -MAX_ENEMYSIZ / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_ENEMYSIZ / 2, -MAX_ENEMYSIZ / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_ENEMYSIZ / 2, MAX_ENEMYSIZ / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_ENEMYSIZ / 2, MAX_ENEMYSIZ / 2, 0.0f);
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
	g_pVtxBuffEnemy->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;
	/*�e�N�X�`���̊J��*/
	for (nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}
	/*���_�o�b�t�@�̊J��*/
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	VERTEX_2D*pVtx;
	PLAYER *pPlayer;
	float fAngle;//�p�x
	int nCntEnemy;
	int g_nCountEnemy = 10;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//�G���g�p����Ă���
		{
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (-MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (-MAX_ENEMYSIZ / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (-MAX_ENEMYSIZ / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (-MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMYSIZ / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMYSIZ / 2), 0.0f);
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move*MOVE_ENEMY;
			/*�G����ʊO�ɍs������*/
			if (g_aEnemy[nCntEnemy].pos.y > SCREEN_HEIGHT)
			{
				/*�g��Ȃ�����*/
				g_aEnemy[nCntEnemy].bUse = false;
			}

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL://�ʏ펞
				
				if ((rand() % (g_nCountEnemy * 20)) == 0)
				{
					pPlayer = GatPlayer();
					/*�p�x�����߂�*/
					fAngle = atan2f(-(g_aEnemy[nCntEnemy].pos.x- pPlayer->pos.x), -(g_aEnemy[nCntEnemy].pos.y - pPlayer->pos.y));
					if (fAngle > D3DX_PI) { fAngle -= D3DX_PI*2.0f; }
					if (fAngle < D3DX_PI) { fAngle += D3DX_PI*2.0f; }

					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(fAngle)*8, cosf(fAngle)*8, 0.0f), BULLETTYPE_ENEMY, 100, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));//�G�̍U��
				}
				break;
			case ENEMYSTATE_DAMAGE://�_���[�W���
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					/*���_�J���[�̐ݒ�*/
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				break;
			
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffEnemy->Unlock();

}
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEnemy;
	/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h*/
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));
	/*���_�t�H�[�}�b�g�̐ݒ�*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*�|���S���̕`��*/
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			/*�e�N�X�`���̐ݒ�*/
			pDevice->SetTexture(0,g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy*4 , NUM_POLYGON);

		}
	}
}

void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;
	VERTEX_2D*pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
	
			if (g_aEnemy[nCntEnemy].bUse == false)					//�G���g�p����Ă��Ȃ��ꍇ
			{
				/*�ʒu�ݒ�*/
				g_aEnemy[nCntEnemy].pos = pos;

				/*�G���*/
				g_aEnemy[nCntEnemy].nType = nType;

				/*�ʒu����*/
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (-MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (-MAX_ENEMYSIZ / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (-MAX_ENEMYSIZ / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (-MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMYSIZ / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMYSIZ / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMYSIZ / 2), 0.0f);

			

				/*�g�p���Ă����Ԃɂ���*/
				g_aEnemy[nCntEnemy].bUse = true;
			
				break;
			}
			pVtx += 4;
	
	}
	g_pVtxBuffEnemy->Unlock();
}

ENEMY *GetEnemy(void)
{
	
		return &g_aEnemy[0];
	
}
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D*pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	int nCntItem = 1;
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		
		
		/*��������*/
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		/*�A�C�e������*/
		if ((rand() % ((nCntItem) * 1)) <= 0)
		{
			SetItem(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

   		g_aEnemy[nCntEnemy].bUse = false;
  		g_aEnemy[nCntEnemy].nLife = 5;
		ScoreUp(1);
	}
	else if (g_aEnemy[nCntEnemy].nLife >= 0)
	{
		/*�_���[�W��ԂɈړ�*/
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;
		/*���_�J���[�̐ݒ�*/
		pVtx[0 + (nCntEnemy * 4)].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVtx[1 + (nCntEnemy * 4)].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVtx[2 + (nCntEnemy * 4)].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVtx[3 + (nCntEnemy * 4)].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
	}
	g_pVtxBuffEnemy->Unlock();
}