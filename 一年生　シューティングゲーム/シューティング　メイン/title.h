#pragma once
#ifndef _MAX_TITLE
#define _MAX_TITLE
#define MAX_TITLE (100)
typedef struct
{
	D3DXVECTOR3 pos;//ˆÊ’u
	D3DXVECTOR3 move;//ˆÚ“®—Ê
	bool bUse;//Žg—p‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©
}TITLE;

void InintTitle(void);
void UpdateTitle(void);
void UninitTitle(void);
void DrawTitle(void);
void SetTitle(D3DXVECTOR3 pos);
#endif