#ifndef _WARNING_H_
#define _WARNING_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include"main.h"
#include"scene2d.h"

//----------------------------------------------
//�N���X
//----------------------------------------------
class CWarning :public CScene2d
{
public:
	CWarning(int nPriorit = 4);			//�R���X�g���N�^
	~CWarning();			//�f�X�g���N�^	

	static CWarning*Create(D3DXVECTOR3 Pos, D3DXVECTOR3 size);	//��������
	static HRESULT Load(void);		//�e�N�X�`���ǂݍ���
	static void Unload(void);		//�e�N�X�`���̔j��


	HRESULT Init(D3DXVECTOR3 size);				//����������
	void	Uninit(void);			//�I������
	void	Update(void);			//�X�V����
	void	Draw(void);				//�`�揈��

private:
	typedef struct
	{
		LPDIRECT3DTEXTURE9	pTexture;			//�e�N�X�`���̃|�C���^
		char				*pTextName;			//�e�L�X�g��
		int					MaxCount;			//�e�N�X�`���̍ő�R�}��
		int					nCountAnime;		//
		bool				bLoop;				//���[�v���邩
	}ANIME_DATA;
	int						nStopCount;
	static ANIME_DATA		WarningAnim;		//�{�X�A�j��
	int m_nCounterAnim;							//�A�j���[�V�����J�E���^�[
	int m_nPatternAnimX;						//�A�j���[�V�����p�^�[��No


};
#endif