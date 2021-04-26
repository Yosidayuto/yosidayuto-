//=============================================================================
//
// 種ブロック [seeds block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "seeds block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSeedsBlock::CSeedsBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CSeedsBlock::~CSeedsBlock()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CSeedsBlock * CSeedsBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CSeedsBlock* pSeedsBlock = NULL;
	pSeedsBlock = new CSeedsBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pSeedsBlock->m_nModel);

	//NULLチェック
	if (pSeedsBlock != NULL)
	{
		//位置設定
		pSeedsBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT, pos.z));
		//向き設定
		pSeedsBlock->SetRotation(rot);
		//カラー設定
		pSeedsBlock->SetScale(size);
		//モデル設定
		pSeedsBlock->SetModelData(Model);
		//初期化処理
		pSeedsBlock->Init();
	}

	return pSeedsBlock;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CSeedsBlock::Init(void)
{
	CItemBlockBase::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CSeedsBlock::Uninit(void)
{
	CItemBlockBase::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CSeedsBlock::Update(void)
{
	CItemBlockBase::Update();

}

//=============================================================================
// 描画関数
//=============================================================================
void CSeedsBlock::Draw(void)
{
	CItemBlockBase::Draw();
}
