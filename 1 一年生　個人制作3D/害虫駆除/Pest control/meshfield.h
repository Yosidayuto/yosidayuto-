#pragma once
#ifndef  MESHFIELD_H_
#define  MESHFIELD_H_

#include"main.h"

#define MESHFIEL_X_BLOCK 2				//X�����̃u���b�N��
#define MESHFIEL_Z_BLOCK 2				//Z�����̃u���b�N��

#define MESHFIEL_VERTEX_NUM ((MESHFIEL_X_BLOCK+1)*(MESHFIEL_Z_BLOCK+1))									//���_
#define MESHFIEL_INDEX_NUM (((((MESHFIEL_X_BLOCK-1)*2)+4)*MESHFIEL_Z_BLOCK)+(2*(MESHFIEL_Z_BLOCK-1)))	//�C���f�b�N�X
#define MESHFIEL_PRIMITIVE_NUM (MESHFIEL_X_BLOCK*MESHFIEL_Z_BLOCK*2)+((MESHFIEL_Z_BLOCK-1)*4)			//�|���S��


/*�v���g�^�C�v�錾*/
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif