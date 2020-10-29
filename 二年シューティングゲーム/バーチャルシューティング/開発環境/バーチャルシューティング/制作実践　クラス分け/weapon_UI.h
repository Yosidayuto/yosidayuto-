#ifndef  _WEAPON_UI_H
#define  _WEAPON_UI_H
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "main.h"
#include "scene2d.h"
#include "player.h"
//----------------------------------------------
//�}�N����`
//----------------------------------------------
#define MAX_BUTTON_TEXTURE 2
//------------------------------------
//�O�u����
//------------------------------------
class CUi;
//------------------------------------
//�N���X����
//------------------------------------
class CWeapon_Ui :public CScene2d
{
public:
	CWeapon_Ui(int nPriorit = 3);			//�R���X�g���N�^
	~CWeapon_Ui();			//�f�X�g���N�^


	static CWeapon_Ui*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CPlayer::WEAPON_MODE Type);	//��������
	static HRESULT		Load(void);				//�e�N�X�`���ǂݍ���
	static void			Unload(void);			//�e�N�X�`���̔j��


	HRESULT Init(void);		//����������
	void	Uninit(void);	//�I������
	void	Update(void);	//�X�V����
	void	Draw(void);		//�`�揈��
	void	SetUI(CPlayer::WEAPON_MODE Type);
private:
	static LPDIRECT3DTEXTURE9	m_Texture;	//�e�N�X�`���̃|�C���^
	CPlayer::WEAPON_MODE		m_Type;
	D3DXVECTOR3			m_pos;				//�ʒu
	D3DXVECTOR3			m_size;				//�T�C�Y
	CUi					*m_pUi;				//UI
};
#endif