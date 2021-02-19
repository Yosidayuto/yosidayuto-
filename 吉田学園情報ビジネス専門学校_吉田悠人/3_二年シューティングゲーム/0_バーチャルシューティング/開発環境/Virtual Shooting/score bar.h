//=============================================================================
//
//	�X�R�A�w�i[score bar.h]
//	Author:�g�c�@�I�l
//
//=============================================================================
#ifndef _SCORE_BAR_H_
#define _SCORE_BAR_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "texture.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CScoreBar :public CTexture
{
public:
	CScoreBar();	//�R���X�g���N�^
	~CScoreBar();	//�f�X�g���N�^

	static HRESULT			Load(void);
	static void				Unload(void);
	static CScoreBar*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			Draw(void);		// �`�揈��
private:
	static TEXTURE_ICON	m_TextureData;	// �e�N�X�`���f�[�^
};
#endif
