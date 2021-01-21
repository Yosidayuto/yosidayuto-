#ifndef  MODEL_H_
#define  MODEL_H_

#include"main.h"
#define MOTION_ANIMATION_NUMMODEL 5	//アニメーション数
#define MOTION_KEYSET_MAXMODEL 5		//キーセット最大数

/*構造体*/
/*プレイヤーの状態*/
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//出現状態
	PLAYERSTATE_NORMAL = 0,	//通常
	PLAYERSTATE_DAMAGE,		//ダメージ
	PLAYERSTATE_DEATH,		//死亡状態
	PLAYERSTATE_MAX
}PLAYER_STATE;
/*パーツの階層構造*/
typedef enum
{
	MODEL_LABEL_Parts0 = 0,		

	MODEL_LABEL_MAX,
} MODEL_LABEL;
/*アニメーションキー情報*/
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//回転
}AnimationKeyMODEL;
/*アニメーションキーセット情報*/
typedef struct
{
	int frame;							//キーフレーム数
	AnimationKeyMODEL key[MODEL_LABEL_MAX];	//キーセットに含むキー情報
}AnimationKeySetMODEL;
/*アニメーション情報*/
typedef struct
{
	bool isLoop;	//モーションループ設定
	int keyNum;		//キー数
	AnimationKeySetMODEL keySet[MOTION_KEYSET_MAXMODEL];//アニメーションに含むキーセット情報
}AnimationMODEL;

/*パーツごとの情報*/
typedef struct
{
	LPD3DXMESH pMesh;		//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアル情報へのポインタ
	DWORD nNumMat;			//マテリアル情報の数
	LPDIRECT3DTEXTURE9 pTextureModel[250];//ポリゴンのテクスチャ
	D3DXVECTOR3 pos;		//位置情報
	D3DXVECTOR3 rot;		//回転情報
	D3DXMATRIX mtxWorld;	//行列計算
	char pFilename;			// ファイル名
	int nldxModelParent;	//親子モデルのインデックス
	D3DXVECTOR3 rotAnime;	//アニメの角度
	D3DXVECTOR3 posAnime;	//アニメの移動量
}MODEL;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posOld;		//ブロックの当たり判定
	D3DXVECTOR3 movePos;	//移動量
	D3DXVECTOR3 rot;		//回転
	D3DXVECTOR3 rotDest;	//目標の角度
	D3DXMATRIX mtxWorld;	//行列計算用
	PLAYER_STATE state;		//状態
	double vx = 0.0f, vy;	//加速度
	float fDist;			//地面の距離
	int nLife;				//プレイヤー体力
	int nMagic;				//マジックスイッチ
	int nDamage;			//ダメージ時間
	MODEL modelParts[MODEL_LABEL_MAX];	//プレイヤーを構成するパーツ群
	float fAngle;			//ダメージを受けた時ののけ反り
	BOOL Hit;				//地面に当たったか
}PLAYER;	
/*プロトタイプ宣言*/
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void HitModel(int nDamage,int nEnemy,int nHit);
PLAYER*GetPlayer();

#endif