#include "boss.h"
#include "manager.h"
#include "renderer.h"
#include "score.h"
#include "game.h"
#include "sound.h"
#include "enemy bullet.h"
#include "boss_anime.h"
#include "player.h"
#include <time.h>
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
bool CBoss::m_bDie = false;
TEXTURE_DATA CBoss::m_TextureData[BOSS_TYPE_MAX] = 
{ { NULL,"data/TEXTURE/Boss_1.png" },
{ NULL,	"data/TEXTURE/Boss_2.png" },
{ NULL,	"data/TEXTURE/Boss_3.png" },
};

//----------------------------------
//�R���X�g���N�^
//----------------------------------
CBoss::CBoss(int nPriorit):CScene2d(nPriorit)
{
	m_bBulletMode = false;
	m_Stats = STATS_MODE_NORMAL;
	m_move= D3DXVECTOR3(0, 0, 0);
	m_BulletType = BULLET_PATTERN_NONE;
	m_bDie = true;
	m_nBulletCoolTime = NULL;
	CScene::SetObjType(CScene::OBJ_TYPE_ENEMY);		//�^�C�v����
	m_pBullet = NULL;								//���̃N���X������
	for (int nNumberBullet = 0; nNumberBullet < MAX_BOSS_BULLET; nNumberBullet++)
	{
		nConutBullet[nNumberBullet]=0;
		m_rot[nNumberBullet] = D3DXVECTOR3(0, 0, 0);
		m_bBullet[nNumberBullet] = false;
	}

}

//----------------------------------
//�f�X�g���N�^
//----------------------------------
CBoss::~CBoss()
{
	m_bDie = false;
}

//----------------------------------
//�e�N�X�`���ǂݍ��ݏ���
//----------------------------------
HRESULT CBoss::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < BOSS_TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, m_TextureData[nCount].m_cFileName, &m_TextureData[nCount].m_Texture);
	}
	return S_OK;
}

//----------------------------------
//�e�N�X�`���j������
//----------------------------------
void CBoss::Unload(void)
{
	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < BOSS_TYPE_MAX; nCount++)
	{
		if (m_TextureData[nCount].m_Texture != NULL)
		{
			m_TextureData[nCount].m_Texture->Release();
			m_TextureData[nCount].m_Texture = NULL;
		}
	}
}

//----------------------------------
//��������
//----------------------------------
CBoss * CBoss::Create(D3DXVECTOR3 Pos, BOSS_TYPE nType, D3DXVECTOR3 size)
{

	CBoss *pBoss;
	pBoss = new CBoss;
	pBoss->m_Type = nType;
	pBoss->m_size = size/2;
	pBoss->m_pos = Pos;
	pBoss->SetSize(size/2);
	pBoss->BindTexture(m_TextureData[nType].m_Texture);
	pBoss->SetPos(Pos);
	pBoss->Init();

	return pBoss;
}

//----------------------------------
//����������
//----------------------------------
HRESULT CBoss::Init(void)
{

	switch (m_Type)
	{
	case BOSS_TYPE_1:
		m_BossAnime = CBossAnime::Create(m_pos, m_size, CBossAnime::BOSS_ANIME_1);
		m_nLife =100;
		break;
	case BOSS_TYPE_2:
		m_BossAnime = CBossAnime::Create(m_pos, m_size, CBossAnime::BOSS_ANIME_3);
		m_nLife = 120;
		break;
	case BOSS_TYPE_3:
		m_BossAnime = CBossAnime::Create(m_pos, m_size, CBossAnime::BOSS_ANIME_5);

		m_nLife = 140;
		break;
	}

	//����������
	CScene2d::Init();

	return S_OK;
}

//----------------------------------
//�I������
//----------------------------------
void CBoss::Uninit(void)
{
	CScene2d::Uninit();
}

//----------------------------------
//�X�V����
//----------------------------------
void CBoss::Update(void)
{
	CScene2d::Update();
	switch (m_Type)
	{
	case BOSS_TYPE_1:
		Hit(m_pos);		//�����蔻��
		Bullet(m_BulletType, m_pos);
		break;
	case BOSS_TYPE_2:
		Hit(m_pos);		//�����蔻��
		Bullet(m_BulletType, m_pos);
		break;

	case BOSS_TYPE_3:
		Hit(m_pos);		//�����蔻��
		Bullet(m_BulletType, m_pos);
		break;

	}
	StatasManage();

}

//----------------------------------
//�`�揈��
//----------------------------------
void CBoss::Draw(void)
{
	CScene2d::Draw();
}

//----------------------------------
//�_���[�W����
//----------------------------------
void CBoss::Damage(int nDamage)
{
	if (m_Stats == STATS_MODE_NORMAL)
	{
		//���C�t�_���[�W
		m_nLife -= nDamage;
		//��ԕϊ�
		if (m_nLife > 0)
		{
			m_Stats = STATS_MODE_DAMAGE;
		}
		else
		{
			m_Stats = STATS_MODE_DEATH;
		}
	}

}

void CBoss::StatasManage(void)
{
	int nScore =10000;
	switch (m_Stats)
	{
	case STATS_MODE_NORMAL:
		//�_���[�W�J���[����
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;
	case STATS_MODE_DAMAGE:
		//�_���[�W�J���[����
		SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.0f));
		m_Stats = STATS_MODE_NORMAL;

		break;
	case STATS_MODE_DEATH:
		CScore *pScore = CGame::GetScore();		//�X�R�A�N���X�擾
		CSound *pSound = CManager::GetSound();	//�T�E���h�N���X�擾

		//�X�R�A�A�b�v
		pScore->AddScore(nScore);

		//�f���[�g���̃G�t�F�N�g
		switch (m_Type)
		{
		case BOSS_TYPE_1:
			//�T�E���h�̍Đ�
			pSound->Play(CSound::LABEL_SE_BOSS_DIE_2);


			CBossAnime::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), D3DXVECTOR3(800, m_size.y, 0.0f), CBossAnime::BOSS_ANIME_2);

			break;
		
		case BOSS_TYPE_2:
			//�T�E���h�̍Đ�
			pSound->Play(CSound::LABEL_SE_BOSS_DIE_1);

			CBossAnime::Create(D3DXVECTOR3(m_pos.x, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, SCREEN_HEIGHT, 0.0f), CBossAnime::BOSS_ANIME_4);
			break;
		case BOSS_TYPE_3:
			//�T�E���h�̍Đ�
			pSound->Play(CSound::LABEL_SE_BOSS_DIE_2);

			CBossAnime::Create(D3DXVECTOR3(m_pos.x, m_pos.y-50 / 2, 0.0f), D3DXVECTOR3(800, m_size.y, 0.0f), CBossAnime::BOSS_ANIME_6);
			break;

		}
	
		//�G�t�F�N�g������
		if (m_BossAnime != NULL)
		{
			m_BossAnime->Uninit();

		}
		CBoss::Uninit();
		break;
	}

}

//----------------------------------
//��]����
//----------------------------------
void CBoss::Rotate(void)
{
	static float fRot = 0;
	//�����Z�b�g
	SetRot(fRot);
	fRot++;
	if (fRot>360.0f)
	{
		fRot = 0;
	}
}

//----------------------------------
//�o���b�g����
//----------------------------------
void CBoss::Bullet(BOSS_PATTERN_BULLET BulletMode, D3DXVECTOR3 Pos)
{
	for (int nNumberBullet = 0; nNumberBullet < MAX_BOSS_BULLET; nNumberBullet++)
	{
		nConutBullet[nNumberBullet]++;
	}
	switch (BulletMode)
	{
	case BULLET_PATTERN_NONE://�������Ȃ�
		//�N�[���^�C��
		m_nBulletCoolTime++;
		if (m_nBulletCoolTime >= 100)
		{
			//�O�̍U�����I����Ă��邩
			if (m_bBulletMode == false)
			{
				//�U�������̏�����
				for (int nNumberBullet = 0; nNumberBullet < MAX_BOSS_BULLET; nNumberBullet++)
				{
					nConutBullet[nNumberBullet] = 0;
					m_rot[nNumberBullet] = D3DXVECTOR3(0, 0, 0);
					m_bBullet[nNumberBullet] = false;
				}
				//�����_���֐��̏�����
				srand((unsigned)time(NULL));
				//�����_���Ɏ��̍U�����@�����߂�i�{�X���ƂɈႤ�j
				switch (m_Type)
				{
				case BOSS_TYPE_1:
					m_BulletType = (BOSS_PATTERN_BULLET)(rand() % BULLET_PATTERN_HOMING2 + BULLET_PATTERN_SHOTS);
					break;
				case BOSS_TYPE_2:
					m_BulletType = (BOSS_PATTERN_BULLET)(rand() % BULLET_PATTERN_All_DIR + BULLET_PATTERN_BUCKSHOT);
					break;
				case BOSS_TYPE_3:
					m_BulletType = (BOSS_PATTERN_BULLET)(rand() % BULLET_PATTERN_All_DIR + BULLET_PATTERN_BUCKSHOT);
					break;
				}
				m_bBulletMode = true;
				//�N�[���^�C���̏�����
				m_nBulletCoolTime = 0;
			}


		}
		break;
	case BULLET_PATTERN_SHOTS://�ʏ�V���b�g
		//10���̃o���b�g����
		for (int nNumberBullet = 0; nNumberBullet < 10; nNumberBullet++)
		{
			//�N�[���^�C�������ɂȂ�����ꔭ������
			if (nConutBullet[nNumberBullet] >= 20 * (nNumberBullet + 1)
				&& m_bBullet[nNumberBullet] == false)
			{
				//�����𑊎�̌����ɏ����i���x�Əꏊ�j
				m_rot[nNumberBullet] = Tracking(7,m_pos);
				//�o���b�g���ˁi���ˏꏊ�ƌ������ƃo���b�g�^�C�v�j
				CEnemyBullet::Create(m_pos, m_rot[0]);
				//�o���b�g�̎g�p���
				m_bBullet[nNumberBullet] = true;
				//�U���I������
				if (m_bBullet[10-1] ==true)
				{
					//�U�����I���ifalse�j�ɂ���
					m_bBulletMode = false;
					//�o���b�g�^�C�v��ς���
					m_BulletType = BULLET_PATTERN_NONE;
				}
			}
		}
		break;
	case BULLET_PATTERN_HOMING://�ǔ��V���b�g
		//10���̃o���b�g����
		for (int nNumberBullet = 0; nNumberBullet < 10; nNumberBullet++)
		{
			//�N�[���^�C�������ɂȂ�����ꔭ������
			if (nConutBullet[nNumberBullet] >= 20 * (nNumberBullet + 1)
				&& m_bBullet[nNumberBullet] == false)
			{
				//�����𑊎�̌����ɏ����i���x�Əꏊ�j
				m_rot[nNumberBullet] = Tracking(7, m_pos);
				//�o���b�g���ˁi���ˏꏊ�ƌ������ƃo���b�g�^�C�v�j
				CEnemyBullet::Create(m_pos, m_rot[nNumberBullet]);
				//�o���b�g�̎g�p���
				m_bBullet[nNumberBullet] = true;
				//�U���I������
				if (m_bBullet[10-1] == true)
				{
					//�U�����I���ifalse�j�ɂ���
					m_bBulletMode = false;
					//�o���b�g�^�C�v��ς���
					m_BulletType = BULLET_PATTERN_NONE;
				}

			}
		}
		break;

		break;
	case BULLET_PATTERN_BUCKSHOT://�U�e�V���b�g
		//70���̃o���b�g����
		for (int nNumberBullet = 0; nNumberBullet < 70; nNumberBullet++)
		{
			//�N�[���^�C�������ɂȂ�����ꔭ������
			if (nConutBullet[nNumberBullet] == 2 * nNumberBullet
				&&m_bBullet[nNumberBullet] == false)
			{
				//�����������_���ɏ����i���x�j
				m_rot[nNumberBullet] = Random(5);
				//�o���b�g���ˁi���ˏꏊ�ƌ������ƃo���b�g�^�C�v�j
				CEnemyBullet::Create(m_pos, m_rot[nNumberBullet]);
				//�o���b�g�̎g�p���
				m_bBullet[nNumberBullet] = true;
				//�U���I������
				if (m_bBullet[70-1] == true)
				{
					//�U�����I���ifalse�j�ɂ���
					m_bBulletMode = false;
					//�o���b�g�^�C�v��ς���
					m_BulletType = BULLET_PATTERN_NONE;
				}

			}
		}
		break;
	case BULLET_PATTERN_SPIRAL://�����V���b�g
		//200���̃o���b�g����
		for (int nNumberBullet = 0; nNumberBullet < MAX_BOSS_BULLET; nNumberBullet++)
		{
			//�ꔭ�ꔭ�̃N�[���^�C��
			if (nConutBullet[nNumberBullet] == nNumberBullet)
			{
				//���̌��������炷
				m_rot[nNumberBullet].x = sinf(Spiral() + (0.2f*nNumberBullet))*7.0f;
				m_rot[nNumberBullet].y = cosf(Spiral() + (0.2f*nNumberBullet))*7.0f;
				//�o���b�g���ˁi���ˏꏊ�ƌ������ƃo���b�g�^�C�v�j
				CEnemyBullet::Create(m_pos, m_rot[nNumberBullet]);
				//�o���b�g�̎g�p���
				m_bBullet[nNumberBullet] = true;
				//�U���I������
				if (m_bBullet[MAX_BOSS_BULLET-1] == true)
				{
					//�U�����I���ifalse�j�ɂ���
					m_bBulletMode = false;
					//�o���b�g�^�C�v��ς���
					m_BulletType = BULLET_PATTERN_NONE;
				}

			}
		}
		break;
	case BULLET_PATTERN_All_DIR://�S���ʃV���b�g
		//10�i�K�̃o���b�g����
		for (int nCount = 0; nCount<10; nCount++)
		{
			//10��̊Ԋu�̏���
			if (nConutBullet[nCount] == 10 * nCount)
			{
				//���20���̏���
				for (int nNumberBullet = 20 * nCount; nNumberBullet < 20 * (nCount + 1); nNumberBullet++)
				{
					//���̌��������炷
					m_rot[nNumberBullet].x = sinf(Spiral() + (2.0f*nNumberBullet))*4.0f;
					m_rot[nNumberBullet].y = cosf(Spiral() + (2.0f*nNumberBullet))*4.0f;
					//�o���b�g���ˁi���ˏꏊ�ƌ������ƃo���b�g�^�C�v�j
					CEnemyBullet::Create(m_pos, m_rot[nNumberBullet]);
					
					//�o���b�g�̎g�p���
					m_bBullet[nNumberBullet] = true;
					//�U���I������
					if (m_bBullet[MAX_BOSS_BULLET - 1] == true)
					{
						//�U�����I���ifalse�j�ɂ���
						m_bBulletMode = false;
						//�o���b�g�^�C�v��ς���
						m_BulletType = BULLET_PATTERN_NONE;
					}

				}
			}
		}
		break;
	case BULLET_PATTERN_SPLIT://����V���b�g
		//�ꔭ�ڂ̔��ˏ���
		if (nConutBullet[0] == 10)
		{
			m_pBullet = CEnemyBullet::Create(m_pos, D3DXVECTOR3(0.0f, 3.5f, 0.0f));
		}
	
		for (int nCount = 0; nCount < 10; nCount++)
		{
			if (nConutBullet[nCount] == 20 * nCount)
			{
				for (int nNumberBullet = 20 * nCount; nNumberBullet < 20 * (nCount + 1); nNumberBullet++)
				{
					//�o���b�g�̕��������߂�
					if (nNumberBullet % 2 == 0)
					{
						m_rot[nNumberBullet].x = 0.7f;
					}
					else
					{
						m_rot[nNumberBullet].x = -0.7f;
					}

					//�o���b�g���ˁi���ˏꏊ�ƌ������ƃo���b�g�^�C�v�j
					CEnemyBullet::Create(m_pBullet->GetPos(), m_rot[nNumberBullet]);
					//�o���b�g���g�p��Ԃɂ���
					m_bBullet[nNumberBullet] = true;

					//�U���I������
					if (m_bBullet[MAX_BOSS_BULLET - 1] == true)
					{
						//�U�����I���ifalse�j�ɂ���
						m_bBulletMode = false;
						//�o���b�g�^�C�v��ς���
						m_BulletType = BULLET_PATTERN_NONE;
					}
				}
			}
		}

		break;
	case BULLET_PATTERN_HOMING2://�z�[�~���O�V���b�g2
		int nPosx = 100;
		int nPosy = 100;

		for (int nCount = 0; nCount<4; nCount++)
		{

			for (int nNumberBullet = 0; nNumberBullet < 20; nNumberBullet++)
			{
				if (nConutBullet[(nNumberBullet)+(nCount * 20)] >= 10 * ((nNumberBullet)+(nCount * 20))
					&& m_bBullet[(nNumberBullet)+(nCount * 20)] == false)
				{
					if (nCount % 2 == 0)
					{
						nPosy *= -1;
					}
					if (nCount >= 2)
					{
						nPosx *= -1;
					}

					D3DXVECTOR3 pos = D3DXVECTOR3((float)(STAGE_POS + nPosx), (float)(SCREEN_HEIGHT / 2) + (float)nPosy, 0.0f);
					m_rot[(nNumberBullet)+(nCount * 20)] = Tracking(4, pos);

					CEnemyBullet::Create(D3DXVECTOR3((float)(STAGE_POS + nPosx), (float)(SCREEN_HEIGHT / 2) + (float)nPosy, 0.0f), m_rot[(nNumberBullet)+(nCount * 20)]);
					m_bBullet[(nNumberBullet)+(nCount * 20)] = true;

				}
			}
		}
		if (m_bBullet[80 - 1] == true)
		{
			m_bBulletMode = false;
			m_BulletType = BULLET_PATTERN_NONE;
		}

		break;

	}

}

