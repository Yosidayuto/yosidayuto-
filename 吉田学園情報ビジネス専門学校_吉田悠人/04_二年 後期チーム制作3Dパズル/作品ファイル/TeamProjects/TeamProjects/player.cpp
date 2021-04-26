//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : 
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "player.h"
#include "resource manager.h"
#include "manager.h"
#include "inputcontroller.h"
#include "inputkeyboard.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"
#include "child.h"
#include "item block base.h"
#include "hindrance block base.h"
#include "particle.h"
#include "talk_base.h"
#include "game.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "sound.h"
#include "tile block base.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_FILE		("Data/Model/Player/Player.x")		// �t�@�C����
#define PLAYER_HEIGHT	(25.0f)                             // �v���C���[�̍���
#define PLAYER_SPEED	(5)							        // �v���C���[�̃X�s�[�h
#define PLAYERL_RANGE	(25.0f)								// �v���C���[�̓����蔻��̍L��

#define MOVE_FRAME      (20.0f)                             // ���̈ړ��̃t���[����
#define MOVE_DISTANCE   (50.0f / (MOVE_FRAME+1))            // ���̈ړ��̋���
#define ADD_ROT_VALU    (D3DXToRadian(90)/MOVE_FRAME)       // ��]��
#define MOVE_Y_VALU     ((sqrtf(powf(50.0f , 2.0f) + powf(50.0f, 2.0f)) / 2) - PLAYER_HEIGHT)	// �ړ���Y
#define MOVE_Y_VALU2    ((sqrtf(powf(100.0f , 2.0f) + powf(50.0f, 2.0f)) / 2) - PLAYER_HEIGHT)	// �ړ���Y) // �ړ���Y

#define MOVE_JOYPAD_EFFECT_FRAME 13    // �ړ����R���g���[���[���U������|�C���g
//=============================================================================
// �ÓI�����o�ϐ�������
//=============================================================================
CPlayer*CPlayer::m_pPlayer = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer()
{
	
	//���f���f�[�^�̏�����
	SetObjType(OBJTYPE_PLAYER);

	m_model				= NULL;
	m_Move				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);        // �ړ��ʂ̏�����
	m_nMoveFrameCount	= 0;                                    // �ړ��t���[�����̃J�E���g�p
	m_nFallFrameCount	= 0;									// �����t���[�����̃J�E���g�p
	m_bPlayer			= false;								// �v���C���[�̍s������
	m_bActiveMove		= false;                                // �ړ������̔���p
	m_bFallMove			= false;								// ���������̔���p
	m_bError			= false;								// �G���[���̔���p
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, 0.0f, 0.0f);// ��]�s��
	m_pChild			= NULL;                                 // �������Ă���I�u�W�F�N�g
	m_movePattern		= STICKY_NONE;							// �ړ��p�^�[��

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
	m_pPlayer = NULL;
}


