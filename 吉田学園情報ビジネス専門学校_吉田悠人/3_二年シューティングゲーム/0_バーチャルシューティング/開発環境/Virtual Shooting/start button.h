//=============================================================================
//
//	�X�^�[�g�{�^��[start button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _START_BUTTON_H_
#define _START_BUTTON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "button.h"

//=============================================================================
//�O���錾
//=============================================================================
class CNumber;

//=============================================================================
// �N���X��`
//=============================================================================
class CStartButton :public CButton
{
public:

	CStartButton(int nPriorit = PRIORITY_UI_1);	//�R���X�g���N�^
	~CStartButton();							//�f�X�g���N�^
	static HRESULT			Load(void);
	static void				Unload(void);
	static CStartButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,int nStage);


	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			Draw(void);		// �`�揈��

	void			SetStage(int stage);	//�X�e�[�W�ԍ��Q�b�^�[
	void			MouseOver(void);		// �}�E�X�I�[�o�[����
	void			Push(void);				// �v�b�V�����菈��
private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
	CNumber*			m_pNumber;		// �i���o�[
	bool				m_bPush;		// �{�^������������
	int					nStage;			// �X�e�[�W�ԍ�
};
#endif
