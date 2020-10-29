//----------------------------------------------
//ヘッダーファイル
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
//マクロ定義
//----------------------------------
#define LASER_SIZE_X 10		//レーザーの大きさ
#define LASER_SIZE_Y 100	//レーザーの大きさ

#define LASER_LIFE 50		//レーザーの射程距離
//----------------------------------
//静的メンバー変数
//----------------------------------
LPDIRECT3DTEXTURE9 CLaser::m_pTexture = NULL;

//----------------------------------
//コンストラクタ
//----------------------------------
CLaser::CLaser(int nPriorit)
{
	nLife = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		m_Hit[nCntScene] = false;

	}
}

//----------------------------------
//デストラクタ
//----------------------------------
CLaser::~CLaser()
{
}

//----------------------------------
//テクスチャ読み込み処理
//----------------------------------
HRESULT CLaser::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Laser.png", &m_pTexture);
	return S_OK;
}

//----------------------------------
//テクスチャ破棄処理
//----------------------------------
void CLaser::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//----------------------------------
//生成処理
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
//初期化処理
//----------------------------------
HRESULT CLaser::Init(D3DXVECTOR3 move, LASER_TYPE Type)
{
	CSound *pSound = CManager::GetSound();	//サウンド取得

	//射程距離
	nLife = LASER_LIFE;
	//移動量
	m_move = move;
	//タイプ
	m_Type = Type;
	if (m_Type== LASER_TYPE_PLAYER)
	{
		pSound->Play(CSound::LABEL_SE_LASER);

	}
	//サイズ
	SetSizeition(D3DXVECTOR3(LASER_SIZE_X / 2, LASER_SIZE_Y / 2, 0.0f));
	//テクスチャの設定
	BindTexture(m_pTexture);


	//初期化処理
	CScene2d::Init();
	return S_OK;
}

//----------------------------------
//終了処理
//----------------------------------
void CLaser::Uninit(void)
{
	//終了処理
	CScene2d::Uninit();
}

//----------------------------------
//更新処理
//----------------------------------
void CLaser::Update(void)
{
	//ポリゴンの位置取得
	D3DXVECTOR3 pos = GetPosition();
	//位置更新
	pos += m_move;
	//球の射程距離
	nLife--;
	//更新処理
	CScene2d::Update();
	//ポリゴンの位置を渡す
	SetPosition(pos);

	//エフェクト生成
	CEffect::Create(pos, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(LASER_SIZE_X / 2, LASER_SIZE_Y / 2, 0.0f),CEffect::EFFECT_TYPE_LASER);

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
		//レーザー効果処理
		for (int nCut = 0; nCut < MAX_PRIORITY; nCut++)
		{
			for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
			{
				
				CScene *pScene = GetScene(nCut, nCntScene);
				if (pScene != NULL)
				{
					OBJTYPE objType;
					//タイプ取得
					objType = pScene->GetObjType();
					switch (m_Type)
					{
					case LASER_TYPE_PLAYER:
						if (objType == OBJ_TYPE_ENEMY)
						{
							D3DXVECTOR3 EnemeyPos = ((CScene2d*)pScene)->GetPosition();
							D3DXVECTOR3 EnemeySize = ((CScene2d*)pScene)->GetSizeition();
							//当たり判定
							
							if (EnemeyPos.x + EnemeySize.x > pos.x
								&& EnemeyPos.x - EnemeySize.x < pos.x
								&&EnemeyPos.y + EnemeySize.y > pos.y
								&&EnemeyPos.y - EnemeySize.y < pos.y
								&&m_Hit[nCntScene]!=true)
							{
			
								m_Hit[nCntScene] = true;

								
								//エネミーダメージ処理
								if (typeid(*pScene) == typeid(CEnemy))
								{
									//エクスプロージョン生成
									CExplosion::Create(EnemeyPos);

									((CEnemy*)pScene)->Damage(1);
								}
								else if (typeid(*pScene) == typeid(CBoss))
								{
									//エクスプロージョン生成
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
//描画処理
//----------------------------------
void CLaser::Draw(void)
{
	//描画処理
	CScene2d::Draw();
}
