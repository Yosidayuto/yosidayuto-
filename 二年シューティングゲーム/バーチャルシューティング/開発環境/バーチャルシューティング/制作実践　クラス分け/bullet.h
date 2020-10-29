#ifndef _BULLET_H_
#define _BULLET_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include"main.h"
#include"scene2d.h"

//----------------------------------------------
//�N���X
//----------------------------------------------
class CBullet :public CScene2d
{
public:
	CBullet(int nPriorit = 1);			//�R���X�g���N�^
	~CBullet();			//�f�X�g���N�^	
	typedef enum  //�o���b�g���
	{
		BULLET_TYPE_PLAYER = 0,
		BULLET_TYPE_ENEMY,
		BULLET_TYPE_BOSS,
		BULLET_TYPE_MAX
	}BULLET_TYPE;


	HRESULT Init(D3DXVECTOR3 move, BULLET_TYPE Type);	//����������
	void	Uninit(void);			//�I������
	void	Update(void);			//�X�V����
	void	Draw(void);				//�`�揈��
	static CBullet*
		Create(D3DXVECTOR3 Pos, D3DXVECTOR3 move, BULLET_TYPE Type);	//��������
	static HRESULT Load(void);		//�e�N�X�`���ǂݍ���
	static void Unload(void);		//�e�N�X�`���̔j��
private:
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_move;					//�ړ���
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^
	int	nLife;								//���̎˒�����
	BULLET_TYPE m_Type;						//���̎��
};
#endif