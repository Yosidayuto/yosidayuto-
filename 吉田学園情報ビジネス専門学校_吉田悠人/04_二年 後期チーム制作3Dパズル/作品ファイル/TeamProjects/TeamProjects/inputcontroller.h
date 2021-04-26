//=============================================================================
//
// ���C������ [inputcontroller.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "input.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_CONTROLLER_NUM		(1)		//�R���g���[���[�̐ڑ��ő吔
#define CROSS_KEY_UP			(0)		//�\���L�[��
#define CROSS_KEY_TOP_RIGHT		(4500)	//�\���L�[�E��
#define CROSS_KEY_RIGHT			(9000)	//�\���L�[�E
#define CROSS_KEY_BOTTOM_RIGHT	(13500)	//�\���L�[�E��
#define CROSS_KEY_DOWN			(18000)	//�\���L�[��
#define CROSS_KEY_BOTTOM_LEFT	(22500)	//�\���L�[����
#define CROSS_KEY_LEFT			(27000)	//�\���L�[��
#define CROSS_KEY_TOP_LEFT		(31500)	//�\���L�[����
#define CROSS_KEY_NEUTRAL		(65535) //�\���L�[�j���[�g����
#define JOYPAD_EFFECT_NUM 2

//=============================================================================
//�W���C�X�e�B�b�N�N���X
//=============================================================================
class CInputJoyStick :public CInput
{
public:
	//=============================================================================
	//�W���C�X�e�B�b�N�̃{�^���p�̗񋓌^��`
	//=============================================================================
	typedef enum
	{
		JOY_BUTTON_X = 0,		//X�{�^��
		JOY_BUTTON_Y,			//Y�{�^��
		JOY_BUTTON_A,			//A�{�^��
		JOY_BUTTON_B,			//B�{�^��
		JOY_BUTTON_L_TRIGGER,	//L�g���K�[�{�^��
		JOY_BUTTON_R_TRIGGER,	//R�g���K�[�{�^��
		JOY_BUTTON_L_TRIGGER2,	//L�g���K�[�{�^��2
		JOY_BUTTON_R_TRIGGER2,	//R�g���K�[�{�^��2
		JOY_BUTTON_L3,			//L�{�^��
		JOY_BUTTON_R3,			//R�{�^��
		JOY_BUTTON_SELECT,		//SELECT�{�^��
		JOY_BUTTON_START,		//START�{�^��
		JOY_BUTTON_HOME,		//HOME�{�^��
		JOY_BUTTON_MAX,			//�ő�{�^����
	}JOY_BUTTON;

	//=============================================================================
	//�W���C�X�e�B�b�N��Ԕ��ʗp�̍\���̒�`
	//=============================================================================
	typedef struct
	{
		DIJOYSTATE	Old;		//�p�b�h�{�^���̑O����
		DIJOYSTATE	Press;		//�p�b�h�{�^���̃v���X���
		DIJOYSTATE	Trigger;	//�p�b�h�{�^���̃g���K�[���
		DIJOYSTATE	Release;	//�p�b�h�{�^���̃����[�X���
	}JoyStickState;

	//=============================================================================
	//�����o�֐��錾
	//=============================================================================
	CInputJoyStick();
	~CInputJoyStick();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void	Uninit(void);
	void	Update(void);

	bool GetJoyStickPress(int nButton);		//�W���C�X�e�B�b�N�N���X�̃v���X���̎擾
	bool GetJoyStickTrigger(int nButton);	//�W���C�X�e�B�b�N�N���X�̃g���K�[���̎擾
	bool GetJoyStickReleas(int nButton);	//�W���C�X�e�B�b�N�N���X�̃����[�X���̎擾

	bool GetPushCross(int nButtond);		//�W���C�X�e�B�b�N�N���X�̏\���L�[�������ꂽ�u�Ԃ̔��菈��
	bool GetPushRelease(int nButtond);		//�W���C�X�e�B�b�N�N���X�̏\���L�[���������u�Ԃ̔��菈��

	void SetVibration(int nNum);             // �U���Z�b�g���� 0* �傫�� 1*������

	DIJOYSTATE	GetJoyStick(void);			//�W���C�X�e�B�b�N�N���X�̃X�e�B�b�N���̎擾
	static BOOL CALLBACK DeviceFindCallBack(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
private:

	void CreateEffect(void); // �U���G�t�F�N�g�̐���
	//=============================================================================
	//�����o�ϐ��錾
	//=============================================================================
	static LPDIRECTINPUTDEVICE8 m_pJoyDevice;	          //�W���C�X�e�B�b�N�̃f�o�C�X���
	JoyStickState				m_JoyState;		          //�W���C�X�e�B�b�N�̏��
	static LPDIRECTINPUTEFFECT  m_lpDIEffect[JOYPAD_EFFECT_NUM];             // �G�t�F�N�g�U���p
	static DWORD                m_dwNumForceFeedbackAxis[JOYPAD_EFFECT_NUM]; // 
};


#endif
