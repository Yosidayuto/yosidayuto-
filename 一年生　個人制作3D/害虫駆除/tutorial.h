#ifndef  TUTORIAL_H_
#define  TUTORIAL_H_
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;//ˆÊ’u	
	bool buse;
}TUTORIAL;


void InintTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
#endif