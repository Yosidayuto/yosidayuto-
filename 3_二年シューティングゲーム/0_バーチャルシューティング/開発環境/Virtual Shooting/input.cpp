#include"input.h"
//�}�N����`
#define NUM_KEY_MAX (256)						//�L�[�̍ő吔

LPDIRECTINPUT8 CInput::m_pInput = NULL;
CInput::CInput()
{
	m_pDevice = NULL;
}

CInput::~CInput()
{
}

//�L�[�{�[�h�̏�����
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		/*Directlnpu+�I�u�W�F�N�g�̍쐬*/
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}
	return S_OK;
}

void CInput::Uninit(void)
{

	/*���̓f�o�C�X�i�L�[�{�[�h�j�̊J��*/
	if (m_pDevice != NULL)
	{
		/*�L�[�{�[�h�ւ̃A�N�Z�X�����J���i���͐���I���j*/
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	/*DireCtInput�I�u�W�F�N�g�̊J��*/
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

}

