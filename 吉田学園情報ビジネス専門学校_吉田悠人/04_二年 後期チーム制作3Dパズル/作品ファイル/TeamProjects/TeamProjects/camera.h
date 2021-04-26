//=============================================================================
//
//	�J��������[camera.h]
//	Author:�g�c�I�l
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define CAMERA_VIEW_RANGE (1000000.0f)
#define CAMERA_SENSITIVITY (3)		//�����}�E�X���x
#define CAMERA_SPEED (10.0f)			//�����J�����X�s�[�h

//=============================================================================
//�N���X��`
//=============================================================================
class CCamera
{
public:
    CCamera();					// �R���X�g���N�^
    ~CCamera();					// �f�X�g���N�^
    HRESULT Init(D3DXVECTOR3 posR);						// �������֐�

    void Uninit(void);			// �I���֐�
    void Update(void);			// �X�V�֐�

    void		SetCamera(void);	// �J�����̌��Ă�����̂�`��
    D3DXVECTOR3 GetPosR(void);		// �����_�Q�b�^�[
	void		Move(void);			// �ړ�����
	void		TitleMove(void);	// �^�C�g���ł̓���

	void		SetPos(D3DXVECTOR3 pos);	//�J�����ʒu�ݒ�

	D3DXMATRIX GetViewMtx(void) { return m_mtxView; }
	D3DXMATRIX GetProjectionMtx(void) { return m_mtxProjection; }
private:
    D3DXVECTOR3 m_posV;				//�J�����̍��W
    D3DXVECTOR3 m_posR;				//�����_�̍��W
    D3DXVECTOR3 m_vecU;				//�J�����̏����
    float		m_fDistance;		//���_-���ӓ_�̋���
    D3DXVECTOR3 m_rot;				//����
	D3DXVECTOR3 m_pos;				//�ʒu
	float		m_moveRot;			//�ړ��������

	int			m_nSensitivity;		//�}�E�X�̊��x
	float		m_fSpeed;			//�J�����X�s�[�h
	
	D3DXMATRIX	m_mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	m_mtxView;//�r���[�}�g���b�N�X
};

#endif