//----------------------------------
//�ǔ�����
//----------------------------------
D3DXVECTOR3 CBoss::Tracking(float fSpeed, D3DXVECTOR3 Pos)
{
	D3DXVECTOR3 rot;
	//�v���C���[�̕���
	if (CGame::GetPlayer() != NULL)
	{
		D3DXVECTOR3 Playerpos = (CGame::GetPlayer())->GetPos();
		float fAngle = atan2f((-Pos.x + Playerpos.x), (-Pos.y + Playerpos.y));
		rot.x = sinf(fAngle)*fSpeed;
		rot.y = cosf(fAngle)*fSpeed;
		return rot;
	}
	return rot;
}

//----------------------------------
//�����_������
//----------------------------------
D3DXVECTOR3 CBoss::Random(float fSpeed)
{
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);;
	//�v���C���[�̕���
	if (CGame::GetPlayer() != NULL)
	{
		D3DXVECTOR3 Playerpos = CGame::GetPlayer()->GetPos();
		int nRandom = rand() % 1500 + 1;
		float fAngle = atan2f((-m_pos.x + Playerpos.x), (-m_pos.y + Playerpos.y)) + (float)nRandom / 1000.0f - 0.75f;
		rot.x = sinf(fAngle)*fSpeed;
		rot.y = cosf(fAngle)*fSpeed;
		return rot;
	}
	return rot;
}

