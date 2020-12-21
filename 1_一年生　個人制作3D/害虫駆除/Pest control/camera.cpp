#include"main.h"
#include"camera.h"
#include"input.h"
#include"model.h"

/*グローバル変数*/
CAMERA g_camera;//カメラ情報
void InitCamera(void)
{
	/*移動量*/
	g_camera.fmove = 1.0f;
	/*距離*/
	g_camera.fDistance = 90.0f;
	/**/
	g_camera.fmove = 0.0f;
	/*カメラの位置・注視点・上方向を設定*/
	g_camera.posV = D3DXVECTOR3(0.0f, 30.0f, g_camera.fDistance);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
void UninitCamera(void)
{

}
void UpdateCamera(void)
{
	/*コントローラーの処理*/
	JOYINFOEX JOYPAD; //現在のジョイスティックのデータ
	/*ジョイパットの入力*/
	JOYPAD.dwSize = sizeof(JOYINFOEX);
	JOYPAD.dwFlags = JOY_RETURNALL; // 全ての情報を取得
	/*-----------------------------------------------------------------------------------------------------*/
	g_camera.fmove = 0.0f;
	/*カメラの向きから、前後左右にカメラを移動させる*/
	//if (Getkeyboardpress(DIK_NUMPAD8))//前
	//{
	//	/*移動量*/
	//	g_camera.fmove -= 1.0f;
	//	g_camera.posV.x += sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fmove;
	//	g_camera.posV.z += cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fmove;
	//	g_camera.posR.x = g_camera.posV.x - sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//}
	//if (Getkeyboardpress(DIK_NUMPAD2))//後ろ
	//{
	//	/*移動量*/
	//	g_camera.fmove += 1.0f;
	//	g_camera.posV.x += sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fmove;
	//	g_camera.posV.z += cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fmove;
	//	g_camera.posR.x = g_camera.posV.x - sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//}
	//if (Getkeyboardpress(DIK_NUMPAD4))//左
	//{
	//	/*移動量*/
	//	g_camera.posV.x += sinf(D3DXToRadian(g_camera.rot.y + 90))*1;
	//	g_camera.posV.z += cosf(D3DXToRadian(g_camera.rot.y + 90))*1;
	//	g_camera.posR.x = g_camera.posV.x - sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//}
	//if (Getkeyboardpress(DIK_NUMPAD6))//右
	//{
	//	/*移動量*/
	//	g_camera.posV.x += sinf (D3DXToRadian(g_camera.rot.y + 90))*-1;
	//	g_camera.posV.z += cosf (D3DXToRadian(g_camera.rot.y + 90))*-1;
	//	g_camera.posR.x = g_camera.posV.x - sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//}
	/*-----------------------------------------------------------------------------------------------------*/
	///*注視点の旋回*/
	//if (Getkeyboardpress(DIK_NUMPAD7))
	//{
	//	g_camera.rot.y += 0.1f;
	//	g_camera.posR.x = g_camera.posV.x - sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//}																			 
	//if (Getkeyboardpress(DIK_NUMPAD9))
	//{																			 
	//	g_camera.rot.y -= 0.1f;													 
	//	g_camera.posR.x = g_camera.posV.x - sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//}
	//
	///*-----------------------------------------------------------------------------------------------------*/
	///*視点（カメラ座標）の旋回*/
	if (joyGetPosEx(JOYSTICKID1, &JOYPAD) == JOYERR_NOERROR)
	{
		if (JOYPAD.dwButtons & 16)
		{
			g_camera.rot.y -= 1.0f;
			g_camera.posV.x = g_camera.posR.x + sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z + cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;

		}
		if (JOYPAD.dwButtons & 32)
		{
			g_camera.rot.y += 1.0f;
			g_camera.posV.x = g_camera.posR.x + sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z + cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;

		}
	}
	/*視点（カメラ座標）の旋回*/
	if (Getkeyboardpress(DIK_NUMPAD1))
	{
		g_camera.rot.y += 1.0f;
		g_camera.posV.x = g_camera.posR.x + sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z + cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	}
	if (Getkeyboardpress(DIK_NUMPAD3))
	{
		g_camera.rot.y -= 1.0f;
		g_camera.posV.x = g_camera.posR.x + sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z + cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	}
	if (D3DXToRadian(g_camera.rot.y) >= (D3DXToRadian(360))|| D3DXToRadian(g_camera.rot.y) <= (D3DXToRadian(-360)))
	{
		g_camera.rot.y = 0;
	}
	/*-----------------------------------------------------------------------------------------------------*/
	PLAYER*pModel = GetPlayer();
	/*注視点をモデルが向いている方向へ移動する*/
	g_camera.posRDest = D3DXVECTOR3
	(pModel->pos.x - sinf(D3DXToRadian(pModel->rot.y))*1,
		40.0f,
		pModel->pos.z - cosf(D3DXToRadian(pModel->rot.y))*1);
	/*モデルを追う*/
	g_camera.posVDest = D3DXVECTOR3
	(pModel->pos.x + sinf(D3DXToRadian(g_camera.rot.y)) * 100,
		20.0f,
		pModel->pos.z + cosf(D3DXToRadian(g_camera.rot.y)) * 100);
	g_camera.posV += (g_camera.posVDest - g_camera.posV)*1;//複数フレームで反映
	g_camera.posR += (g_camera.posRDest - g_camera.posR) * 1;//複数フレームで反映
/*------------------------------------------------------------------------------*/
	///*カメラの角度をモデルの向きに合わせる*/
	//g_camera.rotDest.y = pModel->rot.y;
	///*複数フレームで向きを変化させる*/
	//g_camera.rot.y += (((D3DXToRadian(g_camera.rotDest.y)))- (D3DXToRadian(g_camera.rot.y)))*5;
}
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ
	/*ビューマトリックスの初期化*/
	D3DXMatrixIdentity(&g_camera.mtxView);
	/*ビューマトリックスの作成*/
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);
	/*ビューマトリックスの設定*/
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
	/*プロジェクションマトリックスの初期化処理*/
	D3DXMatrixIdentity(&g_camera.mtxProjection);
	/*プロジェクションマトリックス*/
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		2.0f,
		10000.0f);
	/*プロジェクションマトリックスの設定*/
	pDevice->SetTransform(D3DTS_PROJECTION,
		&g_camera.mtxProjection);
}
CAMERA *GetCamera()
{
	return &g_camera;
}