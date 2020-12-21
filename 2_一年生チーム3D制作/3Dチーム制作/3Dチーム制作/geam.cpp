#include"geam.h"
#include"billboard.h"
#include"block.h"
#include"camera.h"
#include"light.h"
#include"meshfield.h"
#include"meshfield2.h"
#include"model.h"
#include"polygon.h"
#include"shadow.h"
#include"wall.h"
#include"camera.h"
#include"line.h"
#include"item.h"
#include"enemy.h"
#include"goal.h"
#include"time.h"
#include"meshfield2.h"
#include"map.h"
void InitGeam(void)
{
	InitEnemy();
	InitItem();
	InitCamera();
	InitBillboard();
	InitPolygon();
	InitLight();
	InitShadow();
	InitPlayer();
	InitWall();
	InitLine();
	InitMeshField2();
	InitBlock();
	InitGoal();
	InitTime();
	InitMap();
}
void SetGeam(void)
{

	SetItem(D3DXVECTOR3(50, 0, 0), D3DXVECTOR3(0, 0, 0), 0);
	SetItem(D3DXVECTOR3(-50, 0, 0), D3DXVECTOR3(0, 0, 0), 1);
	SetItem(D3DXVECTOR3(-60, 0, 0), D3DXVECTOR3(0, 0, 0), 1);
	SetItem(D3DXVECTOR3(-70, 0, 0), D3DXVECTOR3(0, 0, 0), 2);
	SetItem(D3DXVECTOR3(-80, 0, 0), D3DXVECTOR3(0, 0, 0), 3);
	SetEnemy(0, D3DXVECTOR3 (0,25,380), D3DXVECTOR3(50, 25, 380), D3DXVECTOR3(-50, 25, 380));
	SetGoal(D3DXVECTOR3(-50, 50, 1230), D3DXVECTOR3(10, 10, 10));
	SetBlock(D3DXVECTOR3(100, 0, -430), D3DXVECTOR3(1000, 100, 100));
	SetBlock(D3DXVECTOR3(-250, 0, 550), D3DXVECTOR3(10, 100, 2000));
	SetBlock(D3DXVECTOR3(520, 0, 550), D3DXVECTOR3(100, 100, 2000));
	SetBlock(D3DXVECTOR3(200, 0, 150), D3DXVECTOR3(700, 100, 170));
	SetBlock(D3DXVECTOR3(-100, 0, 530), D3DXVECTOR3(500, 100, 170));
	SetBlock(D3DXVECTOR3(300, 0, 825), D3DXVECTOR3(575, 100, 10));
	SetBlock(D3DXVECTOR3(-200, 0, 825), D3DXVECTOR3(150, 100, 10));
	SetBlock(D3DXVECTOR3(0, 0, 1280), D3DXVECTOR3(1000, 100, 50));
	SetBlock(D3DXVECTOR3(180, 0, -140), D3DXVECTOR3(320, 100, 10));

}
void UninitGeam(void)
{

}
void UpdateGeam(void)
{
	UpdateGoal();
	UpdateItem();
	UpdateLine();
	UpdatePolygon();
	UpdateLight();
	UpdateCamera();
	UpdatePlayer();
	UpdateBillboard();
	UpdateEnemy();
	/*	UpdateMeshField();*/
	UpdateMeshField2();
	UpdateBlock();
	UpdateTime();
	UpdateMeshField2();
	UpdateMap();
}
void DrawGeam(void)
{
	DrawGoal();
	DrawItem();
	DrawLine();
	SetCamera();
	DrawBillboard();
	//DrawPolygon();
	DrawShadow();
	DrawPlayer();
	DrawBlock();
	DrawEnemy();
	DrawWall();
	DrawMap();
	/*DrawMeshField();*/
	DrawMeshField2();
}