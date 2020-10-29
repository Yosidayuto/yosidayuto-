#ifndef  ENEMY_H_
#define  ENEMY_H_
/*-----------------*/
#include"main.h"
/*-----------------*/
#define MAX_ENEMY 30
#define MAX_SIZE1 12
/*-----------------*/
/*構造体*/
/*状態処理構造体*/
typedef enum
{
	ENEMYSTATE_NORMAL = 0,//通状
	ENEMYSTATE_DAMAGE,//ダメージ
	ENEMYSTATE_MAX,
}ENEMYSTATE;

typedef enum
{
	ENEMY_PARTS0 = 0,
	ENEMY_PARTS1,
	ENEMY_PARTS2,
	ENEMY_PARTS3,
	ENEMY_PARTS_MAX,
} ENEMY_PARTS;

typedef struct
{
	LPD3DXMESH pMesh;		//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアル情報へのポインタ
	DWORD nNumMat;			//マテリアル情報の数
	D3DXMATRIX mtxWorld;	//行列計算用
	LPDIRECT3DTEXTURE9 pTextureModel[100];//ポリゴンのテクスチャ
}MODEL_ENEMY;
typedef struct
{
	int nLife;				//体力
	int nType;				//エネミーの種類
	int nCounterState;		//ダメージ状態の処理カウント
	ENEMYSTATE state;		//エネミーの状態
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posOld;		//ブロックの当たり判定
	D3DXVECTOR3 movePos;	//移動量
	D3DXVECTOR3 size;		//大きさ
	D3DXVECTOR3 rot;		//回転
	D3DXVECTOR3 rotDest;	//目標の角度
	D3DXCOLOR col;			//カラー
	float fAngle;			//プレイヤーへの角度
	float fRot;				//進む角度
	double vx = 0.0f, vy;	//加速度
	D3DXMATRIX mtxWorld;	//行列計算用
	bool use = false;		//使っているか
	MODEL_ENEMY enemyParts[ENEMY_PARTS_MAX];	//エネミーの種類
	float fDist;			//地面までの距離
	BOOL Hit;				//地面に当たったか
}ENEMY;
/*プロトタイプ宣言*/
void InitEnemy(void);
void UninitEnemy(void);	
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(int Type, D3DXVECTOR3 pos);
void HitEnemy(int nDamage,int nCntEnemy);
ENEMY*GetEnemy();
#endif