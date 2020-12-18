//=============================================================================
//
// ���̃e�N�X�`������ [ui.h]
// Author : ��R�@���H
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_
//*****************************************************************************
// �}�N����`
//*****************************************************************************
//1P�̃e�N�X�`��
#define UI_TEXTURE_CAT	"data/TEXTURE/cat001.png"// �|���S���̃e�N�X�`���p�X
#define UI_TEXTURE_1P	"data/TEXTURE/playerui_001.png"// �|���S���̃e�N�X�`���p�X
//2P�̃e�N�X�`��
#define UI_TEXTURE_DOG	"data/TEXTURE/dog001.png"// �|���S���̃e�N�X�`���p�X
#define UI_TEXTURE_2P "data/TEXTURE/playerui_002.png"// �|���S���̃e�N�X�`���p�X
//3P�̃e�N�X�`��	 _
#define UI_TEXTURE_USAGI "data/TEXTURE/usa001.png"// �|���S���̃e�N�X�`���p�X
#define UI_TEXTURE_3P "data/TEXTURE/playerui_003.png"// �|���S���̃e�N�X�`���p�X
//4P�̃e�N�X�`��	 _
#define UI_TEXTURE_RISU "data/TEXTURE/risu001.png"// �|���S���̃e�N�X�`���p�X
#define UI_TEXTURE_4P "data/TEXTURE/playerui_004.png"// �|���S���̃e�N�X�`���p�X
//�^�[���e�N�X�`��_ 
#define UI_TEXTURE_YOUTRUN "data/TEXTURE/yourturn.png"// �|���S���̃e�N�X�`���p�X
#define UI_TEXTURE_WAIT "data/TEXTURE/wait.png"// �|���S���̃e�N�X�`���p�X
//���S�e�N�X�`��  _ 
#define UI_TEXTURE_DEATH "data/TEXTURE/death.png"// �|���S���̃e�N�X�`���p�X

//�����e�N�X�`��
#define UI_TEXTURE_WINS_1P "data/TEXTURE/Wins_1P.png"// �|���S���̃e�N�X�`���p�X
#define UI_TEXTURE_WINS_2P "data/TEXTURE/Wins_2P.png"// �|���S���̃e�N�X�`���p�X
#define UI_TEXTURE_WINS_3P "data/TEXTURE/Wins_3P.png"// �|���S���̃e�N�X�`���p�X
#define UI_TEXTURE_WINS_4P "data/TEXTURE/Wins_4P.png"// �|���S���̃e�N�X�`���p�X
//���[�h�e�N�X�`��
#define UI_TEXTURE_LOAD "data/TEXTURE/brush1.png"// �|���S���̃e�N�X�`���p�X


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// �|���S���N���X
//*****************************************************************************
class CUi : public CScene2D
{
public:
	typedef enum
	{
		TEX_LOAD = 0,
		TEX_DOG,
		TEX_CAT,
		TEX_RABBIT,
		TEX_SQUIRREL,
		TEX_1P,
		TEX_2P,
		TEX_3P,
		TEX_4P,
		TEX_YOUTRUN,
		TEX_WAIT,
		TEX_DEATH,
		TEX_WINS_1P,
		TEX_WINS_2P,
		TEX_WINS_3P,
		TEX_WINS_4P,
		TEX_MAX
	}TEXTYPE;
	CUi();													// �R���X�g���N�^
	~CUi();													// �f�X�g���N�^
	static HRESULT Load(void);									// �e�N�X�`���ǂݍ���
	static void Unload(void);									// �e�N�X�`���j��
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXTYPE TYPE);	// �쐬����
	TEXTYPE GetTexType(TEXTYPE TYPE);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	void LoadPos(void);
private:

	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_MAX];				// �e�N�X�`���̃|�C���^

	TEXTYPE TexType;
	D3DXVECTOR3 m_pos;											// �ʒu
	D3DXVECTOR3 m_size;											// �T�C�Y
	D3DXVECTOR3 m_Minsize;                                      // �ŏ��T�C�Y
	static char *m_TextureName[TEX_MAX];						// �e�N�X�`���l�[��
	bool m_bBig;                                                // �傫������
	bool m_bLoad;
};
#endif // !_UI_H_



