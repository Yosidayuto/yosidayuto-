#ifndef  MAGIC_H_
#define  MAGIC_H_
/*-----------------*/
#include"main.h"
/*-----------------*/
#define MAX_MAGIC 30
#define MAX_SIZE1 12
/*-----------------*/
/*構造体*/

typedef enum
{
	MAGIC_PARTS0 = 0,
	MAGIC_PARTS1,
	MAGIC_PARTS2,
	MAGIC_PARTS3,
	MAGIC_PARTS_MAX,
} MAGIC_PARTS;

typedef struct
{
	LPD3DXMESH pMesh;		//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアル情報へのポインタ
	DWORD nNumMat;			//マテリアル情報の数
	D3DXMATRIX mtxWorld;	//行列計算用
	LPDIRECT3DTEXTURE9 pTextureModel[100];//ポリゴンのテクスチャ

}MODEL_MAGIC;
typedef struct
{
	int nType;				//魔法の種類
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 movePos;	//移動量
	D3DXVECTOR3 size;		//大きさ
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 dir;		//方向
	float fAngle;			
	float fRot;				//進む角度
	D3DXMATRIX mtxWorld;	//行列計算用
	bool bUse = false;		//使っているか
	MODEL_MAGIC enemyParts[MAGIC_PARTS_MAX];	//魔法の種類Xファイル
}MAGIC;
/*プロトタイプ宣言*/
void InitMagic(void);
void UninitMagic(void);
void UpdateMagic(void);
void DrawMagic(void);
void SetMagic(int Type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 dir);
MAGIC*GetMagic();
#endif