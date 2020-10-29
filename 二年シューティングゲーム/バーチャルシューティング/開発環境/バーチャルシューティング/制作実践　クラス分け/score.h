#ifndef  SCORE_H
#define  SCORE_H
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene2d.h"

//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define MAX_SCORE 8//�X�R�A�p�l���̍ő吔

class CUi;
class CNumber;
//------------------------------------
//�N���X����
//------------------------------------
class CScore :public CScene
{
public:
	CScore(int nPriorit = 5);			//�R���X�g���N�^
	~CScore();			//�f�X�g���N�^


	static CScore*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,BOOL UI);	//��������


	HRESULT Init(void);		//����������
	void	Uninit(void);	//�I������
	void	Update(void);	//�X�V����
	void	Draw(void);		//�`�揈��

	void	SetScore(int nScore);
	void	ColChange(D3DXCOLOR col);
	void	AddScore(int nValue);
	int		GetScore(void);

	//void ScoreEffect(int nScore);

private:
	bool						UiSwitch;
	CUi							*m_apUi;
	CNumber						*m_apNumber[MAX_SCORE];
	int							m_nScore;
	D3DXVECTOR3					m_pos;
	D3DXVECTOR3					m_size;
};
#endif