#ifndef  _NUMBER_H
#define  _NUMBER_H
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------
//�N���X����
//------------------------------------
class CNumber 
{
public:

	CNumber();		//�R���X�g���N�^
	~CNumber();		//�f�X�g���N�^
	static HRESULT	Load(void);		//�e�N�X�`���ǂݍ���
	static void		Unload(void);	//�e�N�X�`���̔j��
	static CNumber*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//��������

	HRESULT Init(void);				//����������
	void	Uninit(void);			//�I������
	void	Update(void);			//�X�V����
	void	Draw(void);				//�`�揈��
	void	SetNumber(int nNumber);
	void	ColChange(D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
};




#endif