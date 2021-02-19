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
//静的メンバー変数
//----------------------------------
bool CBoss::m_bDie = false;
TEXTURE_DATA CBoss::m_TextureData[BOSS_TYPE_MAX] = 
{ { NULL,"data/TEXTURE/Boss_1.png" },
{ NULL,	"data/TEXTURE/Boss_2.png" },
{ NULL,	"data/TEXTURE/Boss_3.png" },
};

//----------------------------------
//コンストラクタ
//----------------------------------
CBoss::CBoss(int nPriorit):CScene2d(nPriorit)
{
	m_bBulletMode = false;
	m_Stats = STATS_MODE_NORMAL;
	m_move= D3DXVECTOR3(0, 0, 0);
	m_BulletType = BULLET_PATTERN_NONE;
	m_bDie = true;
	m_nBulletCoolTime = NULL;
	CScene::SetObjType(CScene::OBJ_TYPE_ENEMY);		//タイプ処理
	m_pBullet = NULL;								//球のクラス初期化
	for (int nNumberBullet = 0; nNumberBullet < MAX_BOSS_BULLET; nNumberBullet++)
	{
		nConutBullet[nNumberBullet]=0;
		m_rot[nNumberBullet] = D3DXVECTOR3(0, 0, 0);
		m_bBullet[nNumberBullet] = false;
	}

}

//----------------------------------
//デストラクタ
//----------------------------------
CBoss::~CBoss()
{
	m_bDie = false;
}

//----------------------------------
//テクスチャ読み込み処理
//----------------------------------
HRESULT CBoss::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < BOSS_TYPE_MAX; nCount++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, m_TextureData[nCount].m_cFileName, &m_TextureData[nCount].m_Texture);
	}
	return S_OK;
}

//----------------------------------
//テクスチャ破棄処理
//----------------------------------
void CBoss::Unload(void)
{
	//テクスチャの破棄
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
//生成処理
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
//初期化処理
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

	//初期化処理
	CScene2d::Init();

	return S_OK;
}

//----------------------------------
//終了処理
//----------------------------------
void CBoss::Uninit(void)
{
	CScene2d::Uninit();
}

//----------------------------------
//更新処理
//----------------------------------
void CBoss::Update(void)
{
	CScene2d::Update();
	switch (m_Type)
	{
	case BOSS_TYPE_1:
		Hit(m_pos);		//当たり判定
		Bullet(m_BulletType, m_pos);
		break;
	case BOSS_TYPE_2:
		Hit(m_pos);		//当たり判定
		Bullet(m_BulletType, m_pos);
		break;

	case BOSS_TYPE_3:
		Hit(m_pos);		//当たり判定
		Bullet(m_BulletType, m_pos);
		break;

	}
	StatasManage();

}

//----------------------------------
//描画処理
//----------------------------------
void CBoss::Draw(void)
{
	CScene2d::Draw();
}

//----------------------------------
//ダメージ処理
//----------------------------------
void CBoss::Damage(int nDamage)
{
	if (m_Stats == STATS_MODE_NORMAL)
	{
		//ライフダメージ
		m_nLife -= nDamage;
		//状態変換
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
		//ダメージカラー処理
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;
	case STATS_MODE_DAMAGE:
		//ダメージカラー処理
		SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.0f));
		m_Stats = STATS_MODE_NORMAL;

		break;
	case STATS_MODE_DEATH:
		CScore *pScore = CGame::GetScore();		//スコアクラス取得
		CSound *pSound = CManager::GetSound();	//サウンドクラス取得

		//スコアアップ
		pScore->AddScore(nScore);

		//デリート時のエフェクト
		switch (m_Type)
		{
		case BOSS_TYPE_1:
			//サウンドの再生
			pSound->Play(CSound::LABEL_SE_BOSS_DIE_2);


			CBossAnime::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), D3DXVECTOR3(800, m_size.y, 0.0f), CBossAnime::BOSS_ANIME_2);

			break;
		
		case BOSS_TYPE_2:
			//サウンドの再生
			pSound->Play(CSound::LABEL_SE_BOSS_DIE_1);

			CBossAnime::Create(D3DXVECTOR3(m_pos.x, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, SCREEN_HEIGHT, 0.0f), CBossAnime::BOSS_ANIME_4);
			break;
		case BOSS_TYPE_3:
			//サウンドの再生
			pSound->Play(CSound::LABEL_SE_BOSS_DIE_2);

			CBossAnime::Create(D3DXVECTOR3(m_pos.x, m_pos.y-50 / 2, 0.0f), D3DXVECTOR3(800, m_size.y, 0.0f), CBossAnime::BOSS_ANIME_6);
			break;

		}
	
		//エフェクトを消す
		if (m_BossAnime != NULL)
		{
			m_BossAnime->Uninit();

		}
		CBoss::Uninit();
		break;
	}

}

