#ifndef _FADE_H
#define _FADE_H
//------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------
#include"main.h"
#include"manager.h"
//----------------------------------------------
//�V�[���N���X
//----------------------------------------------
class CFade
{
public:
	CFade();
	~CFade();
	typedef enum
	{
		FADE_NONE = 0,		//�����Ȃ����
		FADE_IN,			//�t�F�[�h����
		FADE_OUT,			//�t�F�[�h�A�E�g����
		FADE_MAX
	}FADE;

	//static CFade *Create(CManager::GAME_MODE modeNext);	//��������

	HRESULT Init(/*CManager::GAME_MODE modeNext*/void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Set(CManager::GAME_MODE modeNext);
	FADE Get(void);
private:

	FADE						m_Fade;					//�t�F�[�h���
	D3DXCOLOR					m_Color;				//�t�F�[�h�F
	CManager::GAME_MODE			m_ModeNext;				//���̉�ʁi���[�h�j
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture;	//�e�N�X�`���̃|�C���^
	bool						m_bFade;

};

#endif