#pragma comment(lib,"Winmm.lib")
#include "main.h"
/*----------------------------------------------------------------------*/
/*�w�b�_�[�t�@�C��*/
#include "light.h"
#include "camera.h"
#include "polygon.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "meshfield.h"
#include "meshfield2.h"
#include "block.h"
#include "enemy.h"
#include "life.h"
#include "Game.h"
#include "fade.h"
#include "title.h"
#include "result.h"
#include "gameover.h"
#include "tutorial.h"
#include "tutorial2.h"
#include "sound.h"
/*----------------------------------------------------------------------*/
//�}�N����`
#define CLASS_NAME "window class"//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME "3D"//�E�C���h�E�̖��O(�L���v�V������)

//�v���g�^�C�v�錾

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3D9			g_pD3D = NULL;				//Direct3D�I�u�W�F�N�g�̃|�C���^
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;		//Direct3D�f�o�C�X�̃|�C���^�i�`��j
MODE g_mode = MODE_TITLE;						//���[�h

												/*=============================================================================*/
												/* ���C���֐�																	*/
												/*=============================================================================*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	HWND hWnd;
	MSG msg;
	RECT rect =
	{
		WINDOW_POS_X,
		WINDOW_POS_Y,
		(WINDOW_POS_X + SCREEN_WIDTH),
		(WINDOW_POS_Y + SCREEN_HEIGHT)
	};
	DWORD dwCurrentTime;//���ݎ���
	DWORD dwExecLastTime;//�Ō�ɏ�����������

	RegisterClassEx(&wcex);


	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);


	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		WINDOW_POS_X,
		WINDOW_POS_Y,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);




	//�����������i�E�B���h�E���쐬���Ă���s���j
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//*//
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();//���݂̎����
								   //*//
								   //���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W�������烋�[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//Directx�̏���
			dwCurrentTime = timeGetTime();//�V�X�e���������擾
			if ((dwCurrentTime = dwExecLastTime) >= (1000 / 60))//1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;//��������������ۑ�
											   //�X�V����
				Update();
				//�`�揈��
				Draw();
			}
		}
	}


	//�I������
	Uninit();

	//�E�C���h�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:

			DestroyWindow(hWnd);
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
// hInstance : �C���X�^���X�̃n���h��
// hWnd      : �E�C���h�E�̃n���h��
// bWindow   : �E�C���h�E���[�h�ɂ��邩�ǂ���
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;//�v���[���e�[�V�����p�����[�^
								//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}



	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{

		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{

			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{

				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//���ʂ��i�����j���J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//�����x���g��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//a�f�X�e�B�l�[�V�����J���[�̎w��
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	
	/*------------------------------------------------------------*/
	luitkeyboard(hInstance, hWnd);		//�L�[�{�[�h�̏���������
	InitSound(hWnd);					//�T�E���h�̏���������
	/*------------------------------------------------------------*/
	
	/*------------------------------------------------------------*/
	InintTitle();						//�^�C�g��
	/*------------------------------------------------------------*/
	InintTutorial();					//�`���[�g���A��
	InintTutorial2();					//�`���[�g���A��2

	/*------------------------------------------------------------*/
	InitFade(g_mode);					//�t�F�[�h�̏���������
	SetFade(g_mode);					//�t�F�[�h�Z�b�g
	/*------------------------------------------------------------*/
	InintResult();						//���U���g�̏���������
	/*------------------------------------------------------------*/
	InintGameover();					//�Q�[���I�[�o�[��ʂ̏���������
	/*------------------------------------------------------------*/
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	if (g_pD3DDevice != NULL)
	{//Direct3D�f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;

	}

	if (g_pD3D != NULL)
	{//Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	Updatekeyboard();

	//�e��I�u�W�F�N�g�̍X�V����
	switch (g_mode)
	{

	case MODE_TITLE:						//�^�C�g����ʂ̍X�V����
		UpdateTitle();

		break;
	case MODE_TUTORIAL:						//�`���[�g���A����ʂ̍X�V����
		UpdateTutorial();
	
		break;
	case MODE_TUTORIAL2:					//�`���[�g���A����ʂ̍X�V����
		UpdateTutorial2();
		break;
	case MODE_GAME:							//�Q�[����ʂ̍X�V����
		UpdateGame();
	
		break;
	case MODE_RESULE:						//���U���g��ʂ̍X�V����
		UpdateResult();
	
		break;
	case MODE_GAMEOVER:						//�Q�[���I�[�o�[��ʂ̍X�V����
		UpdateGameover();
		break;
	}
	/*�t�F�[�h�̍X�V����*/
	UpdaFade();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	//�o�b�N�o�b�t�@���o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

		switch (g_mode)
		{
		case MODE_TITLE:			//�^�C�g����ʂ̕`�揈��
			DrawTitle();
			break;
		case MODE_TUTORIAL:			//�`���[�g���A����ʂ̕`�揈��
			DrawTutorial();
			break;
		case MODE_TUTORIAL2:
			DrawTutorial2();
			break;
		case MODE_GAME:				//�Q�[����ʂ̕`�揈��
			DrawGame();
			break;
		case MODE_RESULE:			//���U���g��ʂ̕`�揈��
			DrawResult();
			break;
		case MODE_GAMEOVER:			//�Q�[���I�[�o�[��ʂ̕`�揈��
			DrawGameover();
			break;
		}
		/*�t�F�[�h�̕`�揈��*/
		DrawFade();
		/*�`��̏I������*/
		g_pD3DDevice->EndScene();
	}
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
void SetMode(MODE mode)
{

	g_mode = mode;
	switch (g_mode)
	{
	case  MODE_TITLE:
		InitGame();							//�{��
		StopSound();
		PlaySound(SOUND_LABEL_BGM000);
		break;
	case MODE_TUTORIAL:
		StopSound(SOUND_LABEL_BGM000);
		PlaySound(SOUND_LABEL_BGM001);
		break;
	case MODE_TUTORIAL2:
		break;
	case MODE_GAME:
		StopSound(SOUND_LABEL_BGM001);
		PlaySound(SOUND_LABEL_BGM002);
		break;
	case MODE_RESULE:
		StopSound(SOUND_LABEL_BGM002);
		PlaySound(SOUND_LABEL_BGM003);
		break;
	case MODE_GAMEOVER:
		StopSound(SOUND_LABEL_BGM002);
		PlaySound(SOUND_LABEL_BGM004);

		break;
	}


}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
MODE GetMode(void)
{
	return g_mode;
}