
#pragma once
#ifndef  MESHFIELD2_H_
#define  MESHFIELD2_H_

#include"main.h"

#define MESHFIE2L_X_BLOCK 8				//X方向のブロック数
#define MESHFIEL2_Y_BLOCK 1				//Z方向のブロック数
#define MESHFIEL2_VERTEX_NUM ((MESHFIE2L_X_BLOCK+1)*(MESHFIEL2_Y_BLOCK+1))									//頂点
#define MESHFIEL2_INDEX_NUM (((((MESHFIE2L_X_BLOCK-1)*2)+4)*MESHFIEL2_Y_BLOCK)+(2*(MESHFIEL2_Y_BLOCK-1)))	//インデックス
#define MESHFIEL2_PRIMITIVE_NUM (MESHFIE2L_X_BLOCK*MESHFIEL2_Y_BLOCK*2)+((MESHFIEL2_Y_BLOCK-1)*4)			//ポリゴン

/*プロトタイプ宣言*/
void InitMeshField2(void);
void UninitMeshField2(void);
void UpdateMeshField2(void);
void DrawMeshField2(void);

#endif