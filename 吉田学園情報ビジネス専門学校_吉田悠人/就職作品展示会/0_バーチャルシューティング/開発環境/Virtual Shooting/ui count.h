//=============================================================================
//
//	�J�E���gUI[ui count.h]
//	Author:�g�c�@�I�l
//
//=============================================================================
#ifndef _UI_COUNT_H_
#define _UI_COUNT_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "manager.h"
#include "number.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CUiCount :public CScene
{
public:

	CUiCount(int nPriorit = PRIORITY_UI_1);			//�R���X�g���N�^
	~CUiCount();						//�f�X�g���N�^
	static CUiCount*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, PRIORITY priority = PRIORITY_UI_1);
	HRESULT			Init(void);				//����������
	void			Uninit(void);			//�I������
	void			Update(void);			//�X�V����
	void			Draw(void);				//�`�揈��
	void			SetCount(int nCount);	//�J�E���g�Z�b�^�[
	void			SetCol(D3DXCOLOR col);	//�J���[�Z�b�^�[
private:
	CNumber*		m_apNumber;
	int				m_nCount;

	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_size;

};
#endif