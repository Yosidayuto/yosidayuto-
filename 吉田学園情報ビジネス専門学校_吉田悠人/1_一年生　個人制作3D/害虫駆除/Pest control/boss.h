#ifndef  BOOS_H_
#define  BOOS_H_

#include"main.h"

#define MOTION_ANIMATION_NUM 5	//アニメーション数
#define MOTION_KEYSET_MAX 5		//キーセット最大数
/*構造体*/
/*パーツの階層構造*/
typedef enum
{
	BOOS_PARTS_Parts0 = 0,
	BOOS_PARTS_Parts1,
	BOOS_PARTS_Parts2,
	BOOS_PARTS_Parts3,
	BOOS_PARTS_Parts4,
	BOOS_PARTS_MAX,
} BOOS_PARTS_FILE;
/*アニメーションキー情報*/
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//回転
}AnimationKey;
/*アニメーションキーセット情報*/
typedef struct
{
	int frame;							//キーフレーム数
	AnimationKey key[BOOS_PARTS_MAX];	//キーセットに含むキー情報
}AnimationKeySet;
/*アニメーション情報*/
typedef struct
{
	bool isLoop;	//モーションループ設定
	int keyNum;		//キー数
	AnimationKeySet keySet [MOTION_KEYSET_MAX];//アニメーションに含むキーセット情報
}Animation;
/*ボスの状態*/
typedef enum
{
	BOOS_STATE_NORMAL=0,		//通常
	BOOS_STATE_DAMAGE,		//ダメージ
	BOOS_STATE_DEATH,		//死亡状態
	BOOS_STATE_MAX
}BOOS_STATE;
/*行動パターン*/
typedef enum
{
	BOOS_PATTERN_0 = 0,	
	BOOS_PATTERN_1,		
	BOOS_PATTERN_2,		
	BOOS_PATTERN_3,
	BOOS_PATTERN_MAX
}BOOS_PATTERN;
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
	D3DXVECTOR3 rotAnime;	//アニメの角度
	D3DXVECTOR3 posAnime;	//アニメの移動量
	int nldxModelParent;	//親子モデルのインデックス
}BOOS_PARTS;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 movePos;	//移動量
	D3DXVECTOR3 rot;		//回転
	D3DXVECTOR3 rotDest;	//目標の角度
	D3DXMATRIX mtxWorld;	//行列計算用
	BOOS_STATE state;		//状態
	BOOS_PATTERN pattern;	//行動
	int nLife;				//ボス体力
	int nDamage;			//ダメージ時間
	float fRot;				//進む角度

	BOOS_PARTS modelParts[BOOS_PARTS_MAX];	//プレイヤーを構成するパーツ群
}BOOS;
/*プロトタイプ宣言*/
void InitBoos(void);
void UninitBoos(void);
void UpdateBoos(void);
void DrawBoos(void);
void HitBoos(int nDamage,int nMagicType);
BOOS*GetBoos();

#endif