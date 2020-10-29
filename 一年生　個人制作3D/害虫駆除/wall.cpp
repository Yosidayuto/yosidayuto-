#include"wall.h"
#include"main.h"
//�O���[�o���ϐ�
/*���_�o�b�t�@�ւ̃|�C���^*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;
/*�|���S���̃e�N�X�`��*/
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;
/*��*/
WALL g_Wall[MAX_WALL];


void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_Wall[nCntWall].dir = D3DXVECTOR3(0, 0, 0);
		g_Wall[nCntWall].pos = D3DXVECTOR3(0, 0, 0);
		g_Wall[nCntWall].use = false;
	}
	D3DXCreateTextureFromFile(pDevice, "�摜/gettyimages-514798358-612x612.jpg", &g_pTextureWall);
	/*���_�o�b�t�@�̐���*/
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);
	VERTEX_3D*pVtx = NULL;
	/*���_�o�b�t�@�����b�N*/
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
	/*���_���W�̐ݒ�*/
	pVtx[0].pos = D3DXVECTOR3(-WALL_X / 2, WALL_Y / 2, 0);
	pVtx[1].pos = D3DXVECTOR3(WALL_X / 2, WALL_Y / 2, 0);
	pVtx[2].pos = D3DXVECTOR3(-WALL_X / 2, -WALL_Y / 2, 0);
	pVtx[3].pos = D3DXVECTOR3(WALL_X / 2, -WALL_Y / 2, 0);
	/*�e���_�̖@���̐ݒ�i�x�N�g���̑傫���͂P�ɂ���K�v������j*/
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	/*���_�J���[�̐ݒ�*/
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);
	
	}
	pVtx += 4;
	/*���_�o�b�t�@�̃A�����b�N*/
	g_pVtxBuffWall->Unlock();
}
void UninitWall(void)
{
	/*���_�o�b�t�@�̉��*/
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}
void UpdateWall(void)
{

}
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	VERTEX_3D*pVtx = NULL;
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (!g_Wall[nCntWall].use)
		{
			//g_shadow[nCntShadow]���������Ause��true�ɂ���
			/*�ʒu�ݒ�*/
			g_Wall[nCntWall].pos = pos;
			/*�����ݒ�*/
			g_Wall[nCntWall].dir = dir;

			/*���_�o�b�t�@�����b�N*/
			g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
			/*�ʒu����*/
			pVtx[0].pos = D3DXVECTOR3((-WALL_X / 2),(WALL_Y / 2), 0);
			pVtx[1].pos = D3DXVECTOR3(( WALL_X / 2),(WALL_Y / 2), 0);
			pVtx[2].pos = D3DXVECTOR3((-WALL_X / 2),(-WALL_Y / 2), 0);
			pVtx[3].pos = D3DXVECTOR3(( WALL_X / 2),(-WALL_Y / 2), 0);
			/*���_�o�b�t�@�̃A�����b�N*/
			g_pVtxBuffWall->Unlock();
			/*�g�p���Ă��邩*/
			g_Wall[nCntWall].use = true;
			break;
		}
		pVtx += 4;
	}
	
}
void DrawWall(void)
{
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	
	
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].use)
		{
			/*���[���h�}�g���N�X�̏���������*/
			D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorld);
			/*�����𔽉f*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].dir.y, g_Wall[nCntWall].dir.x, g_Wall[nCntWall].dir.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxRot);
			/*�ʒu�𔽉f*/
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxTrans);
			/*���[���h�}�g���N�X�̐ݒ�*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorld);
			/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�*/
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));
			/*���_�t�H�[�}�b�g�̐ݒ�*/
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureWall);
			/*�|���S���`��*/
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	pDevice->SetTexture(0, NULL);
}