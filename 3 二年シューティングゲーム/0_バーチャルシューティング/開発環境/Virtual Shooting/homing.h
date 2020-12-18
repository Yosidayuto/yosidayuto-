#ifndef _HOMING_H_
#define _HOMING_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include"main.h"
#include"scene2d.h"

//----------------------------------------------
//�N���X
//----------------------------------------------
class CHoming :public CScene2d
{
public:
	CHoming(int nPriorit = 1);			//�R���X�g���N�^
	~CHoming();			//�f�X�g���N�^	
	typedef enum  //�o���b�g���
	{
		HOMING_TYPE_PLAYER = 0,
		HOMING_TYPE_ENEMY,
		HOMING_TYPE_BOSS,
		HOMING_TYPE_MAX
	}HOMING_TYPE;

	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);		//�e�N�X�`���̔j��
	static CHoming*	Create(D3DXVECTOR3 Pos, int nSpeed, HOMING_TYPE Type);	//��������


	HRESULT Init(int nSpeed, HOMING_TYPE Type);	//����������
	void	Uninit(void);			//�I������
	void	Update(void);			//�X�V����
	void	Draw(void);				//�`�揈��


private:
	int	TargetGet(D3DXVECTOR3 pos, D3DXVECTOR3 EnemyPos);		//�^�[�Q�b�g
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXVECTOR3 m_move;
	int			m_nSpeed;					//�X�s�[�h
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^
	int	nLife;								//���̎˒�����
	HOMING_TYPE m_Type;						//���̎��

};
#endif