//=============================================================================
//
// �{�X�G�t�F�N�g�x�[�X���� [boss effect base.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _BOSS_EFFECT_H_
#define _BOSS_EFFECT_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"scene2d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CBossEffectBase :public CScene2d
{
public:
	CBossEffectBase(int nPriorit = PRIORITY_OBJECT_1);	//�R���X�g���N�^
	~CBossEffectBase();									//�f�X�g���N�^	

	static HRESULT Load(void);	//�e�N�X�`���ǂݍ���
	static void Unload(void);	//�e�N�X�`���̔j��

	HRESULT Init(void);			//����������
	void	Uninit(void);		//�I������
	void	Update(void);		//�X�V����
	void	Draw(void);			//�`�揈��

	void	SetMaxTexture(int nMaxTexture);		//�e�N�X�`���̍ő�R�}���Z�b�^�[
	int		GetMaxTexture(void);				//�e�N�X�`���̍ő�R�}���Q�b�^�[
	void	SetCountAnime(int nCountAnime);		//�A�j���[�V�����J�E���g�Z�b�^�[
	int		GetCountAnime(void);				//�A�j���[�V�����J�E���^�Q�b�^�[
	void	SetLoop(bool bLoop);				//���[�v�Q�b�^�[
	bool	GetLoop(void);						//���[�v�Z�b�^�[
private:
	int		m_nMaxCount;			// �e�N�X�`���̍ő�R�}��
	int		m_nMaxCountAnime;		// �A�j���[�V�����ő�J�E���g
	int		m_nCounterAnim;			// �A�j���[�V�����J�E���^�[
	int		m_nPatternAnimX;		// �A�j���[�V�����p�^�[��No

	bool	m_bLoop;				// ���[�v���邩

};
#endif