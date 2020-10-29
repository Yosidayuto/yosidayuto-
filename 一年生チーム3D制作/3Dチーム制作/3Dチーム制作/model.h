#ifndef  MODEL_H
#define  MODEL_H

#include"item.h"
#include"main.h"
#include"map.h"
#define MOTION_ANIMATION_NUM 5	//アニメーション数
#define MOTION_KEYSET_MAX 5		//キーセット最大数
//****************************************************************************
/*構造体*/
//****************************************************************************
/*プレイヤーのパーツ*/
typedef enum
{
	MODEL_LABEL_Parts0 = 0,
	MODEL_LABEL_Parts1,
	MODEL_LABEL_Parts2,
	MODEL_LABEL_Parts3,
	MODEL_LABEL_Parts4,
	MODEL_LABEL_Parts5,
	MODEL_LABEL_Parts6,
	MODEL_LABEL_Parts7,
	MODEL_LABEL_Parts8,
	MODEL_LABEL_Parts9,
	MODEL_LABEL_Parts10,
	MODEL_LABEL_MAX,
} MODEL_LABEL;
/*アニメーションキー情報*/
typedef struct
{
	D3DXVECTOR3		pos;						//位置
	D3DXVECTOR3		rot;						//回転
	D3DXMATRIX		mtxWorldAnime;			//行列計算

}AnimationKey;	
/*アニメーションキーセット情報*/
typedef struct
{
	int				frame;						//キーフレーム数
	AnimationKey	key[MODEL_LABEL_MAX];		//キーセットに含むキー情報
}AnimationKeySet;
/*アニメーション情報*/
typedef struct
{
	bool			isLoop;						//モーションループ設定
	int				keyNum;						//キー数
	AnimationKeySet keySet[MOTION_KEYSET_MAX];	//アニメーションに含むキーセット情報
}Animation;

/*プレイヤーの状態*/
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//出現状態
	PLAYERSTATE_NORMAL = 0,	//通常
	PLAYERSTATE_DAMAGE,		//ダメージ
	PLAYERSTATE_DEATH,		//死亡状態
	PLAYERSTATE_MAX
}PLAYER_STATE;
/*プレイヤーのマップ当たり判定*/
typedef struct
{
	D3DXVECTOR3 directionMap;	//判定する方向
	BOOL		WallHit;		//判定の結果
	float		WallDistance;	//判定したものとの距離
}PLAYER_MAP;
/*パーツの情報*/
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

}MODEL;
/*プレイヤーの情報*/
typedef struct
{
	D3DXVECTOR3		pos;							//位置
	D3DXVECTOR3		posOld;							//ブロックの当たり判定
	D3DXVECTOR3		movePos;						//移動量
	D3DXVECTOR3		rot;							//回転
	D3DXVECTOR3		rotDest;						//目標の角度
	D3DXMATRIX		mtxWorld;						//行列計算用
	PLAYER_STATE	state;							//状態
	//double		vx = 0.0, vy;					//加速度
	float			fAngle;
	bool			bItem[MAX_ITEM][TITLE_TYPE_MAX];//プレイヤーの持っているアイテム
	int				nLife[MAX_ITEM][TITLE_TYPE_MAX];//アイテム品質
	int				nDamage;						//ダメージ時間
	int				x,y,z;							//テキスト
	
	bool			bGoal;							//ゴールスイッチ
	MODEL			modelParts[MODEL_LABEL_MAX];	//プレイヤーを構成するパーツ群
	PLAYER_MAP		MapProcess[DIRECTION_PROCESS];	//地面に当たったか
}PLAYER;
//****************************************************************************
/*プロトタイプ宣言*/
//****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(bool bDamage);
PLAYER*GetPlayer();

#endif