//=============================================================================
// �����֐�
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	if (m_pPlayer == NULL)
	{
		m_pPlayer = new CPlayer;

		//NULL�`�F�b�N
		if (m_pPlayer != NULL)
		{
			//�ʒu�ݒ�
			m_pPlayer->SetPosition(D3DXVECTOR3(pos.x, pos.y + PLAYER_HEIGHT, pos.z));
			//�����ݒ�
			m_pPlayer->SetRotation(rot);
			//�J���[�ݒ�
			m_pPlayer->SetScale(size);
			//����������
			m_pPlayer->Init();
		}
	}
	return m_pPlayer;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(m_nModel);
	//���[���h�ϊ��s��̏�����
	D3DXMatrixIdentity(&Model.mtxWorld);
	// ���f������
	m_model = new CModel;
	if (m_model != NULL)
	{
		m_model->SetPosition(GetPosition());
		m_model->SetRotation(GetRotation());
		m_model->SetScale(GetScale());
		m_model->SetModelData(Model);
		m_model->Init();
	}
	SetPriority(PRIORITY_OBJECT_PLAYER);
	m_model->SetPriority(PRIORITY_OBJECT_PLAYER);
	m_bPlayer = true;

	////////////////////
	m_pChild = CChild::Create(m_model, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	////////////////////
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CPlayer::Uninit(void)
{
	//NULL�`�F�b�N
	if (m_model != NULL)
	{
		m_model->Uninit();
	}

	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CPlayer::Update(void)
{
	//�s���������������Ă��Ȃ��Ƃ�
	if (m_bPlayer == false)
	{
		// ���쏈��
		Control();
		// ��������
		Fall();
		// �ړ�����
		Move();
		//���f���̈ʒu�Z�b�g
		m_model->SetPosition(GetPosition());
	}

	// �`���C���h�̃��[���h���W�擾
	CModel::MODELDATA modelData = m_pChild->GetModel()->GetModelData();
	D3DXVECTOR3 childPos = D3DXVECTOR3(modelData.mtxWorld._41, modelData.mtxWorld._42, modelData.mtxWorld._43);
	//�p�[�e�B�N���̐���
	if (rand() % 3 == 0 && 0 < childPos.y&&m_pChild->GetIsActive() == false)
	{
		CParticle *pParticle = CParticle::Cretae(childPos, m_model->GetPosition(), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CParticle::PARTICLE_TYPE_1);
	}

	// ���[���h�s��v�Z�ϊ�
	ExchangeWorldMtx();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CPlayer::Draw(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

	CModel::MODELDATA modelData = m_model->GetModelData();
	
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &modelData.mtxWorld);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	if (modelData.pBuffMat != NULL)
	{
		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)modelData.pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)modelData.nNumMat; nCntMat++)
		{
			//�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
			pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// �e�N�X�`��
			pDevice->SetTexture(0, modelData.pTexture[nCntMat]);
			//���f���p�[�c�̕`��
			modelData.pMesh->DrawSubset(nCntMat);
		}
	}


}


