#include "player.h"			//プレイヤーヘッダー
#include "input.h"			//インプットヘッダー
#include "inihkeyboard.h"	//インプットキーボードヘッダー
#include "inputmouse.h"		//インプットマウスヘッダー
#include "manager.h"		//マネージャーヘッダー
#include "bullet.h"			//バレットヘッダー
#include "renderer.h"		//レンダリングヘッダー
#include "sound.h"			//サウンドヘッダー
#include "life.h"			//ライフヘッダー
#include "game.h"			//ゲームヘッダー
#include "laser.h"			//レーザーヘッダー
#include "homing.h"			//ホーミングヘッダー
#include "fade.h"			//フェード
#include "explosion.h"		//爆破
//----------------------------------
//マクロ定義
//----------------------------------
#define PLAYER_MOVE 0
#define PLAYER_DAMAGE 100
//----------------------------------
//静的メンバー変数
//----------------------------------
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
WEAPON_MODE CPlayer::m_Weapon[MAX_WEAPON] =
{
	WEAPONS_MODE_BUTTOL,
	WEAPONS_MODE_NONE
};
D3DXVECTOR3 CPlayer::posMove = D3DXVECTOR3(PLAYER_MOVE, PLAYER_MOVE,0.0f);
int CPlayer::m_nLife = 3;
float CPlayer::m_fSpeed = 4.0f;
//=============================================================================
//コンストラクト
//=============================================================================
CPlayer::CPlayer(int nPriorit) :CScene2d(nPriorit)
{
	CScene::SetObjType(CScene::OBJ_TYPE_PLAYER);	//タイプ処理
	Stats = STATS_MODE_NORMAL;						//プレイヤーの状態
	nDamageTime = PLAYER_DAMAGE;					//無敵時間
	for (int nCount = 0; nCount < MAX_WEAPON; nCount++)
	{
		nCountWeapon[nCount] = 0;					//攻撃タイミング
	}
	m_nLife = 3;
	m_fSpeed = 4.0f;
}

//=============================================================================
//デストラクト
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
//生成処理
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 Pos)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Set(Pos);
	pPlayer->m_nLife += CManager::GetPlayer(0);
	pPlayer->m_fSpeed += (CManager::GetPlayer(1)*0.45f);

	pPlayer->Init();
	return pPlayer;
}

//=============================================================================
//テクスチャロード処理
//=============================================================================
HRESULT CPlayer::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Player.png", &m_pTexture);
	return S_OK;
}

//=============================================================================
//テクスチャ破棄処理
//=============================================================================
void CPlayer::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	for (int nCount = 0; nCount < MAX_WEAPON; nCount++)
	{
		m_Weapon[nCount]= CManager::GetWeapon(nCount);
	}
	
	//サイズ
	SetSize(D3DXVECTOR3(PLAYER_SIZE / 2, PLAYER_SIZE / 2, 0.0f));
	//初期化処理
	CScene2d::Init();
	//テクスチャの設定
	BindTexture(m_pTexture);
	//ライフ取得
	pLife = CGame::GetLife();
	if (pLife != NULL)
	{
		pLife->SetLife(m_nLife);
	}

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CPlayer::Update(void)
{
	CInihKeyboard *pKeyboard = CManager::GetKeyboard();	//キーボード取得
	CInihMouse *pMouse = CManager::GetMouse();			//マウス取得
	D3DXVECTOR3 pos;
	pos = GetPos();

	if (pMouse->GetClick(0) == true)
	{
		Weapon(pos,0);
	}
	if (pMouse->GetClick(1) == true)
	{
		Weapon(pos, 1);
	}


	//マウスの座標取得
	float fAngle = atan2f((-pos.x + pMouse->GetMousePos().x), (-pos.y + pMouse->GetMousePos().y));
	
	//位置情報の受け渡し
	posMove.x = sinf(fAngle)*m_fSpeed;
	posMove.y = cosf(fAngle)*m_fSpeed;

	//位置処理
	if (pos.x + 5 > pMouse->GetMousePos().x
		&&pos.x - 5 < pMouse->GetMousePos().x
		&&pos.y + 5 > pMouse->GetMousePos().y
		&&pos.y - 5 < pMouse->GetMousePos().y)
	{
		//ストップ
	}
	else
	{
		//位置更新
		pos += posMove;
	}
	
	////慣性処理
	posMove.x += (0.0f - posMove.x)*0.2f;
	posMove.y += (0.0f - posMove.y)*0.2f;
	
	pos += MoveLimit(pos, fAngle);
	//座標更新
	SetPos(pos);

	CScene2d::Update();

	//状態管理
	StatasManage();

}

