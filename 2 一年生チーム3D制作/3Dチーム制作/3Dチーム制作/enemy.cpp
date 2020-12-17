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
	char *pFilename;	// ファイル名
	int nCntLoop;		// 親子関係		
}FILE;
void SearchEnemy();
/*--グローバル変数--*/
/*モデル情報*/
D3DXMATERIAL *pMatEnemy[ENEMY_PARTS_MAX];
D3DXMATERIAL *pMatSearch;
ENEMY g_Enemy[MAX_ENEMY];
/*影の処理*/
int g_ShadowEnemy = 0;
/*ファイル*/
FILE g_FileEnemy[ENEMY_PARTS_MAX] =
{
	{ "Xファイル/配達員（胴体）.x", -1 },	//0
	{ "Xファイル/配達員（頭）.x", 0 },		//1
	{ "Xファイル/配達員（腹）.x", 0 },		//2
	{ "Xファイル/配達員（右腕1）.x", 0 },	//3
	{ "Xファイル/配達員（右腕2）.x", 3 },	//4
	{ "Xファイル/配達員（左腕1）.x", 0 },	//5
	{ "Xファイル/配達員（左腕2）.x", 5 },	//6
	{ "Xファイル/配達員（右足1）.x", 2 },	//7
	{ "Xファイル/配達員（右足2）.x", 7 },	//8
	{ "Xファイル/配達員（左足1）.x", 2 },	//9
	{ "Xファイル/配達員（左足2）.x", 9 },	//10
	};
/*------------------*/

