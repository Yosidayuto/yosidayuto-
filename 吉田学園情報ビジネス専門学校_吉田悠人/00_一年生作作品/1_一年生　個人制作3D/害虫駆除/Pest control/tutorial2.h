#pragma once
#ifndef  TUTORIAL2_H_
#define  TUTORIAL2_H_
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;//ˆÊ’u	
	bool buse;
}TUTORIAL2;


void InintTutorial2(void);
void UninitTutorial2(void);
void UpdateTutorial2(void);
void DrawTutorial2(void);
#endif