//******************************
// �L�[���쏈��
//******************************
void CPlayer::Control(void)
{
	if (!m_bActiveMove&&!m_bFallMove)
	{// �ړ�������Ȃ��Ƃ�+����������Ȃ��Ƃ�
	  //�L�[�{�[�h���͂̎擾
		CInputKeyboard* pKeyInput = (CInputKeyboard*)CManager::GetInputKey();
		
		// �R���g���[���[�\���L�[�̒l�̎擾
		CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
		WORD joyCross = CROSS_KEY_NEUTRAL;
		if (pJoyInput != NULL) joyCross = (WORD)pJoyInput->GetJoyStick().rgdwPOV[0];

		//�G���[���̐ؑ֊֐�
		ErrorStatus();

		if (pKeyInput->GetKeyPress(DIK_W)|| joyCross == CROSS_KEY_UP)
		{
			// ��]�s��̐ݒ�
			D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, -ADD_ROT_VALU, 0.0f);
			// �ړ��ʂ̐ݒ�
			m_Move = D3DXVECTOR3(0.0f, 0.0f, -MOVE_DISTANCE);

			// �J�E���g�̏�����
			m_nMoveFrameCount = 0;
			// �ړ����t���O��true
			m_bActiveMove = true;

		}
		if (pKeyInput->GetKeyPress(DIK_S) || joyCross == CROSS_KEY_DOWN)
		{
			// ��]�s��̐ݒ�
			D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, ADD_ROT_VALU, 0.0f);

			// �ړ��ʂ̐ݒ�
			m_Move = D3DXVECTOR3(0.0f, 0.0f, MOVE_DISTANCE);

			// �J�E���g�̏�����
			m_nMoveFrameCount = 0;
			// �ړ����t���O��true
			m_bActiveMove = true;
		}
		if (pKeyInput->GetKeyPress(DIK_A) || joyCross == CROSS_KEY_LEFT)
		{
			// ��]�s��̐ݒ�
			D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, 0.0f, -ADD_ROT_VALU);

			// �ړ��ʂ̐ݒ�
			m_Move = D3DXVECTOR3(MOVE_DISTANCE, 0.0f, 0.0f);

			// �J�E���g�̏�����
			m_nMoveFrameCount = 0;

			// �ړ����t���O��true
			m_bActiveMove = true;
		}
		if (pKeyInput->GetKeyPress(DIK_D) || joyCross == CROSS_KEY_RIGHT)
		{
			// ��]�s��̐ݒ�
			D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, 0.0f, ADD_ROT_VALU);

			// �ړ��ʂ̐ݒ�
			m_Move = D3DXVECTOR3(-MOVE_DISTANCE, 0.0f, 0.0f);

			// �J�E���g�̏�����
			m_nMoveFrameCount = 0;

			// �ړ����t���O��true
			m_bActiveMove = true;
		}

		if (m_bActiveMove)
		{
			if (m_pChild->GetIsActive())
			{
				// �������Ă���I�u�W�F�N�g�̃��[���h���W�̎擾
				D3DXVECTOR3 childVec = D3DXVECTOR3(m_pChild->GetModel()->GetModelData().mtxWorld._41, m_pChild->GetModel()->GetModelData().mtxWorld._42, m_pChild->GetModel()->GetModelData().mtxWorld._43);

				if (childVec.y - GetPosition().y <= -0.001)
				{// �ړ��p�^�[���̐ݒ�
					m_movePattern = STICKY_DOWN;
				}
				else if (childVec.y - GetPosition().y >= 0.001)
				{
					m_movePattern = STICKY_UP;
				}
				else
				{
					childVec.y = GetPosition().y;

					if (D3DXVec3Length(&(childVec - GetPosition())) > 10.0f)
					{

						// �v���C���[����I�u�W�F�N�g�ւ̕����x�N�g��
						childVec = childVec - GetPosition();
						childVec.y = 0.0f;
						// ���K��
						D3DXVec3Normalize(&childVec, &childVec);

						// �ړ������̃x�N�g��
						D3DXVECTOR3 moveVec = m_Move;
						moveVec.y = 0.0f;
						// ���K��
						D3DXVec3Normalize(&moveVec, &moveVec);

						if (D3DXVec3Length(&(childVec - moveVec)) < 0.001f)
						{// �ړ��p�^�[���̐ݒ�
							m_movePattern = STICKY_FRONT;
						}
						else
						{// �ړ��p�^�[���̐ݒ�
							m_movePattern = STICKY_NONE;
						}
					}
					else
					{// �ړ��p�^�[���̐ݒ�
						m_movePattern = STICKY_NONE;
					}
				}
			}
			else
			{
				m_movePattern = STICKY_NONE;
			}

			//�����蔻��
			Collision();
			//�s���͈�
			MoveRange();
			//�q���u���b�N�̍s���͈�
			MoveRangeChild();
		}
	}
}

