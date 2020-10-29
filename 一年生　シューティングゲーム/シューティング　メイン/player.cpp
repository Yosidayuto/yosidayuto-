#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include"fade.h"
#include"bomb.h"
						  /*�O���[�o���ϐ�*/
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;//�o�b�t�@�ւ̃|�C���^�[
PLAYER g_aPlayer;

int g_nCounterAnim;//�A�j���[�V�����J�E���^�[
int g_nPatternAnim;//�A�j���[�V�����p�^�[��No
				   //**********//
				   //����������//
				   //**********//
void InintPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	g_nCounterAnim = 0;
	g_nPatternAnim = 0;
	g_aPlayer.nLife = 5;
	g_aPlayer.dDisp = true;
	g_aPlayer.nBulletType = 0;
	g_aPlayer.nBomb = 0;
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(pDevice, "player000.png", &g_pTexturePolygon);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,		//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,											//(�Œ�)
		FVF_VERTEX_2D,												//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,											//�i�Œ�j
		&g_pVtxBuffPolygon,											//�ϐ������ς��ƕύX���K�v
		NULL);

	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	/*���_���W�̐ݒ�i�E���Őݒ肷��j*/
	pVtx[0].pos = D3DXVECTOR3(-POLYGON_SIZE_X / 2, -POLYGON_SIZE_Y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(POLYGON_SIZE_X / 2, -POLYGON_SIZE_Y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-POLYGON_SIZE_X / 2, POLYGON_SIZE_Y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(POLYGON_SIZE_X / 2, POLYGON_SIZE_Y / 2, 0.0f);
	/*rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j*/
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	/*���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	/*�e�N�X�`���̍��W�̐ݒ�*/
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffPolygon->Unlock();

	


}




void UninitPolygon(void)
{
	//�e�N�X�`���̐ݒ�
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}
void UpdatePolygon(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	switch (g_aPlayer.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_aPlayer.nCountState--;
		if (g_aPlayer.nCountState <= 0)
		{
			/*�ʏ�`��ɖ߂�����*/
			g_aPlayer.state = PLAYERSTATE_NORMAL;
			/*���_�J���[�̐ݒ�*/
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;
	case PLAYERSTATE_DEATH:
		g_aPlayer.nCountState--;
		if (g_aPlayer.nCountState <= 0)
		{
			SetFade(MODE_RESULE); 
		}
		return;
		break;
	}
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffPolygon->Unlock();
	/*-----------------------------------------------------------------------------------------------------------------*/



	/*-----------------------------------------------------------------------------------------------------------------*/

	/*�X�y�[�X�L�[�������ꂽ*/
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		switch (g_aPlayer.nBulletType)
		{
		case 0:
 			SetBullet(g_aPlayer.pos, D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 30, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 1:
			SetBullet(g_aPlayer.pos+D3DXVECTOR3(10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos+D3DXVECTOR3(-10,- 30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 2:
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos, D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 40, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 3:
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(10, -30, 1.0f), D3DXVECTOR3(5.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-10, -30, 1.0f), D3DXVECTOR3(-5.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos, D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 40, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 4:
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(10, -30, 1.0f), D3DXVECTOR3(5.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-10, -30, 1.0f), D3DXVECTOR3(-5.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos, D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 55, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 5:
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(30, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-30, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 6:
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(30, -30, 1.0f), D3DXVECTOR3(5.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-10, -30, 1.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_aPlayer.pos + D3DXVECTOR3(-30, -30, 1.0f), D3DXVECTOR3(-5.0f, -8.0f, 0.0f), BULLETTYPE_PLAYE, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		}
 	
	}
	if (GetKeyboardTrigger(DIK_R)&&g_aPlayer.nBomb>0)
	{
		SetBomb(g_aPlayer.pos);
		g_aPlayer.nBomb--;
	}
	/*W�̃L�[�������ꂽ���ǂ���*/
	if (Getkeyboardpress(DIK_W))
	{
		g_aPlayer.move.y -= VALUE_MOVE;
		g_aPlayer.move.y -= VALUE_MOVE;
	}
	/*S�̃L�[�������ꂽ���ǂ���*/
	if (Getkeyboardpress(DIK_S))
	{
		g_aPlayer.move.y += VALUE_MOVE;
		g_aPlayer.move.y += VALUE_MOVE;
	}
	/*A�̃L�[�������ꂽ���ǂ���*/
	if (Getkeyboardpress(DIK_A))
	{
		g_aPlayer.move.x -= VALUE_MOVE;
		g_aPlayer.move.x -= VALUE_MOVE;
	}
	/*D�̃L�[�������ꂽ���ǂ���*/
	if (Getkeyboardpress(DIK_D))
	{
		g_aPlayer.move.x += VALUE_MOVE;
		g_aPlayer.move.x += VALUE_MOVE;
	}
	/*---------------------------------------------------------------*/
	/*��ʊO�ɍs���Ȃ�*/
	if (g_aPlayer.pos.y < 0 + (POLYGON_SIZE_Y / 2))
	{
		g_aPlayer.move.y += VALUE_MOVE;
		g_aPlayer.move.y += VALUE_MOVE;
	}
	if (g_aPlayer.pos.y > SCREEN_HEIGHT - (POLYGON_SIZE_Y / 2))
	{
		g_aPlayer.move.y -= VALUE_MOVE;
		g_aPlayer.move.y -= VALUE_MOVE;
	}
	if (g_aPlayer.pos.x<0 + (POLYGON_SIZE_X / 2) )
	{
		g_aPlayer.move.x += VALUE_MOVE;
		g_aPlayer.move.x += VALUE_MOVE;
	}
	if (g_aPlayer.pos.x > SCREEN_WIDTH - (POLYGON_SIZE_X / 2))
	{
		g_aPlayer.move.x -= VALUE_MOVE;
		g_aPlayer.move.x -= VALUE_MOVE;
	}
	/*-------------------------------------------------------------*/
	/*�V�t�g�����Ȃ���*/
	if (Getkeyboardpress(DIK_LSHIFT))
	{
		if (Getkeyboardpress(DIK_D))
		{
			g_aPlayer.move.x -= VALUE_MOVE;
		}
		if (Getkeyboardpress(DIK_W))
		{
			g_aPlayer.move.y += VALUE_MOVE;
		}
		if (Getkeyboardpress(DIK_S))
		{
			g_aPlayer.move.y -= VALUE_MOVE;
		}
		if (Getkeyboardpress(DIK_A))
		{
			g_aPlayer.move.x += VALUE_MOVE;
		}
	}
	/*�ʒu�X�V*/
	g_aPlayer.pos.x += g_aPlayer.move.x;
	g_aPlayer.pos.y += g_aPlayer.move.y;

	/*����*/
	g_aPlayer.move.x += (0.0f - g_aPlayer.move.x)*RATE_MOVE;
	g_aPlayer.move.y += (0.0f - g_aPlayer.move.y)*RATE_MOVE;

	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

	pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x + (-POLYGON_SIZE_X / 2), g_aPlayer.pos.y + (-POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + (POLYGON_SIZE_X / 2), g_aPlayer.pos.y + (-POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x + (-POLYGON_SIZE_X / 2), g_aPlayer.pos.y + (POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + (POLYGON_SIZE_X / 2), g_aPlayer.pos.y + (POLYGON_SIZE_Y / 2), 0.0f);
	//���_�f�[�^���A�����b�N����7
	g_pVtxBuffPolygon->Unlock();
	//g_nCounterAnim++;//�J�E���^�[�v�Z

}
//�`�揈��
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygon);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}
PLAYER *GatPlayer(void)
{
	return &g_aPlayer;
}

void HitPlayer(int nDamage)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	/*���C�t�����炷*/
	g_aPlayer.nLife -= nDamage;

	if (g_aPlayer.nLife <= 0)
	{/*���C�t���O�ɂȂ����Ƃ�*/
		SetExplosion(g_aPlayer.pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
		g_aPlayer.dDisp = false;
		g_aPlayer.state = PLAYERSTATE_DEATH;//���S��ԂɈڍs
		g_aPlayer.nCountState = 60;
		///*���_�J���[�̐ݒ�*/
		//pVtx[0].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		//pVtx[1].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		//pVtx[2].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		//pVtx[3].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
	}
	else
	{/*�_���[�W��ԃJ�E���^�[��ԂɈڍs*/
		g_aPlayer.state = PLAYERSTATE_DAMAGE;//�_���[�W��ԂɈڍs
		g_aPlayer.nCountState = 5;
		/*���_�J���[�̐ݒ�*/
		pVtx[0].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
	}
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffPolygon->Unlock();
}