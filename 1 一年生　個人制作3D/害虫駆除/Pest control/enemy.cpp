#include "main.h"
#include "shadow.h"
#include "block.h"
#include "polygon.h"
#include "enemy.h"
#include "model.h"
#include "billboard.h"
#include "item.h"
#include "fade.h"
#include "map.h"
#include "sound.h"
#define MAX_SEARCH 1000

typedef struct
{
	char *pFilename;	// �t�@�C����
}FILE;

/*--�O���[�o���ϐ�--*/
/*���f�����*/
D3DXMATERIAL *pMatEnemy[ENEMY_PARTS_MAX];

ENEMY g_Enemy[MAX_ENEMY];
/*�e�̏���*/
int g_ShadowEnemy = 0;
/*�G�̃J�E���g*/
int g_nNumber=0;			

/*�t�@�C��*/
FILE g_FileEnemy[ENEMY_PARTS_MAX] =
{
	{ "data/Xfile/slime.x"},
	{ "data/Xfile/InflammatoryMonsterx.x"},
	{ "data/Xfile/WoodSpirits.x"},
	{ "data/Xfile/UFO.x" },
};
/*------------------*/

void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		
		g_Enemy[nEnemy].state = ENEMYSTATE_NORMAL;
		/*�̗͐ݒ�*/
		g_Enemy[nEnemy].nLife = 5;
		/*�����ʒu*/
		g_Enemy[nEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*��������*/
		g_Enemy[nEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*�����̑傫��*/
		g_Enemy[nEnemy].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*�J���[�̏���������*/
		g_Enemy[nEnemy].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		/*��ނ̏���*/
		g_Enemy[nEnemy].nType = NULL;
		/*�����g�p����*/
		g_Enemy[nEnemy].use = false;
	}
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		for (int nType = 0; nType < ENEMY_PARTS_MAX; nType++)
		{
			/*X�t�@�C���̓ǂݍ���*/
			D3DXLoadMeshFromX(
				g_FileEnemy[nType].pFilename,
				D3DXMESH_MANAGED,
				pDevice,
				NULL,
				&g_Enemy[nEnemy].enemyParts[nType].pBuffMat,
				NULL,
				&g_Enemy[nEnemy].enemyParts[nType].nNumMat,
				&g_Enemy[nEnemy].enemyParts[nType].pMesh);
			/*�}�e���A���f�[�^�ւ̃|�C���^���擾*/
			pMatEnemy[nType] = (D3DXMATERIAL*)g_Enemy[nEnemy].enemyParts[nType].pBuffMat->GetBufferPointer();
			/*�t�@�C���̓ǂݍ���*/
			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nEnemy].enemyParts[nType].nNumMat; nCntMat++)
			{
				if (pMatEnemy[nType][nCntMat].pTextureFilename != NULL)
				{
					D3DXCreateTextureFromFile(pDevice, pMatEnemy[nType][nCntMat].pTextureFilename, &g_Enemy[nEnemy].enemyParts[nType].pTextureModel[nCntMat]);
				}
			}
		}
	}
}
void UninitEnemy(void)
{
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		for (int i = 0; i < ENEMY_PARTS_MAX; i++)
		{
			/*���b�V���̔j��*/
			if (g_Enemy[nEnemy].enemyParts[i].pMesh != NULL)
			{
				g_Enemy[nEnemy].enemyParts[i].pMesh->Release();
				g_Enemy[nEnemy].enemyParts[i].pMesh = NULL;
			}

			/*�}�e���A���̔j��*/
			if (g_Enemy[nEnemy].enemyParts[i].pBuffMat != NULL)
			{
				g_Enemy[nEnemy].enemyParts[i].pBuffMat->Release();
				g_Enemy[nEnemy].enemyParts[i].pBuffMat = NULL;
			}
			/*�e�N�X�`��*/
			for (int nCnt = 0; nCnt < (int)g_Enemy[nEnemy].enemyParts[i].nNumMat; nCnt++)
			{
				if (g_Enemy[nEnemy].enemyParts[i].pTextureModel[nCnt] != NULL)
				{
					g_Enemy[nEnemy].enemyParts[i].pTextureModel[nCnt]->Release();
					g_Enemy[nEnemy].enemyParts[i].pTextureModel[nCnt] = NULL;
				}
			}
		}

	}
}
void UpdateEnemy(void)
{	
	VERTEX_3D*pVtx = NULL;
	PLAYER *pPlayer = GetPlayer();
	MAP* pMap = GetMap();
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		if (g_Enemy[nEnemy].use)
		{
			switch (g_Enemy[nEnemy].state)
			{
			case ENEMYSTATE_NORMAL://�ʏ펞
			

				 /*�s������*/
				if (g_Enemy[nEnemy].pos.x + 30 >= pPlayer->pos.x
					&&g_Enemy[nEnemy].pos.x - 30 <= pPlayer->pos.x
					&&g_Enemy[nEnemy].pos.y + 30 >= pPlayer->pos.y
					&&g_Enemy[nEnemy].pos.y - 30 <= pPlayer->pos.y
					&&g_Enemy[nEnemy].pos.z + 30 >= pPlayer->pos.z
					&&g_Enemy[nEnemy].pos.z - 30 <= pPlayer->pos.z)
				{
					PlaySound(SOUND_LABEL_SE_DAMAGE);
					HitModel(1, nEnemy,1);
				}
				g_Enemy[nEnemy].rot += (g_Enemy[nEnemy].rotDest - g_Enemy[nEnemy].rot)* 0.09f;
				/*����*/
				g_Enemy[nEnemy].movePos.x += (0.0f - g_Enemy[nEnemy].movePos.x)*0.5f;
				g_Enemy[nEnemy].movePos.y += (0.0f - g_Enemy[nEnemy].movePos.y)*0.5f;
				g_Enemy[nEnemy].movePos.z += (0.0f - g_Enemy[nEnemy].movePos.z)*0.5f;
				/*�ʒu�X�V*/
				g_Enemy[nEnemy].pos += g_Enemy[nEnemy].movePos;
				///*�d�͉����x�X�V*/
				//g_Enemy[nEnemy].movePos.y += g_Enemy[nEnemy].vy;
				/*�ʒu�̋L�^*/
				g_Enemy[nEnemy].posOld = g_Enemy[nEnemy].pos;
				
				/*�u���b�N�ɏ�������̏���*/
				if (CollisionBlock(&g_Enemy[nEnemy].pos, &g_Enemy[nEnemy].posOld, D3DXVECTOR3(MAX_SIZE1, MAX_SIZE1, MAX_SIZE1)) == true)
				{
					g_Enemy[nEnemy].movePos.y = 0;
					g_Enemy[nEnemy].vy = 0;
				}
				/*�n�ʂɏ�������̏���*/
				else if (g_Enemy[nEnemy].Hit&&g_Enemy[nEnemy].fDist < 13.0f)
				{
					g_Enemy[nEnemy].pos.y = g_Enemy[nEnemy].pos.y - g_Enemy[nEnemy].fDist + 13.0f;
					g_Enemy[nEnemy].vy = 0;
				}
				else
				{
					///*�d��*/
					//g_Enemy[nEnemy].vy += -0.07f;
				}

				///*�G�l�~�[�r��*/
				//if (g_Enemy[nEnemy].use == false)
				//{
				//	SetFade(MODE_RESULE);
				//}
				/*----------------------------------------------------------------------------------*/
			
				switch (g_Enemy[nEnemy].nType)
				{
				case 0:	
					/*�v���C���[�̈ʒu���擾*/
					g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -pPlayer->pos.x), (-g_Enemy[nEnemy].pos.z - -pPlayer->pos.z));
					/*�v���C���[����������̊p�x���擾*/
					g_Enemy[nEnemy].fRot = atan2f((g_Enemy[nEnemy].pos.x - pPlayer->pos.x), (g_Enemy[nEnemy].pos.z - pPlayer->pos.z));
					if (g_Enemy[nEnemy].pos.x + MAX_SEARCH > pPlayer->pos.x&&g_Enemy[nEnemy].pos.x - MAX_SEARCH < pPlayer->pos.x)
					{
						if (g_Enemy[nEnemy].pos.y + MAX_SEARCH > pPlayer->pos.y&&g_Enemy[nEnemy].pos.y - MAX_SEARCH < pPlayer->pos.y)
						{
							if (g_Enemy[nEnemy].pos.z + MAX_SEARCH > pPlayer->pos.z&&g_Enemy[nEnemy].pos.z - MAX_SEARCH < pPlayer->pos.z)
							{
								/*�v���C���[�̕����ֈړ�*/
								g_Enemy[nEnemy].movePos.x = sinf(g_Enemy[nEnemy].fAngle)*1.0f;
								g_Enemy[nEnemy].movePos.z = cosf(g_Enemy[nEnemy].fAngle)*1.0f;
								if (g_Enemy[nEnemy].rotDest.y>g_Enemy[nEnemy].rot.y + D3DXToRadian(180))
								{/*-180�x����180�x�ɂȂ鏈��*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(180);
								}
								else if (g_Enemy[nEnemy].rotDest.y<g_Enemy[nEnemy].rot.y + D3DXToRadian(-180))
								{/*180�x����-180�x�ɂȂ鏈��*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(-180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(-180);
								}
								/*�v���C���[������p�x�Ɍ���*/
								g_Enemy[nEnemy].rotDest.y = (g_Enemy[nEnemy].fRot);
							}
						}
					}
					break;
				case 1:
					/*�v���C���[�̈ʒu���擾*/
					g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -pPlayer->pos.x), (-g_Enemy[nEnemy].pos.z - -pPlayer->pos.z));
					/*�v���C���[����������̊p�x���擾*/
					g_Enemy[nEnemy].fRot = atan2f((g_Enemy[nEnemy].pos.x - pPlayer->pos.x), (g_Enemy[nEnemy].pos.z - pPlayer->pos.z));
					if (g_Enemy[nEnemy].pos.x + MAX_SEARCH > pPlayer->pos.x&&g_Enemy[nEnemy].pos.x - MAX_SEARCH < pPlayer->pos.x)
					{
						if (g_Enemy[nEnemy].pos.y + MAX_SEARCH > pPlayer->pos.y&&g_Enemy[nEnemy].pos.y - MAX_SEARCH < pPlayer->pos.y)
						{
							if (g_Enemy[nEnemy].pos.z + MAX_SEARCH > pPlayer->pos.z&&g_Enemy[nEnemy].pos.z - MAX_SEARCH < pPlayer->pos.z)
							{
								/*�v���C���[�̕����ֈړ�*/
								g_Enemy[nEnemy].movePos.x = sinf(g_Enemy[nEnemy].fAngle)*1.5f;
								g_Enemy[nEnemy].movePos.z = cosf(g_Enemy[nEnemy].fAngle)*1.5f;
								if (g_Enemy[nEnemy].rotDest.y>g_Enemy[nEnemy].rot.y + D3DXToRadian(180))
								{/*-180�x����180�x�ɂȂ鏈��*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(180);
								}
								else if (g_Enemy[nEnemy].rotDest.y<g_Enemy[nEnemy].rot.y + D3DXToRadian(-180))
								{/*180�x����-180�x�ɂȂ鏈��*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(-180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(-180);
								}
								/*�v���C���[������p�x�Ɍ���*/
								g_Enemy[nEnemy].rotDest.y = (g_Enemy[nEnemy].fRot);
							}
						}
					}
					break;
				case 2:
					/*�v���C���[�̈ʒu���擾*/
					g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -pPlayer->pos.x), (-g_Enemy[nEnemy].pos.z - -pPlayer->pos.z));
					/*�v���C���[����������̊p�x���擾*/
					g_Enemy[nEnemy].fRot = atan2f((g_Enemy[nEnemy].pos.x - pPlayer->pos.x), (g_Enemy[nEnemy].pos.z - pPlayer->pos.z));
					if (g_Enemy[nEnemy].pos.x + MAX_SEARCH > pPlayer->pos.x&&g_Enemy[nEnemy].pos.x - MAX_SEARCH < pPlayer->pos.x)
					{
						if (g_Enemy[nEnemy].pos.y + MAX_SEARCH > pPlayer->pos.y&&g_Enemy[nEnemy].pos.y - MAX_SEARCH < pPlayer->pos.y)
						{
							if (g_Enemy[nEnemy].pos.z + MAX_SEARCH > pPlayer->pos.z&&g_Enemy[nEnemy].pos.z - MAX_SEARCH < pPlayer->pos.z)
							{
								/*�v���C���[�̕����ֈړ�*/
								g_Enemy[nEnemy].movePos.x = sinf(g_Enemy[nEnemy].fAngle)*1.5f;
								g_Enemy[nEnemy].movePos.z = cosf(g_Enemy[nEnemy].fAngle)*1.5f;
								if (g_Enemy[nEnemy].rotDest.y>g_Enemy[nEnemy].rot.y + D3DXToRadian(180))
								{/*-180�x����180�x�ɂȂ鏈��*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(180);
								}
								else if (g_Enemy[nEnemy].rotDest.y<g_Enemy[nEnemy].rot.y + D3DXToRadian(-180))
								{/*180�x����-180�x�ɂȂ鏈��*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(-180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(-180);
								}
								/*�v���C���[������p�x�Ɍ���*/
								g_Enemy[nEnemy].rotDest.y = (g_Enemy[nEnemy].fRot);
							}
						}
					}
					break;
				case 3:
					/*�v���C���[�̈ʒu���擾*/
					g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -pPlayer->pos.x), (-g_Enemy[nEnemy].pos.z - -pPlayer->pos.z));
					/*�v���C���[����������̊p�x���擾*/
					g_Enemy[nEnemy].fRot = atan2f((g_Enemy[nEnemy].pos.x - pPlayer->pos.x), (g_Enemy[nEnemy].pos.z - pPlayer->pos.z));
					if (g_Enemy[nEnemy].pos.x + MAX_SEARCH > pPlayer->pos.x&&g_Enemy[nEnemy].pos.x - MAX_SEARCH < pPlayer->pos.x)
					{
						if (g_Enemy[nEnemy].pos.y + MAX_SEARCH > pPlayer->pos.y&&g_Enemy[nEnemy].pos.y - MAX_SEARCH < pPlayer->pos.y)
						{
							if (g_Enemy[nEnemy].pos.z + MAX_SEARCH > pPlayer->pos.z&&g_Enemy[nEnemy].pos.z - MAX_SEARCH < pPlayer->pos.z)
							{
								/*�v���C���[�̕����ֈړ�*/
								g_Enemy[nEnemy].movePos.x = sinf(g_Enemy[nEnemy].fAngle)*1.5f;
								g_Enemy[nEnemy].movePos.z = cosf(g_Enemy[nEnemy].fAngle)*1.5f;
								if (g_Enemy[nEnemy].rotDest.y>g_Enemy[nEnemy].rot.y + D3DXToRadian(180))
								{/*-180�x����180�x�ɂȂ鏈��*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(180);
								}
								else if (g_Enemy[nEnemy].rotDest.y<g_Enemy[nEnemy].rot.y + D3DXToRadian(-180))
								{/*180�x����-180�x�ɂȂ鏈��*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(-180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(-180);
								}
								/*�v���C���[������p�x�Ɍ���*/
								g_Enemy[nEnemy].rotDest.y += 0.1f;
							}
						}
					}
					break;
				}

				
				
				/*------------------------------------------------------------------------------------*/
				break;
			case ENEMYSTATE_DAMAGE://�_���[�W���
				g_Enemy[nEnemy].nCounterState--;
				if (g_Enemy[nEnemy].nCounterState <= 0)
				{
					g_Enemy[nEnemy].state = ENEMYSTATE_NORMAL;
				}
				break;
			}
			///*-------------------------------------------------------------------------------------*/
			
		}
	}
	
}
void DrawEnemy(void)
{
	/*�f�o�C�X�ւ̃|�C���^*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*���݂̃}�e���A���ێ��p*/
	D3DMATERIAL9 matDef;
	
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		if (g_Enemy[nEnemy].use)
		{
		
			/*���[���h�}�g���N�X�̏���������*/
			D3DXMatrixIdentity(&g_Enemy[nEnemy].mtxWorld);
			/*�����𔽉f*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nEnemy].rot.y, g_Enemy[nEnemy].rot.x, g_Enemy[nEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nEnemy].mtxWorld, &g_Enemy[nEnemy].mtxWorld, &mtxRot);
			/*�ʒu�𔽉f*/
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nEnemy].pos.x, g_Enemy[nEnemy].pos.y, g_Enemy[nEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nEnemy].mtxWorld, &g_Enemy[nEnemy].mtxWorld, &mtxTrans);
			/*���[���h�}�g���b�N�X�̐ݒ�*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nEnemy].mtxWorld);
			/*���݂̃}�e���A�����擾����*/
			pDevice->GetMaterial(&matDef);
			
				for (int nCntMat = 0; nCntMat < (int)g_Enemy[nEnemy].enemyParts[g_Enemy[nEnemy].nType].nNumMat; nCntMat++)
				{
					/*�}�e���A���̐ݒ�*/
					pDevice->SetMaterial(&pMatEnemy[g_Enemy[nEnemy].nType][nCntMat].MatD3D);
					pDevice->SetTexture(0, g_Enemy[nEnemy].enemyParts[g_Enemy[nEnemy].nType].pTextureModel[nCntMat]);
					/*��ޕʂ̕`��*/
					g_Enemy[nEnemy].enemyParts[g_Enemy[nEnemy].nType].pMesh->DrawSubset(nCntMat);
				}
			/*�ێ����Ă����}�e���A����߂�*/
			pDevice->SetMaterial(&matDef);
		}
	}
}
void SetEnemy(int Type, D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{	/*�G�̎�ސݒ�*/
		if (!g_Enemy[nEnemy].use)
		{
			/*�G�J�E���g*/
			g_nNumber += 1;
			/*�ʒu�̏���*/
			g_Enemy[nEnemy].pos = pos;
			g_Enemy[nEnemy].nType = Type;			
			/*�g�p����*/
			g_Enemy[nEnemy].use = true;
			break;
		}
	}
}
void HitEnemy(int nDamage,int nCntEnemy)
{
		g_Enemy[nCntEnemy].nLife -= nDamage;
		if (g_Enemy[nCntEnemy].nLife <= 0)
		{/*���C�t���O�ɂȂ����Ƃ�*/
			g_Enemy[nCntEnemy].use = false;
			switch (g_Enemy[nCntEnemy].nType)
			{
			case 0:
				SetItem(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), 0);
				break;
			case 1:
				SetItem(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), 1);
				break;
			case 2:
				SetItem(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), 2);
				break;
			case 3:
				SetItem(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z), 3);
				break;
			}
			g_nNumber -= 1;
   			if (g_nNumber== 0)
			{
				
			}
		}
		else
		{/*�_���[�W��ԃJ�E���^�[��ԂɈڍs*/
			g_Enemy[nCntEnemy].nCounterState = 5;
			g_Enemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;//�_���[�W��ԂɈڍs
			
		}
}
ENEMY*GetEnemy()
{
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		return &g_Enemy[nEnemy];
	}
	return NULL;
}