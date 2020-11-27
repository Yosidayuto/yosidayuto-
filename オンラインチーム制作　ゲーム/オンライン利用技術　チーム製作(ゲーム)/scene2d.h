//=============================================================================
//
// ポリゴン2D処理 [scene2d.h]
// Author : 俵谷 健太郎
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// オブジェクトクラス(派生)
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D();												// コンストラクタ
	~CScene2D();											// デストラクタ
	static CScene2D *Create(D3DXVECTOR3 size);				// 作成処理
	HRESULT Init(D3DXVECTOR3 size);							// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理
	void SetPosition(D3DXVECTOR3 pos);						// 設置処理

	D3DXVECTOR3 GetPosition(void);							// 位置情報取得
	void SetTexPosition(int nCount, float nPattern);		// テクスチャ座標取得
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);			// テクスチャの割り当て
	void SetCol(D3DXCOLOR col);								// カラーセット
	void SetRotate(float fAngle);							// 角度情報
	void SetAnimation(float nPattern, int nMaxAnimation);	// アニメーション情報
	void SetSize(D3DXVECTOR3 size);                         // サイズ情報

private:
	LPDIRECT3DTEXTURE9		m_pTexture;						// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						// 頂点バッファへのポインタ

	D3DXVECTOR3				m_pos;							// ポリゴンの位置
	D3DXVECTOR3				m_size;							// ポリゴンのサイズ

	float m_fAngle;											// 角度
	float m_fAngle1;										// 角度
	float m_fDiagonal;										// 回転半径
	float m_fChange;										// 拡大縮小変換
	float m_fAdd;											// 符号変え
	float m_fAngleChane;									// 反転
};





#endif // !_SCENE2D_H_







