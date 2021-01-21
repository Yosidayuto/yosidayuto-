#include"line.h"
#include"main.h"
#include"wall.h"
//�O���[�o���ϐ�
/*���_�o�b�t�@�ւ̃|�C���^*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;
/*��*/
LINE  g_Line[MAX_LINE];


void InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nLine = 0; nLine < MAX_LINE; nLine++)
	{
		g_Line[nLine].pos = D3DXVECTOR3(0, 0, 0);
		g_Line[nLine].rot = D3DXVECTOR3(0, 0, 0);
		g_Line[nLine].buse = false;
	}
	/*���_�o�b�t�@�̐���*/
	pDevice->CreateVertexBuffer(sizeof(VERTEX_POINT) * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_POINT,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL);
	VERTEX_POINT*pVtx = NULL;
	/*���_�o�b�t�@�����b�N*/
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);
	/*���_���W�̐ݒ�*/
	pVtx[0].pos = D3DXVECTOR3(0,0,0);
	pVtx[1].pos = D3DXVECTOR3(0,0,0);
	
	/*���_�J���[�̐ݒ�*/
	pVtx[0].col = D3DXCOLOR(1, 1, 1, 1);
	pVtx[1].col = D3DXCOLOR(1, 1, 1, 1);

	/*���_�o�b�t�@�̃A�����b�N*/
	g_pVtxBuffLine->Unlock();
}
void UninitLine(void)
{
	/*���_�o�b�t�@�̉��*/
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
	
}
void UpdateLine(void)
{
	VERTEX_POINT*pVtx = NULL;
	/*���_�o�b�t�@�����b�N*/
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);
	
	/*���_�o�b�t�@�̃A�����b�N*/
	g_pVtxBuffLine->Unlock();
}
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos, D3DXCOLOR color)
{
	VERTEX_POINT*pVtx = NULL;
	/*���_�o�b�t�@�����b�N*/
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);
	for (int nLine = 0; nLine < MAX_LINE; nLine++)
	{
		if (!g_Line[nLine].buse)
		{
			
			/*�ʒu�ݒ�*/
			g_Line[nLine].pos = pos;
			/*�����ݒ�*/
			g_Line[nLine].rot = rot;
			
			/*�ʒu����*/
			pVtx[0].pos = startPos;
			pVtx[1].pos = endPos;

			pVtx[0].col = color;
			pVtx[1].col = color;
			SetWall(pos, rot, startPos, endPos);
			/*�g�p���Ă��邩*/
			g_Line[nLine].buse = true;
			break;
		}
		pVtx += 2;
	}
	/*���_�o�b�t�@�̃A�����b�N*/
	g_pVtxBuffLine->Unlock();
}
void DrawLine(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;


	for (int nLine = 0; nLine < MAX_LINE; nLine++)
	{
		if (g_Line[nLine].buse)
		{
			/*���[���h�}�g���N�X�̏���������*/
			D3DXMatrixIdentity(&g_Line[nLine].mtxWorld);
			/*�����𔽉f*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Line[nLine].rot.y, g_Line[nLine].rot.x, g_Line[nLine].rot.z);
			D3DXMatrixMultiply(&g_Line[nLine].mtxWorld, &g_Line[nLine].mtxWorld, &mtxRot);
			/*�ʒu�𔽉f*/
			D3DXMatrixTranslation(&mtxTrans, g_Line[nLine].pos.x, g_Line[nLine].pos.y, g_Line[nLine].pos.z);
			D3DXMatrixMultiply(&g_Line[nLine].mtxWorld, &g_Line[nLine].mtxWorld, &mtxTrans);
			/*���[���h�}�g���N�X�̐ݒ�*/
			pDevice->SetTransform(D3DTS_WORLD, &g_Line[nLine].mtxWorld);
			/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�*/
			pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_POINT));
			/*���_�t�H�[�}�b�g�̐ݒ�*/
			pDevice->SetFVF(FVF_VERTEX_POINT);
			/*�|���S���`��*/
			pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 2);
		}
	}
}