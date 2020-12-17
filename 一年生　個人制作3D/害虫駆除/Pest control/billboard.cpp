#include"main.h"
#include"billboard.h"
#include"enemy.h"
#include"camera.h"
#include"sound.h"
//�O���[�o���ϐ�
/*���_�o�b�t�@�ւ̃|�C���^*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;
/*�|���S���̃e�N�X�`��*/
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;
/*�r���{�[�h*/
BILLBOARD g_billboard[MAX_BILLBOARD];

void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nBillboard = 0; nBillboard < MAX_BILLBOARD; nBillboard++)
	{
		g_billboard[nBillboard].pos = D3DXVECTOR3(0, 0, 0);
		g_billboard[nBillboard].dir = D3DXVECTOR3(0, 0, 0);
		g_billboard[nBillboard].buse = false;
	}
	/*���_�o�b�t�@�̐���*/
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);
	D3DXCreateTextureFromFile(pDevice, "data/image/bullet.png", &g_pTextureBillboard);
	VERTEX_3D*pVtx = NULL;
	/*���_�o�b�t�@�����b�N*/
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);
	//for (int nBillboard = 0; nBillboard < MAX_BILLBOARD; nBillboard++)
	/*���_���W�̐ݒ�*/
	pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_SIZE / 2, BILLBOARD_SIZE / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BILLBOARD_SIZE / 2, BILLBOARD_SIZE / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_SIZE / 2, -BILLBOARD_SIZE / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BILLBOARD_SIZE / 2, -BILLBOARD_SIZE / 2, 0.0f);
	/*�e���_�̖@���̐ݒ�i�x�N�g���̑傫���͂P�ɂ���K�v������j*/
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	/*���_�J���[�̐ݒ�*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	/*�e�N�X�`���̐ݒ�*/
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);	
	/*���_�o�b�t�@�̃A�����b�N*/
	g_pVtxBuffBillboard->Unlock();
}
void UninitBillboard(void)
{
	/*���_�o�b�t�@�̉��*/
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}
void UpdateBillboard(void)
{
	ENEMY *pEnemy = GetEnemy();
	for (int i = 0;i < MAX_BILLBOARD; i++)
	{
		if (g_billboard[i].buse)
		{
			/*�r���{�[�h�̈ʒu�̍X�V*/
			g_billboard[i].pos += g_billboard[i].dir * 1;
			for (int nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
			{
				if (pEnemy[nEnemy].use)
				{
				
					if (pEnemy[nEnemy].pos.x + 30 >= g_billboard[i].pos.x
						&&pEnemy[nEnemy].pos.x - 30 <= g_billboard[i].pos.x
						&&pEnemy[nEnemy].pos.y + 30 >= g_billboard[i].pos.y
						&&pEnemy[nEnemy].pos.y - 30 <= g_billboard[i].pos.y
						&&pEnemy[nEnemy].pos.z + 30 >= g_billboard[i].pos.z
						&&pEnemy[nEnemy].pos.z - 30 <= g_billboard[i].pos.z)
					{
						PlaySound(SOUND_LABEL_SE_HIT);
						HitEnemy(1, nEnemy);
						g_billboard[i].buse = false;
					}
				}
			}
			
		}
	}
}
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	CAMERA* pCamera = GetCamera();
	VERTEX_3D*pVtx = NULL;
	for (int nCntShadow = 0; nCntShadow < MAX_BILLBOARD; nCntShadow++)
	{
		if (!g_billboard[nCntShadow].buse)
		{
			/*�ʒu�ݒ�*/
			g_billboard[nCntShadow].pos = pos;
			D3DXVec3Normalize(&dir, &dir);//���K������i�傫��1�̃x�N�g���ɂ���K�v������)
			/*�����ݒ�*/
			g_billboard[nCntShadow].dir = dir;
			/*�g�p���Ă��邩*/
			g_billboard[nCntShadow].buse = true;
			break;
		}
	}
}
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	for (int i = 0; i < MAX_BILLBOARD; i++)
	{
		if (g_billboard[i].buse)
		{
			/*�A���t�@�e�X�g��L����*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			/*�A���t�@�e�X�g��l�̐ݒ�*/
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			/*�A���t�@�e�X�g�̔�r���@�̐ݒ�*/
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			/*���[���h�}�g���N�X�̏���������*/
			D3DXMatrixIdentity(&g_billboard[i].mtxWorld);
			//��]�̋t�s��𐶐�
			pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
			D3DXMatrixInverse(&g_billboard[i].mtxWorld, NULL, &mtxRot);
			g_billboard[i].mtxWorld._41 = 0;
			g_billboard[i].mtxWorld._42 = 0;
			g_billboard[i].mtxWorld._43 = 0;		
			/*�ʒu�𔽉f*/
			D3DXMatrixTranslation(&mtxTrans, g_billboard[i].pos.x, g_billboard[i].pos.y, g_billboard[i].pos.z);
			D3DXMatrixMultiply(&g_billboard[i].mtxWorld, &g_billboard[i].mtxWorld, &mtxTrans);
			/*���[���h�}�g���N�X�̐ݒ�*/
			pDevice->SetTransform(D3DTS_WORLD, &g_billboard[i].mtxWorld);
			/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�*/
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));
			/*���_�t�H�[�}�b�g�̐ݒ�*/
			pDevice->SetFVF(FVF_VERTEX_3D);
			/*�e�N�X�`���̐ݒ�*/
			pDevice->SetTexture(0, g_pTextureBillboard);
			/*�|���S���`��*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			/*�A���t�@�e�X�g�𖳌���*/
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
	}
	pDevice->SetTexture(0, NULL);
}
BILLBOARD*GetBillboard()
{
	
	for (int nCntShadow = 0; nCntShadow < MAX_BILLBOARD; nCntShadow++)
	{
		return &g_billboard[nCntShadow];
	}
	return NULL;
}
