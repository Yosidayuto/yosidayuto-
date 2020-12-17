#include"input.h"
#include"main.h"
//マクロ定義
#define NUM_KEY_MAX (256)						//キーの最大数

//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL;					//Directlnputオブジェクトのポインタ
LPDIRECTINPUTDEVICE8 g_pDevkeyboord = NULL;		//入力デバイス（キーボード）へのポインタ
BYTE g_akeyState[NUM_KEY_MAX];					//キーボードの入力情報ワーク
BYTE g_aKesStateTrigger[NUM_KEY_MAX];			//キーボードのトリガー情報
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//キーボードのリリース情報
												/*キーボードの初期化*/
HRESULT luitkeyboard(HINSTANCE hInstance, HWND hWnd)
{
	/*Directlnpu+オブジェクトの作成*/
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	/*入力デバイス（キーボード）の作成*/
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevkeyboord, NULL)))
	{
		return E_FAIL;
	}
	/*データフォーマットを設定*/
	if (FAILED(g_pDevkeyboord->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	/*協調モードを設定（フォアグラウンド＆非排他モード*/
	if (FAILED(g_pDevkeyboord->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	/*キーボードへのアクセス権を会得（入力制御開始）*/
	g_pDevkeyboord->Acquire();
	return S_OK;
}
/*--------------------------------*/
/*		キーボードの終了処理	*/
/*--------------------------------*/
void Uninitkeyboard(void)
{
	/*入力デバイス（キーボード）の開放*/
	if (g_pDevkeyboord != NULL)
	{
		/*キーボードへのアクセス権を開放（入力制御終了）*/
		g_pDevkeyboord->Unacquire();
		g_pDevkeyboord->Release();
		g_pDevkeyboord = NULL;
	}
	/*DireCtInputオブジェクトの開放*/
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
/*------------------------*/
/*		更新処理		 */
/*-----------------------*/
void Updatekeyboard(void)
{
	BYTE akeyState[NUM_KEY_MAX];			//キーボードの入力情報
	int nCntkey;

	/*デバイスからデータを取得*/
	if (SUCCEEDED(g_pDevkeyboord->GetDeviceState(sizeof(akeyState), akeyState)))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			g_aKesStateTrigger[nCntkey] = (g_akeyState[nCntkey] ^ akeyState[nCntkey])&akeyState[nCntkey];
			g_aKeyStateRelease[nCntkey] = (g_akeyState[nCntkey] ^ akeyState[nCntkey])&~akeyState[nCntkey];
			g_akeyState[nCntkey] = akeyState[nCntkey];//キープレス情報保存
		}
	}
	/*キーボードの更新処理*/
	else
	{
		g_pDevkeyboord->Acquire();
	}
}
/*キーボードのプレス状態を習得*/
bool Getkeyboardpress(int nKey)
{
	return (g_akeyState[nKey] & 0x80) ? true : false;
}
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKesStateTrigger[nKey] & 0x80) ? true : false;
}
bool  GetKeyboarRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
