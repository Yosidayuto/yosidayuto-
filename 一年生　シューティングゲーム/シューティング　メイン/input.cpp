#include"input.h"
#include"main.h"
//�}�N����`
#define NUM_KEY_MAX (256)						//�L�[�̍ő吔

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;					//Directlnput�I�u�W�F�N�g�̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevkeyboord = NULL;		//���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
BYTE g_akeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̓��͏�񃏁[�N
BYTE g_aKesStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h�̃����[�X���
												/*�L�[�{�[�h�̏�����*/
HRESULT luitkeyboard(HINSTANCE hInstance, HWND hWnd)
{
	/*Directlnpu+�I�u�W�F�N�g�̍쐬*/
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	/*���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬*/
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevkeyboord, NULL)))
	{
		return E_FAIL;
	}
	/*�f�[�^�t�H�[�}�b�g��ݒ�*/
	if (FAILED(g_pDevkeyboord->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	/*�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h*/
	if (FAILED(g_pDevkeyboord->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	/*�L�[�{�[�h�ւ̃A�N�Z�X������i���͐���J�n�j*/
	g_pDevkeyboord->Acquire();
	return S_OK;
}
/*--------------------------------*/
/*		�L�[�{�[�h�̏I������	*/
/*--------------------------------*/
void Uninitkeyboard(void)
{
	/*���̓f�o�C�X�i�L�[�{�[�h�j�̊J��*/
	if (g_pDevkeyboord != NULL)
	{
		/*�L�[�{�[�h�ւ̃A�N�Z�X�����J���i���͐���I���j*/
		g_pDevkeyboord->Unacquire();
		g_pDevkeyboord->Release();
		g_pDevkeyboord = NULL;
	}
	/*DireCtInput�I�u�W�F�N�g�̊J��*/
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
/*------------------------*/
/*		�X�V����		 */
/*-----------------------*/
void Updatekeyboard(void)
{
	BYTE akeyState[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏��
	int nCntkey;

	/*�f�o�C�X����f�[�^���擾*/
	if (SUCCEEDED(g_pDevkeyboord->GetDeviceState(sizeof(akeyState), akeyState)))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			g_aKesStateTrigger[nCntkey] = (g_akeyState[nCntkey] ^ akeyState[nCntkey])&akeyState[nCntkey];
			g_aKeyStateRelease[nCntkey] = (g_akeyState[nCntkey] ^ akeyState[nCntkey])&~akeyState[nCntkey];
			g_akeyState[nCntkey] = akeyState[nCntkey];//�L�[�v���X���ۑ�
		}
	}
	/*�L�[�{�[�h�̍X�V����*/
	else
	{
		g_pDevkeyboord->Acquire();
	}
}
/*�L�[�{�[�h�̃v���X��Ԃ��K��*/
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
