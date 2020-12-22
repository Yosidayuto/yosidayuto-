//=============================================================================
//
// �Q�[������ [game.h]
// Author : �U�J �����Y �g�c�I�l
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;
class CCommunication;
class CUi;
class CDieScreen;
//*****************************************************************************
// �Q�[���N���X
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame();									// �R���X�g���N�^
	~CGame();									// �f�X�g���N�^
	typedef enum	//�����̏��
	{
		MODE_CONTINUE = 0,						// �p��
		MODE_SETTLED,							// ����
		MODE_MAX
	}MODE;
	typedef enum	//�ʐM�̏��
	{
		COMMUNICATTION_MODE_GAME = 0,			// ���s�����܂������̏���
		COMMUNICATTION_MODE_TURN,				// �^�[������
		COMMUNICATTION_MODE_WINNER,				// �������̏���
		COMMUNICATTION_MODE_MAX
	}COMMUNICATTION_MODE;

	COMMUNICATTION_MODE CommuMode;				// ���݂̏����̃��[�h
	MODE				Mode;					// ���s�̕ϐ�


	static CGame *Create(D3DXVECTOR3 size);		// �쐬����
	HRESULT Init(D3DXVECTOR3 size);				// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��
	static void Load(void);						// ���ǂݍ���
	static bool GetPlayerDie(int nPlayer);		// �v���C���[������ł��邩�̊m�F�֐�
private:
	int				m_nTouch;					// �^�b�`���鎕
	bool			m_bSelect;					// ���̑I��
	static CCommunication	*pCommunication;	// �R�~���j�P�[�V�����N���X
	static CPolygon *pPolgon;					// ��̃|�C���^
	static bool		m_bLoad;					// ���[�h���������Ă��邩
	CUi				*m_pUi;						// UI�N���X
	CDieScreen		*m_pDieScreen;				// ���S��ʃN���X
	static bool		m_bPlayerDie[4];			// �v���C���[4�l�̏��
};





#endif // !_GAME_H_


