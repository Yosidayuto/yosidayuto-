#ifndef  TITLE_H_
#define  TITLE_H_
#include "main.h"
#define  TITLE_COMMAND_SIZE_X 350
#define  TITLE_COMMAND_SIZE_Y 80
#define  TITLE_LOGO_SIZE_X 700
#define  TITLE_LOGO_SIZE_Y 400
typedef enum
{
	TITLE_TEXTURE_0 = 0,
	TITLE_TEXTURE_1,
	TITLE_TEXTURE_2,
	TITLE_TEXTURE_3,
	TITLE_TEXTURE_MAX,
}  TITLE_TEXTURE;
typedef struct
{
	D3DXVECTOR3 pos;//ˆÊ’u	
}TITLE;

void InintTitle(void);
void UpdateTitle(void);
void UninitTitle(void);
void DrawTitle(void);
#endif