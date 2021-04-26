//=============================================================================
//
// ゴミブロック [garbage block.h]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "garbage block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CGarbageBlock::CGarbageBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CGarbageBlock::~CGarbageBlock()
{
}


//=============================================================================
// 生成関数
//=============================================================================
CGarbageBlock * CGarbageBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CGarbageBlock* pGarbageBlock = NULL;
	pGarbageBlock = new CGarbageBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pGarbageBlock->m_nModel);

	//NULLチェック
	if (pGarbageBlock != NULL)
	{
		//位置設定
		pGarbageBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT, pos.z));
		//向き設定
		pGarbageBlock->SetRotation(rot);
		//カラー設定
		pGarbageBlock->SetScale(size);
		//モデル設定
		pGarbageBlock->SetModelData(Model);
		//初期化処理
		pGarbageBlock->Init();
	}

	return pGarbageBlock;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CGarbageBlock::Init(void)
{
	CItemBlockBase::Init();

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CGarbageBlock::Uninit(void)
{
	CItemBlockBase::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CGarbageBlock::Update(void)
{
	CItemBlockBase::Update();

}

//=============================================================================
// 描画関数
//=============================================================================
void CGarbageBlock::Draw(void)
{
	CItemBlockBase::Draw();
}
