#pragma once
#ifndef _MAX_TITLE
#define _MAX_TITLE
#define MAX_TITLE (100)
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	bool bUse;//�g�p���Ă��邩�ǂ���
}TITLE;

void InintTitle(void);
void UpdateTitle(void);
void UninitTitle(void);
void DrawTitle(void);
void SetTitle(D3DXVECTOR3 pos);
#endif