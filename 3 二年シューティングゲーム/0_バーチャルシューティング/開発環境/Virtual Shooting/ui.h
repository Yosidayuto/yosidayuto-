#ifndef  _UI_H
#define  _UI_H
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene2d.h"
//------------------------------------
//�}�N����`
//------------------------------------
//------------------------------------
//�N���X����
//------------------------------------
class CUi
{
public:

	CUi();															//�R���X�g���N�^
	~CUi();															//�f�X�g���N�^
	typedef enum
	{
		TEXTURE_TYPE_SCORE = 0,
		TEXTURE_TYPE_LIFE,
		TEXTURE_TYPE_BULLET,
		TEXTURE_TYPE_LASER,
		TEXTURE_TYPE_HOMING,
		TEXTURE_TYPE_MAX
	}CUI_TYPE;

	static HRESULT	Load(void);														//�e�N�X�`���ǂݍ���
	static void		Unload(void);													//�e�N�X�`���̔j��
	static CUi*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTexture);		//��������

	HRESULT			Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTexture);		//����������
	void			Uninit(void);									//�I������
	void			Update(void);									//�X�V����
	void			Draw(void);										//�`�揈��
private:

	static char						*pTexture[TEXTURE_TYPE_MAX];				//�e�L�X�g��
	static LPDIRECT3DTEXTURE9		m_pTexture[TEXTURE_TYPE_MAX];			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	int								m_nTexture;				//���l
};




#endif