//******************************
// �ړ�����
//******************************
void CPlayer::Move(void)
{
	if (m_bActiveMove)
	{// �ړ����̏���

		// �ʒu�̎擾
		D3DXVECTOR3 pos = GetPosition();
		switch (m_movePattern)
		{
		case STICKY_NONE:
			// �����̒���
			pos.y = ((sinf((D3DXToRadian(180.0f) / MOVE_FRAME)*m_nMoveFrameCount))*MOVE_Y_VALU) + PLAYER_HEIGHT;
			//�ʒu�Z�b�g
			pos += m_Move;
			break;
		
		case STICKY_FRONT:
			// �����̒���
			pos.y = ((sinf((D3DXToRadian(90.0f) / MOVE_FRAME)*m_nMoveFrameCount)) * (PLAYER_HEIGHT * 3)) + (PLAYER_HEIGHT - ((m_nMoveFrameCount / MOVE_FRAME) * PLAYER_HEIGHT));
			//�ʒu�Z�b�g
			pos += m_Move * 2.0f;
			break;

		case STICKY_DOWN:
			// �����̒���
			pos.y = ((sinf(((D3DXToRadian(90.0f) / MOVE_FRAME)*m_nMoveFrameCount) + D3DXToRadian(90.0f))) * (PLAYER_HEIGHT * 3)) + (0 + ((m_nMoveFrameCount / MOVE_FRAME) * PLAYER_HEIGHT));
			//�ʒu�Z�b�g
			pos += m_Move * 2.0f;
			break;

		case STICKY_UP:
			// �����̒���
			pos.y = ((sinf((D3DXToRadian(180.0f) / MOVE_FRAME)*m_nMoveFrameCount))*MOVE_Y_VALU) + PLAYER_HEIGHT;
			//�ʒu�Z�b�g
			pos += m_Move;
			break;
		default:
			break;
		}


		//�ʒu�Z�b�g
		SetPosition(pos);

		// �J�E���g��i�߂Ĉ�萔��
		m_nMoveFrameCount++;

		// �R���g���[���[�̐U������
		if (m_nMoveFrameCount == MOVE_JOYPAD_EFFECT_FRAME)
		{
			// �R���g���[���[�\���L�[�̒l�̎擾
			CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
			pJoyInput->SetVibration(1);
		}

		if (m_nMoveFrameCount > MOVE_FRAME)
		{
			// �ړ��ʂ̏�����
			m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			// ��]�s��̏�����
			D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, 0.0f, 0.0f);

			// �J�E���g�̏�����
			m_nMoveFrameCount = 0;
			// �ړ����J�E���g��false
			m_bActiveMove = false;
			return;
		}
	}
}

//******************************
// ��������
//******************************
void CPlayer::Fall(void)
{
	//�ړ������Ă��Ȃ�
	if (!m_bActiveMove)
	{
		//�������Ă���
		if (m_bFallMove)
		{//�������̏���
			//�ʒu�̎擾
			D3DXVECTOR3 pos = GetPosition();
			
			//�ʒu�v�Z
			pos.y = pos.y + (PLAYER_HEIGHT - pos.y) / (MOVE_FRAME- m_nFallFrameCount);
			//�ʒu�Z�b�g
			SetPosition(pos);
			//�����t���[�����Z
			m_nFallFrameCount++;
			
			if (m_nFallFrameCount>=MOVE_FRAME)
			{
				//�J�E���g������
				m_nFallFrameCount = 0;
				//�������J�E���g��false
				m_bFallMove = false;
			}
		}

	}
}

