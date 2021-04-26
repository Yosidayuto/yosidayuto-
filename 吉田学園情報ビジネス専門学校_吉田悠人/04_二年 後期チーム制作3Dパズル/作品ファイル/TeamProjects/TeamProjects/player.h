//=============================================================================
//
// �v���C���[ [player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "model.h"
#include "object3d.h"
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================
class CModel;
class CChild;
class CParticle;
class CTileBlockBase;
//=============================================================================
// �N���X��`
//=============================================================================
class CPlayer : public CObject3D
{
public:

	// �ړ��p�^�[����
	typedef enum
	{
		STICKY_NONE = 0, // �ʏ�ړ�
		STICKY_FRONT,    // �������Ă�����̂����ʂɂ���A�������̕����Ɉړ�
		STICKY_DOWN,     // �������Ă�����̂����ʂɂ���
		STICKY_UP		 // �������Ă�����̂���ʂɂ���
	}MOVE_PATTERN;

	CPlayer();
	~CPlayer();
	static CPlayer*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	HRESULT Init(void);		//����������
	void	Uninit(void);	//�I������
	void	Update(void);	//�X�V����
	void	Draw(void);		//�`�揈��

	void	Goal(void);		//�S�[������
	static CPlayer* GetPlayer(void)	{ return m_pPlayer; }		// �v���C���[�擾����
	bool	IsActiveMove(void)		{ return m_bActiveMove; }	// �ړ��t���O�擾����
	void	SetAction(bool bPlayer) { m_bPlayer = bPlayer; }	// �v���C���[�̍s����ԃZ�b�^�[
private:
	void Control(void);						// ���쏈��
	void Move(void);						// �ړ�����
	void Fall(void);						// ��������
	void Collision(void);					// �����蔻�菈��
	bool CollisionChild(CObject* Object);	// �q���u���b�N�̓����蔻��
	void MoveRange(void);					// �s���͈͐ݒ菈��
	void MoveRangeChild(void);				// �q���u���b�N�̍s���͈͐ݒ菈��
	void ErrorStatus(void);					// �G���[���̎g�p�m�F�֐�
	void MoveError(void);					// �s���s�\���̏���
	void ExchangeWorldMtx(void);			// ���[���h�ϊ�

	static CPlayer*	m_pPlayer;				// �v���C���[�|�C���^
	CModel*			m_model;				// ���f���|�C���^
	D3DXVECTOR3	 m_Move;					// �ړ���
	D3DXMATRIX	 m_mtxRot;					// ��]�s��
	int			 m_nMoveFrameCount;			// �ړ��t���[�����̃J�E���g�p
	int			 m_nFallFrameCount;			// �����t���[�����̃J�E���g�p
	bool		 m_bPlayer;					// �v���C���[�̐�������
	bool		 m_bActiveMove;				// �ړ������̔���p
	bool		 m_bFallMove;				// ���������̔���p
	bool		 m_bError;					// �G���[���p�̎g�p����
	CChild *	 m_pChild;					// �q��(�������ʂ̏���)�|�C���^
	MOVE_PATTERN m_movePattern;				// �ړ��̃p�^�[��
	const int	 m_nModel = 1;				// ���f���ԍ�

};
#endif