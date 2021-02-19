//=============================================================================
//
// �o���b�g�x�[�X���� [bullet base.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _BULLET_BASE_H_
#define _BULLET_BASE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"scene2d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CBulletBase :public CScene2d
{
public:
	CBulletBase(int nPriorit = PRIORITY_OBJECT_1);	//�R���X�g���N�^
	~CBulletBase();									//�f�X�g���N�^	

	static HRESULT		Load(void);		//�e�N�X�`���ǂݍ���
	static void			Unload(void);	//�e�N�X�`���̔j��

	HRESULT Init(void);						// ����������
	void	Uninit(void);					// �I������
	void	Update(void);					// �X�V����
	void	Draw(void);						// �`�揈��
	void	ObjeSearch(void);				// �I�u�W�F�N�g�T�[�`
	bool	Range(void);					// �˒�����
	virtual void Move(void) = 0;			// �ړ�����
	virtual void Bullet(CScene* pObj) = 0;	// �o���b�g

	void		SetMove(D3DXVECTOR3 move);	// �ړ��ʃZ�b�^�[
	D3DXVECTOR3	GetMove(void);				// �ړ��ʃQ�b�^�[
	void		SetLife(int nLife);			// ���C�t�Z�b�^�[
	int			GetLife(void);				// ���C�t�Q�b�^�[
private:
	D3DXVECTOR3			m_move;			// �ړ���
	int					m_nLife;			// �e�̎˒�����

};
#endif