//******************************
// �����蔻�菈��
//******************************
void CPlayer::Collision(void)
{
	//�I�u�W�F�N�g�擾�p
	CObject* pTop[PRIORITY_MAX] = {};
	//���`�F�b�N����I�u�W�F�N�g�̃|�C���^
	CObject* pNext = NULL;
	//���̈ړ���
	D3DXVECTOR3 NextPos;
	if (m_movePattern != STICKY_DOWN)
	{
		NextPos = GetPosition() + ((m_Move*(MOVE_FRAME + 1)) / 2.0f);
	}
	else
	{
		NextPos = GetPosition() + ((m_Move*(MOVE_FRAME + 1)) * 2.0f);
		NextPos.y -= (PLAYER_HEIGHT * 2.0f);
	}

	//top�̃A�h���X���擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CObject::GetTop() + nCount);
	}

	//�I�u�W�F�N�g�T��
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
			while (pNext != NULL)
			{			
				//�q���u���b�N�̓����蔻��
				if (CollisionChild(pNext))
				{
					//�s���s�\����
					MoveError();
					return;
				}

				//�I�u�W�F�N�g�̃^�C�v���A�C�e���Ȃ�
				if (pNext->GetObjType() == OBJTYPE_ITEM)
				{
					//�A�C�e���u���b�N�̈ʒu�擾
					D3DXVECTOR3 ItemPos = ((CObject3D*)pNext)->GetPosition();

					//�����蔻��(�덷���������߂�+-�P)
					if (NextPos.x + PLAYERL_RANGE + 1 > ItemPos.x
						&&NextPos.x - PLAYERL_RANGE - 1 < ItemPos.x
						&&NextPos.y + PLAYERL_RANGE + 1 > ItemPos.y
						&&NextPos.y - PLAYERL_RANGE - 1 < ItemPos.y
						&&NextPos.z + PLAYERL_RANGE + 1 > ItemPos.z
						&&NextPos.z - PLAYERL_RANGE - 1 < ItemPos.z)
					{
						//�s���s�\����
						MoveError();
						return;
					}
				}
				//�I�u�W�F�N�g�̃^�C�v���u���b�N�Ȃ�
				else if (pNext->GetObjType() == OBJTYPE_BLOCK)
				{
					//��Q�u���b�N�̈ʒu�擾
					D3DXVECTOR3 ObjPos = ((CObject3D*)pNext)->GetPosition();

					//�����蔻��(�덷���������߂�+-�P)
					if (NextPos.x + PLAYERL_RANGE + 1 > ObjPos.x
						&&NextPos.x - PLAYERL_RANGE - 1 < ObjPos.x
						&&NextPos.y + PLAYERL_RANGE + 1 > ObjPos.y
						&&NextPos.y - PLAYERL_RANGE - 1 < ObjPos.y
						&&NextPos.z + PLAYERL_RANGE + 1 > ObjPos.z
						&&NextPos.z - PLAYERL_RANGE - 1 < ObjPos.z)
					{
						//�s���s�\����
						MoveError();
						return;
					}

				}
			
				//���̃I�u�W�F�N�g�̃|�C���^���X�V
				pNext = pNext->GetNext();
			}
		}
	}
}

//******************************
// �q���u���b�N�̓����蔻��
//******************************
bool CPlayer::CollisionChild(CObject * Object)
{	
	if (m_pChild->GetIsActive())
	{
		//�q���u���b�N�̈ʒu�擾
		CModel::MODELDATA modelData = m_pChild->GetModel()->GetModelData();
		D3DXVECTOR3 pos = D3DXVECTOR3(modelData.mtxWorld._41, modelData.mtxWorld._42, modelData.mtxWorld._43);

		//���̈ړ���
		D3DXVECTOR3 NextPos;
		if (m_movePattern != STICKY_UP)
		{
			NextPos = pos + ((m_Move*(MOVE_FRAME + 1)) / 2);
		}
		else
		{
			NextPos = pos + ((m_Move*(MOVE_FRAME + 1)) * 2);
			NextPos.y -= (PLAYER_HEIGHT * 2);
		}

		//�I�u�W�F�N�g�̃^�C�v���A�C�e���Ȃ�
		if (Object->GetObjType() == OBJTYPE_ITEM)
		{
			//�A�C�e���u���b�N�̈ʒu�擾
			D3DXVECTOR3 ItemPos = ((CObject3D*)Object)->GetPosition();

			//�����蔻��(�덷���������߂�+-�P)
			if (NextPos.x + PLAYERL_RANGE + 1 > ItemPos.x
				&&NextPos.x - PLAYERL_RANGE - 1 < ItemPos.x
				&&NextPos.y + PLAYERL_RANGE + 1 > ItemPos.y
				&&NextPos.y - PLAYERL_RANGE - 1 < ItemPos.y
				&&NextPos.z + PLAYERL_RANGE + 1 > ItemPos.z
				&&NextPos.z - PLAYERL_RANGE - 1 < ItemPos.z)
			{
				return true;
			}
		}
		//�I�u�W�F�N�g�̃^�C�v���u���b�N�Ȃ�
		else if (Object->GetObjType() == OBJTYPE_BLOCK)
		{
			//��Q�u���b�N�̈ʒu�擾
			D3DXVECTOR3 ObjPos = ((CObject3D*)Object)->GetPosition();

			//�����蔻��(�덷���������߂�+-�P)
			if (NextPos.x + PLAYERL_RANGE + 1 > ObjPos.x
				&&NextPos.x - PLAYERL_RANGE - 1 < ObjPos.x
				&&NextPos.y + PLAYERL_RANGE + 1 > ObjPos.y
				&&NextPos.y - PLAYERL_RANGE - 1 < ObjPos.y
				&&NextPos.z + PLAYERL_RANGE + 1 > ObjPos.z
				&&NextPos.z - PLAYERL_RANGE - 1 < ObjPos.z)
			{
				return true;
			}

		}
	}

	return false;
}

