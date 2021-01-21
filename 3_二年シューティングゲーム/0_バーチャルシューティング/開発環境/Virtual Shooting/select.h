//=============================================================================
//
// �Z���N�g���� [select.h]
// Author : �g�c �I�l
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"
#include "scene.h"
//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define MAX_NUMBER 2

//------------------------------------
//�O�u����
//------------------------------------
class CSelectBg;
class CButton;
class CWindow;
class CScore;
class CUiCount;
class CWeapon_Ui;
class CTelopText;
class CStartButton;
//------------------------------------
//�N���X����
//------------------------------------
class CSelect
{
public:
	CSelect();	//�R���X�g���N�^
	~CSelect();	//�f�X�g���N�^

	typedef enum
	{
		NUMBER_TYPE_LIEF = 0,
		NUMBER_TYPE_SPEED,
		NUMBER_TYPE_MAX
	}NUMBER_TYPE;

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��
	static CUiCount	*GetNumber(NUMBER_TYPE NumberType);	//�i���o�[�Q�b�g
	static CWeapon_Ui*GetWeaponUi(int nWeaponUi);		//�E�F�|��UI�Q�b�g
	static CScore	*GetScore(void);					//�X�R�A�Q�b�g
	static CScore	*GetMinusScore(void);				//����X�R�A�Q�b�g

	static CTelopText *GetpTelopText(void) { return m_pTelopText; }
private:
	static	CWeapon_Ui* m_pWindowUi[2];
	CWindow*			m_pWindow;
	CSelectBg			*m_pSelectBg;				//�w�i�N���X
	CStartButton*		m_pStartButton;				//�X�^�[�g�{�^���|�C���^
	CButton				*m_pButton[6];				//�{�^���N���X
	static CScore		*m_pScore;					//�X�R�A�N���X
	static CScore		*m_pMinusScore;				//����X�R�A�N���X
	static CUiCount		*Number[NUMBER_TYPE_MAX];	//�J�E���g�N���X
	static CTelopText	*m_pTelopText;				//�e���b�v�e�L�X�g�N���X
};


#endif