#pragma once
#ifndef  MESHFIELD_H_
#define  MESHFIELD_H_

#include"main.h"

#define MESHFIEL_X_BLOCK 2				//X方向のブロック数
#define MESHFIEL_Z_BLOCK 2				//Z方向のブロック数

#define MESHFIEL_VERTEX_NUM ((MESHFIEL_X_BLOCK+1)*(MESHFIEL_Z_BLOCK+1))									//頂点
#define MESHFIEL_INDEX_NUM (((((MESHFIEL_X_BLOCK-1)*2)+4)*MESHFIEL_Z_BLOCK)+(2*(MESHFIEL_Z_BLOCK-1)))	//インデックス
#define MESHFIEL_PRIMITIVE_NUM (MESHFIEL_X_BLOCK*MESHFIEL_Z_BLOCK*2)+((MESHFIEL_Z_BLOCK-1)*4)			//ポリゴン


/*プロトタイプ宣言*/
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif