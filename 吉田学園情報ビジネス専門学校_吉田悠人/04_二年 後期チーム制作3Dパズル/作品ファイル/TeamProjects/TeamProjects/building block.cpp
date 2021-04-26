//=============================================================================
//
// ビルブロック [building block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "building block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBuildingBlock::CBuildingBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CBuildingBlock::~CBuildingBlock()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CBuildingBlock * CBuildingBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CBuildingBlock* pBuildingBlock = NULL;
	pBuildingBlock = new CBuildingBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pBuildingBlock->m_nModel);

	//NULLチェック
	if (pBuildingBlock != NULL)
	{
		//位置設定
		pBuildingBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + HINDRANCE_HEIGHT, pos.z));
		//向き設定
		pBuildingBlock->SetRotation(rot);
		//カラー設定
		pBuildingBlock->SetScale(size);
		//モデル設定
		pBuildingBlock->SetModelData(Model);
		//初期化処理
		pBuildingBlock->Init();
	}

	return pBuildingBlock;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CBuildingBlock::Init(void)
{
	CHindranceBlockBase::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CBuildingBlock::Uninit(void)
{
	CHindranceBlockBase::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CBuildingBlock::Update(void)
{
	CHindranceBlockBase::Update();

}

//=============================================================================
// 描画関数
//=============================================================================
void CBuildingBlock::Draw(void)
{
	CHindranceBlockBase::Draw();

}
