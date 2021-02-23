//=============================================================================
//
// �L�[�{�[�h���� [inihkeyboard.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include"inihkeyboard.h"

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CInihKeyboard::CInihKeyboard()
{
	//�L�[���̏�����
	memset(m_akeyState,0,sizeof(m_akeyState));
	memset(m_aKesStateTrigger, 0, sizeof(m_aKesStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CInihKeyboard::~CInihKeyboard()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CInihKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�C���v�b�g������
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h)
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X������i���͐���J�n�j
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CInihKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CInihKeyboard::Update(void)
{
	BYTE akeyState[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏��
	int nCntkey;

	//�f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(akeyState), akeyState)))
	{
		//�L�[��for�ŉ�
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

//=============================================================================
//�v�b�V���Q�b�^�[
//=============================================================================
bool CInihKeyboard::GetKeyPress(int nKey)
{
	return (m_akeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
//�v�b�V���g���K�[�Q�b�^�[
//=============================================================================
bool CInihKeyboard::GetKeyPressTrigger(int nKey)
{
	return (m_aKesStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
//�v�b�V�������[�X�Q�b�^�[
//=============================================================================
bool CInihKeyboard::GetKeyPressRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
