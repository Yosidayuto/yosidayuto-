//=============================================================================
//
// ���C������ [clean.h]
// Author : ��R���H
//�|���S������
//=============================================================================
#ifndef _CLEAN_H_
#define _CLEAN_H_


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ANIMATION (10)
#define CLEAN_TEXTURE "data/TEXTURE/aa.png"		// �e�N�X�`���p�X


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include"scene2d.h"



class CClean :public CScene2D
{
public:
	CClean();
	~CClean();

	static HRESULT Load(void);
	static void Unload(void);
	static CClean *Create(D3DXVECTOR3 size);

	HRESULT Init(D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̃|�C���^
	int m_nCountAnime;								// �J�E���^�[
	int m_nPatternAnime;							// �p�^�[��No
};

#endif // !_EXPLOSION_H_
