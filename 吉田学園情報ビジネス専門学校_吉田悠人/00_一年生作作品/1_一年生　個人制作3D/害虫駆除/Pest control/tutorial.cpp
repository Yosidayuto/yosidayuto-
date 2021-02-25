#include "main.h"
#include "input.h"
#include "fade.h"
#include "tutorial.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTutorial = {};//�e�N�X�`���ւ̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = {};//�o�b�t�@�ւ̃|�C���^�[
TUTORIAL g_Tutorial;
int g_nTutor = 0;
/*---------------------------------------------------*/
/*����������										*/
/*-------------------------------------------------*/
void InintTutorial(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_nTutor = 0;
	/*�ʒu�̏�����*/
	g_Tutorial.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	/*�g�p�����̏�����*/
	g_Tutorial.buse = false;
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(pDevice, "data/image//tutorial_1.png", &g_pTextureTutorial);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffTutorial,//�ϐ������ς��ƕύX���K�v
		NULL);
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
	//rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�e�N�X�`���̍��W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);
	g_pVtxBuffTutorial->Unlock();		
}
void UninitTutorial(void)
{
	//�e�N�X�`���̐ݒ�
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}
void UpdateTutorial(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

		g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_Tutorial.pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_Tutorial.pos.x + -SCREEN_WIDTH / 2, g_Tutorial.pos.y + -SCREEN_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Tutorial.pos.x + SCREEN_WIDTH / 2, g_Tutorial.pos.y + -SCREEN_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Tutorial.pos.x + -SCREEN_WIDTH / 2, g_Tutorial.pos.y + SCREEN_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Tutorial.pos.x + SCREEN_WIDTH / 2, g_Tutorial.pos.y + SCREEN_HEIGHT / 2, 0.0f);
		g_pVtxBuffTutorial->Unlock();
	
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetFade(MODE_TUTORIAL2);
	}
}
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}