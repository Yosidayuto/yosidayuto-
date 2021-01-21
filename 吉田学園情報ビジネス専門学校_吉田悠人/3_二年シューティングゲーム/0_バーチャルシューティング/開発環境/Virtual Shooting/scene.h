//=============================================================================
//
// �V�[������ [scene.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _SCENE_H_
#define _SCENE_H_

#include"main.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PRIORITY_MAX (6)		// �`��D��x�̍ő�l
//=============================================================================
// �N���X��`
//=============================================================================
class CScene
{
public:
	typedef enum				// �|���S�����
	{							   
		OBJ_TYPE_NONE = 0,		   
		OBJ_TYPE_PLAYER,		// �v���C���[
		OBJ_TYPE_BULLET,		// �o���b�g
		OBJ_TYPE_ENEMY,			// �G�l�~�[
		LABEL_MAX,
	}OBJTYPE;


	CScene(int nPriorit = 3);			// �R���X�g���N�^
	virtual ~CScene();					// �f�X�g���N�^

	virtual	HRESULT Init(void)		= 0;// �������z�֐��Q
	virtual	void	Uninit(void)	= 0;
	virtual void	Draw(void)		= 0;
	virtual void	Update(void)	= 0;

	static void		UpdateAll(void);	// �S�V�[���X�V�����֐�
	static void		DrawAll(void);		// �S�V�[���`�揈���֐� 
	static void		ReleaseAll(void);	// �S�V�[���I�������֐�
	
	void			SetObjType(OBJTYPE Type);	// �I�u�W�F�N�g�^�C�v�Z�b�g
	OBJTYPE			GetObjType(void);			// �I�u�W�F�N�g�^�C�v�Q�b�^�[

	static CScene** GetTop(void);				// �I�u�W�F�N�g�g�b�v�Q�b�^�[

	CScene*			GetNext(void);				// ���̃I�u�W�F�N�g�擾
	CScene*			GetPrev(void);				// �O�̃I�u�W�F�N�g�擾


protected:
	void Release(void);						// �V�[���̊J��
private:
	void	Death(void);					// ���X�g�폜��̃V�[���N���X�I������
	
	static CScene* m_pTop[PRIORITY_MAX];	// �I�u�W�F�N�g�g�b�v
	static CScene* m_pCur[PRIORITY_MAX];	// �I�u�W�F�N�g
	CScene*		m_pPrev;					// ���̃I�u�W�F�N�g�N���X
	CScene*		m_pNext;					// �O�̃I�u�W�F�N�g�N���X
	int			m_nPriority;				// �D�揇�ʗp�ϐ�
	bool		m_bDestroy;					// �I�u�W�F�N�g�j���X�C�b�`
	OBJTYPE		m_objType;					// �I�u�W�F�N�g�^�C�v
};
#endif