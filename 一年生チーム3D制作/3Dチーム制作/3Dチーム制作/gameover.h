#ifndef  GAMEOVER_H_
#define  GAMEOVER_H_
#include "main.h"
#define GAMEOVER_COMMAND_SIZE_X 350
#define GAMEOVER_COMMAND_SIZE_Y 80

typedef enum
{
	GAMEOVER_TEXTURE_0 = 0,
	GAMEOVER_TEXTURE_1,
	GAMEOVER_TEXTURE_2,
	GAMEOVER_TEXTURE_MAX,
} GAMEOVER_TEXTURE;
typedef struct
{
	D3DXVECTOR3 pos;//ˆÊ’u
}GAMEOVER;

void InintGameover(void);
void UpdateGameover(void);
void UninitGameover(void);
void DrawGameover(void);
#endif
