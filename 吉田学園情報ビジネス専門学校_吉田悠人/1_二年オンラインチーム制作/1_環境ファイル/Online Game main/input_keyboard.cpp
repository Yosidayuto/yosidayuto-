//=============================================================================
//
// キーボード処理 [inputkeyboard.cpp]
// Author : 俵谷 健太郎
//
//=============================================================================
#include "input_keyboard.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	//キー情報のクリア
	memset(m_akeyState, 0, sizeof(m_akeyState));
	memset(m_akeyStateTrigger, 0, sizeof(m_akeyStateTrigger));
	memset(m_akeyStateRelease, 0, sizeof(m_akeyStateRelease));
}

//=============================================================================
// デストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//入力デバイス(キーボード)の作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定(フォアグラウンド&非排他モード)
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX]; //キーボードの入力情報
	int nCntKey;

	//デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//キープレス情報を保存
			m_akeyStateTrigger[nCntKey] = (m_akeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			m_akeyState[nCntKey] = aKeyState[nCntKey];

			m_akeyState[nCntKey] = aKeyState[nCntKey];
		}
	}

	else
	{
		//キーボードへのアクセス権を取得
		m_pDevice->Acquire();
	}
}

//=============================================================================
// プレス状態を取得
//=============================================================================
bool CInputKeyboard::GetKeyPress(int nKey)
{
	return(m_akeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// トリガー状態を取得
//=============================================================================
bool CInputKeyboard::GetKeyTrigger(int nKey)
{
	return(m_akeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// リリース状態を取得
//=============================================================================
bool CInputKeyboard::GetKeyRelease(int nKey)
{
	return(m_akeyStateRelease[nKey] & 0x80) ? true : false;
}
