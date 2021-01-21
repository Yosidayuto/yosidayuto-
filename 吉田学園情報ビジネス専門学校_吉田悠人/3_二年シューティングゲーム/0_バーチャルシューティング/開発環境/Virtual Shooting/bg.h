//=============================================================================
//
//	�w�i[bg.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _Bakground_H_
#define _Bakground_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "manager.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CBgc :public CScene2d
{
public:

	CBgc(int nPriorit = 0);			//�R���X�g���N�^
	~CBgc();						//�f�X�g���N�^

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��

	void			ScrollY(float fScroll);	//Y������ʃX�N���[��
	void			ScrollX(float fScroll);	//X������ʃX�N���[��

private:
	int					m_nCounterAnim;	//�A�j���[�V�����J�E���^�[
	int					m_nPatternAnim;	//�A�j���[�V�����p�^�[��No
};
#endif