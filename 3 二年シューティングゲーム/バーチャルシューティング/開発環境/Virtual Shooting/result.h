#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"
#include "game.h"
//------------------------------------
//�}�N����`
//------------------------------------
#define MAX_RANKING 9

//------------------------------------
//�O�u����
//------------------------------------
class CScore;
class CNumber;
//------------------------------------
//�N���X����
//------------------------------------
class CResult :public CScene
{
public:
	CResult(int nPriorit = 5);	//�R���X�g���N�^
	~CResult();	//�f�X�g���N�^


	static CResult*	Create(void);	//��������

	HRESULT			Init(void);				//����������
	void			Uninit(void);			//�I������
	void			Update(void);			//�X�V����
	void			Draw(void);				//�`�揈��
	void			ReadFile(CGame::STAGE_TYPE Stage);			//�����L���O�f�[�^�ǂݍ���
	void			WriteFile(CGame::STAGE_TYPE Stage);		//�����L���O�f�[�^��������
	int				SetRanking(int nScore, CGame::STAGE_TYPE Stage);	//�X�R�A���Ƃ炵���킹��

private:
	CScore	*m_Score[MAX_RANKING];				//�X�R�A�N���X
	CNumber *m_pNumber[MAX_RANKING];			//�i���o�[�N���X
	int nScoreData[MAX_RANKING];				//�L�^���ꂽ�X�R�A
	int nScore;									//���݂̃X�R�A
	static char *pTexture[CGame::STAGE_TYPE_MAX];	//�e�L�X�g��
};


#endif