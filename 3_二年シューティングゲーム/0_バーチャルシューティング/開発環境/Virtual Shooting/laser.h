//=============================================================================
//
// ���[�U�[���� [laser.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _LASER_H_
#define _LASER_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include"main.h"
#include"scene2d.h"
#define MAX_ENEMY (100)

//----------------------------------------------
//�N���X
//----------------------------------------------
class CLaser :public CScene2d
{
public:
	CLaser(int nPriorit = 1);	//�R���X�g���N�^
	~CLaser();					//�f�X�g���N�^	
	typedef enum				//�o���b�g���
	{
		LASER_TYPE_PLAYER = 0,
		LASER_TYPE_ENEMY,
		LASER_TYPE_MAX
	}LASER_TYPE;

	static HRESULT	Load(void);						//�e�N�X�`���ǂݍ���
	static void		Unload(void);					//�e�N�X�`���̔j��
	static CLaser	*Create(D3DXVECTOR3 Pos, D3DXVECTOR3 move, LASER_TYPE Type);	//��������

	HRESULT Init(D3DXVECTOR3 move, LASER_TYPE Type);	//����������
	void	Uninit(void);								//�I������
	void	Update(void);								//�X�V����
	void	Draw(void);									//�`�揈��


private:
	bool						m_Hit[MAX_ENEMY];					//�����������Ƃ����邩�H
	D3DXVECTOR3					m_move;				//�ړ���
	static LPDIRECT3DTEXTURE9	m_pTexture;			//�e�N�X�`���̃|�C���^
	int							nLife;				//���̎˒�����
	LASER_TYPE					m_Type;				//���̎��

};
#endif