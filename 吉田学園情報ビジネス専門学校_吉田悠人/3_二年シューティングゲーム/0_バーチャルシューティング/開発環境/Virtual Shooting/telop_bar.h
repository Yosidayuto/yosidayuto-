#ifndef _TELOP_BER_H_
#define _TELOP_BER_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene.h"
//----------------------------------------------
//�}�N����`
//----------------------------------------------

//----------------------------------------------
//�O�u����
//----------------------------------------------
class CScene2d;
//------------------------------------
//�N���X����
//------------------------------------
class CTelopBer :public CScene
{
public:
	CTelopBer();						//�R���X�g���N�^
	~CTelopBer();						//�f�X�g���N�^
	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);	//�e�N�X�`���̔j��
	static CTelopBer	*Create(void);	//��������
	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��
private:
	static LPDIRECT3DTEXTURE9	m_apTexture;		//�e�N�X�`���ւ̃|�C���^
	CScene2d					*m_apScene2D;		//2D�|���S���̐�
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
};
#endif