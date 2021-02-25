//=============================================================================
//
// �}�Y���t���b�V�� [muzzleflash.h]
// Author : ��K������
//
//=============================================================================
#ifndef _MUZZLEFLASH_H_
#define _MUZZLEFLASH_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
#include "billboard.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MUZZLEFLASH_TEXTURE 	"Data/Texture/explosion.png"	//�����e�N�X�`���̕ۑ���
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMuzzleflash :public CBillboard
{
public:
	CMuzzleflash();
	~CMuzzleflash();
	static HRESULT Load(void);
	static void Unload(void);
	static CMuzzleflash * Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size,D3DXCOLOR col);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;
};
#endif