
#pragma once
#ifndef  MESHFIELD2_H_
#define  MESHFIELD2_H_

#include"main.h"

#define MESHFIE2L_X_BLOCK 8				//X�����̃u���b�N��
#define MESHFIEL2_Y_BLOCK 1				//Z�����̃u���b�N��
#define MESHFIEL2_VERTEX_NUM ((MESHFIE2L_X_BLOCK+1)*(MESHFIEL2_Y_BLOCK+1))									//���_
#define MESHFIEL2_INDEX_NUM (((((MESHFIE2L_X_BLOCK-1)*2)+4)*MESHFIEL2_Y_BLOCK)+(2*(MESHFIEL2_Y_BLOCK-1)))	//�C���f�b�N�X
#define MESHFIEL2_PRIMITIVE_NUM (MESHFIE2L_X_BLOCK*MESHFIEL2_Y_BLOCK*2)+((MESHFIEL2_Y_BLOCK-1)*4)			//�|���S��

/*�v���g�^�C�v�錾*/
void InitMeshField2(void);
void UninitMeshField2(void);
void UpdateMeshField2(void);
void DrawMeshField2(void);

#endif