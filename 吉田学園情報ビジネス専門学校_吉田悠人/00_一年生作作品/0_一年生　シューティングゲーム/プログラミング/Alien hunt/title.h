#pragma once
#ifndef _MAX_TITLE
#define _MAX_TITLE
#define MAX_TITLE (100)
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	bool bUse;//使用しているかどうか
}TITLE;

void InintTitle(void);
void UpdateTitle(void);
void UninitTitle(void);
void DrawTitle(void);
void SetTitle(D3DXVECTOR3 pos);
#endif