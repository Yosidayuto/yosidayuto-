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
class CUiCount;
//------------------------------------
//�N���X����
//------------------------------------
class CResult :public CScene
{
public:
	CResult(int nPriorit = PRIORITY_RESULT);	//�R���X�g���N�^
	~CResult();	//�f�X�g���N�^


	static CResult*	Create(STAGE_TYPE stage);	//��������

	HRESULT			Init(void);									//����������
	void			Uninit(void);								//�I������
	void			Update(void);								//�X�V����
	void			Draw(void);									//�`�揈��
	void			ReadFile(STAGE_TYPE Stage);					//�����L���O�f�[�^�ǂݍ���
	void			WriteFile(STAGE_TYPE Stage);				//�����L���O�f�[�^��������
	int				SetRanking(int nScore, STAGE_TYPE Stage);	//�X�R�A���Ƃ炵���킹��

private:
	STAGE_TYPE	m_Stage;						//���݂̃X�e�[�W
	CScore*		m_Score[MAX_RANKING];		//�X�R�A�N���X
	CUiCount*	m_pUiCount[MAX_RANKING];	//UI�J�E���g�N���X
	int			nScoreData[MAX_RANKING];	//�L�^���ꂽ�X�R�A
	int			nScore;						//���݂̃X�R�A
	static char *pTexture[STAGE_TYPE_MAX];	//�e�L�X�g��
};


#endif