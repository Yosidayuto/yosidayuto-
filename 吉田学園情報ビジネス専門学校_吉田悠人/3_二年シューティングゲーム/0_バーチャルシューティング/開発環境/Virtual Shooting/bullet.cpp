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
		SetSize(m_size);
	}
	else if(m_Type == BULLET_TYPE_ENEMY)
	{
		m_size = D3DXVECTOR3(20, 20, 0.0f);
		SetSize(m_size);
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
	//�I�u�W�F�N�g�擾�p
	CScene* pTop[PRIORITY_MAX] = {};
	//���`�F�b�N����I�u�W�F�N�g�̃|�C���^
	CScene* pNext = NULL;

	//top�̃A�h���X���擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	//�|���S���̈ʒu�擾
	D3DXVECTOR3 pos = GetPos();
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
	SetPos(pos);

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
		for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
		{
			if (pTop[nCount] != NULL)
			{
				pNext = pTop[nCount];
				//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
				while (pNext != NULL)
				{
					switch (m_Type)
					{
					case BULLET_TYPE_PLAYER:
						if (pNext->GetObjType() == OBJ_TYPE_ENEMY)
						{
							D3DXVECTOR3 EnemeyPos = ((CScene2d*)pNext)->GetPos();
							D3DXVECTOR3 EnemeySize = ((CScene2d*)pNext)->GetSize();
							//�����蔻��
							if (EnemeyPos.x + EnemeySize.x/2 > pos.x
								&& EnemeyPos.x - EnemeySize.x/2 < pos.x
								&&EnemeyPos.y + EnemeySize.y/2 > pos.y
								&&EnemeyPos.y - EnemeySize.y/2 < pos.y)
							{
								//�G�l�~�[�_���[�W����
								if (typeid(*pNext) == typeid(CEnemy))
								{
									//�G�N�X�v���[�W��������
									CExplosion::Create(EnemeyPos);

									((CEnemy*)pNext)->Damage(1);
								}
								else if (typeid(*pNext) == typeid(CBoss))
								{
									//�G�N�X�v���[�W��������
									CExplosion::Create(pos);

									((CBoss*)pNext)->Damage(1);
								}
								//�o���b�g�I������
								Uninit();
								return;
							}
						}
						break;
					case BULLET_TYPE_ENEMY:
						if (pNext->GetObjType() == OBJ_TYPE_PLAYER)
						{
							D3DXVECTOR3 PlayerPos = ((CScene2d*)pNext)->GetPos();
							D3DXVECTOR3 PlayerSize = ((CScene2d*)pNext)->GetSize();
							//�����蔻��
							if (PlayerPos.x  > pos.x - m_size.x
								&& PlayerPos.x  < pos.x + m_size.x
								&&PlayerPos.y  > pos.y - m_size.y
								&&PlayerPos.y  < pos.y + m_size.y)
							{
								//�G�N�X�v���[�W��������
								CExplosion::Create(PlayerPos);
								//�G�l�~�[�I������
								((CPlayer*)pNext)->Damage(1);
								//�o���b�g�I������
								Uninit();
								return;
							}
						}
						break;

					}

					//���̃I�u�W�F�N�g�̃|�C���^���X�V
					pNext = pNext->GetNext();
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
	pBullet->SetPos(Pos);
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

