#include"game.h"
#include"bg.h"
#include"bullet.h"
#include"enemy.h"
#include"explosion.h"
#include"player.h"
#include"spawn.h"
#include"score.h"
#include"effect.h"
#include"Item.h"
#include"life.h"
#include"bomb.h"
void InintGame(void)
{	
	InintPolygon();					//プレイヤーの初期化処理
	InintPolygonbg();				//背景の初期化処理
	InitBullet();					//弾の初期化処理
	InitExplosion();				//爆発の初期化処理
	InitEnemy();					//敵の初期化処理
	InitSpawn();
	InintScore();
	InitEffect();					//エフェクトの初期化処理
	InitItem();						//アイテムの初期化処理
	InintLife();					//ライフ表示の初期化処理
	InintBomb();					//ボムの初期化処理
}
void UpdateGame(void)
{
	UpdatePolygon();				//プレイヤーの更新処理
	UpdatePolygonbg();				//背景の更新処理
	UpdateBullet();					//弾の更新処理
	UpdaExplosion();				//爆発の更新処理
	UpdateEnemy();					//敵の更新処理
	UpdateSpawn();
	UpdateEffect();					//エフェクトの更新処理
	UpdaItem();						//アイテムの更新処理
	UpdateLife();					//ライフ表示の更新処理
	UpdateBomb();					//ボムの更新処理

}
void UninitGame(void)
{

}
void DrawGame(void)
{
	DrawPolygon();					//プレイヤーの描画処理
	DrawPolygonbg();				//背景の描画処理
	DrawBullet();					//弾の描画処理
	DraawExplosion();				//爆発の描画処理
	DrawEnemy();					//敵の描画処理
	DrawWpawn();
	DrawEffect();					//エフェクトの描画処理
	DrawItem();						//アイテムの描画処理
	DrawLife();						//ライフ表示の描画処理
	DrawBomb();						//ボムの描画処理
}