void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		
		g_Enemy[nEnemy].state = ENEMYSTATE_NORMAL;
	
		/*初期位置*/
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
		/*初期向き*/
		g_Enemy[nEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*初期の大きさ*/
		g_Enemy[nEnemy].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*カラーの初期化処理*/
		g_Enemy[nEnemy].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		/*種類の初期*/
		g_Enemy[nEnemy].nType = NULL;
		/*初期使用処理*/
		g_Enemy[nEnemy].buse = false;
		/*巡回スイッチ*/
		g_Enemy[nEnemy].nPos = 0;
		/*視野の位置*/
		g_Enemy[nEnemy].enemySearch.SearchRot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	}
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		
		for (int nParts = 0; nParts < ENEMY_PARTS_MAX; nParts++)
		{
			/*Xファイルの読み込み*/
			D3DXLoadMeshFromX(
				g_FileEnemy[nParts].pFilename,
				D3DXMESH_MANAGED,
				pDevice,
				NULL,
				&g_Enemy[nEnemy].enemyParts[nParts].pBuffMat,
				NULL,
				&g_Enemy[nEnemy].enemyParts[nParts].nNumMat,
				&g_Enemy[nEnemy].enemyParts[nParts].pMesh);
			/*マテリアルデータへのポインタを取得*/
			pMatEnemy[nParts] = (D3DXMATERIAL*)g_Enemy[nEnemy].enemyParts[nParts].pBuffMat->GetBufferPointer();
			/*ファイルの読み込み*/
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
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		if (g_Enemy[nEnemy].buse)
		{
		
			/*向き更新*/
			g_Enemy[nEnemy].rot += (g_Enemy[nEnemy].rotDest - g_Enemy[nEnemy].rot)* 0.09;
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
			/*行動処理*/
			if (g_Enemy[nEnemy].pos.x + 30 >= pPlayer->pos.x
				&&g_Enemy[nEnemy].pos.x - 30 <= pPlayer->pos.x
				&&g_Enemy[nEnemy].pos.y + 30 >= pPlayer->pos.y
				&&g_Enemy[nEnemy].pos.y - 30 <= pPlayer->pos.y
				&&g_Enemy[nEnemy].pos.z + 30 >= pPlayer->pos.z
				&&g_Enemy[nEnemy].pos.z - 30 <= pPlayer->pos.z)
			{
				HitPlayer(1);
			}
			/*目標角度に向く*/
			g_Enemy[nEnemy].rotDest.y = (g_Enemy[nEnemy].fRot);
			/*目標方向へ移動*/
			g_Enemy[nEnemy].movePos.x = sinf(g_Enemy[nEnemy].fAngle)*1.0f;
			g_Enemy[nEnemy].movePos.z = cosf(g_Enemy[nEnemy].fAngle)*1.0f;
			/*ブロックに乗った時の処理*/
			if (CollisionBlockEnemy(&g_Enemy[nEnemy].pos, &g_Enemy[nEnemy].posOld, D3DXVECTOR3(MAX_SIZE1, MAX_SIZE1, MAX_SIZE1)) == true)
			{
				g_Enemy[nEnemy].movePos.y = 0;
				g_Enemy[nEnemy].vy = 0;
			}
			///*地面に乗った時の処理*/
			//else if (g_Enemy[nEnemy].Hit&&g_Enemy[nEnemy].fDist < 13.0f)
			//{
			//	g_Enemy[nEnemy].pos.y = g_Enemy[nEnemy].pos.y - g_Enemy[nEnemy].fDist + 13.0f;
			//	g_Enemy[nEnemy].vy = 0;
			//}
			else
			{
				///*重力*/
				//g_Enemy[nEnemy].vy += -0.07f;
			}

			/*方向処理*/
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
		

			/*エネミーの状態*/
			switch (g_Enemy[nEnemy].state)
			{
			case ENEMYSTATE_NORMAL://通常時
				if (g_Enemy[nEnemy].nPos == 0)
				{
					/*スタート位置の方向取得*/
					g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -g_Enemy[nEnemy].startPos.x), (-g_Enemy[nEnemy].pos.z - -g_Enemy[nEnemy].startPos.z));
					/*スタート位置方向の角度を取得*/
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
					/*終了位置の方向取得*/
					g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -g_Enemy[nEnemy].endPos.x), (-g_Enemy[nEnemy].pos.z - -g_Enemy[nEnemy].endPos.z));
					/*終了位置方向の角度を取得*/
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

			case ENEMYSTATE_TRACKING://追尾
				/*プレイヤーの位置を取得*/
				g_Enemy[nEnemy].fAngle = atan2f((-g_Enemy[nEnemy].pos.x - -pPlayer->pos.x), (-g_Enemy[nEnemy].pos.z - -pPlayer->pos.z));
				/*プレイヤーがいる方向の角度を取得*/
				g_Enemy[nEnemy].fRot = atan2f((g_Enemy[nEnemy].pos.x - pPlayer->pos.x), (g_Enemy[nEnemy].pos.z - pPlayer->pos.z));
				
				g_Enemy[nEnemy].movePos.x = sinf(g_Enemy[nEnemy].fAngle)*1.0f;
				g_Enemy[nEnemy].movePos.z = cosf(g_Enemy[nEnemy].fAngle)*1.0f;

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
	D3DXMATRIX mtxParent;
	/*現在のマテリアル保持用*/
	D3DMATERIAL9 matDef;
	
	for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		if (g_Enemy[nEnemy].buse)
		{
		
			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_Enemy[nEnemy].mtxWorld);
			/*向きを反映*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nEnemy].rot.y, g_Enemy[nEnemy].rot.x, g_Enemy[nEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nEnemy].mtxWorld, &g_Enemy[nEnemy].mtxWorld, &mtxRot);
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nEnemy].pos.x, g_Enemy[nEnemy].pos.y, g_Enemy[nEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nEnemy].mtxWorld, &g_Enemy[nEnemy].mtxWorld, &mtxTrans);
		
			SearchEnemy();
			for (int nParts = 0; nParts < ENEMY_PARTS_MAX; nParts++)
			{
				/*パーツワールドマトリクスの初期化処理*/
				D3DXMatrixIdentity(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime);

				/*パーツ向きを反映*/
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nEnemy].enemyParts[nParts].rotAnime.y, g_Enemy[nEnemy].enemyParts[nParts].rotAnime.x, g_Enemy[nEnemy].enemyParts[nParts].rotAnime.z);
				D3DXMatrixMultiply(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime, &mtxRot);
				/*パーツ位置を反映*/
				D3DXMatrixTranslation(&mtxTrans, g_Enemy[nEnemy].enemyParts[nParts].posAnime.x, g_Enemy[nEnemy].enemyParts[nParts].posAnime.y, g_Enemy[nEnemy].enemyParts[nParts].posAnime.z);
				D3DXMatrixMultiply(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime, &mtxTrans);

				/*親モデルのマトリックスの判断*/
				if (g_FileEnemy[nParts].nCntLoop == -1)
				{
					mtxParent = g_Enemy[nEnemy].mtxWorld;
				}
				else
				{
					mtxParent = g_Enemy[nEnemy].enemyParts[g_FileEnemy[nParts].nCntLoop].mtxWorldAnime;
				}
				D3DXMatrixMultiply(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime, &mtxParent);

				/*ワールドマトリックスの設定*/
				pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorld);

				/*パーツワールドマトリクスの初期化処理*/
				D3DXMatrixIdentity(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorld);
				/*アニメパーツ向きを反映*/
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nEnemy].enemyParts[nParts].rot.y, g_Enemy[nEnemy].enemyParts[nParts].rot.x, g_Enemy[nEnemy].enemyParts[nParts].rot.z);
				D3DXMatrixMultiply(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorld, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorld, &mtxRot);
				/*アニメパーツ位置を反映*/
				D3DXMatrixTranslation(&mtxTrans, g_Enemy[nEnemy].enemyParts[nParts].pos.x, g_Enemy[nEnemy].enemyParts[nParts].pos.y, g_Enemy[nEnemy].enemyParts[nParts].pos.z);
				D3DXMatrixMultiply(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorld, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorld, &mtxTrans);

				D3DXMatrixMultiply(&g_Enemy[nEnemy].enemyParts[nParts].mtxWorld, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorld, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorldAnime);

				/*ワールドマトリックスの設定*/
				pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nEnemy].enemyParts[nParts].mtxWorld);

				/*現在のマテリアルを取得する*/
				pDevice->GetMaterial(&matDef);

				for (int nCntMat = 0; nCntMat < (int)g_Enemy[nEnemy].enemyParts[nParts].nNumMat; nCntMat++)
				{
					/*マテリアルの設定*/
					pDevice->SetMaterial(&pMatEnemy[nParts][nCntMat].MatD3D);
					pDevice->SetTexture(0, g_Enemy[nEnemy].enemyParts[nParts].pTextureModel[nCntMat]);
					/*パーツ別の描画*/
					g_Enemy[nEnemy].enemyParts[nParts].pMesh->DrawSubset(nCntMat);
				}
				/*保持していたマテリアルを戻す*/
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
	{	/*敵の種類設定*/
		if (!g_Enemy[nEnemy].buse)
		{
			/*位置の処理*/
			g_Enemy[nEnemy].pos = pos;
			/*巡回スタート位置*/
			g_Enemy[nEnemy].startPos = startPos;
			/*巡回終了位置*/
			g_Enemy[nEnemy].endPos = endPos;
			/*敵の種類*/
			g_Enemy[nEnemy].nType = Type;			
			/*使用処理*/
			g_Enemy[nEnemy].buse = true;
			break;
		}
	}
}
void HitEnemy(int nDamage,int nCntEnemy)
{
		g_Enemy[nCntEnemy].nLife -= nDamage;
		if (g_Enemy[nCntEnemy].nLife <= 0)
		{/*ライフが０になったとき*/
			g_Enemy[nCntEnemy].buse = false;
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
	
}