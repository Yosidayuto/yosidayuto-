//=============================================================================
//
//	�J��������[camera.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "input.h"
#include "inputmouse.h"
#include "inputkeyboard.h"
#include "main.h"
#include "manager.h"
#include "object.h"
#include "renderer.h"
#include "sound.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define PLAYER_DISTANCE (200.0f)	//�J�����ƒ����_�̋���

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	ZeroMemory(&m_mtxProjection,sizeof(m_mtxProjection));//�v���W�F�N�V�����}�g���b�N�X
	ZeroMemory(&m_mtxView, sizeof(m_mtxView));//�r���[�}�g���b�N�X
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
//����������
//=============================================================================
HRESULT CCamera::Init(D3DXVECTOR3 posR)
{
	//�J�����̏���(�ʒu�E���ӓ_�E�����)�ݒ�
	m_posV = D3DXVECTOR3(posR);
	m_posR = m_posV + D3DXVECTOR3(0.0f, 600.0f, 750.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//�J�����̌����ݒ�
	m_rot = D3DXVECTOR3(60.0f, 0.0f, 0.0f);
	//�J�����̈ʒu
	m_pos = m_posV;

	//���_-���ӓ_�̋����̌v�Z
	m_fDistance = (float)sqrt(
		pow(m_posV.x - m_posR.x, 2.0f) + pow(m_posV.z - m_posR.z, 2.0f));

	//�}�E�X�̊��x�̐ݒ�
	m_nSensitivity = CAMERA_SENSITIVITY;
	//�J�����̃X�s�[�h�ݒ�
	m_fSpeed = CAMERA_SPEED;

	//�}�l�[�W���[�ɃJ��������ۑ�
	CManager::BindCamera(this);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
//�X�V����
//=============================================================================
void CCamera::Update(void)
{
	Move();

	//�ړ��̌v�Z
	D3DXVECTOR3 RotateCenter =m_pos + D3DXVECTOR3(sinf(D3DXToRadian(m_rot.y - 90)),
											 50,
											 cosf(D3DXToRadian(-m_rot.y - 90)));
	
	//�J�����̈ړ�����
	m_posV = RotateCenter +
		D3DXVECTOR3(sinf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x))*m_fDistance,
			sinf(D3DXToRadian(m_rot.x))*m_fDistance,
			cosf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x))*m_fDistance);

	//���ӓ_�̈ړ�����
	m_posR = RotateCenter;

}

//=============================================================================
//�J�����ɂ��`��
//=============================================================================
void CCamera::SetCamera(void)
{		
	//�f�o�C�X�ւ̃|�C���^
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice(); 
  
    //�r���[�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxView);
    //�r���[�}�g���b�N�X�̍쐬
    D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
    //�r���[�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
    //�v���W�F�N�V�����}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxProjection);
    //�v���W�F�N�V�����}�g���b�N�X�̍쐬
    D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE);
    //�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//=============================================================================
// �����_�Q�b�^�[
//=============================================================================
D3DXVECTOR3 CCamera::GetPosR(void)
{
    //�����_���������̒����ɕ␳���ďo��
    D3DXVECTOR3 vec;
    D3DXVec3Normalize(&vec, &(m_posR - m_posV));
    vec = vec * m_fDistance + m_posV;
    return vec;
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CCamera::Move(void)
{
#ifdef _DEBUG

	//�L�[�{�[�h���͂̎擾
	CInputKeyboard* pInput = (CInputKeyboard*)CManager::GetInputKey();

	//�}�E�X���͎擾
	CInputMouse *pInputMouse = (CInputMouse*)CManager::GetInputMou();
	//�ړ���
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//���_�𓮂���
	if (pInputMouse->GetClick(1))
	{
		//����
		m_rot.x += (pInputMouse->GetMousePos().lY * (float)(0.01f * m_nSensitivity));
		m_rot.y -= (pInputMouse->GetMousePos().lX * (float)(0.01f * m_nSensitivity));

		//�ړ�
		if (pInput->GetKeyPress(DIK_UP))
		{
			//�P�ʃx�N�g���Ɏ擾
			D3DXVec3Normalize(&move, &(m_posR - m_posV));
		}
		if (pInput->GetKeyPress(DIK_DOWN))
		{
			//�P�ʃx�N�g���Ɏ擾
			D3DXVec3Normalize(&move, &(m_posR - m_posV));
			move *= -1;
		}
		if (pInput->GetKeyPress(DIK_LEFT))
		{
			//�ړ������w��w
			m_moveRot = 0.0f;
			//�ړ����̌����ݒ�
			m_moveRot += m_rot.y;
			//�ړ��ʏ���
			move += D3DXVECTOR3(cosf(D3DXToRadian(m_moveRot)), 0, sinf(D3DXToRadian(m_moveRot)));
		}
		if (pInput->GetKeyPress(DIK_RIGHT))
		{
			//�ړ������w��
			m_moveRot = 180.0f;
			//�ړ����̌����ݒ�
			m_moveRot += m_rot.y;
			//�ړ��ʏ���
			move += D3DXVECTOR3(cosf(D3DXToRadian(m_moveRot)), 0, sinf(D3DXToRadian(m_moveRot)));
		}
		//���x����
		move *= m_fSpeed;
		//�ړ�����
		m_pos += move;
	}


	//�����̌��E�l����
	if ((m_rot.x) >= 89
		|| (m_rot.x) <= -89)
	{
		m_rot.x -= (pInputMouse->GetMousePos().lY * (float)(0.01f * m_nSensitivity));
	}
	if (m_rot.y<0)
	{
		m_rot.y += 360;
	}
	if (m_rot.y > 360)
	{
		m_rot.y -= 360;
	}

#endif

}

//=============================================================================
// �^�C�g���ł̓��������֐�
//=============================================================================
void CCamera::TitleMove(void)
{
	//�J������Y����������������
	m_rot.y+=0.2f;
}

//=============================================================================
// �J�����ʒu�ݒ�֐�
//=============================================================================
void CCamera::SetPos(D3DXVECTOR3 pos)
{
	//�J�����̏���(�ʒu�E���ӓ_�E�����)�ݒ�
	m_posV = D3DXVECTOR3(pos);
	m_posR = m_posV + D3DXVECTOR3(0.0f, 600.0f, 750.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//�J�����̈ʒu
	m_pos = m_posV;

	//���_-���ӓ_�̋����̌v�Z
	m_fDistance = (float)sqrt(
		pow(m_posV.x - m_posR.x, 2.0f) + pow(m_posV.z - m_posR.z, 2.0f));


}

