#include "main.h"
#include "shadow.h"
#include "block.h"
#include "polygon.h"
#include "enemy.h"
#include "model.h"
#include "billboard.h"
#include "item.h"
#include "fade.h"

#define MAX_SEARCH 100
#define MAX_SIGHT 50

typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// �e�q�֌W		
}FILE;
void SearchEnemy();
/*--�O���[�o���ϐ�--*/
/*���f�����*/
D3DXMATERIAL *pMatEnemy[ENEMY_PARTS_MAX];
D3DXMATERIAL *pMatSearch;
ENEMY g_Enemy[MAX_ENEMY];
/*�e�̏���*/
int g_ShadowEnemy = 0;
/*�t�@�C��*/
FILE g_FileEnemy[ENEMY_PARTS_MAX] =
{
	{ "X�t�@�C��/�z�B���i���́j.x", -1 },	//0
	{ "X�t�@�C��/�z�B���i���j.x", 0 },		//1
	{ "X�t�@�C��/�z�B���i���j.x", 0 },		//2
	{ "X�t�@�C��/�z�B���i�E�r1�j.x", 0 },	//3
	{ "X�t�@�C��/�z�B���i�E�r2�j.x", 3 },	//4
	{ "X�t�@�C��/�z�B���i���r1�j.x", 0 },	//5
	{ "X�t�@�C��/�z�B���i���r2�j.x", 5 },	//6
	{ "X�t�@�C��/�z�B���i�E��1�j.x", 2 },	//7
	{ "X�t�@�C��/�z�B���i�E��2�j.x", 7 },	//8
	{ "X�t�@�C��/�z�B���i����1�j.x", 2 },	//9
	{ "X�t�@�C��/�z�B���i����2�j.x", 9 },	//10
	};
/*------------------*/