//******************************
// �s���͈͏����֐�
//******************************
void CPlayer::MoveRange(void)
{
	//���̈ړ���
	D3DXVECTOR3 NextPos;
	//�󋵂ɉ�����
	if (m_movePattern != STICKY_DOWN)
	{
		NextPos = GetPosition() + ((m_Move*(MOVE_FRAME + 1)));
		NextPos.y = NextPos.y - (TILE_HEIGHT + PLAYER_HEIGHT);
	}
	else
	{
		NextPos = GetPosition() + ((m_Move*(MOVE_FRAME + 1.0f))*2);
		NextPos.y -= ((PLAYER_HEIGHT * 2) + (TILE_HEIGHT + PLAYER_HEIGHT));
	}

	//�^�C���̃|�C���^�擾
	CTileBlockBase * pTile = (CTileBlockBase*)(GetTop()[PRIORITY_OBJECT_TILE]);

	while (pTile != NULL)
	{		
		// �A�C�e���̍��W�̎擾
		D3DXVECTOR3 TilePos = pTile->GetPosition();
	
		//�����蔻��
		if (NextPos.x + PLAYERL_RANGE > TilePos.x
			&&NextPos.x - PLAYERL_RANGE < TilePos.x
			&&NextPos.y + PLAYERL_RANGE > TilePos.y
			&&NextPos.y - PLAYERL_RANGE < TilePos.y
			&&NextPos.z + PLAYERL_RANGE > TilePos.z
			&&NextPos.z - PLAYERL_RANGE < TilePos.z)
		{
			return;
		}
		pTile = (CTileBlockBase*)(pTile->GetNext());
	}

	//�s���s�\����
	MoveError();
}

//******************************
// �q���u���b�N�̍s���͈͐ݒ菈��
//******************************
void CPlayer::MoveRangeChild(void)
{
	if (m_pChild->GetIsActive())
	{		
		//�q���u���b�N�̈ʒu�擾
		CModel::MODELDATA modelData = m_pChild->GetModel()->GetModelData();
		D3DXVECTOR3 pos = D3DXVECTOR3(modelData.mtxWorld._41, modelData.mtxWorld._42, modelData.mtxWorld._43);

		//���̈ړ���
		D3DXVECTOR3 NextPos;
		if (m_movePattern != STICKY_UP)
		{
			NextPos = pos + ((m_Move*(MOVE_FRAME + 1)));
			NextPos.y -= (TILE_HEIGHT + PLAYER_HEIGHT);

		}
		else
		{

			NextPos = pos + ((m_Move*(MOVE_FRAME + 1))*2);
			NextPos.y -= ((PLAYER_HEIGHT * 2) + (TILE_HEIGHT + PLAYER_HEIGHT));
		}

		//�^�C���̃|�C���^�擾
		CTileBlockBase * pTile = (CTileBlockBase*)(GetTop()[PRIORITY_OBJECT_TILE]);

		while (pTile != NULL)
		{
			// �A�C�e���̍��W�̎擾
			D3DXVECTOR3 TilePos = pTile->GetPosition();

			//�����蔻��
			if (NextPos.x + PLAYERL_RANGE > TilePos.x
				&&NextPos.x - PLAYERL_RANGE < TilePos.x
				&&NextPos.y + PLAYERL_RANGE > TilePos.y
				&&NextPos.y - PLAYERL_RANGE < TilePos.y
				&&NextPos.z + PLAYERL_RANGE > TilePos.z
				&&NextPos.z - PLAYERL_RANGE < TilePos.z)
			{
				return;
			}
			pTile = (CTileBlockBase*)(pTile->GetNext());
		}

		//�s���s�\����
		MoveError();
	}
}

