#include"main.h"
#include"camera.h"
#include"input.h"
#include"model.h"

/*�O���[�o���ϐ�*/
CAMERA g_camera;//�J�������
void InitCamera(void)
{
	/*�ړ���*/
	g_camera.fmove = 1.0f;
	/*����*/
	g_camera.fDistance = 90.0f;
	/**/
	g_camera.fmove = 0.0f;
	/*�J�����̈ʒu�E�����_�E�������ݒ�*/
	g_camera.posV = D3DXVECTOR3(0.0f, 30.0f, g_camera.fDistance);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
void UninitCamera(void)
{

}
void UpdateCamera(void)
{
	/*�R���g���[���[�̏���*/
	JOYINFOEX JOYPAD; //���݂̃W���C�X�e�B�b�N�̃f�[�^
	/*�W���C�p�b�g�̓���*/
	JOYPAD.dwSize = sizeof(JOYINFOEX);
	JOYPAD.dwFlags = JOY_RETURNALL; // �S�Ă̏����擾
	/*-----------------------------------------------------------------------------------------------------*/
	g_camera.fmove = 0.0f;
	/*�J�����̌�������A�O�㍶�E�ɃJ�������ړ�������*/
	//if (Getkeyboardpress(DIK_NUMPAD8))//�O
	//{
	//	/*�ړ���*/
	//	g_camera.fmove -= 1.0f;
	//	g_camera.posV.x += sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fmove;
	//	g_camera.posV.z += cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fmove;
	//	g_camera.posR.x = g_camera.posV.x - sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//}
	//if (Getkeyboardpress(DIK_NUMPAD2))//���
	//{
	//	/*�ړ���*/
	//	g_camera.fmove += 1.0f;
	//	g_camera.posV.x += sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fmove;
	//	g_camera.posV.z += cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fmove;
	//	g_camera.posR.x = g_camera.posV.x - sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//}
	//if (Getkeyboardpress(DIK_NUMPAD4))//��
	//{
	//	/*�ړ���*/
	//	g_camera.posV.x += sinf(D3DXToRadian(g_camera.rot.y + 90))*1;
	//	g_camera.posV.z += cosf(D3DXToRadian(g_camera.rot.y + 90))*1;
	//	g_camera.posR.x = g_camera.posV.x - sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//}
	//if (Getkeyboardpress(DIK_NUMPAD6))//�E
	//{
	//	/*�ړ���*/
	//	g_camera.posV.x += sinf (D3DXToRadian(g_camera.rot.y + 90))*-1;
	//	g_camera.posV.z += cosf (D3DXToRadian(g_camera.rot.y + 90))*-1;
	//	g_camera.posR.x = g_camera.posV.x - sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//}
	/*-----------------------------------------------------------------------------------------------------*/
	///*�����_�̐���*/
	//if (Getkeyboardpress(DIK_NUMPAD7))
	//{
	//	g_camera.rot.y += 0.1f;
	//	g_camera.posR.x = g_camera.posV.x - sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//}																			 
	//if (Getkeyboardpress(DIK_NUMPAD9))
	//{																			 
	//	g_camera.rot.y -= 0.1f;													 
	//	g_camera.posR.x = g_camera.posV.x - sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	//}
	//
	///*-----------------------------------------------------------------------------------------------------*/
	///*���_�i�J�������W�j�̐���*/
	if (joyGetPosEx(JOYSTICKID1, &JOYPAD) == JOYERR_NOERROR)
	{
		if (JOYPAD.dwButtons & 16)
		{
			g_camera.rot.y -= 1.0f;
			g_camera.posV.x = g_camera.posR.x + sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z + cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;

		}
		if (JOYPAD.dwButtons & 32)
		{
			g_camera.rot.y += 1.0f;
			g_camera.posV.x = g_camera.posR.x + sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z + cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;

		}
	}
	/*���_�i�J�������W�j�̐���*/
	if (Getkeyboardpress(DIK_NUMPAD1))
	{
		g_camera.rot.y += 1.0f;
		g_camera.posV.x = g_camera.posR.x + sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z + cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	}
	if (Getkeyboardpress(DIK_NUMPAD3))
	{
		g_camera.rot.y -= 1.0f;
		g_camera.posV.x = g_camera.posR.x + sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z + cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
	}
	if (D3DXToRadian(g_camera.rot.y) >= (D3DXToRadian(360))|| D3DXToRadian(g_camera.rot.y) <= (D3DXToRadian(-360)))
	{
		g_camera.rot.y = 0;
	}
	/*-----------------------------------------------------------------------------------------------------*/
	PLAYER*pModel = GetPlayer();
	/*�����_�����f���������Ă�������ֈړ�����*/
	g_camera.posRDest = D3DXVECTOR3
	(pModel->pos.x - sinf(D3DXToRadian(pModel->rot.y))*1,
		40.0f,
		pModel->pos.z - cosf(D3DXToRadian(pModel->rot.y))*1);
	/*���f����ǂ�*/
	g_camera.posVDest = D3DXVECTOR3
	(pModel->pos.x + sinf(D3DXToRadian(g_camera.rot.y)) * 100,
		20.0f,
		pModel->pos.z + cosf(D3DXToRadian(g_camera.rot.y)) * 100);
	g_camera.posV += (g_camera.posVDest - g_camera.posV)*1;//�����t���[���Ŕ��f
	g_camera.posR += (g_camera.posRDest - g_camera.posR) * 1;//�����t���[���Ŕ��f
/*------------------------------------------------------------------------------*/
	///*�J�����̊p�x�����f���̌����ɍ��킹��*/
	//g_camera.rotDest.y = pModel->rot.y;
	///*�����t���[���Ō�����ω�������*/
	//g_camera.rot.y += (((D3DXToRadian(g_camera.rotDest.y)))- (D3DXToRadian(g_camera.rot.y)))*5;
}
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^
	/*�r���[�}�g���b�N�X�̏�����*/
	D3DXMatrixIdentity(&g_camera.mtxView);
	/*�r���[�}�g���b�N�X�̍쐬*/
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);
	/*�r���[�}�g���b�N�X�̐ݒ�*/
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
	/*�v���W�F�N�V�����}�g���b�N�X�̏���������*/
	D3DXMatrixIdentity(&g_camera.mtxProjection);
	/*�v���W�F�N�V�����}�g���b�N�X*/
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		2.0f,
		10000.0f);
	/*�v���W�F�N�V�����}�g���b�N�X�̐ݒ�*/
	pDevice->SetTransform(D3DTS_PROJECTION,
		&g_camera.mtxProjection);
}
CAMERA *GetCamera()
{
	return &g_camera;
}