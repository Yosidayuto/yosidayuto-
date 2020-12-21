//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	camera.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "camera.h"

#include "input.h"
#include "inputkeyboard.h"
#include "main.h"
#include "manager.h"
#include "object.h"
#include "player.h"
#include "renderer.h"
#include "sound.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCamera::CCamera()
{
}
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCamera::~CCamera()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CCamera::Init(void)
{
    //�J�����̏���(�ʒu�E���ӓ_�E�����)�ݒ�
    m_posV = D3DXVECTOR3(20, 40, -100);
    m_posR = m_posV + D3DXVECTOR3(0, 0, 500);
    m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //�J�����̌����ݒ�
    m_rot = D3DXVECTOR3(45.0f, 180.0f, 0.0f);
    //�J�����̃v���C���[����̋����ݒ�
    m_fDistanceFromPlayer = CAMERA_DISTANCE_FROM_PLAYER;
    //���_-���ӓ_�̋����̌v�Z
    m_fDistance = (float)sqrt(
      pow(m_posV.x - m_posR.x, 2.0f) + pow(m_posV.z - m_posR.z, 2.0f));
    //�}�l�[�W���[�ɃJ��������ۑ�
    CManager::BindCamera(this);
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCamera::Uninit(void)
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCamera::Update(void)
{
    CPlayer* pPlayer = NULL;
    //�v���C���[�̃|�C���^�擾
    pPlayer = CManager::GetPlayer();
    //�L�[�{�[�h���͂̎擾
    CInputKeyboard* pInput = (CInputKeyboard*)CManager::GetInputKey();
    //�v���C���[�̏�Ԃɂ���ăJ���������𐧌�
    switch(pPlayer->GetState())
    {
        case CPlayer::STATE_AIM:
            m_fDistanceFromPlayerDest = CAMERA_DISTANCE_FROM_PLAYER_AIM;
            break;
        default:
            m_fDistanceFromPlayerDest = CAMERA_DISTANCE_FROM_PLAYER_STAND;
            break;
    }
    //�J���������̕ω���⊮
    m_fDistanceFromPlayer += (m_fDistanceFromPlayerDest - m_fDistanceFromPlayer) / 3;
    //�J������]�̒��S���v���C���[�̉��Ɏ����Ă���
    m_RotateCenter = pPlayer->GetPos() + D3DXVECTOR3(sinf(D3DXToRadian(m_rot.y - 90)) * CAMERA_DISTANCE_FROM_PLAYER, PLAYER_HEAD_HEIGHT, cosf(D3DXToRadian(-m_rot.y - 90)) * CAMERA_DISTANCE_FROM_PLAYER);
    //�J�������n�ʂ��ђʂ��Ă��܂��ꍇ�n�ʂɔ��킹��悤��
    if(m_RotateCenter.y + sinf(D3DXToRadian(m_rot.x)) * m_fDistanceFromPlayer > 0)
    {
        m_posV = m_RotateCenter + D3DXVECTOR3(sinf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x)) * m_fDistanceFromPlayer, sinf(D3DXToRadian(m_rot.x)) * m_fDistanceFromPlayer, cosf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x)) * m_fDistanceFromPlayer);
    }
    else
    {
        m_posV = m_RotateCenter + D3DXVECTOR3(sinf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x)) * m_fDistanceFromPlayer, -m_RotateCenter.y + 1, cosf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x)) * m_fDistanceFromPlayer);
    }
    //�����_����]�̒��S�ɂ��킹��
    m_posR = m_RotateCenter;
}
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�J�����ɂ��`��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCamera::SetCamera(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();    //�f�o�C�X�ւ̃|�C���^
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

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
D3DXVECTOR3 CCamera::GetRot(void)
{
    return m_rot;
}

D3DXVECTOR3 CCamera::GetPosR(void)
{
    //�����_���������̒����ɕ␳���ďo��
    D3DXVECTOR3 vec;
    D3DXVec3Normalize(&vec, &(m_posR - m_posV));
    vec = vec * m_fDistance + m_posV;
    return vec;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Z�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCamera::SetRot(D3DXVECTOR3 rot)
{
    m_rot = rot;
}
