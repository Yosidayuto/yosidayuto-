//=============================================================================
//
// ブドウブロック [grapes block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "grapes block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CGrapesBlock::CGrapesBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CGrapesBlock::~CGrapesBlock()
{
}


//=============================================================================
// 生成関数
//=============================================================================
CGrapesBlock * CGrapesBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CGrapesBlock* pGrapesBlock = NULL;
	pGrapesBlock = new CGrapesBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pGrapesBlock->m_nModel);


	//NULLチェック
	if (pGrapesBlock != NULL)
	{
		//位置設定
		pGrapesBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT, pos.z));
		//向き設定
		pGrapesBlock->SetRotation(rot);
		//カラー設定
		pGrapesBlock->SetScale(size);
		//モデル設定
		pGrapesBlock->SetModelData(Model);
		//初期化処理
		pGrapesBlock->Init();
	}

	return pGrapesBlock;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CGrapesBlock::Init(void)
{
	CItemBlockBase::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CGrapesBlock::Uninit(void)
{
	CItemBlockBase::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CGrapesBlock::Update(void)
{
	CItemBlockBase::Update();

}

//=============================================================================
// 描画関数
//=============================================================================
void CGrapesBlock::Draw(void)
{
	CItemBlockBase::Draw();
}
