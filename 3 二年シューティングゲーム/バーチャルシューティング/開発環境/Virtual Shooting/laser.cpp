//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "laser.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "explosion.h"
#include "enemy.h"
#include "boss.h"
#include "sound.h"
#include <typeinfo.h>
//----------------------------------
//�}�N����`
//----------------------------------
#define LASER_SIZE_X 10		//���[�U�[�̑傫��
#define LASER_SIZE_Y 100	//���[�U�[�̑傫��

#define LASER_LIFE 50		//���[�U�[�̎˒�����
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
LPDIRECT3DTEXTURE9 CLaser::m_pTexture = NULL;

//----------------------------------
//�R���X�g���N�^
//----------------------------------
CLaser::CLaser(int nPriorit)
{
	nLife = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		m_Hit[nCntScene] = false;

	}
}

//----------------------------------
//�f�X�g���N�^
//----------------------------------
CLaser::~CLaser()
{
}

//----------------------------------
//�e�N�X�`���ǂݍ��ݏ���
//----------------------------------
HRESULT CLaser::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Laser.png", &m_pTexture);
	return S_OK;
}

//----------------------------------
//�e�N�X�`���j������
//----------------------------------
void CLaser::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//----------------------------------
//��������
//----------------------------------
CLaser * CLaser::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 move, LASER_TYPE Type)
{
	CLaser *pLaser;
	pLaser = new CLaser;
	pLaser->Set(Pos);
	pLaser->Init(move, Type);
	return pLaser;
}

//----------------------------------
//����������
//----------------------------------
HRESULT CLaser::Init(D3DXVECTOR3 move, LASER_TYPE Type)
{
	CSound *pSound = CManager::GetSound();	//�T�E���h�擾

	//�˒�����
	nLife = LASER_LIFE;
	//�ړ���
	m_move = move;
	//�^�C�v
	m_Type = Type;
	if (m_Type== LASER_TYPE_PLAYER)
	{
		pSound->Play(CSound::LABEL_SE_LASER);

	}
	//�T�C�Y
	SetSizeition(D3DXVECTOR3(LASER_SIZE_X / 2, LASER_SIZE_Y / 2, 0.0f));
	//�e�N�X�`���̐ݒ�
	BindTexture(m_pTexture);


	//����������
	CScene2d::Init();
	return S_OK;
}

//----------------------------------
//�I������
//----------------------------------
void CLaser::Uninit(void)
{
	//�I������
	CScene2d::Uninit();
}

//----------------------------------
//�X�V����
//----------------------------------
void CLaser::Update(void)
{
	//�|���S���̈ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	//�ʒu�X�V
	pos += m_move;
	//���̎˒�����
	nLife--;
	//�X�V����
	CScene2d::Update();
	//�|���S���̈ʒu��n��
	SetPosition(pos);

	//�G�t�F�N�g����
	CEffect::Create(pos, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(LASER_SIZE_X / 2, LASER_SIZE_Y / 2, 0.0f),CEffect::EFFECT_TYPE_LASER);

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
		//���[�U�[���ʏ���
		for (int nCut = 0; nCut < MAX_DRAW; nCut++)
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
					case LASER_TYPE_PLAYER:
						if (objType == OBJ_TYPE_ENEMY)
						{
							D3DXVECTOR3 EnemeyPos = ((CScene2d*)pScene)->GetPosition();
							D3DXVECTOR3 EnemeySize = ((CScene2d*)pScene)->GetSizeition();
							//�����蔻��
							
							if (EnemeyPos.x + EnemeySize.x > pos.x
								&& EnemeyPos.x - EnemeySize.x < pos.x
								&&EnemeyPos.y + EnemeySize.y > pos.y
								&&EnemeyPos.y - EnemeySize.y < pos.y
								&&m_Hit[nCntScene]!=true)
							{
			
								m_Hit[nCntScene] = true;

								
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
							}
						}
						break;
					case LASER_TYPE_ENEMY:

						break;

					}

				}
			}
		}
	}

}

//----------------------------------
//�`�揈��
//----------------------------------
void CLaser::Draw(void)
{
	//�`�揈��
	CScene2d::Draw();
}
