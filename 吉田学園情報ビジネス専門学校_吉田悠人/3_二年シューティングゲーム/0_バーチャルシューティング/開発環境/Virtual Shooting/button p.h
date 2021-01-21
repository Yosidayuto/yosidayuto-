//=============================================================================
//
//	�{�^���i���j[button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _BUTTONP_H_
#define _BUTTONP_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

typedef enum  //�{�^���e�N�X�`�����
{
	BUTTON_NORMAL =0,
	BUTTON_PUSH,
	BUTTON_MAX
}BUTTON_STATE;

//=============================================================================
// �N���X��`
//=============================================================================
class CButtonp :public CScene2d
{
public:

	CButtonp(int nPriorit = 0);			//�R���X�g���N�^
	~CButtonp();						//�f�X�g���N�^
	static HRESULT	Load(void);
	static void		Unload(void);

	HRESULT		Init(void);				//����������
	void		Uninit(void);			//�I������
	void		Update(void);			//�X�V����
	void		Draw(void);				//�`�揈��
	bool		Hit(void);				//�����蔻��

private:
	static TEXTURE_DATA	m_TextureData[BUTTON_MAX];	//�e�N�X�`���f�[�^
	CScene2d*			m_pScene2d;					//�I�u�W�F�N�g�|�C���^
};
#endif
