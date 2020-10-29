//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "homing.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include <typeinfo.h>
#include "enemy.h"
#include "player.h"
#include "boss.h"
#include "sound.h"
#include "effect.h"
//----------------------------------
//�}�N����`
//----------------------------------
#define HOMING_LIFE	50
#define HOMING_SIZE 25
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
LPDIRECT3DTEXTURE9 CHoming::m_pTexture = NULL;

CHoming::CHoming(int nPriorit)
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
	nLife = 0;
	m_move = D3DXVECTOR3(0.0f, -3.0f, 0.0f);

}

CHoming::~CHoming()
{
}

HRESULT CHoming::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Bullet.png", &m_pTexture);
	return S_OK;
}

void CHoming::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

CHoming * CHoming::Create(D3DXVECTOR3 Pos, int nSpeed, HOMING_TYPE Type)
{
	CHoming *pHoming;
	pHoming = new CHoming;
	pHoming->Set(Pos);
	pHoming->Init(nSpeed, Type);
	return pHoming;
}

HRESULT CHoming::Init(int nSpeed, HOMING_TYPE Type)
{
	CSound *pSound = CManager::GetSound();	//�T�E���h�擾

	//�˒�����
	nLife = HOMING_LIFE;
	//�X�s�[�h�@
	m_nSpeed = nSpeed;
	//�^�C�v
	m_Type = Type;
	if (m_Type == HOMING_TYPE_PLAYER)
	{
		pSound->Play(CSound::LABEL_SE_SHOTS);
	}
	//�T�C�Y
	SetSizeition(D3DXVECTOR3(HOMING_SIZE / 2, HOMING_SIZE / 2, 0.0f));
	//�e�N�X�`���̐ݒ�
	BindTexture(m_pTexture);


	//����������
	CScene2d::Init();
	return S_OK;
}

void CHoming::Uninit(void)
{
	//�I������
	CScene2d::Uninit();
}

void CHoming::Update(void)
{
	//�|���S���̈ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
		//�G�t�F�N�g����
		CEffect::Create(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(HOMING_SIZE / 2, HOMING_SIZE, 0.0f), CEffect::EFFECT_TYPE_BULLET);


	int nRange =780;
	float fAngle;
	for (int nCut = 0; nCut < MAX_PRIORITY; nCut++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene *pScene = GetScene(nCut, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objType;
				//�^�C�v�擾
				objType = pScene->GetObjType();
				switch (m_Type)
				{
				case HOMING_TYPE_PLAYER:
					if (objType == OBJ_TYPE_ENEMY)
					{
						D3DXVECTOR3 EnemeyPos = ((CScene2d*)pScene)->GetPosition();
						if (TargetGet(pos, EnemeyPos)<nRange)
						{
							nRange = TargetGet(pos, EnemeyPos);
							fAngle = atan2f((-pos.x + EnemeyPos.x), (-pos.y + EnemeyPos.y));
							m_move.x = sinf(fAngle)*m_nSpeed;
							m_move.y = cosf(fAngle)*m_nSpeed;


						}
					}
					break;

				}
			}

		}
	}


	//�ʒu�X�V
	pos += m_move;
	//���̎˒�����
	nLife--;

	//�|���S���̈ʒu��n��
	SetPosition(pos);
	//�X�V����
	CScene2d::Update();

	//�˒�����
	if (nLife <= 0)
	{
		CExplosion::Create(pos);
		Uninit();	//�I������
		return;

	}
	//��ʊO�ɏo����
	else if (pos.y < 0 || pos.y>SCREEN_HEIGHT || pos.x<0 || pos.x>SCREEN_WIDTH)
	{
		Uninit();	//�I������
		return;
	}
	if (nLife > 0)		//�˒�������
	{
		//�z�[�~���O���ʏ���
		for (int nCut = 0; nCut < MAX_PRIORITY; nCut++)
		{
			for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
			{
				CScene *pScene = GetScene(nCut, nCntScene);
				if (pScene != NULL)
				{
					OBJTYPE objType;
					//�^�C�v�擾
					objType = pScene->GetObjType();
					switch (m_Type)
					{
					case HOMING_TYPE_PLAYER:
						if (objType == OBJ_TYPE_ENEMY)
						{
							D3DXVECTOR3 EnemeyPos = ((CScene2d*)pScene)->GetPosition();
							D3DXVECTOR3 EnemeySize = ((CScene2d*)pScene)->GetSizeition();					
							//�����蔻��
							if (EnemeyPos.x + EnemeySize.x / 2 > pos.x
								&& EnemeyPos.x - EnemeySize.x / 2 < pos.x
								&&EnemeyPos.y + EnemeySize.y / 2 > pos.y
								&&EnemeyPos.y - EnemeySize.y / 2 < pos.y)
							{
								//�G�l�~�[�_���[�W����
								if (typeid(*pScene) == typeid(CEnemy))
								{
									//�G�N�X�v���[�W��������
									CExplosion::Create(EnemeyPos);

									((CEnemy*)pScene)->Damage(1);
								}
								else if (typeid(*pScene) == typeid(CBoss))
								{
									//�G�N�X�v���[�W��������
									CExplosion::Create(pos);

									((CBoss*)pScene)->Damage(1);
								}
								Uninit();
								break;

							}
						}
						break;
					case HOMING_TYPE_ENEMY:

						break;
					}
				}
			}
		}
	}

}

void CHoming::Draw(void)
{
	//�`�揈��
	CScene2d::Draw();
}

int CHoming::TargetGet(D3DXVECTOR3 pos, D3DXVECTOR3 EnemyPos)
{
			
	//�^�C�v�擾
	switch (m_Type)
	{
	case HOMING_TYPE_PLAYER:
			int nDistance = (pos.x- EnemyPos.x)*(pos.x - EnemyPos.x) + (pos.y - EnemyPos.y)*(pos.y - EnemyPos.y);
			int a = sqrt(nDistance);
			return a;
		break;
	
	}
			
	return 0;
}
