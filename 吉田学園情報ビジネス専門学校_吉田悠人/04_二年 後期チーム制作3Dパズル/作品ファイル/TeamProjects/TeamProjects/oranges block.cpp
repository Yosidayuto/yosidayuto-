//=============================================================================
//
// ミカンブロック [oranges block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "oranges block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// コンストラクタ
//=============================================================================
COrangesBlock::COrangesBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
COrangesBlock::~COrangesBlock()
{
}


//=============================================================================
// 生成関数
//=============================================================================
COrangesBlock * COrangesBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	COrangesBlock* pOrangesBlock = NULL;
	pOrangesBlock = new COrangesBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pOrangesBlock->m_nModel);

	//NULLチェック
	if (pOrangesBlock != NULL)
	{
		//位置設定
		pOrangesBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT, pos.z));
		//向き設定
		pOrangesBlock->SetRotation(rot);
		//カラー設定
		pOrangesBlock->SetScale(size);
		//モデル設定
		pOrangesBlock->SetModelData(Model);
		//初期化処理
		pOrangesBlock->Init();
	}

	return pOrangesBlock;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT COrangesBlock::Init(void)
{
	CItemBlockBase::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void COrangesBlock::Uninit(void)
{
	CItemBlockBase::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void COrangesBlock::Update(void)
{
	CItemBlockBase::Update();

}

//=============================================================================
// 描画関数
//=============================================================================
void COrangesBlock::Draw(void)
{
	CItemBlockBase::Draw();
}
