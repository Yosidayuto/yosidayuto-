//=============================================================================
//
// エネミーベース処理 [enemy base.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy base.h"
#include "score.h"
#include "game.h"
#include "player.h"
#include "enemy type1.h"
#include "enemy type2.h"
#include "enemy type3.h"
#include "enemy type4.h"
#include "shots.h"
#include "spiral.h"
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// コンストラクト
//=============================================================================
CEnemyBase::CEnemyBase(int nPriorit)
{
	m_nLife = 0;
	m_Score = 0;
	m_nPointer = 0;
	m_bAttack = false;
	m_Stats = STATS_MODE_NORMAL;
	m_Shots = BULLET_PATTERN_NONE;
	memset(m_move,NULL, sizeof(m_move));
	memset(m_movePointer, NULL, sizeof(m_movePointer));
	SetObjType(OBJ_TYPE_ENEMY);				//タイプ処理
	m_pShotsBase = NULL;
}

//=============================================================================
// デストラクト
//=============================================================================
CEnemyBase::~CEnemyBase()
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CEnemyBase::Load(void)
{
	CEnemyType1::Load();
	CEnemyType2::Load();
	CEnemyType3::Load();
	CEnemyType4::Load();

	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CEnemyBase::Unload(void)
{
	CEnemyType1::Unload();
	CEnemyType2::Unload();
	CEnemyType3::Unload();
	CEnemyType4::Unload();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemyBase::Init(void)
{
	//初期化処理
	CScene2d::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemyBase::Uninit(void)
{
	if (m_pShotsBase!=NULL)
	{
		m_pShotsBase->Uninit();
		m_pShotsBase = NULL;
	}
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyBase::Update(void)
{
	CScene2d::Update();
	//当たり判定
	Hit();
	//移動処理
	Move();
	//ステータ管理
	StatasManage();
	//ショットの更新
	if (m_pShotsBase!=NULL)
	{
		m_pShotsBase->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemyBase::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// ダメージ処理
//=============================================================================
void CEnemyBase::Damage(int nDamage)
{
	//状態確認
	if (m_Stats == STATS_MODE_NORMAL)
	{
		//ライフダメージ
		m_nLife -= nDamage;
		
		//ライフが0なら
		if (m_nLife > 0)
		{
			//死亡状態に移行
			m_Stats = STATS_MODE_DAMAGE;
			return;
		}
		//ダメージ状態に移行
		m_Stats = STATS_MODE_DEATH;
	}

}

//=============================================================================
// エネミーの状態管理処理
//=============================================================================
void CEnemyBase::StatasManage(void)
{
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
		//スコアポインタ取得
		CScore *pScore = CGame::GetScore();
		//スコア加算
		pScore->AddScore(m_Score);
		//終了
		CEnemyBase::Uninit();
		break;
	}

}

//=============================================================================
// 回転処理
//=============================================================================
void CEnemyBase::Rotate(void)
{
	//回転角度
	static float fRot = 0;
	
	//向きセット
	SetRot(fRot);
	//回転角度プラス
	fRot += 2.0f;
	//回転角度が一定に達したら
	if (fRot>360.0f)
	{
		//角度初期化
		fRot = 0;
	}

}

//=============================================================================
// ショット判定
//=============================================================================
void CEnemyBase::Bullet(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	if (!m_bAttack)
	{
		switch (m_Shots)
		{
		case BULLET_PATTERN_SHOTS:
			m_pShotsBase = CShots::Create(pos);
			m_Shots = BULLET_PATTERN_NONE;
			break;
		case BULLET_PATTERN_SPIRAL:
			m_pShotsBase = CSpiral::Create(pos);
			m_Shots = BULLET_PATTERN_NONE;
			break;
		}
		m_bAttack = true;
	}
}

//=============================================================================
// 当たり判定
//=============================================================================
void CEnemyBase::Hit(void)
{
	//オブジェクト取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするオブジェクトのポインタ
	CScene* pNext = NULL;
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

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
					if (Playerpos.x > pos.x - size.x / 2
						&& Playerpos.x  < pos.x + size.x / 2
						&& Playerpos.y > pos.y - size.y / 2
						&& Playerpos.y < pos.y + size.y / 2)
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

//=============================================================================
// 移動処理
//=============================================================================
void CEnemyBase::Move(void)
{
	//目標の方向
	float fAngle;
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//サイズ取得
	D3DXVECTOR3 size = GetSize();
	//移動位置
	if (m_nPointer>0)
	{
		if (pos.x + 1.0f>m_movePointer[m_nPointer].x
			&&pos.x - 1.0f<m_movePointer[m_nPointer].x
			&&pos.y + 1.0f>m_movePointer[m_nPointer].y
			&&pos.y - 1.0f<m_movePointer[m_nPointer].y)
		{
			//次の位置
			m_nPointer--;
		}
		//目標の位置方向取得
		fAngle = atan2f((-pos.x + m_movePointer[m_nPointer].x), (-pos.y + m_movePointer[m_nPointer].z));
		//目標までの移動
		m_move.x = sinf(fAngle) * 1.0f;
		m_move.y = cosf(fAngle) * 1.0f;
		//位置更新
		pos += m_move;
		//位置設定
		SetPos(pos);

		//画面外処理
		if (pos.y > SCREEN_HEIGHT+(size.y / 2)						// 画面下
			|| pos.x > (STAGE_POS+ STAGE_SIZE /2)+ (size.x / 2)		// 画面右
			|| pos.x < (STAGE_POS - STAGE_SIZE / 2) - (size.x / 2))	// 画面左
		{
			//終了
			CEnemyBase::Uninit();
		}
	}
}

//=============================================================================
// 移動量セッター
//=============================================================================
void CEnemyBase::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 移動量ゲッター
//=============================================================================
D3DXVECTOR3 CEnemyBase::GetMove(void)
{
	return m_move;
}

//=============================================================================
// ライフセッター
//=============================================================================
void CEnemyBase::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// ライフセッター
//=============================================================================
int CEnemyBase::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// スコアセッター
//=============================================================================
void CEnemyBase::SetScore(int nScore)
{
	m_Score = nScore;
}

//=============================================================================
// スコアゲッター
//=============================================================================
int CEnemyBase::GetScore(void)
{
	return m_Score;
}

//=============================================================================
// 移動地点ポインター
//=============================================================================
void CEnemyBase::SetMovePointer(D3DXVECTOR3 pointer, int nPointer)
{
	m_nPointer = nPointer;
	m_movePointer[m_nPointer] = pointer;
}

//=============================================================================
// 攻撃パターンセッター
//=============================================================================
void CEnemyBase::SetPattern(ENEMY_PATTERN type)
{
	m_Shots = type;
}

//=============================================================================
// 攻撃パターンゲッター
//=============================================================================
ENEMY_PATTERN CEnemyBase::GetPattern(void)
{
	return m_Shots;
}
