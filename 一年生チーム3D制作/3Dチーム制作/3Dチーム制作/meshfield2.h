
#pragma once
#ifndef  MESHFIELD2_H
#define  MESHFIELD2_H

#include"main.h"

#define MESHFIE2L_X_BLOCK 8				//X方向のブロック数
#define MESHFIEL2_Y_BLOCK 10			//Y方向のブロック数
#define MESHFIEL2_VERTEX_NUM ((MESHFIE2L_X_BLOCK+1)*(MESHFIEL2_Y_BLOCK+1))									//頂点
#define MESHFIEL2_INDEX_NUM (((((MESHFIE2L_X_BLOCK-1)*2)+4)*MESHFIEL2_Y_BLOCK)+(2*(MESHFIEL2_Y_BLOCK-1)))	//インデックス
#define MESHFIEL2_PRIMITIVE_NUM (MESHFIE2L_X_BLOCK*MESHFIEL2_Y_BLOCK*2)+((MESHFIEL2_Y_BLOCK-1)*4)			//ポリゴン

typedef struct
{
	D3DXVECTOR3 pos;//位置情報
	D3DXVECTOR3 rot;//向き情報
	bool bUse;
	D3DXMATRIX mtxWorld;//行列計算用
	LPDIRECT3DTEXTURE9 g_pTextureMeshField2;//メッシュフィールドのテクスチャ
	LPD3DXMESH pMeshMeshField2;//メッシュ情報へのポインタ
	LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField2;//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 pIdxBuffMeshField2;//インデックスバッファへのポインタ
	DWORD nNumMatMeshField2;//マテリアル情報の数
}MESHFIELD2;

/*プロトタイプ宣言*/
void InitMeshField2(void);
void UninitMeshField2(void);
void UpdateMeshField2(void);
void DrawMeshField2(void);

void SetMeshField2(D3DXVECTOR3 pos);

#endif