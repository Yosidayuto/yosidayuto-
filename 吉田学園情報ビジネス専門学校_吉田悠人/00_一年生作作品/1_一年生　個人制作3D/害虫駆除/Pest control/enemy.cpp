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
	char *pFilename;	// ファイル名
}FILE;

/*--グローバル変数--*/
/*モデル情報*/
D3DXMATERIAL *pMatEnemy[ENEMY_PARTS_MAX];

ENEMY g_Enemy[MAX_ENEMY];
/*影の処理*/
int g_ShadowEnemy = 0;
/*敵のカウント*/
int g_nNumber=0;			

/*ファイル*/
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
		/*体力設定*/
		g_Enemy[nEnemy].nLife = 5;
		/*初期位置*/
		g_Enemy[nEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*初期向き*/
		g_Enemy[nEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*初期の大きさ*/
		g_Enemy[nEnemy].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*カラーの初期化処理*/
		g_Enemy[nEnemy].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		/*種類の初期*/
		g_Enemy[nEnemy].nType = NULL;
		/*初期使用処理*/
		g_Enemy[nEnemy].use = false;
	}
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		for (int nType = 0; nType < ENEMY_PARTS_MAX; nType++)
		{
			/*Xファイルの読み込み*/
			D3DXLoadMeshFromX(
				g_FileEnemy[nType].pFilename,
				D3DXMESH_MANAGED,
				pDevice,
				NULL,
				&g_Enemy[nEnemy].enemyParts[nType].pBuffMat,
				NULL,
				&g_Enemy[nEnemy].enemyParts[nType].nNumMat,
				&g_Enemy[nEnemy].enemyParts[nType].pMesh);
			/*マテリアルデータへのポインタを取得*/
			pMatEnemy[nType] = (D3DXMATERIAL*)g_Enemy[nEnemy].enemyParts[nType].pBuffMat->GetBufferPointer();
			/*ファイルの読み込み*/
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
			/*メッシュの破棄*/
			if (g_Enemy[nEnemy].enemyParts[i].pMesh != NULL)
			{
				g_Enemy[nEnemy].enemyParts[i].pMesh->Release();
				g_Enemy[nEnemy].enemyParts[i].pMesh = NULL;
			}

			/*マテリアルの破棄*/
			if (g_Enemy[nEnemy].enemyParts[i].pBuffMat != NULL)
			{
				g_Enemy[nEnemy].enemyParts[i].pBuffMat->Release();
				g_Enemy[nEnemy].enemyParts[i].pBuffMat = NULL;
			}
			/*テクスチャ*/
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
			case ENEMYSTATE_NORMAL://通常時
			

				 /*行動処理*/
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
				/*慣性*/
				g_Enemy[nEnemy].movePos.x += (0.0f - g_Enemy[nEnemy].movePos.x)*0.5f;
				g_Enemy[nEnemy].movePos.y += (0.0f - g_Enemy[nEnemy].movePos.y)*0.5f;
				g_Enemy[nEnemy].movePos.z += (0.0f - g_Enemy[nEnemy].movePos.z)*0.5f;
				/*位置更新*/
				g_Enemy[nEnemy].pos += g_Enemy[nEnemy].movePos;
				///*重力加速度更新*/
				//g_Enemy[nEnemy].movePos.y += g_Enemy[nEnemy].vy;
				/*位置の記録*/
				g_Enemy[nEnemy].posOld = g_Enemy[nEnemy].pos;
				
				/*ブロックに乗った時の処理*/
				if (CollisionBlock(&g_Enemy[nEnemy].pos, &g_Enemy[nEnemy].posOld, D3DXVECTOR3(MAX_SIZE1, MAX_SIZE1, MAX_SIZE1)) == true)
				{
					g_Enemy[nEnemy].movePos.y = 0;
					g_Enemy[nEnemy].vy = 0;
				}
				/*地面に乗った時の処理*/
				else if (g_Enemy[nEnemy].Hit&&g_Enemy[nEnemy].fDist < 13.0f)
				{
					g_Enemy[nEnemy].pos.y = g_Enemy[nEnemy].pos.y - g_Enemy[nEnemy].fDist + 13.0f;
					g_Enemy[nEnemy].vy = 0;
				}
				else
				{
					///*重力*/
					//g_Enemy[nEnemy].vy += -0.07f;
				}

				///*エネミー殲滅*/
				//if (g_Enemy[nEnemy].use == false)
				//{
				//	SetFade(MODE_RESULE);
				//}
				/*----------------------------------------------------------------------------------*/
			
				switch (g_Enemy[nEnemy].nType)
				{
				case 0:	
					/*プレイヤーの位置を取得*/
					g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -pPlayer->pos.x), (-g_Enemy[nEnemy].pos.z - -pPlayer->pos.z));
					/*プレイヤーがいる方向の角度を取得*/
					g_Enemy[nEnemy].fRot = atan2f((g_Enemy[nEnemy].pos.x - pPlayer->pos.x), (g_Enemy[nEnemy].pos.z - pPlayer->pos.z));
					if (g_Enemy[nEnemy].pos.x + MAX_SEARCH > pPlayer->pos.x&&g_Enemy[nEnemy].pos.x - MAX_SEARCH < pPlayer->pos.x)
					{
						if (g_Enemy[nEnemy].pos.y + MAX_SEARCH > pPlayer->pos.y&&g_Enemy[nEnemy].pos.y - MAX_SEARCH < pPlayer->pos.y)
						{
							if (g_Enemy[nEnemy].pos.z + MAX_SEARCH > pPlayer->pos.z&&g_Enemy[nEnemy].pos.z - MAX_SEARCH < pPlayer->pos.z)
							{
								/*プレイヤーの方向へ移動*/
								g_Enemy[nEnemy].movePos.x = sinf(g_Enemy[nEnemy].fAngle)*1.0f;
								g_Enemy[nEnemy].movePos.z = cosf(g_Enemy[nEnemy].fAngle)*1.0f;
								if (g_Enemy[nEnemy].rotDest.y>g_Enemy[nEnemy].rot.y + D3DXToRadian(180))
								{/*-180度から180度になる処理*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(180);
								}
								else if (g_Enemy[nEnemy].rotDest.y<g_Enemy[nEnemy].rot.y + D3DXToRadian(-180))
								{/*180度から-180度になる処理*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(-180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(-180);
								}
								/*プレイヤーがいる角度に向く*/
								g_Enemy[nEnemy].rotDest.y = (g_Enemy[nEnemy].fRot);
							}
						}
					}
					break;
				case 1:
					/*プレイヤーの位置を取得*/
					g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -pPlayer->pos.x), (-g_Enemy[nEnemy].pos.z - -pPlayer->pos.z));
					/*プレイヤーがいる方向の角度を取得*/
					g_Enemy[nEnemy].fRot = atan2f((g_Enemy[nEnemy].pos.x - pPlayer->pos.x), (g_Enemy[nEnemy].pos.z - pPlayer->pos.z));
					if (g_Enemy[nEnemy].pos.x + MAX_SEARCH > pPlayer->pos.x&&g_Enemy[nEnemy].pos.x - MAX_SEARCH < pPlayer->pos.x)
					{
						if (g_Enemy[nEnemy].pos.y + MAX_SEARCH > pPlayer->pos.y&&g_Enemy[nEnemy].pos.y - MAX_SEARCH < pPlayer->pos.y)
						{
							if (g_Enemy[nEnemy].pos.z + MAX_SEARCH > pPlayer->pos.z&&g_Enemy[nEnemy].pos.z - MAX_SEARCH < pPlayer->pos.z)
							{
								/*プレイヤーの方向へ移動*/
								g_Enemy[nEnemy].movePos.x = sinf(g_Enemy[nEnemy].fAngle)*1.5f;
								g_Enemy[nEnemy].movePos.z = cosf(g_Enemy[nEnemy].fAngle)*1.5f;
								if (g_Enemy[nEnemy].rotDest.y>g_Enemy[nEnemy].rot.y + D3DXToRadian(180))
								{/*-180度から180度になる処理*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(180);
								}
								else if (g_Enemy[nEnemy].rotDest.y<g_Enemy[nEnemy].rot.y + D3DXToRadian(-180))
								{/*180度から-180度になる処理*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(-180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(-180);
								}
								/*プレイヤーがいる角度に向く*/
								g_Enemy[nEnemy].rotDest.y = (g_Enemy[nEnemy].fRot);
							}
						}
					}
					break;
				case 2:
					/*プレイヤーの位置を取得*/
					g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -pPlayer->pos.x), (-g_Enemy[nEnemy].pos.z - -pPlayer->pos.z));
					/*プレイヤーがいる方向の角度を取得*/
					g_Enemy[nEnemy].fRot = atan2f((g_Enemy[nEnemy].pos.x - pPlayer->pos.x), (g_Enemy[nEnemy].pos.z - pPlayer->pos.z));
					if (g_Enemy[nEnemy].pos.x + MAX_SEARCH > pPlayer->pos.x&&g_Enemy[nEnemy].pos.x - MAX_SEARCH < pPlayer->pos.x)
					{
						if (g_Enemy[nEnemy].pos.y + MAX_SEARCH > pPlayer->pos.y&&g_Enemy[nEnemy].pos.y - MAX_SEARCH < pPlayer->pos.y)
						{
							if (g_Enemy[nEnemy].pos.z + MAX_SEARCH > pPlayer->pos.z&&g_Enemy[nEnemy].pos.z - MAX_SEARCH < pPlayer->pos.z)
							{
								/*プレイヤーの方向へ移動*/
								g_Enemy[nEnemy].movePos.x = sinf(g_Enemy[nEnemy].fAngle)*1.5f;
								g_Enemy[nEnemy].movePos.z = cosf(g_Enemy[nEnemy].fAngle)*1.5f;
								if (g_Enemy[nEnemy].rotDest.y>g_Enemy[nEnemy].rot.y + D3DXToRadian(180))
								{/*-180度から180度になる処理*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(180);
								}
								else if (g_Enemy[nEnemy].rotDest.y<g_Enemy[nEnemy].rot.y + D3DXToRadian(-180))
								{/*180度から-180度になる処理*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(-180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(-180);
								}
								/*プレイヤーがいる角度に向く*/
								g_Enemy[nEnemy].rotDest.y = (g_Enemy[nEnemy].fRot);
							}
						}
					}
					break;
				case 3:
					/*プレイヤーの位置を取得*/
					g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -pPlayer->pos.x), (-g_Enemy[nEnemy].pos.z - -pPlayer->pos.z));
					/*プレイヤーがいる方向の角度を取得*/
					g_Enemy[nEnemy].fRot = atan2f((g_Enemy[nEnemy].pos.x - pPlayer->pos.x), (g_Enemy[nEnemy].pos.z - pPlayer->pos.z));
					if (g_Enemy[nEnemy].pos.x + MAX_SEARCH > pPlayer->pos.x&&g_Enemy[nEnemy].pos.x - MAX_SEARCH < pPlayer->pos.x)
					{
						if (g_Enemy[nEnemy].pos.y + MAX_SEARCH > pPlayer->pos.y&&g_Enemy[nEnemy].pos.y - MAX_SEARCH < pPlayer->pos.y)
						{
							if (g_Enemy[nEnemy].pos.z + MAX_SEARCH > pPlayer->pos.z&&g_Enemy[nEnemy].pos.z - MAX_SEARCH < pPlayer->pos.z)
							{
								/*プレイヤーの方向へ移動*/
								g_Enemy[nEnemy].movePos.x = sinf(g_Enemy[nEnemy].fAngle)*1.5f;
								g_Enemy[nEnemy].movePos.z = cosf(g_Enemy[nEnemy].fAngle)*1.5f;
								if (g_Enemy[nEnemy].rotDest.y>g_Enemy[nEnemy].rot.y + D3DXToRadian(180))
								{/*-180度から180度になる処理*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(180);
								}
								else if (g_Enemy[nEnemy].rotDest.y<g_Enemy[nEnemy].rot.y + D3DXToRadian(-180))
								{/*180度から-180度になる処理*/
									g_Enemy[nEnemy].rot.y = D3DXToRadian(-180);
									g_Enemy[nEnemy].rotDest.y = D3DXToRadian(-180);
								}
								/*プレイヤーがいる角度に向く*/
								g_Enemy[nEnemy].rotDest.y += 0.1f;
							}
						}
					}
					break;
				}

				
				
				/*------------------------------------------------------------------------------------*/
				break;
			case ENEMYSTATE_DAMAGE://ダメージ状態
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
	/*デバイスへのポインタ*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	/*現在のマテリアル保持用*/
	D3DMATERIAL9 matDef;
	
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		if (g_Enemy[nEnemy].use)
		{
		
			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_Enemy[nEnemy].mtxWorld);
			/*向きを反映*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nEnemy].rot.y, g_Enemy[nEnemy].rot.x, g_Enemy[nEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nEnemy].mtxWorld, &g_Enemy[nEnemy].mtxWorld, &mtxRot);
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nEnemy].pos.x, g_Enemy[nEnemy].pos.y, g_Enemy[nEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nEnemy].mtxWorld, &g_Enemy[nEnemy].mtxWorld, &mtxTrans);
			/*ワールドマトリックスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nEnemy].mtxWorld);
			/*現在のマテリアルを取得する*/
			pDevice->GetMaterial(&matDef);
			
				for (int nCntMat = 0; nCntMat < (int)g_Enemy[nEnemy].enemyParts[g_Enemy[nEnemy].nType].nNumMat; nCntMat++)
				{
					/*マテリアルの設定*/
					pDevice->SetMaterial(&pMatEnemy[g_Enemy[nEnemy].nType][nCntMat].MatD3D);
					pDevice->SetTexture(0, g_Enemy[nEnemy].enemyParts[g_Enemy[nEnemy].nType].pTextureModel[nCntMat]);
					/*種類別の描画*/
					g_Enemy[nEnemy].enemyParts[g_Enemy[nEnemy].nType].pMesh->DrawSubset(nCntMat);
				}
			/*保持していたマテリアルを戻す*/
			pDevice->SetMaterial(&matDef);
		}
	}
}
void SetEnemy(int Type, D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{	/*敵の種類設定*/
		if (!g_Enemy[nEnemy].use)
		{
			/*敵カウント*/
			g_nNumber += 1;
			/*位置の処理*/
			g_Enemy[nEnemy].pos = pos;
			g_Enemy[nEnemy].nType = Type;			
			/*使用処理*/
			g_Enemy[nEnemy].use = true;
			break;
		}
	}
}
void HitEnemy(int nDamage,int nCntEnemy)
{
		g_Enemy[nCntEnemy].nLife -= nDamage;
		if (g_Enemy[nCntEnemy].nLife <= 0)
		{/*ライフが０になったとき*/
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
		{/*ダメージ状態カウンター状態に移行*/
			g_Enemy[nCntEnemy].nCounterState = 5;
			g_Enemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;//ダメージ状態に移行
			
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