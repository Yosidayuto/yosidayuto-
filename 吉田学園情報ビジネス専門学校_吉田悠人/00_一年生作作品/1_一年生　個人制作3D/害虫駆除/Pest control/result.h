#ifndef  RESULT_H_
#define  RESULT_H_
#include "main.h"
#define RESULT_COMMAND_SIZE_X 350
#define RESULT_COMMAND_SIZE_Y 80

typedef enum
{
	RESULT_TEXTURE_0 = 0,
	RESULT_TEXTURE_1,
	RESULT_TEXTURE_2,
	RESULT_TEXTURE_MAX,
} RESULT_TEXTURE;

typedef struct
{
	D3DXVECTOR3 pos;//ˆÊ’u
}RESULT;

void InintResult(void);
void UpdateResult(void);
void UninitResult(void);
void DrawResult(void);
#endif