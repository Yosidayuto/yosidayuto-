//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : �U�J �����Y�@�g�c �I�l
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "polygon.h"
#include "mouse_pointer.h"
#include "communication.h"
#include "manager.h"
#include "fade.h"
#include "turn wait.h"
#include "ui.h"
#include "death.h"
#include "die screen.h"
#include "sound.h"
//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CCommunication * CGame::pCommunication = NULL;
CPolygon * CGame::pPolgon = NULL;
bool CGame::m_bLoad = false;
bool CGame::m_bPlayerDie[4] = {};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	//�ϐ�������
	Mode = MODE_CONTINUE;					
	m_bSelect = false;						
	m_nTouch = MAX_NUMBER;
	CommuMode = COMMUNICATTION_MODE_GAME;
	m_pUi = NULL;
	m_pDieScreen = NULL;
	for (int nCount = 0; nCount < 4; nCount++)
	{
		m_bPlayerDie[nCount] = false;
	}
	m_bLoad = false;
	pCommunication = NULL;
	pPolgon = NULL;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// �쐬����
//=============================================================================
CGame * CGame::Create(D3DXVECTOR3 size)
{
	CGame *pGame;
	//�C���X�^���X����
	pGame = new CGame;

	//����������
	if (pGame != NULL)
	{
		pGame->Init(size);
	}

	return pGame;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 size)
{
	//�w�i����
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	//�ʐM�f�[�^�̎擾
	pCommunication = CManager::GetCommunication();
	//��̐���
	pPolgon = CPolygon::Create(D3DXVECTOR3(TEXTURE_WIDTH, TEXTURE_HEIGHT, 0.0f));
	//�}�E�X�|�C���^�[����
	CPointer::Create();

	//UI
	//�g
	CUi::Create(D3DXVECTOR3(150, 75, 0), D3DXVECTOR3(300, 175, 0), CUi::TEX_1P);
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 150, 75, 0), D3DXVECTOR3(300, 175, 0), CUi::TEX_2P);
	CUi::Create(D3DXVECTOR3(150, SCREEN_HEIGHT - 90, 0), D3DXVECTOR3(300, 175, 0), CUi::TEX_3P);
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 150, SCREEN_HEIGHT - 90, 0), D3DXVECTOR3(300, 175, 0), CUi::TEX_4P);


	//�L�����N�^�[
	CUi::Create(D3DXVECTOR3(75, 75, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_CAT);
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 75, 75, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_DOG);
	CUi::Create(D3DXVECTOR3(75, SCREEN_HEIGHT - 90, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_RABBIT);
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 75, SCREEN_HEIGHT - 90, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_SQUIRREL);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	CSound *pSound = CManager::GetSound();
	//�Q�[����
	switch (CommuMode)
	{
	case COMMUNICATTION_MODE_GAME:
		//������������
		if (pCommunication->GetMode() != MODE_CONTINUE)
		{
			//�����������ꍇ
			pCommunication->SetMode(MODE_SETTLED);
			CommuMode = COMMUNICATTION_MODE_WINNER;
		}
		else
		{
			//���Ȃ������ꍇ
			CommuMode = COMMUNICATTION_MODE_TURN;
		}
		break;

	case COMMUNICATTION_MODE_TURN:
		//�v���C���[��l�ЂƂ�̐����m�F
		if (pCommunication->GetnDie()!=-1)
		{
			//�v���C���[�P�̏���
			if (pCommunication->GetnDie() == 0 && m_bPlayerDie[0] == false)
			{
				m_bPlayerDie[0] = true;
				CUi::Create(D3DXVECTOR3(75, 75, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_DEATH);
			}
			//�v���C���[�Q�̏���
			if (pCommunication->GetnDie() == 1 && m_bPlayerDie[1] == false)
			{
				m_bPlayerDie[1] = true;
				CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 75, 75, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_DEATH);
			}
			//�v���C���[�R�̏���
			if (pCommunication->GetnDie() == 2 && m_bPlayerDie[2] == false)
			{
				m_bPlayerDie[2] = true;
				CUi::Create(D3DXVECTOR3(75, SCREEN_HEIGHT - 90, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_DEATH);
			}
			//�v���C���[�S�̏���
			if (pCommunication->GetnDie() == 3 && m_bPlayerDie[3] == false)
			{
				m_bPlayerDie[3] = true;
				CUi::Create(D3DXVECTOR3(SCREEN_WIDTH - 75, SCREEN_HEIGHT - 90, 0), D3DXVECTOR3(125, 125, 0), CUi::TEX_DEATH);
			}
		}
		//���s�����܂���������
		if (pCommunication->GetbRecv() == true)
		{
			//UI�̏���
			if (m_pUi != NULL)
			{
				m_pUi->Uninit();
				m_pUi = NULL;
			}
			//�Q�[�����[�h����
			CommuMode = COMMUNICATTION_MODE_GAME;
			pCommunication->SetbRecv();

		}
		//���������񂾂Ƃ��̉�ʉ��o
		if (pCommunication->GetbPlayer() == false)
		{
			if (m_pDieScreen==NULL)
			{
				//���񂾉��o
				m_pDieScreen = CDieScreen::Create();
				//���݂�SE
				pSound->Play(CSound::SOUND_LABEL_SE_BYTE);
				//���S�A�j���[�V����
				CDeath::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f))->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));

			}

		}

		//�����̃^�[��
		if (pCommunication->GetnPlayer() == 0)
		{
			//�^�[���\����UI
			if (m_pUi == NULL)
			{
				m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0), D3DXVECTOR3(650, 100, 0), CUi::TEX_YOUTRUN);
			}
			if (pCommunication->GetbPlayer() == true)//�����Ă�ꍇ
			{
				//�I�񂾎�����
				int nTooth = pPolgon->Touch();
				if (m_nTouch != CPolygon::GetTooth())
				{
					if (CCommunication::GetabTooth(nTooth) == true)
					{
						//�|��SE
						pSound->Play(CSound::SOUND_LABEL_SE_CLEAN);		
						pCommunication->PicPlayer(nTooth);
						m_nTouch = CPolygon::GetTooth();

						//����M
						if (m_bLoad == false)
						{
							std::thread thWorker(Load);
							thWorker.detach();
						}
					}
				}
			}
			else//����ł�ꍇ
			{

				//�I�����������𑗂�
				pCommunication->PicPlayer(-1);
				if (m_bLoad == false)
				{
					std::thread thWorker(Load);
					thWorker.detach();
				}
			}
		}
		//�����ȊO�̃^�[��
		else
		{
			//�^�[���\����UI
			if (m_pUi == NULL&&m_pDieScreen==NULL)
			{
				m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0), D3DXVECTOR3(700, 100, 0), CUi::TEX_WAIT);
			}

			if (m_bLoad == false)
			{
				std::thread thWorker(Load);
				thWorker.detach();
			}

		}
		break;
		//��������
	case COMMUNICATTION_MODE_WINNER:
		//����
		if (pCommunication->GetMode() == MODE_SETTLED)
		{
			CFade *pFade = CManager::GetFade();
			pCommunication->Winner();
			pFade->SetFade(CManager::MODE_RESULT);
		}
		break;


	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// ���[�h����
//=============================================================================
void CGame::Load(void)
{
	//���[�h�������J�n
	m_bLoad = true;
	//����M
	pCommunication->RecvPlayer();
	//��M�������̏���
	if (CCommunication::GetnTooth() != -1)
	{
		pPolgon->TouchCol(CCommunication::GetnTooth());
	}
	//���[�h�����I��
	m_bLoad = false;
}

//=============================================================================
// �v���C���[������ł��邩�̊m�F�֐�
//=============================================================================
bool CGame::GetPlayerDie(int nPlayer)
{
	return m_bPlayerDie[nPlayer];
}


