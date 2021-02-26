//=============================================================================
//
// �X�R�A���� [score.h]
// Author : �g�c �I�l
//
//=============================================================================

#ifndef  _SCORE_H_
#define  _SCORE_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_SCORE (8)//�X�R�A�p�l���̍ő吔

//=============================================================================
//�O���錾
//=============================================================================
class CUi;
class CNumber;
class CScoreBar;
//=============================================================================
// �N���X��`
//=============================================================================
class CScore :public CScene
{
public:
	CScore(int nPriorit = PRIORITY_UI_3);	//�R���X�g���N�^
	~CScore();								//�f�X�g���N�^

	static CScore*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,bool UI, PRIORITY priority = PRIORITY_UI_3);	//��������


	HRESULT Init(void);		//����������
	void	Uninit(void);	//�I������
	void	Update(void);	//�X�V����
	void	Draw(void);		//�`�揈��

	void	SetScore(int nScore);
	void	ColChange(D3DXCOLOR col);
	void	AddScore(int nValue);
	int		GetScore(void);

private:
	bool						UiSwitch;				//�w�i�����邩
	CScoreBar*					m_pScoreBar;				//�w�i
	CNumber						*m_apNumber[MAX_SCORE];	//�i���o�[�N���X
	int							m_nScore;				//�X�R�A
	D3DXVECTOR3					m_pos;					//�ʒu
	D3DXVECTOR3					m_size;					//�T�C�Y
};
#endif