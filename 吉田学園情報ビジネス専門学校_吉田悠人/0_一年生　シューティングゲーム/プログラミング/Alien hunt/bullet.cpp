#include"main.h"
#include"bullet.h"
#include"explosion.h"
#include"enemy.h"
#include"player.h"
#include"effect.h"
/*�}�N����`*/
#define MAX_BULLET (128)							//�e�̍ő吔
//�\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	D3DXVECTOR3 move;								//�ړ���
	BULLETTYPE type;								//���
	int nLife;										//����
	D3DXCOLOR col;									//�F
	bool bUse;										//�g�p����Ă��邩
}BULLET;
/*�O���[�o���ϐ�*/
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBullet = NULL;		//���_�o�b�t�@�ւ̃|�C���^

BULLET g_aBullet[MAX_BULLET];//�e�̏��

							 /*����������*/
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntBullet;

	/*�e�̏��̏�����*/
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aBullet[nCntBullet].nLife = 50;
		g_aBullet[nCntBullet].bUse = false;
	}
	D3DXCreateTextureFromFile(pDevice, "TEXTURE/bullet.png", &g_pTextureBullet);//�e�N�X�`���̓ǂݍ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_BULLET,		//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,											//(�Œ�)
		FVF_VERTEX_2D,												//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,											//�i�Œ�j
		&g_pVtxBullet,												//�ϐ������ς��ƕύX���K�v
		NULL);
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		/*���_���W�̐ݒ�*/
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(100, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 100, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(100, 100, 0.0f);
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
	}
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBullet->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	//�e�N�X�`���̐ݒ�
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBullet != NULL)
	{
		g_pVtxBullet->Release();
		g_pVtxBullet = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	VERTEX_2D*pVtx;
	ENEMY*pEnemy;
	PLAYER *pPlayer;
	int nCntEnemy;
	int nCntBullet;
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)//�e���g�p����Ă���					
		{
			
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYE)
			{/*�v���C���[�̒e*/

				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1.5f, 6);
				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					/*�G���擾*/
					pEnemy = GetEnemy();
					if (pEnemy[nCntEnemy].bUse == true)
					{
						if (pEnemy[nCntEnemy].pos.x + 30 >= g_aBullet[nCntBullet].pos.x
							&&pEnemy[nCntEnemy].pos.x - 30 <= g_aBullet[nCntBullet].pos.x
							&&pEnemy[nCntEnemy].pos.y + 30 >= g_aBullet[nCntBullet].pos.y
							&&pEnemy[nCntEnemy].pos.y - 30 <= g_aBullet[nCntBullet].pos.y)
						{
							/*��������*/
  							HitEnemy(nCntEnemy, 1);

							g_aBullet[nCntBullet].bUse = false;//�g�p���Ȃ���Ԃɂ���
							g_aBullet[nCntBullet].nLife = 50;
						}
					}
				}
				/*�ʒu�X�V*/
				g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{/*�G�̒e*/
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 1.5f, 5);
				pPlayer = GatPlayer();
				if (pPlayer->pos.x + 30 >= g_aBullet[nCntBullet].pos.x
					&&pPlayer->pos.x - 30 <= g_aBullet[nCntBullet].pos.x
					&&pPlayer->pos.y + 30 >= g_aBullet[nCntBullet].pos.y
					&&pPlayer->pos.y - 30 <= g_aBullet[nCntBullet].pos.y)
				{
					HitPlayer(1);
					g_aBullet[nCntBullet].bUse = false;//�g�p���Ȃ���Ԃɂ���
					g_aBullet[nCntBullet].nLife = 50;
				}
				/*�ʒu�X�V*/
				g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move*0.4f;
			}


		

			/*���_���W�̐ݒ�*/
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (-BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (-BULLET_SIZE_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (-BULLET_SIZE_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (-BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE_Y / 2), 0.0f);

			if (g_aBullet[nCntBullet].pos.y>SCREEN_HEIGHT ||
				g_aBullet[nCntBullet].pos.y<0 ||
				g_aBullet[nCntBullet].pos.x> SCREEN_WIDTH ||
				g_aBullet[nCntBullet].pos.x<0)
			{
				g_aBullet[nCntBullet].bUse = false;
				g_aBullet[nCntBullet].nLife = 50;
			}
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				/*���j����*/
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				g_aBullet[nCntBullet].bUse = false;
				g_aBullet[nCntBullet].nLife = 50;
			}
		}
		pVtx += 4;													//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	g_pVtxBullet->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBullet;
	/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h*/
	pDevice->SetStreamSource(0, g_pVtxBullet, 0, sizeof(VERTEX_2D));
	/*���_�t�H�[�}�b�g�̐ݒ�*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*�e�N�X�`���̐ݒ�*/
	pDevice->SetTexture(0, g_pTextureBullet);


	/*�|���S���̕`��*/
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			/*�e���g�p���Ȃ�`��*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, NUM_POLYGON);
		}
	}
}

void SetBullet(D3DXVECTOR3 pos/*���ˈʒu*/, D3DXVECTOR3 move/*�ړ���*/, BULLETTYPE type, int nLife, D3DXCOLOR col)
{

	int nCntBullet;
	VERTEX_2D*pVtx;
	g_pVtxBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{

		if (g_aBullet[nCntBullet].bUse == false)					//�e���g�p����Ă��Ȃ��ꍇ
		{
			/*�ʒu�ݒ�*/
			g_aBullet[nCntBullet].pos = pos;
			/*���*/
			g_aBullet[nCntBullet].type = type;
			/*�ړ��ʂ�ݒ�*/
			g_aBullet[nCntBullet].move = move;
			/*����*/
			g_aBullet[nCntBullet].nLife = nLife;
			/*�F*/
			g_aBullet[nCntBullet].col = col;
			/*���_���W�̐ݒ�*/
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (-BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (-BULLET_SIZE_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (-BULLET_SIZE_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (-BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE_Y / 2), 0.0f);

			pVtx[0].col = g_aBullet[nCntBullet].col;
			pVtx[1].col = g_aBullet[nCntBullet].col;
			pVtx[2].col = g_aBullet[nCntBullet].col;
			pVtx[3].col = g_aBullet[nCntBullet].col;

			/*�g�p���Ă����Ԃɂ���*/
			g_aBullet[nCntBullet].bUse = true;
			break;
		}
		pVtx += 4;													//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	g_pVtxBullet->Unlock();
}