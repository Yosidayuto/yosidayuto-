#include"fade.h"
#include"manager.h"
#include"renderer.h"
//----------------------------------
//マクロ定義
//----------------------------------
#define FADE_RATE (0.01f)
//----------------------------------
//静的メンバー変数
//----------------------------------
LPDIRECT3DTEXTURE9 CFade::m_pTexture = NULL;

//----------------------------------
//コンストラクタ
//----------------------------------
CFade::CFade()
{
	//フェードモード
	m_Fade = FADE_OUT;
	//黒い画面（透明）
	m_Color= D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	

}

//----------------------------------
//デストラクタ
//----------------------------------
CFade::~CFade()
{
}


//----------------------------------
//初期化処理
//----------------------------------
HRESULT CFade::Init(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();


	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&m_pVtxBuff,//変数名が変わると変更が必要
		NULL);
	VERTEX_2D *pVtx;//頂点情報へのポインター

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点バッファの生成
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH , 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH , SCREEN_HEIGHT, 0.0f);

	// テクスチャの生成
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);


	// 頂点情報を設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	
	//rhwの設定（値は１，０で固定）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;


}

//----------------------------------
//終了処理
//----------------------------------
void CFade::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//----------------------------------
//更新処理
//----------------------------------
void CFade::Update(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター

	if (m_Fade != FADE_NONE)
	{//フェード処理中
		if (m_Fade == FADE_IN)
		{//フェードイン処理
			m_Color.a -= FADE_RATE;			//a値を減算して後ろの画面を浮き上がらせる
			if (m_Color.a <= 0.0f)
			{
				/*フェード処理終了*/
				m_Color.a = 0.0f;
				m_Fade = FADE_NONE;
			}
		}
		else if (m_Fade == FADE_OUT)
		{//フェードアウト処理
			m_Color.a += FADE_RATE;			//a値を加算して後ろの画面を消していく
			if (m_Color.a >= 1.0f)
			{
				/*フェードイン処理に切り替え*/
				m_Color.a = 1.0f;
				m_Fade = FADE_IN;
				/*モードを設定*/
				CManager::SetMode(m_ModeNext);
			}
		}

	}

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//頂点データをアンロックする
	m_pVtxBuff->Unlock();


}

//----------------------------------
//描画処理
//----------------------------------
void CFade::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, 0);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//----------------------------------
//フェードの状態設定
//----------------------------------
bool CFade::Set(CManager::GAME_MODE modeNext)
{
	if (m_Fade == FADE_NONE)
	{
		m_Fade = FADE_OUT;
		m_ModeNext = modeNext;
		m_bFade = true;
		return true;
	}
	return false;
}

CFade::FADE CFade::Get(void)
{
	return m_Fade;
}
