//=============================================================================
//
// �V�[������ [scene.h]
// Author : �U�J �����Y
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_POLYGON		(50)		// �|���S���̍ő吔

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_MAX
	}OBJTYPE;
	CScene();										// �R���X�g���N�^
	virtual ~CScene();								// �f�X�g���N�^
	virtual HRESULT Init(D3DXVECTOR3 size) = 0;		// ����������
	virtual void Uninit() = 0;						// �I������
	virtual void Update(void) = 0;					// �X�V����
	virtual void Draw(void) = 0;					// �`�揈��
	static void UpdateAll(void);					// �S�I�u�W�F�N�g�X�V����
	static void DrawAll(void);						// �S�I�u�W�F�N�g�`�揈��
	static void ReleaseAll(void);					// �S�I�u�W�F�N�g�����[�X����
	static CScene *GetScene(int nNumber);			// �V�[���̎擾
	void SetObjType(OBJTYPE objType);				// �I�u�W�F�N�g�ݒ�
	OBJTYPE GetObjType(void) { return m_objType; }	// �I�u�W�F�N�g��Ԏ擾

protected:
	void Release(void);								// �����[�X����

private:
	static CScene *m_apScene[MAX_POLYGON];			// �V�[���̔z��
	static int m_nNumAll;							// �I�u�W�F�N�g��
	int m_nID;										// �I�u�W�F�N�g�ԍ�
	OBJTYPE m_objType;								// �I�u�W�F�N�g�̎��
};

#endif 










