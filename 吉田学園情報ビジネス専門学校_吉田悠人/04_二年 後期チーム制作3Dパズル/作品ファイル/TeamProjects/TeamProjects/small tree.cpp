//=============================================================================
//
// 針葉樹(小さい) [small tree.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "small tree.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSmallTree::CSmallTree()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CSmallTree::~CSmallTree()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CSmallTree * CSmallTree::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CSmallTree* pSmallTree = NULL;
	pSmallTree = new CSmallTree;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pSmallTree->m_nModel);

	//NULLチェック
	if (pSmallTree != NULL)
	{
		//位置設定
		pSmallTree->SetPosition(D3DXVECTOR3(pos.x, pos.y + HINDRANCE_HEIGHT, pos.z));
		//向き設定
		pSmallTree->SetRotation(rot);
		//カラー設定
		pSmallTree->SetScale(size);
		//モデル設定
		pSmallTree->SetModelData(Model);
		//初期化処理
		pSmallTree->Init();
	}

	return pSmallTree;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CSmallTree::Init(void)
{
	CHindranceBlockBase::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CSmallTree::Uninit(void)
{
	CHindranceBlockBase::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CSmallTree::Update(void)
{
	CHindranceBlockBase::Update();

}

//=============================================================================
// 描画関数
//=============================================================================
void CSmallTree::Draw(void)
{
	CHindranceBlockBase::Draw();

}
