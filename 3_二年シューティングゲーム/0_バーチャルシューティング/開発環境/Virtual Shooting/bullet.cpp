//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "bullet.h"			//�o���b�g
#include "manager.h"		//�}�l�[�W���[
#include "renderer.h"		//�����_�����O
#include "explosion.h"		//�G�N�X�v���[�W����
#include "sound.h"			//�T�E���h
#include "effect.h"			//�G�t�F�N�g
#include "enemy.h"			//�G�l�~�[
#include "boss.h"			//�{�X
#include <typeinfo.h>
//----------------------------------
//�}�N����`
//----------------------------------
#define BULLET_SIZE 20		//�o���b�g�̑傫��
#define BULLET_LIFE 1000		//�o���b�g�̎˒�����
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;
//----------------------------------
//�R���X�g���N�^
//----------------------------------
CBullet::CBullet(int nPriorit) :CScene2d(nPriorit)
{
	nLife = 0;
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//----------------------------------
//�f�X�g���N�^
//----------------------------------
CBullet::~CBullet()
{
}

//----------------------------------
//����������
//----------------------------------
HRESULT CBullet::Init(D3DXVECTOR3 move, BULLET_TYPE Type)
{
	CSound *pSound = CManager::GetSound();	//�T�E���h�擾


	//�˒�����
	nLife = BULLET_LIFE;
	//�ړ���
	m_move = move;
	//�^�C�v
	m_Type = Type;
	//�T�C�Y
	if (m_Type == BULLET_TYPE_PLAYER )
	{
		pSound->Play(CSound::LABEL_SE_SHOTS);
		m_size = D3DXVECTOR3(BULLET_SIZE / 2, BULLET_SIZE / 2, 0.0f);
		SetSizeition(m_size);
	}
	else if(m_Type == BULLET_TYPE_ENEMY)
	{
		m_size = D3DXVECTOR3(20, 20, 0.0f);
		SetSizeition(m_size);
	}
	//����������
	CScene2d::Init();
	//�e�N�X�`���̐ݒ�
	BindTexture(m_pTexture);

	return S_OK;
}

//----------------------------------
//�I������
//----------------------------------
void CBullet::Uninit(void)
{
	//�I������
	CScene2d::Uninit();
}

//----------------------------------
//�X�V����
//----------------------------------
void CBullet::Update(void)
{
	//�|���S���̈ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	if (m_Type== BULLET_TYPE_PLAYER)
	{
		//�G�t�F�N�g����
		CEffect::Create(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(BULLET_SIZE / 2, BULLET_SIZE, 0.0f), CEffect::EFFECT_TYPE_BULLET);

	}


	//�ʒu�X�V
	pos += m_move;
	//���̎˒�����
	nLife --;
	//�X�V����
	CScene2d::Update();
	//�|���S���̈ʒu��n��
	SetPosition(pos);
	//�X�R�A�擾
	//CScore *pScore = CManager::GetScore();

	//�˒�����
	if (nLife <= 0)
	{
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
		//�o���b�g���ʏ���
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
					case BULLET_TYPE_PLAYER:
						if (objType == OBJ_TYPE_ENEMY)
						{
							D3DXVECTOR3 EnemeyPos = ((CScene2d*)pScene)->GetPosition();
							D3DXVECTOR3 EnemeySize = ((CScene2d*)pScene)->GetSizeition();
							//�����蔻��
							if (EnemeyPos.x + EnemeySize.x/2 > pos.x
								&& EnemeyPos.x - EnemeySize.x/2 < pos.x
								&&EnemeyPos.y + EnemeySize.y/2 > pos.y
								&&EnemeyPos.y - EnemeySize.y/2 < pos.y)
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
								//�o���b�g�I������
								Uninit();
								return;
							}
						}
						break;
					case BULLET_TYPE_ENEMY:
						if (objType == OBJ_TYPE_PLAYER)
						{
							D3DXVECTOR3 PlayerPos = ((CScene2d*)pScene)->GetPosition();
							D3DXVECTOR3 PlayerSize = ((CScene2d*)pScene)->GetSizeition();
							//�����蔻��
							if (PlayerPos.x  > pos.x - m_size.x
								&& PlayerPos.x  < pos.x + m_size.x
								&&PlayerPos.y  > pos.y - m_size.y
								&&PlayerPos.y  < pos.y + m_size.y)
							{
								//�G�N�X�v���[�W��������
								CExplosion::Create(PlayerPos);
								//�G�l�~�[�I������
								((CPlayer*)pScene)->Damage(1);
								//�o���b�g�I������
								Uninit();
								return;
							}
						}
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
void CBullet::Draw(void)
{
	//�`�揈��
	CScene2d::Draw();
}

//----------------------------------
//��������
//----------------------------------
CBullet * CBullet::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 move, BULLET_TYPE Type)
{
	CBullet *pBullet;
	pBullet = new CBullet;
	pBullet->Set(Pos);
	pBullet->Init(move, Type);
	return pBullet;
}

HRESULT CBullet::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Bullet.png", &m_pTexture);	
	return S_OK;
}

void CBullet::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

