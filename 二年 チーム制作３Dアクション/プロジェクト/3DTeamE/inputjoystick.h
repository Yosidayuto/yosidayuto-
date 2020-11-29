//=============================================================================
//
// �W���C�X�e�B�b�N���� [joystick.h]
// Author : ��K������
//
//=============================================================================
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_
#define INITGUID
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define JS_X 0
#define JS_Y 1
#define JS_A 2
#define JS_B 3
#define	NUM_JS_MAX (32)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CInputJoystick : public CInput
{
public:
	CInputJoystick();
	~CInputJoystick();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetJoystickPress(int nKey);
	bool GetJoystickTrigger(int nKey);
	bool GetJoystickRelease(int nKey);
	BOOL CreateEffect(HWND);
	static BOOL CALLBACK EnumFFDevicesCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext);
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
	static LPDIRECTINPUTDEVICE8 GetDevice(void) { return m_pJDevice; }
	static LPDIRECTINPUTEFFECT GetEffect(void) { return m_IpDIEffect; }
private:
	static LPDIRECTINPUTDEVICE8 m_pJDevice;
	DIDEVCAPS	m_diDevCaps;				//Caps
	static LPDIRECTINPUTEFFECT m_IpDIEffect;//�G�t�F�N�g
	DWORD m_dwNumForceFeedbackAxis;			//�t�H�[�X�t�B�[�h�o�b�N
	DWORD m_rgdwAxes[2] = { DIJOFS_X , DIJOFS_Y };
	LONG  m_rglDirection[2] = { 1 , 1 };
	DICONSTANTFORCE cf;
	DIEFFECT        eff;

	BYTE m_aJoyState[NUM_JS_MAX];			// �W���C�X�e�B�b�N�̓��͏�񃏁[�N
	BYTE m_aJoyStateTrigger[NUM_JS_MAX];	//�W���C�X�e�B�b�N�g���K�[���
	BYTE m_aJoyStateRelease[NUM_JS_MAX];	// �W���C�X�e�B�b�N�����[�X���
};
#endif