//=============================================================================
//描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	//描画処理
	CScene2d::Draw();
}

//=============================================================================
//生成位置処理
//=============================================================================
void CPlayer::Set(D3DXVECTOR3 Pos)
{
	CScene2d::SetPos(Pos);
}

//=============================================================================
//ダメージ処理
//=============================================================================
void CPlayer::Damage(int nDamage)
{
	if (Stats == STATS_MODE_NORMAL)
	{
		//ライフダメージ
		m_nLife -= nDamage;
		//ライフ表示処理
		pLife->DownLife(nDamage);
		//状態変換
		if (m_nLife > 0)
		{
			Stats = STATS_MODE_DAMAGE;
		}
		else
		{
			Stats = STATS_MODE_DEATH;
		}
	}

}



//=============================================================================
//状態管理処理
//=============================================================================
void CPlayer::StatasManage(void)
{
	switch (Stats)
	{
	case STATS_MODE_NORMAL:
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;
	case STATS_MODE_DAMAGE:
		nDamageTime -= 1;

		//ダメージカラー
		if (nDamageTime % 25)
		{
			SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.0f));
		}
		else
		{
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		if (nDamageTime <= 0)
		{
			Stats = STATS_MODE_NORMAL;
			nDamageTime = PLAYER_DAMAGE;
		}

		break;
	case STATS_MODE_DEATH:
		//サウンドクラス受け取り
		CSound *pSound = CManager::GetSound();
		//フェード取得	
		CFade *pFade = CManager::GetFade();

		//サウンドの再生
		pSound->Play(CSound::LABEL_SE_DIE);
		
		//エクスプロージョン生成
		CExplosion::Create(GetPos());

		//セレクト移動
		pFade->SetFade(GAME_MODE_SELECT);
		
		//終了処理
		CPlayer::Uninit();
		break;
	}
}

//=============================================================================
//プレイヤーの移動範囲処理
//=============================================================================
D3DXVECTOR3 CPlayer::MoveLimit(D3DXVECTOR3 pos, float fAngle)
{
	D3DXVECTOR3 MoveLimit= D3DXVECTOR3(0,0,0);
	if (pos.x < 420|| pos.x > 1145)
	{
		MoveLimit.x = sinf(fAngle)*-m_fSpeed;

	}
	if (pos.y < 25|| pos.y>700)
	{
		MoveLimit.y = cosf(fAngle)*-m_fSpeed;
	}
	return D3DXVECTOR3(MoveLimit);
}


//=============================================================================
//プレイヤーの武器使用
//=============================================================================
void CPlayer::Weapon(D3DXVECTOR3 pos, int nWeapon)
{
	nCountWeapon[nWeapon]++;
	int nPos;
	switch (nWeapon)
	{
	case 0:
		nPos = -20;
		break;
	case 1:
		nPos = 20;
		break;
	}
	switch (m_Weapon[nWeapon])
	{
	case WEAPONS_MODE_BUTTOL:
		if (nCountWeapon[nWeapon]>=20)
		{
			CBullet::Create(D3DXVECTOR3(pos.x + nPos, pos.y, pos.z), D3DXVECTOR3(0, -20, 0.0f), CBullet::BULLET_TYPE_PLAYER);
			nCountWeapon[nWeapon] = 0;
		}
		break;
	case WEAPONS_MODE_LASER:
		if (nCountWeapon[nWeapon] >= 40)
		{
			CLaser::Create(D3DXVECTOR3(pos.x + nPos, pos.y, pos.z), D3DXVECTOR3(0, -17, 0.0f), CLaser::LASER_TYPE_PLAYER);
			nCountWeapon[nWeapon] = 0;
		}
		break;
	case WEAPONS_MODE_HOMING:
		if (nCountWeapon[nWeapon] >= 35)
		{
			CHoming::Create(D3DXVECTOR3(pos.x + nPos, pos.y, pos.z), 15, CHoming::HOMING_TYPE_PLAYER);
			nCountWeapon[nWeapon] = 0;
		}
		break;

	}
}
