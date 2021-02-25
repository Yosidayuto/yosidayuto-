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
	InintPolygon();					//�v���C���[�̏���������
	InintPolygonbg();				//�w�i�̏���������
	InitBullet();					//�e�̏���������
	InitExplosion();				//�����̏���������
	InitEnemy();					//�G�̏���������
	InitSpawn();
	InintScore();
	InitEffect();					//�G�t�F�N�g�̏���������
	InitItem();						//�A�C�e���̏���������
	InintLife();					//���C�t�\���̏���������
	InintBomb();					//�{���̏���������
}
void UpdateGame(void)
{
	UpdatePolygon();				//�v���C���[�̍X�V����
	UpdatePolygonbg();				//�w�i�̍X�V����
	UpdateBullet();					//�e�̍X�V����
	UpdaExplosion();				//�����̍X�V����
	UpdateEnemy();					//�G�̍X�V����
	UpdateSpawn();
	UpdateEffect();					//�G�t�F�N�g�̍X�V����
	UpdaItem();						//�A�C�e���̍X�V����
	UpdateLife();					//���C�t�\���̍X�V����
	UpdateBomb();					//�{���̍X�V����

}
void UninitGame(void)
{

}
void DrawGame(void)
{
	DrawPolygon();					//�v���C���[�̕`�揈��
	DrawPolygonbg();				//�w�i�̕`�揈��
	DrawBullet();					//�e�̕`�揈��
	DraawExplosion();				//�����̕`�揈��
	DrawEnemy();					//�G�̕`�揈��
	DrawWpawn();
	DrawEffect();					//�G�t�F�N�g�̕`�揈��
	DrawItem();						//�A�C�e���̕`�揈��
	DrawLife();						//���C�t�\���̕`�揈��
	DrawBomb();						//�{���̕`�揈��
}
