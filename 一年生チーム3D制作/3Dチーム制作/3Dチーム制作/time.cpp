//=============================================================================
//
// 3D�Q�[��
// Author :�����D�I
//
//=============================================================================

#include "time.h"
#include "item.h"
#include"model.h"
#include "geam.h"
#include"model.h"

//=============================================================================
//�O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;//���_�o�b�t�@�ւ̃|�C���^

int g_nCounterTime; //���Ԃ𐔂���
int g_nPatternTime; //���Ԃ𔽉f������

int g_nTime; //���Ԃ̏��


			 //=============================================================================
			 // �^�C������������
			 //=============================================================================
void InitTime(void)
{
	//�ϐ��錾
	VERTEX_2D*pVtx;//���_���̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�������Ԃ̏�����
	g_nCounterTime = 0;
	g_nPatternTime = 0;
	g_nTime = TIME_LIMIT;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "�摜/�X�R�A2.png", &g_pTextureTime);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX * MAX_TIME,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�j
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffTime,//�ϐ������ς��ƕύX���K�v
		NULL);

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�����

	for (int nTime = 0; nTime < MAX_TIME; nTime++)
	{
		//���_���W�̐ݒ�i�E���Őݒ肷��j
		pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH - (nTime*TIME_SIZE_X + TIME_SIZE_X / 2) - (TIME_SIZE_X / 2) - 200, (SCREEN_HEIGHT - TIME_SIZE_Y / 2) - (TIME_SIZE_Y / 2) - 620, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH - (nTime*TIME_SIZE_X + TIME_SIZE_X / 2) + (TIME_SIZE_X / 2) - 200, (SCREEN_HEIGHT - TIME_SIZE_Y / 2) - (TIME_SIZE_Y / 2) - 620, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH - (nTime*TIME_SIZE_X + TIME_SIZE_X / 2) - (TIME_SIZE_X / 2) - 200, (SCREEN_HEIGHT - TIME_SIZE_Y / 2) + (TIME_SIZE_Y / 2) - 620, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH - (nTime*TIME_SIZE_X + TIME_SIZE_X / 2) + (TIME_SIZE_X / 2) - 200, (SCREEN_HEIGHT - TIME_SIZE_Y / 2) + (TIME_SIZE_Y / 2) - 620, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`���̍��W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�f�[�^�A�����b�N
	g_pVtxBuffTime->Unlock();

}
//=============================================================================
// �^�C���X�V����
//=============================================================================
void UpdateTime(void)
{
	//�ϐ��錾
	VERTEX_2D*pVtx;//���_���̃|�C���^
	float fIndex;  //�w���@(�X�R�A�\���p)
	float fRadix = 10.0f; //��@(�X�R�A�\���p)

	PLAYER *pPlayer = GetPlayer();

	//���Ԃ̊T�O���l��
	//if (pPlayer->bDisp == true)
	{
		g_nCounterTime++; //�J�E���^���Z
		if (g_nCounterTime == 120) //59fps+1fps��1�b
		{
			g_nCounterTime = 0;
			g_nPatternTime++;
			if (g_nPatternTime == 1)//�e�N�X�`�����X�V����Ԋu��1�b
			{


				//�J�E���g�_�E��
				g_nTime += g_nPatternTime;

				g_nPatternTime = 0;
			}
		}
	}

	////�^�C���A�b�v
	//if (g_nTime <= 0)
	//{
	//	g_nTime = 0;

	//	if (pPlayer->nStock > -1) //�X�g�b�N���c���Ă���Ƃ�
	//	{
	//		pPlayer->nStock = -1; //�Q�[���I�[�o�[�ɂ��邽�߁A�X�g�b�N�𒼐ڒ���
	//	}
	//	SetGameState(GAMESTATE_ENDPLAYER);
	//}

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�����

	for (fIndex = 0; fIndex < MAX_TIME; fIndex++)
	{
		int nTime = (int)powf(fRadix, MAX_TIME - fIndex);
		int nTime2 = (int)powf(fRadix, MAX_TIME - fIndex - 1);
		int nAnswer = g_nTime % nTime / nTime2;

		//�e�N�X�`���̍��W
		pVtx[4].tex = D3DXVECTOR2(0.0f + (0.1f*  (float)nAnswer), 0.0f);
		pVtx[5].tex = D3DXVECTOR2(0.1f + (0.1f*  (float)nAnswer), 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f + (0.1f* (float)nAnswer), 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.1f + (0.1f* (float)nAnswer), 1.0f);

		pVtx -= 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�f�[�^�A�����b�N
	g_pVtxBuffTime->Unlock();
}
//=============================================================================
// �^�C���I������
//=============================================================================
void UninitTime(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// �^�C���`�揈��
//=============================================================================
void DrawTime(void)
{

	//���_�t�H�[�}�b�g�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

								   //�X�R�A�̐����̕`��
	for (int nTime = 0; nTime < MAX_TIME; nTime++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTime);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nTime, NUM_POLYGON);
	}
}

//=============================================================================
// �^�C�����̑��M
//=============================================================================
int GetTime(void)
{
	return g_nTime;
}