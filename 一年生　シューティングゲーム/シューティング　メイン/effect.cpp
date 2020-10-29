#include"main.h"
#include"effect.h"
#include"player.h"
#include"enemy.h"

#define MAX_EFFECT (4096)//�G�t�F�N�g�ő吔

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	float fRadius;			//���a
	float fRadiusValue;		//���a�ω���
	float fColAlphaValue;	//�F�ω���
	int nLife;				//���C�t

	bool bUse;				//�g�p���Ă��邩�ǂ���
}EFFECT;
/*�O���[�o���ϐ�*/
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect= NULL;		//���_�o�b�t�@�ւ̃|�C���^

EFFECT g_aEffect[MAX_EFFECT];

void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntEffect;

	/*�e�̏��̏�����*/
	for (nCntEffect = 0; nCntEffect< MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(255, 255, 255,5);
		g_aEffect[nCntEffect].nLife = 50;
		g_aEffect[nCntEffect].bUse = false;
		g_aEffect[nCntEffect].fRadius = 0;
		g_aEffect[nCntEffect].fRadiusValue = 0;
	}
	D3DXCreateTextureFromFile(pDevice, "bullet000.png", &g_pTextureEffect);//�e�N�X�`���̓ǂݍ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_EFFECT,		//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,											//(�Œ�)
		FVF_VERTEX_2D,												//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,											//�i�Œ�j
		&g_pVtxBuffEffect,												//�ϐ������ς��ƕύX���K�v
		NULL);
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		/*���_���W�̐ݒ�*/
		pVtx[0].pos = D3DXVECTOR3(-EFFECT_SIZE/2,- EFFECT_SIZE/2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(EFFECT_SIZE/2, -EFFECT_SIZE/2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EFFECT_SIZE/2, EFFECT_SIZE/2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EFFECT_SIZE/2, EFFECT_SIZE/2, 0.0f);
		/*rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j*/
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		/*���_�J���[�̐ݒ�*/
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		/*�e�N�X�`���̍��W�̐ݒ�*/
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		/*���_�f�[�^�̃|�C���^��4��*/
		pVtx += 4;
	}
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffEffect->Unlock();
}
void UninitEffect(void)
{
	//�e�N�X�`���̐ݒ�
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
void UpdateEffect(void)
{
	VERTEX_2D*pVtx;
	int nCntEffect;
	/*���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾*/
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			g_aEffect[nCntEffect].fRadiusValue++;
			if (g_aEffect[nCntEffect].fRadiusValue>= 1)
			{
				g_aEffect[nCntEffect].fRadiusValue = 0;//�J�E���^�[�������l�ɖ߂�
				g_aEffect[nCntEffect].nLife--;
				g_aEffect[nCntEffect].fRadius--;
				if (g_aEffect[nCntEffect].nLife == 0)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
			}
		
			pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r +0, g_aEffect[nCntEffect].col.g+0, g_aEffect[nCntEffect].col.b+0, g_aEffect[nCntEffect].col.a+0);
			pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r + 0, g_aEffect[nCntEffect].col.g + 0, g_aEffect[nCntEffect].col.b+0, g_aEffect[nCntEffect].col.a+0);
			pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r + 0, g_aEffect[nCntEffect].col.g + 0, g_aEffect[nCntEffect].col.b+0, g_aEffect[nCntEffect].col.a+0);
			pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r + 0, g_aEffect[nCntEffect].col.g + 0, g_aEffect[nCntEffect].col.b+0, g_aEffect[nCntEffect].col.a+0);
		}
		pVtx += 4;
	}
	/*���_�f�[�^���A�����b�N����*/
	g_pVtxBuffEffect->Unlock();
}
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEffect;
	/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h*/
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));
	/*���_�t�H�[�}�b�g�̐ݒ�*/
	pDevice->SetFVF(FVF_VERTEX_2D);
	/*�e�N�X�`���̐ݒ�*/
	pDevice->SetTexture(0, g_pTextureEffect);
	/*�����_�����O�X�e�[�g(���Z��������)*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	/*�|���S���̕`��*/
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			/*�e���g�p���Ȃ�`��*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, NUM_POLYGON);
		}
	}
	/*�����_�[�X�e�[�g*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
void SetEffect(D3DXVECTOR3 pos/*���ˈʒu*/, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;
	VERTEX_2D*pVtx;
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{

		if (g_aEffect[nCntEffect].bUse == false)					//�e���g�p����Ă��Ȃ��ꍇ
		{
			/*�ʒu�ݒ�*/
			g_aEffect[nCntEffect].pos = pos;
			/*����*/
			g_aEffect[nCntEffect].nLife = nLife;
			/*�F*/
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].col.r = col.r;
			g_aEffect[nCntEffect].col.a = col.a;
			g_aEffect[nCntEffect].col.b = col.b;
			g_aEffect[nCntEffect].col.g = col.g;

			g_aEffect[nCntEffect].fRadius = fRadius;
			/*���_���W�̐ݒ�*/
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (-EFFECT_SIZE / 2)* g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + (-EFFECT_SIZE / 2)* g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (EFFECT_SIZE / 2)*g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + (-EFFECT_SIZE / 2)* g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (-EFFECT_SIZE / 2)*g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + (EFFECT_SIZE / 2)*g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (EFFECT_SIZE / 2)* g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + (EFFECT_SIZE / 2)*g_aEffect[nCntEffect].fRadius, 0.0f);
				/*���_�J���[�̐ݒ�*/
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			/*�g�p���Ă����Ԃɂ���*/
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;													//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	g_pVtxBuffEffect->Unlock();
}