//----------------------------------------------
//ヘッダーファイル
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
//マクロ定義
//----------------------------------
#define HOMING_LIFE	50
#define HOMING_SIZE 25
//----------------------------------
//静的メンバー変数
//----------------------------------
LPDIRECT3DTEXTURE9 CHoming::m_pTexture = NULL;

CHoming::CHoming(int nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
	nLife = 0;
	m_move = D3DXVECTOR3(0.0f, -3.0f, 0.0f);

}

CHoming::~CHoming()
{
}

HRESULT CHoming::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Bullet.png", &m_pTexture);
	return S_OK;
}

void CHoming::Unload(void)
{
	//テクスチャの破棄
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
	pHoming->SetPos(Pos);
	pHoming->Init(nSpeed, Type);
	return pHoming;
}

HRESULT CHoming::Init(int nSpeed, HOMING_TYPE Type)
{
	CSound *pSound = CManager::GetSound();	//サウンド取得

	//射程距離
	nLife = HOMING_LIFE;
	//スピード　
	m_nSpeed = nSpeed;
	//タイプ
	m_Type = Type;
	if (m_Type == HOMING_TYPE_PLAYER)
	{
		pSound->Play(CSound::LABEL_SE_SHOTS);
	}
	//サイズ
	SetSize(D3DXVECTOR3(HOMING_SIZE / 2, HOMING_SIZE / 2, 0.0f));
	//テクスチャの設定
	BindTexture(m_pTexture);


	//初期化処理
	CScene2d::Init();
	return S_OK;
}

void CHoming::Uninit(void)
{
	//終了処理
	CScene2d::Uninit();
}

void CHoming::Update(void)
{
	//ポリゴンの位置取得
	D3DXVECTOR3 pos = GetPos();
	//オブジェクト取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするオブジェクトのポインタ
	CScene* pNext = NULL;

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	//エフェクト生成
	CEffect::Create(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(HOMING_SIZE / 2, HOMING_SIZE, 0.0f), CEffect::EFFECT_TYPE_BULLET);

	int nRange =780;
	float fAngle;
	//オブジェクト探査
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				switch (m_Type)
				{
				case HOMING_TYPE_PLAYER:
					if (pNext->GetObjType() == OBJ_TYPE_ENEMY)
					{
						D3DXVECTOR3 EnemeyPos = ((CScene2d*)pNext)->GetPos();
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
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();
			}
		}
	}

	//位置更新
	pos += m_move;
	//球の射程距離
	nLife--;

	//ポリゴンの位置を渡す
	SetPos(pos);
	//更新処理
	CScene2d::Update();

	//射程距離
	if (nLife <= 0)
	{
		CExplosion::Create(pos);
		Uninit();	//終了処理
		return;

	}
	//画面外に出た時
	else if (pos.y < 0 || pos.y>SCREEN_HEIGHT || pos.x<0 || pos.x>SCREEN_WIDTH)
	{
		Uninit();	//終了処理
		return;
	}
	if (nLife > 0)		//射程距離内
	{
		//topのアドレスを取得
		for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
		{
			pTop[nCount] = *(CScene::GetTop() + nCount);
		}

		//ホーミング効果処理
		for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
		{
			if (pTop[nCount] != NULL)
			{
				pNext = pTop[nCount];
				//その描画優先度のオブジェクトがなくなるまでループ
				while (pNext != NULL)
				{
					switch (m_Type)
					{
					case HOMING_TYPE_PLAYER:
						if (pNext->GetObjType() == OBJ_TYPE_ENEMY)
						{
							D3DXVECTOR3 EnemeyPos = ((CScene2d*)pNext)->GetPos();
							D3DXVECTOR3 EnemeySize = ((CScene2d*)pNext)->GetSize();
							//当たり判定
							if (EnemeyPos.x + EnemeySize.x / 2 > pos.x
								&& EnemeyPos.x - EnemeySize.x / 2 < pos.x
								&&EnemeyPos.y + EnemeySize.y / 2 > pos.y
								&&EnemeyPos.y - EnemeySize.y / 2 < pos.y)
							{
								//エネミーダメージ処理
								if (typeid(*pNext) == typeid(CEnemy))
								{
									//エクスプロージョン生成
									CExplosion::Create(EnemeyPos);

									((CEnemy*)pNext)->Damage(1);
								}
								else if (typeid(*pNext) == typeid(CBoss))
								{
									//エクスプロージョン生成
									CExplosion::Create(pos);

									((CBoss*)pNext)->Damage(1);
								}
								Uninit();
								break;
							}
						}
						break;
					}
					//次のオブジェクトのポインタを更新
					pNext = pNext->GetNext();

				}
			}
		}
	}

}

void CHoming::Draw(void)
{
	//描画処理
	CScene2d::Draw();
}

int CHoming::TargetGet(D3DXVECTOR3 pos, D3DXVECTOR3 EnemyPos)
{
			
	//タイプ取得
	switch (m_Type)
	{
	case HOMING_TYPE_PLAYER:
			float nDistance = (pos.x- EnemyPos.x)*(pos.x - EnemyPos.x) + (pos.y - EnemyPos.y)*(pos.y - EnemyPos.y);
			return (int)(sqrt(nDistance));
		break;
	
	}
			
	return 0;
}
