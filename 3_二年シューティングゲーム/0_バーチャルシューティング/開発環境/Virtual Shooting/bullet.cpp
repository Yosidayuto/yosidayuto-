//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "bullet.h"			//バレット
#include "manager.h"		//マネージャー
#include "renderer.h"		//レンダリング
#include "explosion.h"		//エクスプロージョン
#include "sound.h"			//サウンド
#include "effect.h"			//エフェクト
#include "enemy.h"			//エネミー
#include "boss.h"			//ボス
#include <typeinfo.h>
//----------------------------------
//マクロ定義
//----------------------------------
#define BULLET_SIZE 20		//バレットの大きさ
#define BULLET_LIFE 1000		//バレットの射程距離
//----------------------------------
//静的メンバー変数
//----------------------------------
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;
//----------------------------------
//コンストラクタ
//----------------------------------
CBullet::CBullet(int nPriorit) :CScene2d(nPriorit)
{
	nLife = 0;
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//----------------------------------
//デストラクタ
//----------------------------------
CBullet::~CBullet()
{
}

//----------------------------------
//初期化処理
//----------------------------------
HRESULT CBullet::Init(D3DXVECTOR3 move, BULLET_TYPE Type)
{
	CSound *pSound = CManager::GetSound();	//サウンド取得


	//射程距離
	nLife = BULLET_LIFE;
	//移動量
	m_move = move;
	//タイプ
	m_Type = Type;
	//サイズ
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
	//初期化処理
	CScene2d::Init();
	//テクスチャの設定
	BindTexture(m_pTexture);

	return S_OK;
}

//----------------------------------
//終了処理
//----------------------------------
void CBullet::Uninit(void)
{
	//終了処理
	CScene2d::Uninit();
}

//----------------------------------
//更新処理
//----------------------------------
void CBullet::Update(void)
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

	//ポリゴンの位置取得
	D3DXVECTOR3 pos = GetPos();
	if (m_Type== BULLET_TYPE_PLAYER)
	{
		//エフェクト生成
		CEffect::Create(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(BULLET_SIZE / 2, BULLET_SIZE, 0.0f), CEffect::EFFECT_TYPE_BULLET);
	}


	//位置更新
	pos += m_move;
	//球の射程距離
	nLife --;
	//更新処理
	CScene2d::Update();
	//ポリゴンの位置を渡す
	SetPos(pos);

	//射程距離
	if (nLife <= 0)
	{
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
		//バレット効果処理
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
					case BULLET_TYPE_PLAYER:
						if (pNext->GetObjType() == OBJ_TYPE_ENEMY)
						{
							D3DXVECTOR3 EnemeyPos = ((CScene2d*)pNext)->GetPos();
							D3DXVECTOR3 EnemeySize = ((CScene2d*)pNext)->GetSize();
							//当たり判定
							if (EnemeyPos.x + EnemeySize.x/2 > pos.x
								&& EnemeyPos.x - EnemeySize.x/2 < pos.x
								&&EnemeyPos.y + EnemeySize.y/2 > pos.y
								&&EnemeyPos.y - EnemeySize.y/2 < pos.y)
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
								//バレット終了処理
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
							//当たり判定
							if (PlayerPos.x  > pos.x - m_size.x
								&& PlayerPos.x  < pos.x + m_size.x
								&&PlayerPos.y  > pos.y - m_size.y
								&&PlayerPos.y  < pos.y + m_size.y)
							{
								//エクスプロージョン生成
								CExplosion::Create(PlayerPos);
								//エネミー終了処理
								((CPlayer*)pNext)->Damage(1);
								//バレット終了処理
								Uninit();
								return;
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

//----------------------------------
//描画処理
//----------------------------------
void CBullet::Draw(void)
{
	//描画処理
	CScene2d::Draw();
}

//----------------------------------
//生成処理
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
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Bullet.png", &m_pTexture);	
	return S_OK;
}

void CBullet::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

