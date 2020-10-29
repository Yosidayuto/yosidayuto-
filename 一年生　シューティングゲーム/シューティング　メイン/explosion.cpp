#include "explosion.h"
#include"main.h"
/*�}�N����`*/
#define  MAX_EXPLOSLON (128)//�����̍ő吔

/*�\���̒�`*/
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXCOLOR col;//�F
	int nCounterAnim;//�J�E���^�[
	int nPtternAnim;//�p�^�[��No
	bool bUse;//�g�p���Ă��邩�ǂ���
}EXPLOSION;
/*�O���[�o���ϐ�*/
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
EXPLOSION g_aExplosion[MAX_EXPLOSLON];//�����̏��

									  /*����������*/
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntExplosion;
	/*�������̏�����*/
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSLON; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPtternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}
	/*�e�N�X�`���̓ǂݍ���*/
	D3DXCreateTextureFromFile(pDevice, "explosion000.png", &g_pTextureExplosion);//�e�N�X�`���̓ǂݍ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_EXPLOSLON,		//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,											//(�Œ�)
		FVF_VERTEX_2D,												//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,											//�i�Œ�j
		&g_pVtxBuffExplosion,												//�ϐ������ς��ƕύX���K�v
		NULL);
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSLON; nCntExplosion++)
	{
		/*���_���W�̐ݒ�*/
		pVtx[0].pos = D3DXVECTOR3(-MAX_EXPLOSION / 2, -MAX_EXPLOSION / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_EXPLOSION / 2, -MAX_EXPLOSION / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_EXPLOSION / 2, MAX_EXPLOSION / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_EXPLOSION / 2, MAX_EXPLOSION / 2, 0.0f);
		/*rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j*/
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		/*���_�J���[�̐ݒ�*/
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		/*�e�N�X�`���̍��W�̐ݒ�*/
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		/*���_�f�[�^�̃|�C���^��4��*/
		pVtx += 4;
	}
	/*���_�f�[�^���A�����b�N*/
	g_pVtxBuffExplosion->Unlock();

}
//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	//�e�N�X�`���̐ݒ�
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdaExplosion(void)
{

	VERTEX_2D*pVtx;
	int  nCntExplosion;
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSLON; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{

			g_aExplosion[nCntExplosion].nCounterAnim++;
			if (g_aExplosion[nCntExplosion].nCounterAnim == 10)
			{
				g_aExplosion[nCntExplosion].nCounterAnim = 0;//�J�E���^�[�������l�ɖ߂�
				g_aExplosion[nCntExplosion].nPtternAnim++;

				if (g_aExplosion[nCntExplosion].nPtternAnim == 8)
				{
					g_aExplosion[nCntExplosion].nPtternAnim = 0;
					g_aExplosion[nCntExplosion].bUse = false;
				}

			}
			if (g_aExplosion[nCntExplosion].pos.y>SCREEN_HEIGHT ||
				g_aExplosion[nCntExplosion].pos.y<0 ||
				g_aExplosion[nCntExplosion].pos.x> SCREEN_WIDTH ||
				g_aExplosion[nCntExplosion].pos.x<0)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (-MAX_EXPLOSION / 2), g_aExplosion[nCntExplosion].pos.y + (-MAX_EXPLOSION / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (MAX_EXPLOSION / 2), g_aExplosion[nCntExplosion].pos.y + (-MAX_EXPLOSION / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (-MAX_EXPLOSION / 2), g_aExplosion[nCntExplosion].pos.y + (MAX_EXPLOSION / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (MAX_EXPLOSION / 2), g_aExplosion[nCntExplosion].pos.y + (MAX_EXPLOSION / 2), 0.0f);

			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPtternAnim*0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPtternAnim*0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPtternAnim*0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPtternAnim*0.125f + 0.125f, 1.0f);
			
		}
		pVtx += 4;
	}
	/*���_�f�[�^���A�����b�N*/
	g_pVtxBuffExplosion->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DraawExplosion(void)
{
	int  nCntExplosion;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h*/
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
	/*���_�t�H�[�}�b�g�̐ݒ�*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*�e�N�X�`���̐ݒ�*/
	pDevice->SetTexture(0, g_pTextureExplosion);
	/*�|���S���̕`��*/
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSLON; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)//�������g�p���Ȃ�`��
		{

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion*4, NUM_POLYGON);
		}
	}
}
void SetExplosion(D3DXVECTOR3 pos/*���ˈʒu*/, D3DXCOLOR col/*�F*/)
{
	VERTEX_2D*pVtx;
	int nCntExplosion;
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSLON; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)//���������g�p�̏ꍇ
		{
			g_aExplosion[nCntExplosion].pos = pos;//�ʒu
			g_aExplosion[nCntExplosion].col = col;//�F

													/*���_���W�̐ݒ�*/
			pVtx[0].pos = D3DXVECTOR3(-MAX_EXPLOSION / 2, -MAX_EXPLOSION / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(MAX_EXPLOSION / 2, -MAX_EXPLOSION / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-MAX_EXPLOSION / 2, MAX_EXPLOSION / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(MAX_EXPLOSION / 2, MAX_EXPLOSION / 2, 0.0f);
			g_aExplosion[nCntExplosion].bUse = true;//�g�p���Ă����Ԃɂ���
			break;
		}
		pVtx += 4;
	}
	/*���_�f�[�^���A�����b�N*/
	g_pVtxBuffExplosion->Unlock();
}