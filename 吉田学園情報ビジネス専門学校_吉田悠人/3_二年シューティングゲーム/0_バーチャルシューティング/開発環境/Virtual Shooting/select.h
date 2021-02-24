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
#include "player.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_NUMBER 2

//=============================================================================
//�O���錾
//=============================================================================
class CSelectBg;
class CScore;
class CUiCount;
class CTelop;
class CButtonManager;
class CWeaponManager;
class CSelectPointer;
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
	void			SetStage(int nStage);	//�X�e�[�W�Z�b�^

	static CUiCount*	GetNumber(NUMBER_TYPE NumberType);	// �i���o�[�Q�b�g
	static CScore*		GetScore(void);						// �X�R�A�Q�b�g
	static CScore*		GetMinusScore(void);				// ����X�R�A�Q�b�g
	static CTelop*		GetTelop(void);						// �e���b�v�Q�b�g
private:
	CSelectBg*			m_pSelectBg;				// �w�i�|�C���^
	CWeaponManager*		m_pWeaponManager;			// �E�F�|��UI�}�l�[�W���[�|�C���^
	static CScore*		m_pScore;					// �X�R�A�|�C���^
	static CScore*		m_pMinusScore;				// ����X�R�A�|�C���^
	static CUiCount*	Number[NUMBER_TYPE_MAX];	// �J�E���g�|�C���^
	static CTelop*		m_pTelop;					// �e���b�v�|�C���^
	CButtonManager*		m_pButtonManager;			// �{�^���}�l�[�W���[�|�C���^
	CSelectPointer*		m_pSelectPointer;			// �}�E�X�|�C���^
	int					m_nStage;					// �X�e�[�W�ԍ�
};
#endif