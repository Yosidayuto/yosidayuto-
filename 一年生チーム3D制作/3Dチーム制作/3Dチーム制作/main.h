#pragma once
//インクルードファイル
#ifndef  _POLYGON_H_
#define  _POLYGON_H_

#include<Windows.h>
#define DIRECTINPUT_VERSION (0x0800) 
#include<dinput.h>
#include"XAudio2.h"		//サウンド処理
#include"d3dx9.h"
//ライブラリのリンク
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"dinput8.lib")//入力処理に必要

//マクロ定義
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)


#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)//座標・法線・カラー・テクスチャ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE|D3DFVF_TEX1)

#define NUM_VERTEX (4)//頂点数
#define NUM_POLYGON (2)//ポリゴン数




//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);

/*モードの種類*/
typedef enum
{
	MODE_TITLE = 0,		//タイトル画面
	MODE_TUTORIAL,		//チュートリアル画面
	MODE_GAME,			//ゲーム画面
	MODE_GAMEOVER,		//ゲームオーバー画面
	MODE_RESULE,		//リザルト画面
	MODE_MAX,
}MODE;
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	D3DXVECTOR3 nor;//法線ベクトル
	D3DCOLOR	col;//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_3D;
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換要係数（１．０ｆで固定）
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_2D;
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);


#endif


