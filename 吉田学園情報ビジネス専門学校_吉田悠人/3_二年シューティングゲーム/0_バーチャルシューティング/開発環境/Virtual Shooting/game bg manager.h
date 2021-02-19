//=============================================================================
//
//	�Q�[���w�i�}�l�[�W���[[game bg manager.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _GAME_BG_MANAGER_H_
#define _GAME_BG_MANAGER_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CGameBgManager :public CScene
{
public:
	CGameBgManager(int nPriorit = PRIORITY_BG_0);	//�R���X�g���N�^
	~CGameBgManager();								//�f�X�g���N�^

	static HRESULT			Load(void);		//�e�N�X�`���ǂݍ���
	static void				Unload(void);	//�e�N�X�`���̔j��
	static CGameBgManager*	Create(void);	//��������

	HRESULT			Init(void);		//����������
	void			Uninit(void);	//�I������
	void			Update(void);	//�X�V����
	void			Draw(void);		//�`�揈��

private:

};
#endif