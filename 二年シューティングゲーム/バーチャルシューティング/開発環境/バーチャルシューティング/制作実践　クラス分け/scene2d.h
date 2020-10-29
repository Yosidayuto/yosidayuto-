#pragma once
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include"main.h"	//メインヘッダー
#include"scene.h"	//シーンファイル
//----------------------------------------------
//クラス
//----------------------------------------------
class CScene2d :public CScene
{
public:
	
	CScene2d(int nPriorit = 3);						//コンストラクタ
	~CScene2d();					//デストラクタ
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//テクスチャの読み込み処理
	static CScene2d*
		Create(D3DXVECTOR3 Pos);	//生成処理
	HRESULT Init(void);				//初期化処理
	void	Uninit(void);			//終了処理
	void	Update(void);			//更新処理
	void	Draw(void);				//描画処理
	void	Set(D3DXVECTOR3 Pos);	//設置位置

	void	TextureAnim(D3DXVECTOR2 *Texture);	//テクスチャアニメーション
	void	SetRotate(void);			//ポリゴン回転

	void	SetPosition(D3DXVECTOR3 pos) { m_posPolygon = pos; }		//位置設置
	D3DXVECTOR3 GetPosition(void) { return m_posPolygon; }				//位置取得


	void	SetSizeition(D3DXVECTOR3 size) { m_sizePolygon = size; }	//サイズセット
	D3DXVECTOR3 GetSizeition(void) { return m_sizePolygon; }			//サイズ取得

	void	ColChange(D3DXCOLOR col);									//カラーセット

private:

	D3DXVECTOR3				m_posPolygon;	// ポリゴンの位置
	D3DXVECTOR3				m_sizePolygon;	// ポリゴンの大きさ

	float					g_fLengthpos;	//頂点までの長さ	
	float					g_Angle;		//中心から頂点までの角度

	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

};