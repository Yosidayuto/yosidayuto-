//いる？
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "window.h"		
#include "manager.h"	
#include "renderer.h"	
#include "inputmouse.h"	
#include "button.h"		
#include "score.h"		
//----------------------------------
//静的メンバー変数
//----------------------------------
LPDIRECT3DTEXTURE9	CWindow::m_Texture[WINDOW_TYPE_MAX] = {};
char *				CWindow::m_pcTexture[WINDOW_TYPE_MAX] =
{
	"data/TEXTURE/Window_Description.png",
};
bool CWindow::m_Window[WINDOW_TYPE_MAX] = 
{
	false
};

//----------------------------------
//コンストラクタ
//----------------------------------
CWindow::CWindow(int nPriorit)
{
	m_pos = D3DXVECTOR3(0,0,0);
}

//----------------------------------
//デストラクタ
//----------------------------------
CWindow::~CWindow()
{
}

//----------------------------------
//生成処理
//----------------------------------
CWindow * CWindow::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 size, WINDOW_TYPE Type)
{
	if (m_Window[Type] == false)
	{
		CWindow *pWindow;
		pWindow = new CWindow;
		pWindow->m_pos = Pos;
		pWindow->m_size = size;
		//位置
		pWindow->SetPos(pWindow->m_pos);
		//サイズ
		pWindow->SetSize(pWindow->m_size);
		pWindow->BindTexture(m_Texture[Type]);
		pWindow->Init();
		m_Window[Type] = true;
		return pWindow;

	}
	return NULL;
}

//----------------------------------
//テクスチャ読み込み処理
//----------------------------------
HRESULT CWindow::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < WINDOW_TYPE_MAX; nCount++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, m_pcTexture[nCount], &m_Texture[nCount]);
	}
	return S_OK;
}

//----------------------------------
//テクスチャ破棄処理
//----------------------------------
void CWindow::Unload(void)
{
	for (int nCount = 0; nCount < WINDOW_TYPE_MAX; nCount++)
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
HRESULT CWindow::Init(void)
{
	//初期化処理
	CScene2d::Init();

	return S_OK;
}

//----------------------------------
//終了処理
//----------------------------------
void CWindow::Uninit(void)
{

	CScene2d::Uninit();
}

//----------------------------------
//更新処理
//----------------------------------
void CWindow::Update(void)
{
	CInihMouse *pMouse = CManager::GetMouse();			//マウス取得

	if (pMouse->GetClickTrigger(1) == true)
	{
		Uninit();
	}
}

//----------------------------------
//描画処理
//----------------------------------
void CWindow::Draw(void)
{
	CScene2d::Draw();
}

bool CWindow::Window(void)
{
	return m_Window[0];
}

