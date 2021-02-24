//=============================================================================
//
// �V���b�g �x�[�X���� [shots base.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _SHOTS_BASE_H_
#define _SHOTS_BASE_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CShotsBase 
{
public:
	CShotsBase();				// �R���X�g���N�^
	~CShotsBase();				// �f�X�g���N�^	
	HRESULT Init(void);			// ����������
	void	Uninit(void);		// �I������
	void	Update(void);		// �X�V����
	void	Tracking(float fSpeed);		// �ǔ������������
	float	Tracking(void);					// �����̊p�x�擾
	void	Random(float fSpeed);		// �����_���Ȍ����擾����

	virtual void Shots(void) = 0;

	void		SetRot(D3DXVECTOR3 rot);	// �����Z�b�^�[
	D3DXVECTOR3	GetRot(void);				// �����Q�b�^�[
	void		SetPos(D3DXVECTOR3 pos);	// �ʒu�Z�b�^�[
	D3DXVECTOR3	GetPos(void);				// �ʒu�Q�b�^�[
	void		SetShotsEnd(bool bShots);	// �����I��������̃Z�b�^�[
	bool		GetShotsEnd(void);			// �����I��������̃Q�b�^�[
private:
	D3DXVECTOR3	m_rot;	// �G�l�~�[�̌���
	D3DXVECTOR3 m_pos;	// �G�l�~�[�̈ʒu
	bool		m_bShotsEnd;	//�����I�������
};
#endif