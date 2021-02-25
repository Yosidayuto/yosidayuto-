/*----------------------------------------------------------------------*/
/*ヘッダーファイル*/
#include "light.h"
#include "camera.h"
#include "polygon.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "meshfield.h"
#include "meshfield2.h"
#include "block.h"
#include "enemy.h"
#include "life.h"
#include "Game.h"
#include "item.h"
#include "background.h"
#include "life.h"
#include "magic.h"
#include "magic_ui.h"
#include "map.h"
#include "boss.h"
/*----------------------------------------------------------------------*/

void InitGame(void)
{
	InitMap();
	InitCamera();
	InitBillboard();
	InitLight();
	InitShadow();
	InitModel();
	InitWall();
	InitEnemy();
	InitBlock();
	InintLife();
	InitItem();
	InitBackground();
	InitMagic();
	InintMafic_Ui();
	InitBoos();
	SetBackground(D3DXVECTOR3(0, 0, 0));
	SetBlock(D3DXVECTOR3(0, 15, 700), D3DXVECTOR3(1400, 50, 50), D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f));
	SetBlock(D3DXVECTOR3(0, 15, -700), D3DXVECTOR3(1400, 50, 50), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBlock(D3DXVECTOR3(700, 15, 0), D3DXVECTOR3(50, 50, 1700), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	SetBlock(D3DXVECTOR3(-700, 15, 0), D3DXVECTOR3(50, 50, 1700), D3DXVECTOR3(0.0f, D3DXToRadian(-90.0f), 0.0f));	
}
void UninitGame(void)
{

}
void UpdateGame(void)
{
	UpdatePolygon();
	UpdateLight();
	UpdateCamera();
	UpdateModel();
	UpdateBillboard();
	/*	UpdateMeshField();*/
	UpdateMeshField2();
	UpdateBlock();
	UpdateEnemy();
	UpdateLife();
	UpdateItem();
	UpdateBackground();
	UpdateMagic();
	UpdateMap();
	UpdateMafic_Ui();
	UpdateBoos();
}
void DrawGame(void)
{
	DrawBlock();
	SetCamera();
	DrawBillboard();
	DrawPolygon();
	DrawShadow();
	DrawWall();
	DrawModel();
	
	DrawEnemy();
	DrawMap();
	DrawLife();
	DrawItem();
	DrawBackground();
	DrawMagic();
	DrawMafic_Ui();
	DrawBoos();
	/*DrawMeshField();*/
	/*DrawMeshField2();*/
}