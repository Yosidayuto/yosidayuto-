#include "enemy.h"
#include "manager.h"
#include "enemy bullet.h"
#include "renderer.h"
#include "sound.h"
#include "player.h"
#include "score.h"
#include "game.h"

//----------------------------------
//マクロ定義
//----------------------------------
//----------------------------------
//静的メンバー変数
//----------------------------------
LPDIRECT3DTEXTURE9 CEnemy::m_Texture[ENEMY_TYPE_MAX] = {};
char * CEnemy::pTexture[ENEMY_TYPE_MAX]=
{
	"data/TEXTURE/Enemy_1.png",
	"data/TEXTURE/Enemy_2.png",
	"data/TEXTURE/Enemy_3.png",
	"data/TEXTURE/Enemy_4.png",
};
//----------------------------------
//コンストラクタ
//----------------------------------
CEnemy::CEnemy(int nPriorit):CScene2d(nPriorit)
{
	for (int nConut=0;nConut<MAX_ENEMY_BULLET; nConut++)
	{
		m_bBullet[nConut] = false;
		nConutBullet[nConut] = 0;
		m_rot[nConut] = D3DXVECTOR3(0, 0, 0);//エネミーの向き
		memset(m_rot, NULL, sizeof(m_rot));
	}
	SetObjType(OBJ_TYPE_ENEMY);				//タイプ処理
	m_Stats = STATS_MODE_NORMAL;			//エネミーの状態
	m_PatternCount = 0;						//パターンカウント
	memset(m_move, NULL, sizeof(m_move));	//移動量

}

//----------------------------------
//デストラクタ
//----------------------------------
CEnemy::~CEnemy()
{
}
//----------------------------------
//生成処理
//----------------------------------
CEnemy * CEnemy::Create(D3DXVECTOR3 Pos, ENEMY_TYPE nType, PATTERN_MODE nPattern, int nCountPattern, BULLET_PATTERN BulletMode, D3DXVECTOR3 size)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy;
	pEnemy->m_Type = nType;
	pEnemy->m_Pattern = nPattern;
	pEnemy->m_PatternCount= nCountPattern;
	pEnemy->m_size = size;
	pEnemy->m_BulletMode = BulletMode;
	pEnemy->SetPos(Pos);
	pEnemy->SetSize(size);
	pEnemy->SetTexture(nType);
	
	pEnemy->Init();

	return pEnemy;
}

//----------------------------------
//テクスチャ読み込み処理
//----------------------------------
HRESULT CEnemy::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < ENEMY_TYPE_MAX; nCount++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, pTexture[nCount], &m_Texture[nCount]);
	}
	return S_OK;
}

//----------------------------------
//テクスチャ破棄処理
//----------------------------------
void CEnemy::Unload(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < ENEMY_TYPE_MAX; nCount++)
	{
		if (m_Texture[nCount] != NULL)
		{
			m_Texture[nCount]->Release();
			m_Texture[nCount] = NULL;
		}
	}

}

//----------------------------------
//初期化処理
//----------------------------------
HRESULT CEnemy::Init(void)
{
	switch (m_Type)
	{
	case ENEMY_TYPE_1:
		m_nLife = 2;
		m_nScore = 100;
		m_move = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
		break;
	case ENEMY_TYPE_2:
		m_nLife = 1;
		m_nScore = 200;
		m_move = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
		break;
	case ENEMY_TYPE_3:
		m_nLife = 3;
		m_nScore = 300;
		m_move = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
		break;
	case ENEMY_TYPE_4:
		m_nLife = 2;
		m_nScore = 400;
		m_move = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
		break;
	}

	//初期化処理
	CScene2d::Init();

	return S_OK;
}

//----------------------------------
//終了処理
//----------------------------------
void CEnemy::Uninit(void)
{
	CScene2d::Uninit();
}

//----------------------------------
//更新処理
//----------------------------------
void CEnemy::Update(void)
{	
	CScene2d::Update();
	m_pos = GetPos();	//エネミー位置
	switch (m_Type)
	{
	case ENEMY_TYPE_1:
		Hit(m_pos);		//当たり判定
		Move(m_pos);			//動き
		break;
	case ENEMY_TYPE_2:
		Hit(m_pos);		//当たり判定
		Rotate();				//回転
		Move(m_pos);			//動き
		break;
	case ENEMY_TYPE_3:
		Hit(m_pos);		//当たり判定
		Move(m_pos);			//動き
		break;
	case ENEMY_TYPE_4:
		Hit(m_pos);		//当たり判定
		//Bullet(10, m_pos, Tracking(5.0f));	//攻撃
		Move(m_pos);			//動き
		break;
	}
	Bullet(m_BulletMode);
	StatasManage();


}

//----------------------------------
//描画処理
//----------------------------------
void CEnemy::Draw(void)
{
	CScene2d::Draw();
}


//----------------------------------
//テクスチャセット
//----------------------------------
void CEnemy::SetTexture(ENEMY_TYPE nType)
{
	BindTexture(m_Texture[nType]);
}

