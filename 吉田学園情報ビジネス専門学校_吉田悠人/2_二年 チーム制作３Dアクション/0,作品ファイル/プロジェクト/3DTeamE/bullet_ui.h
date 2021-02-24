//=============================================================================
//
// �eUi���� [bullet_ui.h]
// Author : ��R�@���H
//
//=============================================================================
#ifndef _BULLET_UI_H_
#define _BULLET_UI_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
#include "object2d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_UI_TEXTURE 	"Data/Texture/bullet2.png"	//�ǂݍ��ޗp�̒e�e�N�X�`��
#define BULLET_TEXTURE_MAX 1
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBullet_ui :public CObject2D
{
public:
	CBullet_ui();
	~CBullet_ui();
	static HRESULT Load(void);
	static void Unload(void);
	static CBullet_ui * Create(D3DXVECTOR3 pos);//(D3DXVECTOR3 pos, float frot, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[BULLET_TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^
	static char *m_cFileName[BULLET_TEXTURE_MAX];			//�t�@�C���̖��O

	D3DXVECTOR3 m_pos;
	float m_frot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;

};
#endif