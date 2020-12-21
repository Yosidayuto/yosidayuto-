#include"input.h"
//マクロ定義
#define NUM_KEY_MAX (256)						//キーの最大数

LPDIRECTINPUT8 CInput::m_pInput = NULL;
CInput::CInput()
{
	m_pDevice = NULL;
}

CInput::~CInput()
{
}

//キーボードの初期化
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		/*Directlnpu+オブジェクトの作成*/
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}
	return S_OK;
}

void CInput::Uninit(void)
{

	/*入力デバイス（キーボード）の開放*/
	if (m_pDevice != NULL)
	{
		/*キーボードへのアクセス権を開放（入力制御終了）*/
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	/*DireCtInputオブジェクトの開放*/
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

}

