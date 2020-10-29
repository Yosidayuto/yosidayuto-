#include "main.h"
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "billboard.h"
#include "block.h"
#include "enemy.h"
#include "item.h"
#include "fade.h"
#include "score.h"
#include "map.h"
#include <stdio.h>
#include <string.h>
/*マクロ定義*/
#define FILE_DATA 3				//テキスト読み込みのデータ
/*--グローバル変数--*/
void SetPlayeAnimation(int playerAnimation);
void UpdatePlayeAnimation();
typedef struct 
{
	char			file[100];	//読み込んだ１列の文字
	int				nAnimaTion;	//何番目のアニメーションか
	int				nFrame;		//フレイム数
	int				nKeySet;	//現在のキーセットの数
}FILETEXT;
FILETEXT g_filetext;
typedef struct
{
	char *pFilename;	// ファイル名
	int nCntLoop;		// 親子関係		
}FILEDATA;
/*マテリアルデータへのポインタ*/
D3DXMATERIAL *pMat[MODEL_LABEL_MAX];
/*モデル情報*/
PLAYER g_Player;
/*影の処理*/
int g_Shadow=0;
/*モデルの向き*/
D3DXVECTOR3 dir;
/*現在のフレーム数*/
int g_frameCountModel = 0;
/*再生中のキーセットインデックス*/
int g_playKeySetlndexModel = 0;
/*再生中のアニメモーション*/
int g_PlayerCurrentAnimationModel = 0;
/*ファイル*/
FILEDATA g_FilePlayer[MODEL_LABEL_MAX] =
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
void anime(void);
Animation g_motion[MOTION_ANIMATION_NUM];
/*------------------*/
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA* pCamera = GetCamera();
	for (int nParts = 0; nParts < MODEL_LABEL_MAX; nParts++)
	{
		/*Xファイルの読み込み*/
		D3DXLoadMeshFromX(
			g_FilePlayer[nParts].pFilename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.modelParts[nParts].pBuffMat,
			NULL,
			&g_Player.modelParts[nParts].nNumMat,
			&g_Player.modelParts[nParts].pMesh);
		/*マテリアルデータへのポインタを取得*/
		pMat[nParts] = (D3DXMATERIAL*)g_Player.modelParts[nParts].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.modelParts[nParts].nNumMat; nCntMat++)
		{
			if (pMat[nParts][nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nParts][nCntMat].pTextureFilename, &g_Player.modelParts[nParts].pTextureModel[nCntMat]);
			}
		}
	}
	/*テキスト情報の初期化*/
	g_filetext.nAnimaTion	 = 0;
	g_filetext.nFrame		 = 0;
	/*初期位置*/
	g_Player.pos = D3DXVECTOR3(0.0f, 25.0f, 0.0f);
	g_Player.modelParts[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.modelParts[1].pos = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	g_Player.modelParts[2].pos = D3DXVECTOR3(0.0f, -7.0f, 0.0f);
	g_Player.modelParts[3].pos = D3DXVECTOR3(-4.1f, 1.0f, 0.0f);
	g_Player.modelParts[4].pos = D3DXVECTOR3(-4.1f, -3.0f, 0.0f);
	g_Player.modelParts[5].pos = D3DXVECTOR3(4.0f, 1.0f, 0.0f);
	g_Player.modelParts[6].pos = D3DXVECTOR3(4.1f, -3.0f, 0.0f);
	g_Player.modelParts[7].pos = D3DXVECTOR3(-1.0f, -8.0f, 0.1f);
	g_Player.modelParts[8].pos = D3DXVECTOR3(-2.0f, -15.0f, 0.1f);
	g_Player.modelParts[9].pos = D3DXVECTOR3(1.0f, -8.0f, 0.1f);
	g_Player.modelParts[10].pos = D3DXVECTOR3(2.0f, -15.0f, 0.1f);
	/*初期向き*/
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nItemType = 0; nItemType < TITLE_TYPE_MAX; nItemType++)
	{	
		for (int nItem=0; nItem < MAX_ITEM; nItem++)
		{	/*初期アイテム所持*/
			g_Player.bItem[nItem][nItemType] = false;
			/*アイテムライフ*/
			g_Player.nLife[nItem][nItemType] = 0;
		}
	}
	/*ダメージ無敵時間*/
	g_Player.nDamage = 0;
	/*ゴールスイッチ初期化*/
	g_Player.bGoal = false;
	dir = D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y)), 0, -cosf(D3DXToRadian(pCamera->rot.y)));
	g_Shadow=SetShadow(D3DXVECTOR3(g_Player.pos.x, 0, g_Player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	anime();
}
void UninitPlayer(void)
{
	for (int nParts = 0; nParts < MODEL_LABEL_MAX; nParts++)
	{
		/*メッシュの破棄*/
		if (g_Player.modelParts[nParts].pMesh != NULL)
		{
			g_Player.modelParts[nParts].pMesh->Release();
			g_Player.modelParts[nParts].pMesh = NULL;
		}

		/*マテリアルの破棄*/
		if (g_Player.modelParts[nParts].pBuffMat != NULL)
		{
			g_Player.modelParts[nParts].pBuffMat->Release();
			g_Player.modelParts[nParts].pBuffMat = NULL;
		}
		/*テクスチャ*/
		for (int nCnt = 0; nCnt < (int)g_Player.modelParts[nParts].nNumMat; nCnt++)
		{
			if (g_Player.modelParts[nParts].pTextureModel[nCnt] != NULL)
			{
				g_Player.modelParts[nParts].pTextureModel[nCnt]->Release();
				g_Player.modelParts[nParts].pTextureModel[nCnt] = NULL;
			}
		}
	}

	
}
void UpdatePlayer(void)
{
	/*コントローラーの処理*/
	JOYINFOEX JOYPAD;
	CAMERA* pCamera = GetCamera();
	/*ジョイパットの入力*/
	JOYPAD.dwSize = sizeof(JOYINFOEX);
	JOYPAD.dwFlags = JOY_RETURNALL; // 全ての情報を取得
	
	/*----------------------------------------------------------------------------------*/
	/*影の処理*/
	SetPositionShadow(g_Shadow, D3DXVECTOR3(g_Player.pos.x,0.1f, g_Player.pos.z));
	/*----------------------------------------------------------------------------------*/
	/*カメラの向きから、前後左右にモデルを移動させる*/
	if (joyGetPosEx(JOYSTICKID1, &JOYPAD) == JOYERR_NOERROR)
	{
		if (JOYPAD.dwButtons & JOY_BUTTON1)//歩き
		{
			if (JOYPAD.dwXpos > 0x7FFF + 0x4000)//左に倒すスティック
			{
				g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y - 90)) * 0.5f;
				g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y - 90)) * 0.5f;
			}
			if (JOYPAD.dwXpos < 0x7FFF - 0x4000)//右に倒すスティック
			{
				g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y + 90)) * 0.5f;
				g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y + 90)) * 0.5f;
			}
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)//後ろに倒すスティック
			{
				g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y)) * 0.5f;
				g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y)) * 0.5f;
			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)//前に倒すスティック
			{
				g_Player.movePos.x -= sinf(D3DXToRadian(pCamera->rot.y)) * 0.5f;
				g_Player.movePos.z -= cosf(D3DXToRadian(pCamera->rot.y)) * 0.5f;
			}
		}
		else//通常
		{
			if (JOYPAD.dwXpos > 0x7FFF + 0x4000)//左に倒すスティック
			{
				g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y - 90)) * 1;
				g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y - 90)) * 1;
			}
			if (JOYPAD.dwXpos < 0x7FFF - 0x4000)//右に倒すスティック
			{
				g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y + 90)) * 1;
				g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y + 90)) * 1;
			}
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)//後ろに倒すスティック
			{
				g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y)) * 1;
				g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y)) * 1;
			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)//前に倒すスティック
			{
				g_Player.movePos.x -= sinf(D3DXToRadian(pCamera->rot.y)) * 1;
				g_Player.movePos.z -= cosf(D3DXToRadian(pCamera->rot.y)) * 1;
			}
		}
		if (JOYPAD.dwXpos > 0x7FFF + 0x4000)//左に倒すスティック
		{
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 135);
			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 45);
			}
			else
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 90);

			}
		}
		
		else if (JOYPAD.dwXpos < 0x7FFF - 0x4000)//右に倒すスティック
		{
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 225);
			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 315);
			}
			else
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 270);
			}
		}
		else if (JOYPAD.dwYpos > 0x7FFF + 0x4000)//後ろに倒すスティック
		{
			g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 180);
		}
		else if (JOYPAD.dwYpos < 0x7FFF - 0x4000)//前に倒すスティック
		{
			g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 0);
		}

		/*g_Model.movePos.x = sinf(D3DXToRadian(pCamera->rot.y)) * 1;
		g_Model.movePos.z = cosf(D3DXToRadian(pCamera->rot.y)) * 1;*/
		/*ボタン32個まで 空制御 */
		
		
		//g_Model.rotDest.y = D3DXToRadian(pCamera->rot.y );
		dir = D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y+ JOYPAD.dwXpos)), 0, -cosf(D3DXToRadian(pCamera->rot.y+ JOYPAD.dwYpos)));
	}
	//if (Getkeyboardpress(DIK_UP))
	//{
	//	g_Model.movePos.x -= sinf(D3DXToRadian(pCamera->rot.y)) * 1;
	//	g_Model.movePos.z -= cosf(D3DXToRadian(pCamera->rot.y)) * 1;
	//	g_Model.rotDest.y = D3DXToRadian(pCamera->rot.y + 0);
	//	dir = D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y)), 0, -cosf(D3DXToRadian(pCamera->rot.y)));
	//}
	//if (Getkeyboardpress(DIK_DOWN))
	//{
	//	g_Model.movePos.x += sinf(D3DXToRadian(pCamera->rot.y)) * 1;
	//	g_Model.movePos.z += cosf(D3DXToRadian(pCamera->rot.y)) * 1;
	//	g_Model.rotDest.y = D3DXToRadian(pCamera->rot.y + 180);
	//	dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y)), 0, cosf(D3DXToRadian(pCamera->rot.y)));
	//}
	//if (Getkeyboardpress(DIK_LEFT))
	//{
	//	g_Model.movePos.x += sinf(D3DXToRadian(pCamera->rot.y + 90)) * 1;
	//	g_Model.movePos.z += cosf(D3DXToRadian(pCamera->rot.y+90)) * 1;
	//	g_Model.rotDest.y = D3DXToRadian(pCamera->rot.y + 270);
	//	dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y + 90)), 0, cosf(D3DXToRadian(pCamera->rot.y + 90)));
	//}
	//if (Getkeyboardpress(DIK_RIGHT))
	//{
	//	g_Model.movePos.x += sinf(D3DXToRadian(pCamera->rot.y - 90)) * 1;
	//	g_Model.movePos.z += cosf(D3DXToRadian(pCamera->rot.y - 90)) * 1;
	//	g_Model.rotDest.y = D3DXToRadian(pCamera->rot.y + 90);
	//	dir = D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y + 90)), 0, -cosf(D3DXToRadian(pCamera->rot.y + 90)));
	//}
	/*----------------------------------------------------------------------------------*/
	/*振り向き処理*/
	if (D3DXToRadian(pCamera->rot.y) >= (D3DXToRadian(360)) || D3DXToRadian(pCamera->rot.y) <= (D3DXToRadian(-360)))
	{
		pCamera->rot.y = D3DXToRadian(0);
		//g_Player.rotDest.y = D3DXToRadian(0);
		if (JOYPAD.dwXpos > 0x7FFF + 0x4000)//左に倒すスティック
		{
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)
			{
				g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 135);
			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)
			{
				g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 45);
			}
			else
			{
				g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 90);
			}
		}

		else if (JOYPAD.dwXpos < 0x7FFF - 0x4000)//右に倒すスティック
		{
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)
			{
				g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 225);
			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)
			{
				g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 315);
			}
			else
			{
				g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 270);
			}
		}
		else if (JOYPAD.dwYpos > 0x7FFF + 0x4000)//後ろに倒すスティック
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 180);
		}
		else if (JOYPAD.dwYpos < 0x7FFF - 0x4000)//前に倒すスティック
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 0);
		}
		
	}
	else if (g_Player.rot.y >=D3DXToRadian(pCamera->rot.y+180)&& g_Player.rotDest.y == D3DXToRadian(pCamera->rot.y + 0))//右回り処理
	{
		if (g_Player.rot.y <= D3DXToRadian(pCamera->rot.y + 315))
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y - 45);
		}
		else if (g_Player.rot.y >= D3DXToRadian(pCamera->rot.y + 270) && g_Player.rot.y < D3DXToRadian(pCamera->rot.y + 314))
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y - 90);
		}
	}
	else if (g_Player.rot.y<=D3DXToRadian(pCamera->rot.y + 90))//左回り
	{
		if (g_Player.rotDest.y == D3DXToRadian(pCamera->rot.y + 270))
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 360);
		}
		else if (g_Player.rotDest.y == D3DXToRadian(pCamera->rot.y + 315))
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 360);
		}
	}
	
	g_Player.rot += (g_Player.rotDest - g_Player.rot)* 0.09;
	/*----------------------------------------------------------------------------------*/
	/*ブロック判定*/
	if (CollisionBlock(&g_Player.pos, &g_Player.posOld, D3DXVECTOR3(10, 40, 10)) == true)
	{
		g_Player.movePos.y = 0;
		//g_Player.vy = 0;
	}
	else
	{

	}
	if (g_Player.state != PLAYERSTATE_DAMAGE)
	{
		CollisionItem(&g_Player.pos, &g_Player.posOld, D3DXVECTOR3(10, 40, 10));
	}
	/*-------------------------------------------------------------------------------------*/



	/*慣性*/
	g_Player.movePos.x += (0.0f - g_Player.movePos.x)*0.5f;
	g_Player.movePos.y += (0.0f - g_Player.movePos.y)*0.5f;
	g_Player.movePos.z += (0.0f - g_Player.movePos.z)*0.5f;
	/*位置更新*/
	g_Player.pos += g_Player.movePos;
	/*重力加速度更新*/
	//g_Player.movePos.y += g_Player.vy;
	/*位置の記録*/
	g_Player.posOld = g_Player.pos;
	/*-------------------------------------------------------------------------------------*/
	/*プレイヤーモード(ダメージ)*/
	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_Player.nDamage--;
		if (g_Player.nDamage <= 0)
		{
			/*通常描画に戻す処理*/
			g_Player.state = PLAYERSTATE_NORMAL;
		}
		break;
	case PLAYERSTATE_DEATH:
		SetFade(MODE_GAMEOVER);
		return;
		break;
	}
	/*アニメーション再生*/
	UpdatePlayeAnimation();
}
void DrawPlayer(void)
{
	/*デバイスへのポインタ*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxParent;
	/*現在のマテリアル保持用*/
	D3DMATERIAL9 matDef;
	
	/*ワールドマトリクスの初期化処理*/
	D3DXMatrixIdentity(&g_Player.mtxWorld);
	/*向きを反映*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);
	/*位置を反映*/
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);
	for (int nParts = 0; nParts < MODEL_LABEL_MAX; nParts++)
	{
		/*パーツワールドマトリクスの初期化処理*/
		D3DXMatrixIdentity(&g_Player.modelParts[nParts].mtxWorldAnime);

		/*パーツ向きを反映*/
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.modelParts[nParts].rotAnime.y, g_Player.modelParts[nParts].rotAnime.x, g_Player.modelParts[nParts].rotAnime.z);
		D3DXMatrixMultiply(&g_Player.modelParts[nParts].mtxWorldAnime, &g_Player.modelParts[nParts].mtxWorldAnime, &mtxRot);
		/*パーツ位置を反映*/
		D3DXMatrixTranslation(&mtxTrans, g_Player.modelParts[nParts].posAnime.x, g_Player.modelParts[nParts].posAnime.y, g_Player.modelParts[nParts].posAnime.z);
		D3DXMatrixMultiply(&g_Player.modelParts[nParts].mtxWorldAnime, &g_Player.modelParts[nParts].mtxWorldAnime, &mtxTrans);

		/*親モデルのマトリックスの判断*/
		if (g_FilePlayer[nParts].nCntLoop == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.modelParts[g_FilePlayer[nParts].nCntLoop].mtxWorldAnime;
		}
		D3DXMatrixMultiply(&g_Player.modelParts[nParts].mtxWorldAnime, &g_Player.modelParts[nParts].mtxWorldAnime, &mtxParent);
		
		/*ワールドマトリックスの設定*/
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.modelParts[nParts].mtxWorld);
		
		/*パーツワールドマトリクスの初期化処理*/
		D3DXMatrixIdentity(&g_Player.modelParts[nParts].mtxWorld);
		/*アニメパーツ向きを反映*/
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.modelParts[nParts].rot.y, g_Player.modelParts[nParts].rot.x, g_Player.modelParts[nParts].rot.z);
		D3DXMatrixMultiply(&g_Player.modelParts[nParts].mtxWorld, &g_Player.modelParts[nParts].mtxWorld, &mtxRot);
		/*アニメパーツ位置を反映*/
		D3DXMatrixTranslation(&mtxTrans, g_Player.modelParts[nParts].pos.x, g_Player.modelParts[nParts].pos.y, g_Player.modelParts[nParts].pos.z);
		D3DXMatrixMultiply(&g_Player.modelParts[nParts].mtxWorld, &g_Player.modelParts[nParts].mtxWorld, &mtxTrans);

		D3DXMatrixMultiply(&g_Player.modelParts[nParts].mtxWorld, &g_Player.modelParts[nParts].mtxWorld, &g_Player.modelParts[nParts].mtxWorldAnime);

		/*ワールドマトリックスの設定*/
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.modelParts[nParts].mtxWorld);

	
		/*現在のマテリアルを取得する*/
		pDevice->GetMaterial(&matDef);
		for (int nCntMat = 0; nCntMat < (int)g_Player.modelParts[nParts].nNumMat; nCntMat++)
		{
			/*マテリアルの設定*/
			pDevice->SetMaterial(&pMat[nParts][nCntMat].MatD3D);

			pDevice->SetTexture(0, g_Player.modelParts[nParts].pTextureModel[nCntMat]);
			/*モデルパーツの描画*/
			g_Player.modelParts[nParts].pMesh->DrawSubset(nCntMat);
		}
		/*保持していたマテリアルを戻す*/
		pDevice->SetMaterial(&matDef);
	}
}
void HitPlayer(bool bDamage)
{
	ITEM* pItem = GetItem();
	CAMERA* pCamera = GetCamera();
	ENEMY* pEnemy = GetEnemy();
	if (g_Player.state == PLAYERSTATE_NORMAL)
	{
		for (int nItem = 0; nItem < MAX_ITEM; nItem++)
		{
			for (int nItemType = 0; nItemType < TITLE_TYPE_MAX; nItemType++)
			{
				if (g_Player.bItem[nItem][nItemType])
				{
					SetItem(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y+10, g_Player.pos.z), D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y +45* (nItem))), 0.1f, -cosf(D3DXToRadian(pCamera->rot.y +45 * (nItem)))), nItemType);
					g_Player.bItem[nItem][nItemType] = false;
					if (g_Player.nLife[nItem][nItemType] < 3)
					{
						g_Player.nLife[nItem][nItemType] += 1;
					}
					
				}
			}
		}
		g_Player.state = PLAYERSTATE_DAMAGE;//ダメージ状態に移行
		g_Player.nDamage = 100;
		g_Player.bGoal = false;
	}
}
void SetPlayeAnimation(int playerAnimation)
{
	if (g_PlayerCurrentAnimationModel != playerAnimation)
	{
		g_frameCountModel = 0;
		g_playKeySetlndexModel = 0;
	}
	g_PlayerCurrentAnimationModel = playerAnimation;
	g_motion[g_PlayerCurrentAnimationModel].keySet[g_playKeySetlndexModel];

}
void UpdatePlayeAnimation()
{
	if (g_frameCountModel == 0)
	{
	
		for (int nAnime = 0; nAnime < MODEL_LABEL_MAX; nAnime++)
		{
			g_Player.modelParts[nAnime].moverotAnime = (g_motion[g_PlayerCurrentAnimationModel].keySet[g_playKeySetlndexModel].key[nAnime].rot - g_Player.modelParts[nAnime].rotAnime) / g_motion[g_PlayerCurrentAnimationModel].keySet[g_playKeySetlndexModel].frame;
			g_Player.modelParts[nAnime].moveposAnime = (g_motion[g_PlayerCurrentAnimationModel].keySet[g_playKeySetlndexModel].key[nAnime].pos - g_Player.modelParts[nAnime].posAnime) / g_motion[g_PlayerCurrentAnimationModel].keySet[g_playKeySetlndexModel].frame;
		}
	}
	g_frameCountModel++;
	if (g_motion[g_PlayerCurrentAnimationModel].keySet[g_playKeySetlndexModel].frame == g_frameCountModel)
	{
		g_frameCountModel = 0;
		g_playKeySetlndexModel++;
		if (g_playKeySetlndexModel == g_motion[g_PlayerCurrentAnimationModel].keyNum&&g_motion[g_PlayerCurrentAnimationModel].isLoop)
		{
			g_playKeySetlndexModel = 0;
		}
		else
		{
			SetPlayeAnimation(0);
			g_frameCountModel = 0;
		}
	}
	for (int nAnime = 0; nAnime < MODEL_LABEL_MAX; nAnime++)
	{
		g_Player.modelParts[nAnime].rotAnime += g_Player.modelParts[nAnime].moverotAnime;
		g_Player.modelParts[nAnime].posAnime += g_Player.modelParts[nAnime].moveposAnime;
	}

}
void anime(void)
{
	/*テキスト読み込み*/
	FILE *file;
	char *fileneName = "テキスト/test.txt";	//テキストの名前
	char *Type;								//読み込んだテキスト（アニメーション再生）
	char *Status;							//読み込んだ項目


				
	if ((file = fopen(fileneName, "r"))!=NULL)//テキストを開く
	{
		while (fgets(g_filetext.file, 100, file) != NULL)//テキストを読み成功
		{	
			if ((Type = strstr(g_filetext.file, "MOTIONSET"))!=NULL)//検索して一致していたら
			{

			}
			/*ループするかの処理*/
			if ((Status = strstr(g_filetext.file, "LOOP")) != NULL)//検索して一致していたら
			{
				char *hbool;
				g_Player.x += 1;//ブレイクポイント置くため
				hbool = strchr(g_filetext.file, '1');//１か０かの比例
				if (hbool != NULL)
				{
					g_motion[g_filetext.nAnimaTion].isLoop = true;
				}
				else
				{
					g_motion[g_filetext.nAnimaTion].isLoop = false;
				}
				
			}
			/*キーの数の読み込み処理*/
			else if ((Status = strstr(g_filetext.file, "NUM_KEY")) != NULL)//検索して一致していたら
			{
				int  nKey;
				
				for (int nCount = 0; nCount < 100; nCount++)//文字列の数字読み込み
				{
					if ((isdigit(g_filetext.file[nCount])) != NULL)
					{
						nKey = atoi(&g_filetext.file[nCount]);//読み込んだ文字列をint型に変換
						
						g_motion[g_filetext.nAnimaTion].keyNum += nKey;
						g_Player.x += 1;//ブレイクポイント置くため
					}
				}
			}
			/*キーフレーム数処理*/
			else if ((Status = strstr(g_filetext.file, "FRAME")) != NULL)
			{
				for (int nCount = 0; nCount < 100; nCount++)//文字列の数字読み込み
				{
					if ((isdigit(g_filetext.file[nCount])) != 0)
					{
						int  nKey = atoi(&g_filetext.file[nCount]);//読み込んだ文字列をint型に変換
						g_motion[g_filetext.nAnimaTion].keySet[g_filetext.nFrame].frame += nKey;
						g_Player.z += 1;//ブレイクポイント置くため
					}
				}
			}
			else if ((Status = strstr(g_filetext.file, "KEY")) != NULL)
			{

			}
			/*各部位の座標処理*/
			else if ((Status = strstr(g_filetext.file, "POS")) != NULL)
			{
				char	sSymbolpos[]="POS =	";	//分解する区切り文字
				char	*testpos;			//分解したテキストを保存
				double	dpos[FILE_DATA];		//座標の保存
				int		nCountpos =0;		//座標XYZの数値保存

				testpos = strtok(g_filetext.file, sSymbolpos);
				while (testpos != NULL)
				{
					dpos[nCountpos] = atof(testpos);
					g_motion[g_filetext.nAnimaTion].keySet[g_filetext.nFrame].key[g_filetext.nKeySet].pos = D3DXVECTOR3(dpos[0], dpos[1], dpos[2]);
					testpos = strtok(NULL, sSymbolpos);
					nCountpos += 1;
				}
			}
			else if ((Status = strstr(g_filetext.file, "ROT")) != NULL)
			{
				char	sSymbolrot[] = "ROT =	";	//分解する区切り文字
				char	*testrot;					//分解したテキストを保存
				double	drot[FILE_DATA];			//座標の保存
				int		nCountrot = 0;				//座標XYZの数値保存

				testrot = strtok(g_filetext.file, sSymbolrot);
				while (testrot != NULL)
				{
					drot[nCountrot] = atof(testrot);
					g_motion[g_filetext.nAnimaTion].keySet[g_filetext.nFrame].key[g_filetext.nKeySet].rot = D3DXVECTOR3(D3DXToRadian(drot[0]), D3DXToRadian(drot[1]), D3DXToRadian(drot[2]));
					testrot = strtok(NULL, sSymbolrot);
					nCountrot += 1;
				}
			}
			if ((Status = strstr(g_filetext.file, "END_KEY")) != NULL)
			{
				g_filetext.nKeySet += 1;
			}
			if ((Status = strstr(g_filetext.file, "END_KEYSET")) != NULL)
			{
				g_filetext.nFrame += 1;
				g_filetext.nKeySet = 0;
			}
			if ((Status = strstr(g_filetext.file, "END_MOTIONSET")) != NULL)
			{
				g_filetext.nFrame = 0;
				g_filetext.nAnimaTion += 1;
			}
		}
		fclose(file);							//テキストを閉じる
	}
	
}
PLAYER*GetPlayer()
{
	return &g_Player;
}