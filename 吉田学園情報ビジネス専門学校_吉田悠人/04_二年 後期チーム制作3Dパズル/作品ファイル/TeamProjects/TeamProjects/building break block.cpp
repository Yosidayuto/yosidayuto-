//=============================================================================
//
// ビル（半壊）ブロック [building break block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "building break block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBuildingBreakBlock::CBuildingBreakBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CBuildingBreakBlock::~CBuildingBreakBlock()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CBuildingBreakBlock * CBuildingBreakBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CBuildingBreakBlock* pBuildingBreakBlock = NULL;
	pBuildingBreakBlock = new CBuildingBreakBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pBuildingBreakBlock->m_nModel);

	//NULLチェック
	if (pBuildingBreakBlock != NULL)
	{
		//位置設定
		pBuildingBreakBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + HINDRANCE_HEIGHT, pos.z));
		//向き設定
		pBuildingBreakBlock->SetRotation(rot);
		//カラー設定
		pBuildingBreakBlock->SetScale(size);
		//モデル設定
		pBuildingBreakBlock->SetModelData(Model);
		//初期化処理
		pBuildingBreakBlock->Init();
	}

	return pBuildingBreakBlock;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CBuildingBreakBlock::Init(void)
{
	CHindranceBlockBase::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CBuildingBreakBlock::Uninit(void)
{
	CHindranceBlockBase::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CBuildingBreakBlock::Update(void)
{
	CHindranceBlockBase::Update();

}

//=============================================================================
// 描画関数
//=============================================================================
void CBuildingBreakBlock::Draw(void)
{
	CHindranceBlockBase::Draw();

}