//----------------------------------
//ダメージ処理
//----------------------------------
void CEnemy::Damage(int nDamage)
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
//----------------------------------
//エネミーの状態管理
//----------------------------------
void CEnemy::StatasManage(void)
{
	int nScore=0;
	switch (m_Stats)
	{
	case STATS_MODE_NORMAL:
		//ダメージカラー処理
		//SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;
	case STATS_MODE_DAMAGE:
		//ダメージカラー処理
		//SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.0f));

		m_Stats = STATS_MODE_NORMAL;

		break;
	case STATS_MODE_DEATH:
		CScore *pScore = CGame::GetScore();
		switch (m_Type)
		{
		case ENEMY_TYPE_1:
			nScore = 200;
			break;
		case ENEMY_TYPE_2:
			nScore = 100;
			break;
		case ENEMY_TYPE_3:
			nScore = 50;
			break;
		case ENEMY_TYPE_4:
			nScore = 500;
			break;

		}

		pScore->AddScore(m_Type*100);
		CEnemy::Uninit();
		break;
	}

}
//----------------------------------
//回転処理
//----------------------------------
void CEnemy::Rotate(void)
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
void CEnemy::Bullet(BULLET_PATTERN BulletMode)
{
	for (int nNumberBullet = 0; nNumberBullet < MAX_ENEMY_BULLET; nNumberBullet++)
	{
		nConutBullet[nNumberBullet]++;
	}
	switch (BulletMode)
	{
	case BULLET_PATTERN_NONE://何もしない
		break;
	case BULLET_PATTERN_SHOTS://通常ショット
	
		for (int nNumberBullet = 0; nNumberBullet < 10; nNumberBullet++)
		{
			if (nConutBullet[nNumberBullet] >=20 * (nNumberBullet+1)
				&& m_bBullet[nNumberBullet]== false)
			{
				m_rot[nNumberBullet] = Tracking(7);
				CEnemyBullet::Create(m_pos, m_rot[0]);
				m_bBullet[nNumberBullet] = true;
			}
		}
		break;
	case BULLET_PATTERN_HOMING://追尾ショット
		for (int nNumberBullet = 0; nNumberBullet < 10; nNumberBullet++)
		{

			if (nConutBullet[nNumberBullet] >= 20 * (nNumberBullet + 1)
				&& m_bBullet[nNumberBullet] == false)
			{
				m_rot[nNumberBullet] = Tracking(7);
				CEnemyBullet::Create(m_pos, m_rot[nNumberBullet]);
				m_bBullet[nNumberBullet] = true;
			}
		}
		break;

		break;
	case BULLET_PATTERN_BUCKSHOT://散弾ショット
		for (int nNumberBullet = 0; nNumberBullet < MAX_ENEMY_BULLET; nNumberBullet++)
		{
			if (nConutBullet[nNumberBullet] == 2 * nNumberBullet
				&&m_bBullet[nNumberBullet] == false)
			{
				m_rot[nNumberBullet] = Random(5);
				CEnemyBullet::Create(m_pos, m_rot[nNumberBullet]);
				m_bBullet[nNumberBullet] = true;
			}
		}
		break;
	case BULLET_PATTERN_SPIRAL://螺旋ショット
		for (int nNumberBullet = 0; nNumberBullet < MAX_ENEMY_BULLET; nNumberBullet++)
		{
			if (nConutBullet[nNumberBullet] == nNumberBullet)
			{
				
				m_rot[nNumberBullet].x = sinf(Spiral() + (0.2f*nNumberBullet))*7.0f;
				m_rot[nNumberBullet].y = cosf(Spiral() + (0.2f*nNumberBullet))*7.0f;

				CEnemyBullet::Create(m_pos, m_rot[nNumberBullet]);
			}
		}
		break;
	case BULLET_PATTERN_All_DIR://全方位ショット
		for (int nCount=0;nCount<10;nCount++)
		{
			if (nConutBullet[nCount]== 10 * nCount)
			{
				for (int nNumberBullet = 20 * nCount; nNumberBullet < 20 * (nCount + 1); nNumberBullet++)
				{
						m_rot[nNumberBullet].x = sinf(Spiral() + (2.0f*nNumberBullet))*4.0f;
						m_rot[nNumberBullet].y = cosf(Spiral() + (2.0f*nNumberBullet))*4.0f;
						CEnemyBullet::Create(m_pos, m_rot[nNumberBullet]);
				}
			}
		}
		break;
	}
}