void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		
		g_Enemy[nEnemy].state = ENEMYSTATE_NORMAL;
	
		/*�����ʒu*/
		g_Enemy[nEnemy].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
		g_Enemy[nEnemy].enemyParts[0].pos= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nEnemy].enemyParts[1].pos= D3DXVECTOR3(0.0f, 3.0f, 0.0f);
		g_Enemy[nEnemy].enemyParts[2].pos= D3DXVECTOR3(0.0f, -7.0f, 0.0f);
		g_Enemy[nEnemy].enemyParts[3].pos= D3DXVECTOR3(-4.1f, 1.0f, 0.0f);
		g_Enemy[nEnemy].enemyParts[4].pos= D3DXVECTOR3(-4.1f, -3.0f, 0.0f);
		g_Enemy[nEnemy].enemyParts[5].pos= D3DXVECTOR3(4.0f, 1.0f, 0.0f);
		g_Enemy[nEnemy].enemyParts[6].pos= D3DXVECTOR3(4.1f, -3.0f, 0.0f);
		g_Enemy[nEnemy].enemyParts[7].pos= D3DXVECTOR3(-1.0f, -8.0f, 0.1f);
		g_Enemy[nEnemy].enemyParts[8].pos= D3DXVECTOR3(-2.0f, -15.0f, 0.1f);
		g_Enemy[nEnemy].enemyParts[9].pos= D3DXVECTOR3(1.0f, -8.0f, 0.1f);
		g_Enemy[nEnemy].enemyParts[10].pos = D3DXVECTOR3(2.0f, -15.0f, 0.1f);
		/*��������*/
		g_Enemy[nEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*�����̑傫��*/
		g_Enemy[nEnemy].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*�J���[�̏���������*/
		g_Enemy[nEnemy].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		/*��ނ̏���*/
		g_Enemy[nEnemy].nType = NULL;
		/*�����g�p����*/
		g_Enemy[nEnemy].buse = false;
		/*����X�C�b�`*/
		g_Enemy[nEnemy].nPos = 0;
		/*����̈ʒu*/
		g_Enemy[nEnemy].enemySearch.SearchRot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	}
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		
		for (int nParts = 0; nParts < ENEMY_PARTS_MAX; nParts++)
		{
			/*X�t�@�C���̓ǂݍ���*/
			D3DXLoadMeshFromX(
				g_FileEnemy[nParts].pFilename,
				D3DXMESH_MANAGED,
				pDevice,
				NULL,
				&g_Enemy[nEnemy].enemyParts[nParts].pBuffMat,
				NULL,
				&g_Enemy[nEnemy].enemyParts[nParts].nNumMat,
				&g_Enemy[nEnemy].enemyParts[nParts].pMesh);
			/*�}�e���A���f�[�^�ւ̃|�C���^���擾*/
			pMatEnemy[nParts] = (D3DXMATERIAL*)g_Enemy[nEnemy].enemyParts[nParts].pBuffMat->GetBufferPointer();
			/*�t�@�C���̓ǂݍ���*/
			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nEnemy].enemyParts[nParts].nNumMat; nCntMat++)
			{
				if (pMatEnemy[nParts][nCntMat].pTextureFilename != NULL)
				{
					D3DXCreateTextureFromFile(pDevice, pMatEnemy[nParts][nCntMat].pTextureFilename, &g_Enemy[nEnemy].enemyParts[nParts].pTextureModel[nCntMat]);
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
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		if (g_Enemy[nEnemy].buse)
		{
		
			/*�����X�V*/
			g_Enemy[nEnemy].rot += (g_Enemy[nEnemy].rotDest - g_Enemy[nEnemy].rot)* 0.09;
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
			/*�s������*/
			if (g_Enemy[nEnemy].pos.x + 30 >= pPlayer->pos.x
				&&g_Enemy[nEnemy].pos.x - 30 <= pPlayer->pos.x
				&&g_Enemy[nEnemy].pos.y + 30 >= pPlayer->pos.y
				&&g_Enemy[nEnemy].pos.y - 30 <= pPlayer->pos.y
				&&g_Enemy[nEnemy].pos.z + 30 >= pPlayer->pos.z
				&&g_Enemy[nEnemy].pos.z - 30 <= pPlayer->pos.z)
			{
				HitPlayer(1);
			}
			/*�ڕW�p�x�Ɍ���*/
			g_Enemy[nEnemy].rotDest.y = (g_Enemy[nEnemy].fRot);
			/*�ڕW�����ֈړ�*/
			g_Enemy[nEnemy].movePos.x = sinf(g_Enemy[nEnemy].fAngle)*1.0f;
			g_Enemy[nEnemy].movePos.z = cosf(g_Enemy[nEnemy].fAngle)*1.0f;
			/*�u���b�N�ɏ�������̏���*/
			if (CollisionBlockEnemy(&g_Enemy[nEnemy].pos, &g_Enemy[nEnemy].posOld, D3DXVECTOR3(MAX_SIZE1, MAX_SIZE1, MAX_SIZE1)) == true)
			{
				g_Enemy[nEnemy].movePos.y = 0;
				g_Enemy[nEnemy].vy = 0;
			}
			///*�n�ʂɏ�������̏���*/
			//else if (g_Enemy[nEnemy].Hit&&g_Enemy[nEnemy].fDist < 13.0f)
			//{
			//	g_Enemy[nEnemy].pos.y = g_Enemy[nEnemy].pos.y - g_Enemy[nEnemy].fDist + 13.0f;
			//	g_Enemy[nEnemy].vy = 0;
			//}
			else
			{
				///*�d��*/
				//g_Enemy[nEnemy].vy += -0.07f;
			}

			/*��������*/
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
		

			/*�G�l�~�[�̏��*/
			switch (g_Enemy[nEnemy].state)
			{
			case ENEMYSTATE_NORMAL://�ʏ펞
				if (g_Enemy[nEnemy].nPos == 0)
				{
					/*�X�^�[�g�ʒu�̕����擾*/
					g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -g_Enemy[nEnemy].startPos.x), (-g_Enemy[nEnemy].pos.z - -g_Enemy[nEnemy].startPos.z));
					/*�X�^�[�g�ʒu�����̊p�x���擾*/
					g_Enemy[nEnemy].fRot = atan2f((g_Enemy[nEnemy].pos.x - g_Enemy[nEnemy].startPos.x), (g_Enemy[nEnemy].pos.z - g_Enemy[nEnemy].startPos.z));
					if (g_Enemy[nEnemy].pos.x+5> g_Enemy[nEnemy].startPos.x
						&&g_Enemy[nEnemy].pos.x - 5<g_Enemy[nEnemy].startPos.x
						&&g_Enemy[nEnemy].pos.y + 5> g_Enemy[nEnemy].startPos.y
						&&g_Enemy[nEnemy].pos.y - 5< g_Enemy[nEnemy].startPos.y
						&&g_Enemy[nEnemy].pos.z + 5> g_Enemy[nEnemy].startPos.z
						&&g_Enemy[nEnemy].pos.z - 5< g_Enemy[nEnemy].startPos.z)
					{
						g_Enemy[nEnemy].nPos = 1;
					}
				}
				else if (g_Enemy[nEnemy].nPos == 1)
				{
					/*�I���ʒu�̕����擾*/
					g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -g_Enemy[nEnemy].endPos.x), (-g_Enemy[nEnemy].pos.z - -g_Enemy[nEnemy].endPos.z));
					/*�I���ʒu�����̊p�x���擾*/
					g_Enemy[nEnemy].fRot = atan2f((g_Enemy[nEnemy].pos.x - g_Enemy[nEnemy].endPos.x), (g_Enemy[nEnemy].pos.z - g_Enemy[nEnemy].endPos.z));
					if(g_Enemy[nEnemy].pos.x+5> g_Enemy[nEnemy].endPos.x
						&&g_Enemy[nEnemy].pos.x - 5<g_Enemy[nEnemy].endPos.x
						&&g_Enemy[nEnemy].pos.y + 5> g_Enemy[nEnemy].endPos.y
						&&g_Enemy[nEnemy].pos.y - 5< g_Enemy[nEnemy].endPos.y
						&&g_Enemy[nEnemy].pos.z + 5> g_Enemy[nEnemy].endPos.z
						&&g_Enemy[nEnemy].pos.z - 5< g_Enemy[nEnemy].endPos.z)
					{
						g_Enemy[nEnemy].nPos = 0;
					}
				}
			
				
				break;

			case ENEMYSTATE_TRACKING://�ǔ�
				/*�v���C���[�̈ʒu���擾*/
				g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -pPlayer->pos.x), (-g_Enemy[nEnemy].pos.z - -pPlayer->pos.z));
				/*�v���C���[����������̊p�x���擾*/
				g_Enemy[nEnemy].fRot = atan2f((g_Enemy[nEnemy].pos.x - pPlayer->pos.x), (g_Enemy[nEnemy].pos.z - pPlayer->pos.z));
				
				g_Enemy[nEnemy].movePos.x = sinf(g_Enemy[nEnemy].fAngle)*1.0f;
				g_Enemy[nEnemy].movePos.z = cosf(g_Enemy[nEnemy].fAngle)*1.0f;

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
	D3DXMATRIX mtxParent;
	/*���݂̃}�e���A���ێ��p*/
	D3DMATERIAL9 matDef;
	
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		if (g_Enemy[nEnemy].buse)
		{
		
			/*���[���h�}�g���N�X�̏���������*/
			D3DXMatrixIdentity(&g_Enemy[nEnemy].mtxWorld);
			/*�����𔽉f*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nEnemy].rot.y, g_Enemy[nEnemy].rot.x, g_Enemy[nEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nEnemy].mtxWorld, &g_Enemy[nEnemy].mtxWorld, &mtxRot);
			/*�ʒu�𔽉f*/
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nEnemy].pos.x, g_Enemy[nEnemy].pos.y, g_Enemy[nEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nEnemy].mtxWorld, &g_Enemy[nEnemy].mtxWorld, &mtxTrans);
		
			SearchEnemy();
			for (int nParts = 0; nParts < ENEMY_PARTS_MAX; nParts++)
			{
				/*�p�[�c���[���h�}�g���N�X�̏���������*/
				D3DXMatrixIdentity(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime);

				/*�p�[�c�����𔽉f*/
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nEnemy].enemyParts[nParts].rotAnime.y, g_Enemy[nEnemy].enemyParts[nParts].rotAnime.x, g_Enemy[nEnemy].enemyParts[nParts].rotAnime.z);
				D3DXMatrixMultiply(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime, &mtxRot);
				/*�p�[�c�ʒu�𔽉f*/
				D3DXMatrixTranslation(&mtxTrans, g_Enemy[nEnemy].enemyParts[nParts].posAnime.x, g_Enemy[nEnemy].enemyParts[nParts].posAnime.y, g_Enemy[nEnemy].enemyParts[nParts].posAnime.z);
				D3DXMatrixMultiply(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime, &mtxTrans);

				/*�e���f���̃}�g���b�N�X�̔��f*/
				if (g_FileEnemy[nParts].nCntLoop == -1)
				{
					mtxParent = g_Enemy[nEnemy].mtxWorld;
				}
				else
				{
					mtxParent = g_Enemy[nEnemy].enemyParts[g_FileEnemy[nParts].nCntLoop].mtxWorldAnime;
				}
				D3DXMatrixMultiply(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime, &mtxParent);

				/*���[���h�}�g���b�N�X�̐ݒ�*/
				pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorld);

				/*�p�[�c���[���h�}�g���N�X�̏���������*/
				D3DXMatrixIdentity(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorld);
				/*�A�j���p�[�c�����𔽉f*/
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nEnemy].enemyParts[nParts].rot.y, g_Enemy[nEnemy].enemyParts[nParts].rot.x, g_Enemy[nEnemy].enemyParts[nParts].rot.z);
				D3DXMatrixMultiply(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorld, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorld, &mtxRot);
				/*�A�j���p�[�c�ʒu�𔽉f*/
				D3DXMatrixTranslation(&mtxTrans, g_Enemy[nEnemy].enemyParts[nParts].pos.x, g_Enemy[nEnemy].enemyParts[nParts].pos.y, g_Enemy[nEnemy].enemyParts[nParts].pos.z);
				D3DXMatrixMultiply(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorld, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorld, &mtxTrans);

				D3DXMatrixMultiply(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorld, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorld, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime);

				/*���[���h�}�g���b�N�X�̐ݒ�*/
				pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorld);

				/*���݂̃}�e���A�����擾����*/
				pDevice->GetMaterial(&matDef);

				for (int nCntMat = 0; nCntMat < (int)g_Enemy[nEnemy].enemyParts[nParts].nNumMat; nCntMat++)
				{
					/*�}�e���A���̐ݒ�*/
					pDevice->SetMaterial(&pMatEnemy[nParts][nCntMat].MatD3D);
					pDevice->SetTexture(0, g_Enemy[nEnemy].enemyParts[nParts].pTextureModel[nCntMat]);
					/*�p�[�c�ʂ̕`��*/
					g_Enemy[nEnemy].enemyParts[nParts].pMesh->DrawSubset(nCntMat);
				}
				/*�ێ����Ă����}�e���A����߂�*/
				pDevice->SetMaterial(&matDef);
			}
		}
	}
	
}
void SearchEnemy()
{

	PLAYER *pPlayer = GetPlayer();
	BLOCK* pBlock = GetBlock();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 dir;
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{

		if (g_Enemy[nEnemy].buse)
		{
			g_Enemy[nEnemy].enemySearch.fRot = atan2f((g_Enemy[nEnemy].pos.x - pPlayer->pos.x), (g_Enemy[nEnemy].pos.z - pPlayer->pos.z));
			g_Enemy[nEnemy].enemySearch.fdistance = hypotf(g_Enemy[nEnemy].pos.x - pPlayer->pos.x, g_Enemy[nEnemy].pos.z - pPlayer->pos.z);
			bool bSearch = false;
			for (int n = 0; n < MAX_BLOCK; n++)
			{

				if (pBlock[n].used)
				{
					dir = D3DXVECTOR3(pPlayer->pos.x - g_Enemy[nEnemy].pos.x, pPlayer->pos.y - g_Enemy[nEnemy].pos.y, pPlayer->pos.z - g_Enemy[nEnemy].pos.z);
					bool isCollision = ColRayBox(&g_Enemy[nEnemy].pos, &dir, &pBlock[n].box, &pBlock[n].mtxWorld, g_Enemy[nEnemy].fcol_t);
					if (isCollision)
					{
						bSearch = true;
					}
				}


			}
			if ((D3DXToDegree(g_Enemy[nEnemy].rot.y) + 75)  > D3DXToDegree(g_Enemy[nEnemy].enemySearch.fRot) && (D3DXToDegree(g_Enemy[nEnemy].rot.y) - 75) <D3DXToDegree(g_Enemy[nEnemy].enemySearch.fRot)
				&& g_Enemy[nEnemy].enemySearch.fdistance<300 && bSearch == false)
			{

				g_Enemy[nEnemy].state = ENEMYSTATE_TRACKING;
			}
			else
			{
				g_Enemy[nEnemy].state = ENEMYSTATE_NORMAL;
			}



		}
	}


}
void SetEnemy(int Type, D3DXVECTOR3 pos, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{	/*�G�̎�ސݒ�*/
		if (!g_Enemy[nEnemy].buse)
		{
			/*�ʒu�̏���*/
			g_Enemy[nEnemy].pos = pos;
			/*����X�^�[�g�ʒu*/
			g_Enemy[nEnemy].startPos = startPos;
			/*����I���ʒu*/
			g_Enemy[nEnemy].endPos = endPos;
			/*�G�̎��*/
			g_Enemy[nEnemy].nType = Type;			
			/*�g�p����*/
			g_Enemy[nEnemy].buse = true;
			break;
		}
	}
}
void HitEnemy(int nDamage,int nCntEnemy)
{
		g_Enemy[nCntEnemy].nLife -= nDamage;
		if (g_Enemy[nCntEnemy].nLife <= 0)
		{/*���C�t���O�ɂȂ����Ƃ�*/
			g_Enemy[nCntEnemy].buse = false;
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
	
}