//----------------------------------
//������������
//----------------------------------
float CBoss::Spiral(void)
{
	//�v���C���[�̕���
	if (CGame::GetPlayer()!=NULL)
	{
		D3DXVECTOR3 Playerpos = CGame::GetPlayer()->GetPos();
		float fAngle = atan2f((-m_pos.x + Playerpos.x), (-m_pos.y + Playerpos.y));
		return fAngle;
	}
	return NULL;
}

//----------------------------------
//�����蔻��
//----------------------------------
void CBoss::Hit(D3DXVECTOR3 Pos)
{
	//�V�[���擾�p
	CScene* pTop[PRIORITY_MAX] = {};
	//���`�F�b�N����V�[���|�C���^
	CScene* pNext = NULL;

	//top�̃A�h���X���擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}


	//�v���C���[�Ƃ̓����蔻��
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
			while (pNext != NULL)
			{
				//�I�u�W�F�N�g�̃^�C�v���v���C���[�Ȃ�
				if (pNext->GetObjType() == OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					//�����蔻��
					if (Playerpos.x > Pos.x - m_size.x / 2
						&& Playerpos.x  < Pos.x + m_size.x / 2
						&& Playerpos.y > Pos.y - m_size.y / 2
						&& Playerpos.y < Pos.y + m_size.y / 2)
					{
						((CPlayer*)pNext)->Damage(1);
					}

				}
				//���̃I�u�W�F�N�g�̃|�C���^���X�V
				pNext = pNext->GetNext();

			}
		}

	}

}
