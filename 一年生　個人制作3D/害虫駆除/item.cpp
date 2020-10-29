#include"main.h"
#include"item.h"
#include"model.h"
#include"magic_ui.h"
#include"sound.h"
//グローバル変数
/*頂点バッファへのポインタ*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem[TITLE_TYPE_MAX] = {};
/*ポリゴンのテクスチャ*/
LPDIRECT3DTEXTURE9 g_pTextureItem[TITLE_TYPE_MAX] = {};
/*ビルボード*/
ITEM g_Item[MAX_ITEM];
/*画像の読み込み準備*/
typedef struct
{
	char *pFilename;	// ファイル名
	//int n_Type;			//種類
}FILE_ITEM;
/*画像の種類*/
FILE_ITEM g_File[TITLE_TYPE_MAX] =
{
	{ "data/image/Water.png" },
	{ "data/image/Phlogistic.png" },
	{ "data/image/Grass.png" },
	{ "data/image/star.png" },
};
void InitItem(void)
{
	VERTEX_3D*pVtx = NULL;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nItem = 0; nItem< MAX_ITEM; nItem++)
	{
		g_Item[nItem].use = false;
		g_Item[nItem].nType = 0;
	}
	for (int i = 0; i < TITLE_TYPE_MAX; i++)
	{
		/*頂点バッファの生成*/
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ITEM,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffItem[i],
			NULL);
		D3DXCreateTextureFromFile(pDevice,g_File[i].pFilename, &g_pTextureItem[i]);
		/*頂点バッファをロック*/
		g_pVtxBuffItem[i]->Lock(0, 0, (void**)&pVtx, 0);
			/*頂点座標の設定*/
			pVtx[0].pos = D3DXVECTOR3(-ITEM_SIZE / 2, ITEM_SIZE / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(ITEM_SIZE / 2, ITEM_SIZE / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-ITEM_SIZE / 2, -ITEM_SIZE / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(ITEM_SIZE / 2, -ITEM_SIZE / 2, 0.0f);
			/*各頂点の法線の設定（ベクトルの大きさは１にする必要がある）*/
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			/*頂点カラーの設定*/
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			/*テクスチャの設定*/
			pVtx[0].tex = D3DXVECTOR2(0, 0);
			pVtx[1].tex = D3DXVECTOR2(1, 0);
			pVtx[2].tex = D3DXVECTOR2(0, 1);
			pVtx[3].tex = D3DXVECTOR2(1, 1);
		
		/*頂点バッファのアンロック*/
		g_pVtxBuffItem[i]->Unlock();
	}
	
}
void UninitItem(void)
{
	for (int i = 0; i < TITLE_TYPE_MAX; i++)
	{
		if (g_pTextureItem[i] != NULL)
		{
			g_pTextureItem[i]->Release();
			g_pTextureItem[i] = NULL;
		}
		/*頂点バッファの解放*/
		if (g_pVtxBuffItem[i] != NULL)
		{
			g_pVtxBuffItem[i]->Release();
			g_pVtxBuffItem[i] = NULL;
		}
	}
	
}
void UpdateItem(void)
{
	
}
void SetItem(D3DXVECTOR3 pos,int nType)
{
	VERTEX_3D*pVtx = NULL;
	for (int nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (!g_Item[nItem].use)
		{
			/*位置設定*/
			g_Item[nItem].pos = pos;
			/*アイテム種類*/
			g_Item[nItem].nType = nType;
			/*使用しているか*/
			g_Item[nItem].use = true;
			break;
		}
		
	}
}
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	for (int nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_Item[nItem].use)
		{
			/*アルファテストを有効化*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			/*アルファテスト基準値の設定*/
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			/*アルファテストの比較方法の設定*/
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			/*ワールドマトリクスの初期化処理*/
			D3DXMatrixIdentity(&g_Item[nItem].mtxWorld);
			//回転の逆行列を生成
			pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
			D3DXMatrixInverse(&g_Item[nItem].mtxWorld, NULL, &mtxRot);
			g_Item[nItem].mtxWorld._41 = 0;
			g_Item[nItem].mtxWorld._42 = 0;
			g_Item[nItem].mtxWorld._43 = 0;
			/*位置を反映*/
			D3DXMatrixTranslation(&mtxTrans, g_Item[nItem].pos.x, g_Item[nItem].pos.y, g_Item[nItem].pos.z);
			D3DXMatrixMultiply(&g_Item[nItem].mtxWorld, &g_Item[nItem].mtxWorld, &mtxTrans);
			/*ワールドマトリクスの設定*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Item[nItem].mtxWorld);
			/*頂点バッファをデバイスのデータストリームに設定*/
			pDevice->SetStreamSource(0, g_pVtxBuffItem[g_Item[nItem].nType], 0, sizeof(VERTEX_3D));
			/*頂点フォーマットの設定*/
			pDevice->SetFVF(FVF_VERTEX_3D);

			pDevice->SetTexture(0, g_pTextureItem[g_Item[nItem].nType]);
			/*ポリゴン描画*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			/*アルファテストを無効化*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
			
		
	}
	pDevice->SetTexture(0, NULL);
}
bool CollisionItem(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	PLAYER *pPlayer = GetPlayer();
	bool isGround = false;
	for (int nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_Item[nItem].use == true)
		{
			D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / 2, size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / 2, -size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 box2Max = D3DXVECTOR3(ITEM_SIZE / 2, ITEM_SIZE / 2, ITEM_SIZE / 2) + g_Item[nItem].pos;
			D3DXVECTOR3 box2Min = D3DXVECTOR3(-ITEM_SIZE / 2, -ITEM_SIZE / 2, -ITEM_SIZE / 2) + g_Item[nItem].pos;
			if (box2Min.y <= box1Max.y&&box2Max.y >= box1Max.y
				|| box2Max.y >= box1Min.y&&box2Min.y <= box1Min.y)
			{
				if (box2Min.x <= box1Max.x&&box2Max.x >= box1Max.x
					|| box2Max.x >= box1Min.x&&box2Min.x <= box1Min.x)
				{
					if (box2Min.z <= box1Max.z&&box2Max.z >= box1Max.z
						|| box2Max.z >= box1Min.z&&box2Min.z <= box1Min.z)
					{
						PlaySound(SOUND_LABEL_SE_ITEM);
						Magic_Number(1, g_Item[nItem].nType);
						g_Item[nItem].use = false;
					}
				}
			}
		}
	}
	return isGround;
}