#ifndef _BOSS_ANIME_H_
#define _BOSS_ANIME_H_
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include"main.h"
#include"scene2d.h"

//----------------------------------------------
//�N���X
//----------------------------------------------
class CBossAnime :public CScene2d
{
public:
	CBossAnime(int nPriorit = 0);			//�R���X�g���N�^
	~CBossAnime();			//�f�X�g���N�^	
	typedef enum  //�A�j�����
	{
		BOSS_ANIME_1 = 0,
		BOSS_ANIME_2,
		BOSS_ANIME_3,
		BOSS_ANIME_4,
		BOSS_ANIME_5,
		BOSS_ANIME_6,

		BOSS_ANIME_MAX
	}BOSS_ANIME;

	static CBossAnime*Create(D3DXVECTOR3 Pos, D3DXVECTOR3 size, BOSS_ANIME Type);	//��������
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
	BOSS_ANIME				m_Type;				//�^�C�v
	static ANIME_DATA		BossAnim[BOSS_ANIME_MAX];	//�{�X�A�j��
	int m_nCounterAnim;							//�A�j���[�V�����J�E���^�[
	int m_nPatternAnimX;						//�A�j���[�V�����p�^�[��No


};
#endif