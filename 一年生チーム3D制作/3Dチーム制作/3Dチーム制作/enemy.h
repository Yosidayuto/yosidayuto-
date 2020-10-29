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
	ENEMYSTATE_TRACKING,//追尾
	ENEMYSTATE_DAMAGE,//ダメージ
	ENEMYSTATE_MAX,
}ENEMYSTATE;
/*エネミーパーツ*/
typedef enum
{
	ENEMY_PARTS0 = 0,
	ENEMY_PARTS1,
	ENEMY_PARTS2,
	ENEMY_PARTS3,
	ENEMY_PARTS4,
	ENEMY_PARTS5,
	ENEMY_PARTS6,
	ENEMY_PARTS7,
	ENEMY_PARTS8,
	ENEMY_PARTS9,
	ENEMY_PARTS10,
	ENEMY_PARTS_MAX,
} ENEMY_PARTS;
/*エネミーのパーツ情報*/
typedef struct
{
	LPD3DXMESH			pMesh;				//メッシュ情報へのポインタ
	LPD3DXBUFFER		pBuffMat;			//マテリアル情報へのポインタ
	DWORD				nNumMat;			//マテリアル情報の数
	LPDIRECT3DTEXTURE9	pTextureModel[50];	//ポリゴンのテクスチャ
	D3DXVECTOR3			pos;				//位置情報
	D3DXVECTOR3			rot;				//回転情報
	D3DXVECTOR3			rotAnime;			//アニメの角度
	D3DXVECTOR3			posAnime;			//アニメの移動量
	D3DXVECTOR3			moverotAnime;		//アニメの角度
	D3DXVECTOR3			moveposAnime;		//アニメの移動量

	D3DXMATRIX			mtxWorld;			//行列計算
	D3DXMATRIX			mtxWorldAnime;		//行列計算

}MODEL_ENEMY;
/*エネミーの視野判定*/
typedef struct
{

	D3DXVECTOR3		SearchRot;
	float			fdistance;
	float			fRot;
	bool			bSearch;
}ENEMY_SEARCH;
/*エネミーのマップ当たり判定*/
typedef struct
{
	D3DXVECTOR3 directionMap;					//判定する方向
	BOOL		WallHit;						//判定の結果
	float		WallDistance;					//判定したものとの距離
}ENEMY_MAP;
/*エネミーの情報*/
typedef struct
{
	int				nLife;							//体力
	int				nType;							//エネミーの種類
	int				nCounterState;					//ダメージ状態の処理カウント
	ENEMYSTATE		state;							//エネミーの状態
	D3DXVECTOR3		pos;							//位置
	D3DXVECTOR3		posOld;							//ブロックの当たり判定
	D3DXVECTOR3		movePos;						//移動量
	D3DXVECTOR3		size;							//大きさ
	D3DXVECTOR3		rot;							//回転
	D3DXVECTOR3		rotDest;						//目標の角度
	D3DXCOLOR		col;							//カラー
	D3DXVECTOR3		startPos;						//巡回スタート位置
	D3DXVECTOR3		endPos;							//巡回終了位置
	float			fAngle;							//目標への位置
	float			fRot;							//進む角度
	float			fcol_t;							//目線の衝突感覚
	int				x;
	double			vx = 0.0f, vy;					//加速度
	D3DXMATRIX		mtxWorld;						//行列計算用
	bool			buse = false;					//使っているか
	int				nPos;							//巡回スイッチ
	MODEL_ENEMY		enemyParts[ENEMY_PARTS_MAX];	//エネミーの種類
	ENEMY_SEARCH	enemySearch;					//エネミーの視野
}ENEMY;
/*プロトタイプ宣言*/
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(int Type, D3DXVECTOR3 pos, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos);
void HitEnemy(int nDamage, int nCntEnemy);
ENEMY*GetEnemy();
void SearchEnemy();
#endif