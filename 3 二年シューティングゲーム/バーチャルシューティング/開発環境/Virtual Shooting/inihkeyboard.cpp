#include"inihkeyboard.h"

CInihKeyboard::CInihKeyboard()
{
	//�L�[���̏�����
	memset(m_akeyState,0,sizeof(m_akeyState));
	memset(m_aKesStateTrigger, 0, sizeof(m_aKesStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
}

CInihKeyboard::~CInihKeyboard()
{
}

HRESULT CInihKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	/*���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬*/
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	/*�f�[�^�t�H�[�}�b�g��ݒ�*/
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	/*�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h*/
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	/*�L�[�{�[�h�ւ̃A�N�Z�X������i���͐���J�n�j*/
	m_pDevice->Acquire();
	return S_OK;
}

void CInihKeyboard::Uninit(void)
{
	CInput::Uninit();
}

void CInihKeyboard::Update(void)
{
	BYTE akeyState[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏��
	int nCntkey;

	/*�f�o�C�X����f�[�^���擾*/
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(akeyState), akeyState)))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			m_aKesStateTrigger[nCntkey] = (m_akeyState[nCntkey] ^ akeyState[nCntkey])&akeyState[nCntkey];
			m_aKeyStateRelease[nCntkey] = (m_akeyState[nCntkey] ^ akeyState[nCntkey])&~akeyState[nCntkey];
			m_akeyState[nCntkey] = akeyState[nCntkey];//�L�[�v���X���ۑ�
		}
	}
	/*�L�[�{�[�h�̍X�V����*/
	else
	{
		m_pDevice->Acquire();
	}

}

bool CInihKeyboard::GetKeyPress(int nKey)
{
	return (m_akeyState[nKey] & 0x80) ? true : false;
}

bool CInihKeyboard::GetKeyPressTrigger(int nKey)
{
	return (m_aKesStateTrigger[nKey] & 0x80) ? true : false;
}

bool CInihKeyboard::GetKeyPressRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
