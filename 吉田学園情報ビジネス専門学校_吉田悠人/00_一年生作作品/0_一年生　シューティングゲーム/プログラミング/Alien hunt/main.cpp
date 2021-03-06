#pragma comment(lib,"Winmm.lib")
#include "main.h"
#include "bg.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "title.h"
#include "result.h"
#include "game.h"
#include "spawn.h"
#include "score.h"
#include"fade.h"
#include"life.h"
//マクロ定義
#define CLASS_NAME "window class"//ウインドウクラスの名前
#define WINDOW_NAME "Alien hunt"//ウインドウの名前(キャプション名)

//プロトタイプ宣言

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);




//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3D9			g_pD3D = NULL;				//Direct3Dオブジェクトのポインタ
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;		//Direct3Dデバイスのポインタ（描画）
MODE g_mode = MODE_TITLE;						//モード

												/*=============================================================================*/
												/* メイン関数																	*/
												/*=============================================================================*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	HWND hWnd;
	MSG msg;
	RECT rect =
	{
		WINDOW_POS_X,
		WINDOW_POS_Y,
		(WINDOW_POS_X + SCREEN_WIDTH),
		(WINDOW_POS_Y + SCREEN_HEIGHT)
	};
	DWORD dwCurrentTime;//現在時刻
	DWORD dwExecLastTime;//最後に処理した時刻

	RegisterClassEx(&wcex);


	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);


	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		WINDOW_POS_X,
		WINDOW_POS_Y,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);




	//初期化処理（ウィンドウを作成してから行う）
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//*//
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();//現在の時刻会得
								   //*//
								   //メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージが来たらループを抜ける
				break;
			}
			else
			{
				//メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//Directxの処理
			dwCurrentTime = timeGetTime();//システム時刻を取得
			if ((dwCurrentTime = dwExecLastTime) >= (1000 / 60))//1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;//処理した時刻を保存
											   //更新処理
				Update();
				//描画処理
				Draw();
			}
		}
	}


	//終了処理
	Uninit();

	//ウインドクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:

			DestroyWindow(hWnd);

		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
// hInstance : インスタンスのハンドル
// hWnd      : ウインドウのハンドル
// bWindow   : ウインドウモードにするかどうか
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;//プレゼンテーションパラメータ
								//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}



	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{

		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{

			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{

				return E_FAIL;
			}
		}
	}

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);    //透明度を使うか
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);    //αデスティ
																			// サンプラーステートの設定

	luitkeyboard(hInstance, hWnd);					//キーボードの初期化処理

	
		InintTitle();								//タイトル画面の初期化処理

		InintGame();								//ゲーム画面の初期化処理
		SetTitle(D3DXVECTOR3(640, -200, 0.0f));
		InintScore();
		SetWpawn(D3DXVECTOR3(100, 100, 0.0f));
		SetScore(D3DXVECTOR3(10, 30, 0.0f));
		InintResult();								//リザルト画面の初期化処理
		SetLife(D3DXVECTOR3(1000, 30, 0.0f));
		InitFade(g_mode);								//フェードの初期化処理
		SetFade(g_mode);
		return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	if (g_pD3DDevice != NULL)
	{//Direct3Dデバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{//Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	Updatekeyboard();

	//各種オブジェクトの更新処理
	switch (g_mode)
	{
	case MODE_TITLE:						//タイトル画面の更新処理
		UpdateTitle();
		break;
	case MODE_GAME:							//ゲーム画面の更新処理
		UpdateGame();
		UpdateScore();
		break;
	case MODE_RESULE:						//リザルト画面の更新処理
		UpdateResult();
		UpdateScore();

		break;
	}
	UpdaFade();
	
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	//バックバッファ＆バッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		
		switch (g_mode)
		{
		case MODE_TITLE:			//タイトル画面の描画処理
			DrawTitle();
			break;
		case MODE_GAME:				//ゲーム画面の描画処理
			DrawGame();
			DrawScore();

			break;
		case MODE_RESULE:			//リザルト画面の描画処理
			DrawResult();
			DrawScore();
			break;
		}
		/*フェードの描画処理*/
		DrawFade();
		/*描画の終了処理*/
		g_pD3DDevice->EndScene();
	}

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
void SetMode(MODE mode)
{

	g_mode = mode;
	switch (g_mode)
	{
	case  MODE_TITLE:
		
		break;
	case MODE_GAME:
	
		break;
	case MODE_RESULE:
	
		break;
	}
	

}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
MODE GetMode(void)
{
	return g_mode;
}