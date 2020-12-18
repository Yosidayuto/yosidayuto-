#ifndef _LIFE_H_
#define _LIFE_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene.h"
//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define MAX_LIFE 8
#define PRIORIT_LIFE 5
//----------------------------------------------
//�O�u����
//----------------------------------------------
class CScene2d;
class CUi;
//------------------------------------
//�N���X����
//------------------------------------
class CLife :public CScene
{
public:
	CLife(int nPriorit= 3);							//�R���X�g���N�^
	~CLife();							//�f�X�g���N�^

	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);	//�e�N�X�`���̔j��
	static CLife*	Create(D3DXVECTOR3 pos);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��
	void			SetLife(int nLifeNumber);	//���C�t�Z�b�g
	void			SetPos(D3DXVECTOR3 Lifepos);//���C�t�ʒu
	void			DownLife(int nLifeDown);	//�_���[�W���󂯂���
private:
	static LPDIRECT3DTEXTURE9	m_apTexture;				//�e�N�X�`���ւ̃|�C���^
	CScene2d					*m_apScene2D[MAX_LIFE];		//2D�|���S���̐�
	CUi							*m_Ui;						//UI�N���X
	int							nLife;						//���C�t��
	D3DXVECTOR3					pos;						//�ʒu
};



#endif