//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	inputmouse.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E


#include "inputmouse.h"

CInputMouse::CInputMouse()
{
	//���W�̏�����
#ifdef  MOUSE_POS_TYPE
	m_aMousePos.lX = (LONG)0.0f;
	m_aMousePos.lY = (LONG)0.0f;

#else 
	posMouse.x = 0.0f;
	posMouse.y = 0.0f;
#endif
	memset(m_aClickState.rgbButtons, 0, sizeof(m_aClickState.rgbButtons));
	memset(m_aClickTrigger.rgbButtons, 0, sizeof(m_aClickTrigger.rgbButtons));
	memset(m_aClickRelease.rgbButtons, 0, sizeof(m_aClickRelease.rgbButtons));


}

CInputMouse::~CInputMouse()
{
}

HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//���W�̏�����
#ifdef  MOUSE_POS_TYPE
	m_aMousePos.lX = (LONG)0.0f;
	m_aMousePos.lY = (LONG)0.0f;
#else 
	hPointerpos = hWnd;
	posMouse.x = 0.0f;
	posMouse.y = 0.0f;
#endif

	//���̓f�o�C�X�i�}�E�X�j�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDeviceInput, NULL)))
	{
		return E_FAIL;
	}
	/*�f�[�^�t�H�[�}�b�g��ݒ�*/
	if (FAILED(m_pDeviceInput->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	/*�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h*/
	if (FAILED(m_pDeviceInput->SetCooperativeLevel(hWnd, (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))))
	{
		return E_FAIL;
	}
	// �����[�h��ݒ�i���Βl���[�h�ɐݒ�j
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;
	//diprop.dwData       = DIPROPAXISMODE_ABS; // ��Βl���[�h�̏ꍇ

	if (FAILED(m_pDeviceInput->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}
	/*�}�E�X�ւ̃A�N�Z�X������i���͐���J�n�j*/
	m_pDeviceInput->Acquire();




	return S_OK;
}

void CInputMouse::Uninit(void)
{
	CInput::Uninit();
}


void CInputMouse::Update(void)
{


#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE ClickState;
	if (SUCCEEDED(m_pDeviceInput->GetDeviceState(sizeof(DIMOUSESTATE), &ClickState)))
	{
		for (int nCntClick = 0; nCntClick < NUM_CLICK_MAX; nCntClick++)
		{
			//�N���b�N����
			m_aClickState.rgbButtons[nCntClick] = ClickState.rgbButtons[nCntClick];
			//�N���b�N�g���K�[����
			m_aClickTrigger.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&ClickState.rgbButtons[nCntClick];
			//�N���b�N�����[�X����
			m_aClickRelease.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&~ClickState.rgbButtons[nCntClick];
		}
		//�}�E�X�̈ړ��ʎ擾�iIX��IY�̈ړ��ʁj
		m_aMousePos = ClickState;
	}

	else
	{
		m_pDeviceInput->Acquire();
	}
#else 
	DIMOUSESTATE ClickState;

	if (SUCCEEDED(m_pDeviceInput->GetDeviceState(sizeof(DIMOUSESTATE), &ClickState)))
	{
		for (int nCntClick = 0; nCntClick < NUM_CLICK_MAX; nCntClick++)
		{
			//�N���b�N�g���K�[����
			m_aClickTrigger.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&ClickState.rgbButtons[nCntClick];
			//�N���b�N�����[�X����
			m_aClickRelease.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&~ClickState.rgbButtons[nCntClick];
			//�N���b�N����
			m_aClickState.rgbButtons[nCntClick] = ClickState.rgbButtons[nCntClick];

		}
	}

	else
	{
		m_pDeviceInput->Acquire();
	}
	////�X�N���[�����W�擾
	GetCursorPos(&posMouse);
	ScreenToClient(hPointerpos, &posMouse);

#endif

}

#ifdef  MOUSE_POS_TYPE
DIMOUSESTATE CInputMouse::GetMousePos(void)
{
	return m_aMousePos;
}
#else 
POINT CInputMouse::GetMousePos(void)
{
	return posMouse;
}
#endif

bool CInputMouse::GetClick(int nClick)
{
	return (m_aClickState.rgbButtons[nClick] & 0x80) ? true : false;
}

bool CInputMouse::GetClickTrigger(int nClick)
{
	return (m_aClickTrigger.rgbButtons[nClick] & 0x80) ? true : false;
}

bool CInputMouse::GetClickRelease(int nClick)
{
	return (m_aClickRelease.rgbButtons[nClick] & 0x80) ? true : false;
}
