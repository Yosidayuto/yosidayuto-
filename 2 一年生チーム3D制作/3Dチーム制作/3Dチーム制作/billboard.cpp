#include"main.h"
#include"billboard.h"
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
	for (int nCntShadow = 0; nCntShadow < MAX_BILLBOARD; nCntShadow++)
	{
		g_billboard[nCntShadow].use = false;
	}
	/*���_�o�b�t�@�̐���*/
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4* MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);
	D3DXCreateTextureFromFile(pDevice, "�摜/3D�摜_�V_��.png", &g_pTextureBillboard);
	VERTEX_3D*pVtx = NULL;
	/*���_�o�b�t�@�����b�N*/
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntShadow = 0; nCntShadow < MAX_BILLBOARD; nCntShadow++)
	{
		/*���_���W�̐ݒ�*/
		pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_SIZE / 2, BILLBOARD_SIZE/2,0.0f);
		pVtx[1].pos = D3DXVECTOR3(BILLBOARD_SIZE / 2, BILLBOARD_SIZE/2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_SIZE / 2,-BILLBOARD_SIZE/2,0.0f);
		pVtx[3].pos = D3DXVECTOR3(BILLBOARD_SIZE / 2, -BILLBOARD_SIZE/2,0.0f);
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
	}
	

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
	for (int i = 0;i < MAX_BILLBOARD; i++)
	{
		if (g_billboard[i].use)
		{
			/*�r���{�[�h�̈ʒu�̍X�V�i���ʒu���X�V�������ꍇ�j*/
			g_billboard[i].pos += g_billboard[i].dir * 1/*�ړ���*/;
		
		}
	}
}
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	VERTEX_3D*pVtx = NULL;
	for (int nCntShadow = 0; nCntShadow < MAX_BILLBOARD; nCntShadow++)
	{
		D3DXVec3Normalize(&dir, &dir);//���K������i�傫��1�̃x�N�g���ɂ���K�v������j
		/*�ʒu�ݒ�*/
		g_billboard[nCntShadow].pos = pos;
		/*�����ݒ�*/
		g_billboard[nCntShadow].dir = dir;

		
		/*�g�p���Ă��邩*/
		g_billboard[nCntShadow].use = true;
		break;
	}
}
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	for (int i = 0; i < MAX_BILLBOARD; i++)
	{
		if (g_billboard[i].use)
		{
			/*���[���h�}�g���N�X�̏���������*/
			D3DXMatrixIdentity(&g_billboard[i].mtxWorld);

			//��]�̋t�s��𐶐�
			pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
			D3DXMatrixInverse(&g_billboard[i].mtxWorld, NULL, &mtxRot);
			g_billboard[i].mtxWorld._41 = 0;
			g_billboard[i].mtxWorld._42 = 0;
			g_billboard[i].mtxWorld._43 = 0;
			/*�ʒu�𔽉f�A���[���h�}�g���b�N�X�ݒ�A�|���S���`��*/
			
			
			/*�ʒu�𔽉f*/
			D3DXMatrixTranslation(&mtxTrans, g_billboard[i].pos.x, g_billboard[i].pos.y, g_billboard[i].pos.z);
			D3DXMatrixMultiply(&g_billboard[i].mtxWorld, &g_billboard[i].mtxWorld, &mtxTrans);
			/*���[���h�}�g���N�X�̐ݒ�*/
			pDevice->SetTransform(D3DTS_WORLD, &g_billboard[i].mtxWorld);
			/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�*/
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));
			/*���_�t�H�[�}�b�g�̐ݒ�*/
			pDevice->SetFVF(FVF_VERTEX_3D);

			pDevice->SetTexture(0, g_pTextureBillboard);
			/*�|���S���`��*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}
		
	}
	pDevice->SetTexture(0, NULL);
}
