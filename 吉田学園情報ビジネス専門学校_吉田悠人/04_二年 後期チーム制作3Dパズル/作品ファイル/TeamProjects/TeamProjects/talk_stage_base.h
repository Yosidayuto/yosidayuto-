//=============================================================================
//
//	�g�[�N�����x�[�X [talk_stage_base.h]
//	Author : ����@�r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _TALK_STAGE_BASE_H_
#define _TALK_STAGE_BASE_H_

//====================================
//�C���N���[�h
//====================================
#include "main.h"
#include "object.h"

//====================================
//�O���錾
//====================================
class CTutorial;
class CTalkbase;
//====================================
// �N���X��`
//====================================
class CTalkStageBese :public CObject
{
public:

	CTalkStageBese(int nPriorit = PRIORITY_UI_0);
	virtual HRESULT Init(void);
	virtual void	Uninit(void);
	virtual void	Update(void);
	virtual void	Draw(void);

	void		SetPos(D3DXVECTOR3 pos);	//�ʒu�Z�b�^�[
	D3DXVECTOR3	GetPos(void);				//�ʒu�Q�b�^�[
	void		SetSize(D3DXVECTOR3 size);	//�T�C�Y�Z�b�^�[
	D3DXVECTOR3	Getsize(void);				//�T�C�Y�Q�b�^�[

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};
#endif // !_UI_H_
