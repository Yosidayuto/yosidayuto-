#ifndef  CAMERA_H
#define  CAMERA_H

#include"main.h"
typedef struct
{
	D3DXVECTOR3 posV;//カメラの座標
	D3DXVECTOR3 posR;//注視点
	D3DXVECTOR3 vecU;//上方向ベクトル
	D3DXMATRIX mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX mtxView;//ビューマトリックス
	
	D3DXVECTOR3 rotDest;//カメラの目的向き
	D3DXVECTOR3 rot;//向き取得
	float fDistance;//視点-注視点の距離
	float fmove;		//カメラの移動量

	D3DXVECTOR3 posVDest;//カメラの座標（目標値）
	D3DXVECTOR3 posRDest;//注視点（目標値）
}CAMERA;
/*プロトタイプ宣言*/
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
CAMERA *GetCamera(void);
#endif