//----------------------------------
//回転処理
//----------------------------------
void CBoss::Rotate(void)
{
	static float fRot = 0;
	//向きセット
	SetRot(fRot);
	fRot++;
	if (fRot>360.0f)
	{
		fRot = 0;
	}
}

//----------------------------------
//バレット処理
//----------------------------------
void CBoss::Bullet(BOSS_PATTERN_BULLET BulletMode, D3DXVECTOR3 Pos)
{
	for (int nNumberBullet = 0; nNumberBullet < MAX_BOSS_BULLET; nNumberBullet++)
	{
		nConutBullet[nNumberBullet]++;
	}
	switch (BulletMode)
	{
	case BULLET_PATTERN_NONE://何もしない
		//クールタイム
		m_nBulletCoolTime++;
		if (m_nBulletCoolTime >= 100)
		{
			//前の攻撃が終わっているか
			if (m_bBulletMode == false)
			{
				//攻撃処理の初期化
				for (int nNumberBullet = 0; nNumberBullet < MAX_BOSS_BULLET; nNumberBullet++)
				{
					nConutBullet[nNumberBullet] = 0;
					m_rot[nNumberBullet] = D3DXVECTOR3(0, 0, 0);
					m_bBullet[nNumberBullet] = false;
				}
				//ランダム関数の初期化
				srand((unsigned)time(NULL));
				//ランダムに次の攻撃方法を決める（ボスごとに違う）
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
				//クールタイムの初期化
				m_nBulletCoolTime = 0;
			}


		}
		break;
	case BULLET_PATTERN_SHOTS://通常ショット
		//10発のバレット処理
		for (int nNumberBullet = 0; nNumberBullet < 10; nNumberBullet++)
		{
			//クールタイムが一定になったら一発ずつ撃つ
			if (nConutBullet[nNumberBullet] >= 20 * (nNumberBullet + 1)
				&& m_bBullet[nNumberBullet] == false)
			{
				//向きを相手の向きに処理（速度と場所）
				m_rot[nNumberBullet] = Tracking(7,m_pos);
				//バレット発射（発射場所と撃つ方向とバレットタイプ）
				CEnemyBullet::Create(m_pos, m_rot[0]);
				//バレットの使用状態
				m_bBullet[nNumberBullet] = true;
				//攻撃終了処理
				if (m_bBullet[10-1] ==true)
				{
					//攻撃を終了（false）にする
					m_bBulletMode = false;
					//バレットタイプを変える
					m_BulletType = BULLET_PATTERN_NONE;
				}
			}
		}
		break;
	case BULLET_PATTERN_HOMING://追尾ショット
		//10発のバレット処理
		for (int nNumberBullet = 0; nNumberBullet < 10; nNumberBullet++)
		{
			//クールタイムが一定になったら一発ずつ撃つ
			if (nConutBullet[nNumberBullet] >= 20 * (nNumberBullet + 1)
				&& m_bBullet[nNumberBullet] == false)
			{
				//向きを相手の向きに処理（速度と場所）
				m_rot[nNumberBullet] = Tracking(7, m_pos);
				//バレット発射（発射場所と撃つ方向とバレットタイプ）
				CEnemyBullet::Create(m_pos, m_rot[nNumberBullet]);
				//バレットの使用状態
				m_bBullet[nNumberBullet] = true;
				//攻撃終了処理
				if (m_bBullet[10-1] == true)
				{
					//攻撃を終了（false）にする
					m_bBulletMode = false;
					//バレットタイプを変える
					m_BulletType = BULLET_PATTERN_NONE;
				}

			}
		}
		break;

		break;
	case BULLET_PATTERN_BUCKSHOT://散弾ショット
		//70発のバレット処理
		for (int nNumberBullet = 0; nNumberBullet < 70; nNumberBullet++)
		{
			//クールタイムが一定になったら一発ずつ撃つ
			if (nConutBullet[nNumberBullet] == 2 * nNumberBullet
				&&m_bBullet[nNumberBullet] == false)
			{
				//向きをランダムに処理（速度）
				m_rot[nNumberBullet] = Random(5);
				//バレット発射（発射場所と撃つ方向とバレットタイプ）
				CEnemyBullet::Create(m_pos, m_rot[nNumberBullet]);
				//バレットの使用状態
				m_bBullet[nNumberBullet] = true;
				//攻撃終了処理
				if (m_bBullet[70-1] == true)
				{
					//攻撃を終了（false）にする
					m_bBulletMode = false;
					//バレットタイプを変える
					m_BulletType = BULLET_PATTERN_NONE;
				}

			}
		}
		break;
	case BULLET_PATTERN_SPIRAL://螺旋ショット
		//200発のバレット処理
		for (int nNumberBullet = 0; nNumberBullet < MAX_BOSS_BULLET; nNumberBullet++)
		{
			//一発一発のクールタイム
			if (nConutBullet[nNumberBullet] == nNumberBullet)
			{
				//球の向きをずらす
				m_rot[nNumberBullet].x = sinf(Spiral() + (0.2f*nNumberBullet))*7.0f;
				m_rot[nNumberBullet].y = cosf(Spiral() + (0.2f*nNumberBullet))*7.0f;
				//バレット発射（発射場所と撃つ方向とバレットタイプ）
				CEnemyBullet::Create(m_pos, m_rot[nNumberBullet]);
				//バレットの使用状態
				m_bBullet[nNumberBullet] = true;
				//攻撃終了処理
				if (m_bBullet[MAX_BOSS_BULLET-1] == true)
				{
					//攻撃を終了（false）にする
					m_bBulletMode = false;
					//バレットタイプを変える
					m_BulletType = BULLET_PATTERN_NONE;
				}

			}
		}
		break;
	case BULLET_PATTERN_All_DIR://全方位ショット
		//10段階のバレット処理
		for (int nCount = 0; nCount<10; nCount++)
		{
			//10回の間隔の処理
			if (nConutBullet[nCount] == 10 * nCount)
			{
				//一回20発の処理
				for (int nNumberBullet = 20 * nCount; nNumberBullet < 20 * (nCount + 1); nNumberBullet++)
				{
					//球の向きをずらす
					m_rot[nNumberBullet].x = sinf(Spiral() + (2.0f*nNumberBullet))*4.0f;
					m_rot[nNumberBullet].y = cosf(Spiral() + (2.0f*nNumberBullet))*4.0f;
					//バレット発射（発射場所と撃つ方向とバレットタイプ）
					CEnemyBullet::Create(m_pos, m_rot[nNumberBullet]);
					
					//バレットの使用状態
					m_bBullet[nNumberBullet] = true;
					//攻撃終了処理
					if (m_bBullet[MAX_BOSS_BULLET - 1] == true)
					{
						//攻撃を終了（false）にする
						m_bBulletMode = false;
						//バレットタイプを変える
						m_BulletType = BULLET_PATTERN_NONE;
					}

				}
			}
		}
		break;
	case BULLET_PATTERN_SPLIT://分裂ショット
		//一発目の発射処理
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
					//バレットの方向を決める
					if (nNumberBullet % 2 == 0)
					{
						m_rot[nNumberBullet].x = 0.7f;
					}
					else
					{
						m_rot[nNumberBullet].x = -0.7f;
					}

					//バレット発射（発射場所と撃つ方向とバレットタイプ）
					CEnemyBullet::Create(m_pBullet->GetPos(), m_rot[nNumberBullet]);
					//バレットを使用状態にする
					m_bBullet[nNumberBullet] = true;

					//攻撃終了処理
					if (m_bBullet[MAX_BOSS_BULLET - 1] == true)
					{
						//攻撃を終了（false）にする
						m_bBulletMode = false;
						//バレットタイプを変える
						m_BulletType = BULLET_PATTERN_NONE;
					}
				}
			}
		}

		break;
	case BULLET_PATTERN_HOMING2://ホーミングショット2
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
//追尾処理
//----------------------------------
D3DXVECTOR3 CBoss::Tracking(float fSpeed, D3DXVECTOR3 Pos)
{
	D3DXVECTOR3 rot;
	//プレイヤーの方向
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
//ランダム処理
//----------------------------------
D3DXVECTOR3 CBoss::Random(float fSpeed)
{
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);;
	//プレイヤーの方向
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
//螺旋処理処理
//----------------------------------
float CBoss::Spiral(void)
{
	//プレイヤーの方向
	if (CGame::GetPlayer()!=NULL)
	{
		D3DXVECTOR3 Playerpos = CGame::GetPlayer()->GetPos();
		float fAngle = atan2f((-m_pos.x + Playerpos.x), (-m_pos.y + Playerpos.y));
		return fAngle;
	}
	return NULL;
}

//----------------------------------
//当たり判定
//----------------------------------
void CBoss::Hit(D3DXVECTOR3 Pos)
{
	//シーン取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするシーンポインタ
	CScene* pNext = NULL;

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}


	//プレイヤーとの当たり判定
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				//オブジェクトのタイプがプレイヤーなら
				if (pNext->GetObjType() == OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					//当たり判定
					if (Playerpos.x > Pos.x - m_size.x / 2
						&& Playerpos.x  < Pos.x + m_size.x / 2
						&& Playerpos.y > Pos.y - m_size.y / 2
						&& Playerpos.y < Pos.y + m_size.y / 2)
					{
						((CPlayer*)pNext)->Damage(1);
					}

				}
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();

			}
		}

	}

}
