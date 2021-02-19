//=============================================================================
//
//	�e���b�v[telop.h]
//	Author:�g�c�@�I�l
//
//=============================================================================
#ifndef _TELOP_BER_H_
#define _TELOP_BER_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define TELOP_X_SIZE (70)	//�\�������e���b�v�̃T�C�Y�����p
#define TELOP_Y_SIZE (20)	//�\�������e���b�v�̃T�C�Y�����p

//=============================================================================
// �O���錾
//=============================================================================
class CTexture;
typedef enum	//�e���b�v�̎��
{
	TELOP_TYPE_TUTORIAL = 0,// �`���[�g���A��
	TELOP_TYPE_LIFEUP,		// ���C�t�A�b�v
	TELOP_TYPE_SPEEDUP,		// �X�s�[�h�A�b�v
	TELOP_TYPE_BUTTOL,		// �o���b�g
	TELOP_TYPE_LASER,		// ���[�U�[
	TELOP_TYPE_HOMING,		// �z�[�~���O
	TELOP_TYPE_MAX
}TELOP_TYPE;

//=============================================================================
// �N���X��`
//=============================================================================
class CTelop :public CScene2d
{
public:
	CTelop(int nPriorit = PRIORITY_UI_0);						//�R���X�g���N�^
	~CTelop();						//�f�X�g���N�^

	static HRESULT		Load(void);		//�e�N�X�`���ǂݍ���
	static void			Unload(void);	//�e�N�X�`���̔j��
	static CTelop*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//��������

	HRESULT				Init(void);		//����������
	void				Uninit(void);	//�I������
	void				Update(void);	//�X�V����
	void				Draw(void);		//�`�揈��

	TELOP_TYPE			GetTelopType(void);				// �e���b�v�^�C�v�擾
	void				TypeChange(TELOP_TYPE Type);	// �e���b�v�̐ؑց@

private:
	static void			TelopLoad(void);	// �e���b�v���[�h
	static void			TelopUnload(void);	// �e���b�v�A�����[�h

	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
	CScene2d*			m_pTelop;		// �e���b�v�p�̃|�C���^
	TELOP_TYPE			m_TelopType;	// �e���b�v�̃^�C�v
};
#endif