//******************************
// �G���[���̎g�p�m�F�֐�
//******************************
void CPlayer::ErrorStatus(void)
{
	//�L�[�{�[�h���͂̎擾
	CInputKeyboard* pKeyInput = (CInputKeyboard*)CManager::GetInputKey();
	// �R���g���[���[�\���L�[�̒l�̎擾
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	WORD joyCross = CROSS_KEY_NEUTRAL;
	if (pJoyInput != NULL)
	{ 
		if (pJoyInput->GetPushCross(CROSS_KEY_UP)
			|| pJoyInput->GetPushCross(CROSS_KEY_RIGHT)
			|| pJoyInput->GetPushCross(CROSS_KEY_DOWN)
			|| pJoyInput->GetPushCross(CROSS_KEY_LEFT))
		{
			m_bError = false;
		}
		
	}

	if (pKeyInput->GetKeyTrigger(DIK_W)
		|| pKeyInput->GetKeyTrigger(DIK_A)
		|| pKeyInput->GetKeyTrigger(DIK_S)
		|| pKeyInput->GetKeyTrigger(DIK_D))
	{
		m_bError = false;
	}
}

//******************************
// �s���s�\���̏����֐�
//******************************
void CPlayer::MoveError(void)
{
	//�G���[�I���p�̏���
	if (m_bError == false)
	{
		//BGM�̍Đ�
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_ERROR);
		//SE�t���O�I��
		m_bError = true;
	}
	// ��]�s��̏�����
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, 0.0f, 0.0f);
	//�ړ��ʂ�������
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �ړ����J�E���g��false
	m_bActiveMove = false;
}

//******************************
// ���[���h�ϊ�
//******************************
void CPlayer::ExchangeWorldMtx(void)
{

	D3DXMATRIX mtxTrans, mtxScail;

	CModel::MODELDATA modelData = m_model->GetModelData();

	// �ʒu�̏�����
	modelData.mtxWorld._41 = 0.0f;
	modelData.mtxWorld._42 = 0.0f;
	modelData.mtxWorld._43 = 0.0f;

	//�T�C�Y�𔽉f
	D3DXMatrixScaling(&mtxScail, m_model->GetScale().x, m_model->GetScale().y, m_model->GetScale().z);
	D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &mtxScail);

	//�����𔽉f
	D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &m_mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_model->GetPosition().x, m_model->GetPosition().y, m_model->GetPosition().z);
	D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &mtxTrans);

	// �Z�b�g
	m_model->SetModelData(modelData);
}

//******************************
// �S�[�������֐�
//******************************
void CPlayer::Goal(void)
{
	//�A�C�e�����������Ă��邩
	if (m_pChild->GetIsActive())
	{
		// �ʒu�̎擾
		D3DXVECTOR3 pos = GetPosition();
		//�I������
		m_pChild->Uninit();
		//��������
		m_pChild = CChild::Create(m_model, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		
		if (m_movePattern == STICKY_FRONT)
		{
			//�t���[�����̏�����
			m_nFallFrameCount = 0;

			//��������
			m_bFallMove = true;
		}


		//BGM�̍Đ�
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_REACHED);
	}
}