//----------------------------------
//追尾処理
//----------------------------------
D3DXVECTOR3 CEnemy::Tracking(float fSpeed)
{
	D3DXVECTOR3 rot;
	//シーン取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするシーンポインタ
	CScene* pNext = NULL;

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}


	//プレイヤーの方向
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				//オブジェクトのタイプがエネミーなら
				if (pNext->GetObjType() == OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					float fAngle = atan2f((-m_pos.x + Playerpos.x), (-m_pos.y + Playerpos.y));
					rot.x = sinf(fAngle)*fSpeed;
					rot.y = cosf(fAngle)*fSpeed;
					return rot;
				}
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();
			}
		}
	}
	return rot;
}
//----------------------------------
//ランダム処理
//----------------------------------
D3DXVECTOR3 CEnemy::Random(float fSpeed)
{
	D3DXVECTOR3 rot= D3DXVECTOR3(0.0f,0.0f,0.0f);

	//シーン取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするシーンポインタ
	CScene* pNext = NULL;

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	//プレイヤーの方向
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				//オブジェクトのタイプがプレイヤーなら
				if (pNext->GetObjType() == OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					int nRandom =	rand() % 1500 + 1;
					float fAngle = atan2f((-m_pos.x + Playerpos.x), (-m_pos.y + Playerpos.y)) + (float)nRandom / 1000.0f - 0.75f;
					rot.x = sinf(fAngle)*fSpeed;
					rot.y = cosf(fAngle)*fSpeed;
					return rot;
				}
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();

			}
		}
	}
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//----------------------------------
//螺旋処理処理
//----------------------------------
float CEnemy::Spiral(void)
{
	D3DXVECTOR3 rot;
	float fAngle = 0;

	//オブジェクト取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするオブジェクトのポインタ
	CScene* pNext = NULL;

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	//オブジェクト探査
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				if (pNext->GetObjType() == OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					fAngle = atan2f((-m_pos.x + Playerpos.x), (-m_pos.y + Playerpos.y));
					return fAngle;
				}
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();

			}
		}
	}
	return NULL;
}

//----------------------------------
//移動処理
//----------------------------------
void CEnemy::Move(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 Pos = pos;
	//パターンカウントを減らす
	m_PatternCount--;

	switch (m_Pattern)
	{
	case PATTERN_MODE_STRAIGHT:	//直進処理
		Pos += m_move;
		SetPos(Pos);
		//画面外処理
		if (m_pos.y > 825)
		{
			CEnemy::Uninit();
		}

		break;
	case PATTERN_MODE_CROSS:	//交差処理
		if (m_PatternCount < 0)
		{
			if (Pos.x > 780)
			{
				if (m_move.x == 0)
				{
					m_move.x = -3.0f;
				}

			}
			else if (Pos.x < 780)
			{
				if (m_move.x == 0)
				{
					m_move.x = 3.0f;
				}
			}

		}

		Pos += m_move;

		SetPos(Pos);

		//画面外処理
		if (m_pos.y > 825 || Pos.x > 1180 + (m_size.x / 2) || Pos.x < 380 - (m_size.x / 2))
		{
			CEnemy::Uninit();
		}


		break;
	case PATTERN_MODE_CORNER:	//曲がる処理

		if (m_PatternCount < 0)
		{
			if (Pos.x > 780)
			{
				m_move.x = 3.0f;
			}
			else if (Pos.x < 780)
			{
				m_move.x = -3.0f;
			}

		}
		Pos += m_move;

		SetPos(Pos);

		//画面外処理
		if (m_pos.y > 825 || Pos.x > 1180 + (m_size.x / 2) || Pos.x < 380 - (m_size.x / 2))
		{
			CEnemy::Uninit();
		}

		break;
	case PATTERN_MODE_SIDE:		//横移動処理

		if (m_PatternCount <= 0)
		{
			if (m_move.y > 0)
			{
				m_move.y -= m_move.y;
				if (Pos.x > 780)
				{
					m_move.x = 3.5f;
				}
				else if (Pos.x < 780)
				{
					m_move.x = -3.5f;
				}
			}
		}
		Pos += m_move;

		SetPos(Pos);

		//画面外処理
		if (m_pos.y > 825 || Pos.x > 1180 + (m_size.x / 2) || Pos.x < 380 - (m_size.x / 2))
		{
			CEnemy::Uninit();
		}

		break;
	case PATTERN_MODE_U_TURN:		//Uターン処理
		if (m_PatternCount <= 0)
		{
			if (m_move.y > 0)
			{
				m_move.y -= m_move.y * 2;
			}
			if (Pos.y <= -25)
			{
				Uninit();
				return;
			}
		}
		Pos += m_move;

		SetPos(Pos);

		break;
	case PATTERN_MODE_STOP:
		if (m_PatternCount <= 0)
		{
			if (m_move.y > 0)
			{
				m_move.y -= m_move.y;
			}
		}
		Pos += m_move;
		SetPos(Pos);
		break;

	case PATTERN_MODE_ROUND_TRIP:	//往復処理
		if (m_PatternCount <= 0)
		{
			if (m_move.y > 0)
			{
				m_move.y -= m_move.y;
				m_move.x = 3.5f;
			}
		}
		if (Pos.x > 1180 || Pos.x < 380)
		{
			m_move.x *= -1.0f;
		}
		Pos += m_move;

		SetPos(Pos);
		break;
	}
}

//----------------------------------
//当たり判定
//----------------------------------
void CEnemy::Hit(D3DXVECTOR3 Pos)
{
	//オブジェクト取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするオブジェクトのポインタ
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
					if (Playerpos.x > Pos.x- m_size.x/2
						&& Playerpos.x  < Pos.x+ m_size.x/2
						&&Playerpos.y > Pos.y- m_size.y/2
						&&Playerpos.y < Pos.y+ m_size.y/2)
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

