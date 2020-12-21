#include "main.h"
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "billboard.h"
#include "block.h"
#include "enemy.h"
#include "item.h"
#include "fade.h"
#include "score.h"
#include "map.h"
#include <stdio.h>
#include <string.h>
/*�}�N����`*/
#define FILE_DATA 3				//�e�L�X�g�ǂݍ��݂̃f�[�^
/*--�O���[�o���ϐ�--*/
void SetPlayeAnimation(int playerAnimation);
void UpdatePlayeAnimation();
typedef struct 
{
	char			file[100];	//�ǂݍ��񂾂P��̕���
	int				nAnimaTion;	//���Ԗڂ̃A�j���[�V������
	int				nFrame;		//�t���C����
	int				nKeySet;	//���݂̃L�[�Z�b�g�̐�
}FILETEXT;
FILETEXT g_filetext;
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// �e�q�֌W		
}FILEDATA;
/*�}�e���A���f�[�^�ւ̃|�C���^*/
D3DXMATERIAL *pMat[MODEL_LABEL_MAX];
/*���f�����*/
PLAYER g_Player;
/*�e�̏���*/
int g_Shadow=0;
/*���f���̌���*/
D3DXVECTOR3 dir;
/*���݂̃t���[����*/
int g_frameCountModel = 0;
/*�Đ����̃L�[�Z�b�g�C���f�b�N�X*/
int g_playKeySetlndexModel = 0;
/*�Đ����̃A�j�����[�V����*/
int g_PlayerCurrentAnimationModel = 0;
/*�t�@�C��*/
FILEDATA g_FilePlayer[MODEL_LABEL_MAX] =
{
	{ "X�t�@�C��/�z�B���i���́j.x", -1 },	//0
	{ "X�t�@�C��/�z�B���i���j.x", 0 },		//1
	{ "X�t�@�C��/�z�B���i���j.x", 0 },		//2
	{ "X�t�@�C��/�z�B���i�E�r1�j.x", 0 },	//3
	{ "X�t�@�C��/�z�B���i�E�r2�j.x", 3 },	//4
	{ "X�t�@�C��/�z�B���i���r1�j.x", 0 },	//5
	{ "X�t�@�C��/�z�B���i���r2�j.x", 5 },	//6
	{ "X�t�@�C��/�z�B���i�E��1�j.x", 2 },	//7
	{ "X�t�@�C��/�z�B���i�E��2�j.x", 7 },	//8
	{ "X�t�@�C��/�z�B���i����1�j.x", 2 },	//9
	{ "X�t�@�C��/�z�B���i����2�j.x", 9 },	//10
};
void anime(void);
Animation g_motion[MOTION_ANIMATION_NUM];
/*------------------*/
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA* pCamera = GetCamera();
	for (int nParts = 0; nParts < MODEL_LABEL_MAX; nParts++)
	{
		/*X�t�@�C���̓ǂݍ���*/
		D3DXLoadMeshFromX(
			g_FilePlayer[nParts].pFilename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.modelParts[nParts].pBuffMat,
			NULL,
			&g_Player.modelParts[nParts].nNumMat,
			&g_Player.modelParts[nParts].pMesh);
		/*�}�e���A���f�[�^�ւ̃|�C���^���擾*/
		pMat[nParts] = (D3DXMATERIAL*)g_Player.modelParts[nParts].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.modelParts[nParts].nNumMat; nCntMat++)
		{
			if (pMat[nParts][nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nParts][nCntMat].pTextureFilename, &g_Player.modelParts[nParts].pTextureModel[nCntMat]);
			}
		}
	}
	/*�e�L�X�g���̏�����*/
	g_filetext.nAnimaTion	 = 0;
	g_filetext.nFrame		 = 0;
	/*�����ʒu*/
	g_Player.pos = D3DXVECTOR3(0.0f, 25.0f, 0.0f);
	g_Player.modelParts[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.modelParts[1].pos = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	g_Player.modelParts[2].pos = D3DXVECTOR3(0.0f, -7.0f, 0.0f);
	g_Player.modelParts[3].pos = D3DXVECTOR3(-4.1f, 1.0f, 0.0f);
	g_Player.modelParts[4].pos = D3DXVECTOR3(-4.1f, -3.0f, 0.0f);
	g_Player.modelParts[5].pos = D3DXVECTOR3(4.0f, 1.0f, 0.0f);
	g_Player.modelParts[6].pos = D3DXVECTOR3(4.1f, -3.0f, 0.0f);
	g_Player.modelParts[7].pos = D3DXVECTOR3(-1.0f, -8.0f, 0.1f);
	g_Player.modelParts[8].pos = D3DXVECTOR3(-2.0f, -15.0f, 0.1f);
	g_Player.modelParts[9].pos = D3DXVECTOR3(1.0f, -8.0f, 0.1f);
	g_Player.modelParts[10].pos = D3DXVECTOR3(2.0f, -15.0f, 0.1f);
	/*��������*/
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nItemType = 0; nItemType < TITLE_TYPE_MAX; nItemType++)
	{	
		for (int nItem=0; nItem < MAX_ITEM; nItem++)
		{	/*�����A�C�e������*/
			g_Player.bItem[nItem][nItemType] = false;
			/*�A�C�e�����C�t*/
			g_Player.nLife[nItem][nItemType] = 0;
		}
	}
	/*�_���[�W���G����*/
	g_Player.nDamage = 0;
	/*�S�[���X�C�b�`������*/
	g_Player.bGoal = false;
	dir = D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y)), 0, -cosf(D3DXToRadian(pCamera->rot.y)));
	g_Shadow=SetShadow(D3DXVECTOR3(g_Player.pos.x, 0, g_Player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	anime();
}
void UninitPlayer(void)
{
	for (int nParts = 0; nParts < MODEL_LABEL_MAX; nParts++)
	{
		/*���b�V���̔j��*/
		if (g_Player.modelParts[nParts].pMesh != NULL)
		{
			g_Player.modelParts[nParts].pMesh->Release();
			g_Player.modelParts[nParts].pMesh = NULL;
		}

		/*�}�e���A���̔j��*/
		if (g_Player.modelParts[nParts].pBuffMat != NULL)
		{
			g_Player.modelParts[nParts].pBuffMat->Release();
			g_Player.modelParts[nParts].pBuffMat = NULL;
		}
		/*�e�N�X�`��*/
		for (int nCnt = 0; nCnt < (int)g_Player.modelParts[nParts].nNumMat; nCnt++)
		{
			if (g_Player.modelParts[nParts].pTextureModel[nCnt] != NULL)
			{
				g_Player.modelParts[nParts].pTextureModel[nCnt]->Release();
				g_Player.modelParts[nParts].pTextureModel[nCnt] = NULL;
			}
		}
	}

	
}
void UpdatePlayer(void)
{
	/*�R���g���[���[�̏���*/
	JOYINFOEX JOYPAD;
	CAMERA* pCamera = GetCamera();
	/*�W���C�p�b�g�̓���*/
	JOYPAD.dwSize = sizeof(JOYINFOEX);
	JOYPAD.dwFlags = JOY_RETURNALL; // �S�Ă̏����擾
	
	/*----------------------------------------------------------------------------------*/
	/*�e�̏���*/
	SetPositionShadow(g_Shadow, D3DXVECTOR3(g_Player.pos.x,0.1f, g_Player.pos.z));
	/*----------------------------------------------------------------------------------*/
	/*�J�����̌�������A�O�㍶�E�Ƀ��f�����ړ�������*/
	if (joyGetPosEx(JOYSTICKID1, &JOYPAD) == JOYERR_NOERROR)
	{
		if (JOYPAD.dwButtons & JOY_BUTTON1)//����
		{
			if (JOYPAD.dwXpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
			{
				g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y - 90)) * 0.5f;
				g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y - 90)) * 0.5f;
			}
			if (JOYPAD.dwXpos < 0x7FFF - 0x4000)//�E�ɓ|���X�e�B�b�N
			{
				g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y + 90)) * 0.5f;
				g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y + 90)) * 0.5f;
			}
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
			{
				g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y)) * 0.5f;
				g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y)) * 0.5f;
			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)//�O�ɓ|���X�e�B�b�N
			{
				g_Player.movePos.x -= sinf(D3DXToRadian(pCamera->rot.y)) * 0.5f;
				g_Player.movePos.z -= cosf(D3DXToRadian(pCamera->rot.y)) * 0.5f;
			}
		}
		else//�ʏ�
		{
			if (JOYPAD.dwXpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
			{
				g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y - 90)) * 1;
				g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y - 90)) * 1;
			}
			if (JOYPAD.dwXpos < 0x7FFF - 0x4000)//�E�ɓ|���X�e�B�b�N
			{
				g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y + 90)) * 1;
				g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y + 90)) * 1;
			}
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
			{
				g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y)) * 1;
				g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y)) * 1;
			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)//�O�ɓ|���X�e�B�b�N
			{
				g_Player.movePos.x -= sinf(D3DXToRadian(pCamera->rot.y)) * 1;
				g_Player.movePos.z -= cosf(D3DXToRadian(pCamera->rot.y)) * 1;
			}
		}
		if (JOYPAD.dwXpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
		{
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 135);
			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 45);
			}
			else
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 90);

			}
		}
		
		else if (JOYPAD.dwXpos < 0x7FFF - 0x4000)//�E�ɓ|���X�e�B�b�N
		{
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 225);
			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 315);
			}
			else
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 270);
			}
		}
		else if (JOYPAD.dwYpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
		{
			g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 180);
		}
		else if (JOYPAD.dwYpos < 0x7FFF - 0x4000)//�O�ɓ|���X�e�B�b�N
		{
			g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 0);
		}

		/*g_Model.movePos.x = sinf(D3DXToRadian(pCamera->rot.y)) * 1;
		g_Model.movePos.z = cosf(D3DXToRadian(pCamera->rot.y)) * 1;*/
		/*�{�^��32�܂� �󐧌� */
		
		
		//g_Model.rotDest.y = D3DXToRadian(pCamera->rot.y );
		dir = D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y+ JOYPAD.dwXpos)), 0, -cosf(D3DXToRadian(pCamera->rot.y+ JOYPAD.dwYpos)));
	}
	//if (Getkeyboardpress(DIK_UP))
	//{
	//	g_Model.movePos.x -= sinf(D3DXToRadian(pCamera->rot.y)) * 1;
	//	g_Model.movePos.z -= cosf(D3DXToRadian(pCamera->rot.y)) * 1;
	//	g_Model.rotDest.y = D3DXToRadian(pCamera->rot.y + 0);
	//	dir = D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y)), 0, -cosf(D3DXToRadian(pCamera->rot.y)));
	//}
	//if (Getkeyboardpress(DIK_DOWN))
	//{
	//	g_Model.movePos.x += sinf(D3DXToRadian(pCamera->rot.y)) * 1;
	//	g_Model.movePos.z += cosf(D3DXToRadian(pCamera->rot.y)) * 1;
	//	g_Model.rotDest.y = D3DXToRadian(pCamera->rot.y + 180);
	//	dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y)), 0, cosf(D3DXToRadian(pCamera->rot.y)));
	//}
	//if (Getkeyboardpress(DIK_LEFT))
	//{
	//	g_Model.movePos.x += sinf(D3DXToRadian(pCamera->rot.y + 90)) * 1;
	//	g_Model.movePos.z += cosf(D3DXToRadian(pCamera->rot.y+90)) * 1;
	//	g_Model.rotDest.y = D3DXToRadian(pCamera->rot.y + 270);
	//	dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y + 90)), 0, cosf(D3DXToRadian(pCamera->rot.y + 90)));
	//}
	//if (Getkeyboardpress(DIK_RIGHT))
	//{
	//	g_Model.movePos.x += sinf(D3DXToRadian(pCamera->rot.y - 90)) * 1;
	//	g_Model.movePos.z += cosf(D3DXToRadian(pCamera->rot.y - 90)) * 1;
	//	g_Model.rotDest.y = D3DXToRadian(pCamera->rot.y + 90);
	//	dir = D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y + 90)), 0, -cosf(D3DXToRadian(pCamera->rot.y + 90)));
	//}
	/*----------------------------------------------------------------------------------*/
	/*�U���������*/
	if (D3DXToRadian(pCamera->rot.y) >= (D3DXToRadian(360)) || D3DXToRadian(pCamera->rot.y) <= (D3DXToRadian(-360)))
	{
		pCamera->rot.y = D3DXToRadian(0);
		//g_Player.rotDest.y = D3DXToRadian(0);
		if (JOYPAD.dwXpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
		{
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)
			{
				g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 135);
			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)
			{
				g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 45);
			}
			else
			{
				g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 90);
			}
		}

		else if (JOYPAD.dwXpos < 0x7FFF - 0x4000)//�E�ɓ|���X�e�B�b�N
		{
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)
			{
				g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 225);
			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)
			{
				g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 315);
			}
			else
			{
				g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 270);
			}
		}
		else if (JOYPAD.dwYpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 180);
		}
		else if (JOYPAD.dwYpos < 0x7FFF - 0x4000)//�O�ɓ|���X�e�B�b�N
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 0);
		}
		
	}
	else if (g_Player.rot.y >=D3DXToRadian(pCamera->rot.y+180)&& g_Player.rotDest.y == D3DXToRadian(pCamera->rot.y + 0))//�E��菈��
	{
		if (g_Player.rot.y <= D3DXToRadian(pCamera->rot.y + 315))
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y - 45);
		}
		else if (g_Player.rot.y >= D3DXToRadian(pCamera->rot.y + 270) && g_Player.rot.y < D3DXToRadian(pCamera->rot.y + 314))
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y - 90);
		}
	}
	else if (g_Player.rot.y<=D3DXToRadian(pCamera->rot.y + 90))//�����
	{
		if (g_Player.rotDest.y == D3DXToRadian(pCamera->rot.y + 270))
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 360);
		}
		else if (g_Player.rotDest.y == D3DXToRadian(pCamera->rot.y + 315))
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 360);
		}
	}
	
	g_Player.rot += (g_Player.rotDest - g_Player.rot)* 0.09;
	/*----------------------------------------------------------------------------------*/
	/*�u���b�N����*/
	if (CollisionBlock(&g_Player.pos, &g_Player.posOld, D3DXVECTOR3(10, 40, 10)) == true)
	{
		g_Player.movePos.y = 0;
		//g_Player.vy = 0;
	}
	else
	{

	}
	if (g_Player.state != PLAYERSTATE_DAMAGE)
	{
		CollisionItem(&g_Player.pos, &g_Player.posOld, D3DXVECTOR3(10, 40, 10));
	}
	/*-------------------------------------------------------------------------------------*/



	/*����*/
	g_Player.movePos.x += (0.0f - g_Player.movePos.x)*0.5f;
	g_Player.movePos.y += (0.0f - g_Player.movePos.y)*0.5f;
	g_Player.movePos.z += (0.0f - g_Player.movePos.z)*0.5f;
	/*�ʒu�X�V*/
	g_Player.pos += g_Player.movePos;
	/*�d�͉����x�X�V*/
	//g_Player.movePos.y += g_Player.vy;
	/*�ʒu�̋L�^*/
	g_Player.posOld = g_Player.pos;
	/*-------------------------------------------------------------------------------------*/
	/*�v���C���[���[�h(�_���[�W)*/
	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_Player.nDamage--;
		if (g_Player.nDamage <= 0)
		{
			/*�ʏ�`��ɖ߂�����*/
			g_Player.state = PLAYERSTATE_NORMAL;
		}
		break;
	case PLAYERSTATE_DEATH:
		SetFade(MODE_GAMEOVER);
		return;
		break;
	}
	/*�A�j���[�V�����Đ�*/
	UpdatePlayeAnimation();
}
void DrawPlayer(void)
{
	/*�f�o�C�X�ւ̃|�C���^*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxParent;
	/*���݂̃}�e���A���ێ��p*/
	D3DMATERIAL9 matDef;
	
	/*���[���h�}�g���N�X�̏���������*/
	D3DXMatrixIdentity(&g_Player.mtxWorld);
	/*�����𔽉f*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);
	/*�ʒu�𔽉f*/
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);
	for (int nParts = 0; nParts < MODEL_LABEL_MAX; nParts++)
	{
		/*�p�[�c���[���h�}�g���N�X�̏���������*/
		D3DXMatrixIdentity(&g_Player.modelParts[nParts].mtxWorldAnime);

		/*�p�[�c�����𔽉f*/
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.modelParts[nParts].rotAnime.y, g_Player.modelParts[nParts].rotAnime.x, g_Player.modelParts[nParts].rotAnime.z);
		D3DXMatrixMultiply(&g_Player.modelParts[nParts].mtxWorldAnime, &g_Player.modelParts[nParts].mtxWorldAnime, &mtxRot);
		/*�p�[�c�ʒu�𔽉f*/
		D3DXMatrixTranslation(&mtxTrans, g_Player.modelParts[nParts].posAnime.x, g_Player.modelParts[nParts].posAnime.y, g_Player.modelParts[nParts].posAnime.z);
		D3DXMatrixMultiply(&g_Player.modelParts[nParts].mtxWorldAnime, &g_Player.modelParts[nParts].mtxWorldAnime, &mtxTrans);

		/*�e���f���̃}�g���b�N�X�̔��f*/
		if (g_FilePlayer[nParts].nCntLoop == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.modelParts[g_FilePlayer[nParts].nCntLoop].mtxWorldAnime;
		}
		D3DXMatrixMultiply(&g_Player.modelParts[nParts].mtxWorldAnime, &g_Player.modelParts[nParts].mtxWorldAnime, &mtxParent);
		
		/*���[���h�}�g���b�N�X�̐ݒ�*/
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.modelParts[nParts].mtxWorld);
		
		/*�p�[�c���[���h�}�g���N�X�̏���������*/
		D3DXMatrixIdentity(&g_Player.modelParts[nParts].mtxWorld);
		/*�A�j���p�[�c�����𔽉f*/
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.modelParts[nParts].rot.y, g_Player.modelParts[nParts].rot.x, g_Player.modelParts[nParts].rot.z);
		D3DXMatrixMultiply(&g_Player.modelParts[nParts].mtxWorld, &g_Player.modelParts[nParts].mtxWorld, &mtxRot);
		/*�A�j���p�[�c�ʒu�𔽉f*/
		D3DXMatrixTranslation(&mtxTrans, g_Player.modelParts[nParts].pos.x, g_Player.modelParts[nParts].pos.y, g_Player.modelParts[nParts].pos.z);
		D3DXMatrixMultiply(&g_Player.modelParts[nParts].mtxWorld, &g_Player.modelParts[nParts].mtxWorld, &mtxTrans);

		D3DXMatrixMultiply(&g_Player.modelParts[nParts].mtxWorld, &g_Player.modelParts[nParts].mtxWorld, &g_Player.modelParts[nParts].mtxWorldAnime);

		/*���[���h�}�g���b�N�X�̐ݒ�*/
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.modelParts[nParts].mtxWorld);

	
		/*���݂̃}�e���A�����擾����*/
		pDevice->GetMaterial(&matDef);
		for (int nCntMat = 0; nCntMat < (int)g_Player.modelParts[nParts].nNumMat; nCntMat++)
		{
			/*�}�e���A���̐ݒ�*/
			pDevice->SetMaterial(&pMat[nParts][nCntMat].MatD3D);

			pDevice->SetTexture(0, g_Player.modelParts[nParts].pTextureModel[nCntMat]);
			/*���f���p�[�c�̕`��*/
			g_Player.modelParts[nParts].pMesh->DrawSubset(nCntMat);
		}
		/*�ێ����Ă����}�e���A����߂�*/
		pDevice->SetMaterial(&matDef);
	}
}
void HitPlayer(bool bDamage)
{
	ITEM* pItem = GetItem();
	CAMERA* pCamera = GetCamera();
	ENEMY* pEnemy = GetEnemy();
	if (g_Player.state == PLAYERSTATE_NORMAL)
	{
		for (int nItem = 0; nItem < MAX_ITEM; nItem++)
		{
			for (int nItemType = 0; nItemType < TITLE_TYPE_MAX; nItemType++)
			{
				if (g_Player.bItem[nItem][nItemType])
				{
					SetItem(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y+10, g_Player.pos.z), D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y +45* (nItem))), 0.1f, -cosf(D3DXToRadian(pCamera->rot.y +45 * (nItem)))), nItemType);
					g_Player.bItem[nItem][nItemType] = false;
					if (g_Player.nLife[nItem][nItemType] < 3)
					{
						g_Player.nLife[nItem][nItemType] += 1;
					}
					
				}
			}
		}
		g_Player.state = PLAYERSTATE_DAMAGE;//�_���[�W��ԂɈڍs
		g_Player.nDamage = 100;
		g_Player.bGoal = false;
	}
}
void SetPlayeAnimation(int playerAnimation)
{
	if (g_PlayerCurrentAnimationModel != playerAnimation)
	{
		g_frameCountModel = 0;
		g_playKeySetlndexModel = 0;
	}
	g_PlayerCurrentAnimationModel = playerAnimation;
	g_motion[g_PlayerCurrentAnimationModel].keySet[g_playKeySetlndexModel];

}
void UpdatePlayeAnimation()
{
	if (g_frameCountModel == 0)
	{
	
		for (int nAnime = 0; nAnime < MODEL_LABEL_MAX; nAnime++)
		{
			g_Player.modelParts[nAnime].moverotAnime = (g_motion[g_PlayerCurrentAnimationModel].keySet[g_playKeySetlndexModel].key[nAnime].rot - g_Player.modelParts[nAnime].rotAnime) / g_motion[g_PlayerCurrentAnimationModel].keySet[g_playKeySetlndexModel].frame;
			g_Player.modelParts[nAnime].moveposAnime = (g_motion[g_PlayerCurrentAnimationModel].keySet[g_playKeySetlndexModel].key[nAnime].pos - g_Player.modelParts[nAnime].posAnime) / g_motion[g_PlayerCurrentAnimationModel].keySet[g_playKeySetlndexModel].frame;
		}
	}
	g_frameCountModel++;
	if (g_motion[g_PlayerCurrentAnimationModel].keySet[g_playKeySetlndexModel].frame == g_frameCountModel)
	{
		g_frameCountModel = 0;
		g_playKeySetlndexModel++;
		if (g_playKeySetlndexModel == g_motion[g_PlayerCurrentAnimationModel].keyNum&&g_motion[g_PlayerCurrentAnimationModel].isLoop)
		{
			g_playKeySetlndexModel = 0;
		}
		else
		{
			SetPlayeAnimation(0);
			g_frameCountModel = 0;
		}
	}
	for (int nAnime = 0; nAnime < MODEL_LABEL_MAX; nAnime++)
	{
		g_Player.modelParts[nAnime].rotAnime += g_Player.modelParts[nAnime].moverotAnime;
		g_Player.modelParts[nAnime].posAnime += g_Player.modelParts[nAnime].moveposAnime;
	}

}
void anime(void)
{
	/*�e�L�X�g�ǂݍ���*/
	FILE *file;
	char *fileneName = "�e�L�X�g/test.txt";	//�e�L�X�g�̖��O
	char *Type;								//�ǂݍ��񂾃e�L�X�g�i�A�j���[�V�����Đ��j
	char *Status;							//�ǂݍ��񂾍���


				
	if ((file = fopen(fileneName, "r"))!=NULL)//�e�L�X�g���J��
	{
		while (fgets(g_filetext.file, 100, file) != NULL)//�e�L�X�g��ǂݐ���
		{	
			if ((Type = strstr(g_filetext.file, "MOTIONSET"))!=NULL)//�������Ĉ�v���Ă�����
			{

			}
			/*���[�v���邩�̏���*/
			if ((Status = strstr(g_filetext.file, "LOOP")) != NULL)//�������Ĉ�v���Ă�����
			{
				char *hbool;
				g_Player.x += 1;//�u���C�N�|�C���g�u������
				hbool = strchr(g_filetext.file, '1');//�P���O���̔��
				if (hbool != NULL)
				{
					g_motion[g_filetext.nAnimaTion].isLoop = true;
				}
				else
				{
					g_motion[g_filetext.nAnimaTion].isLoop = false;
				}
				
			}
			/*�L�[�̐��̓ǂݍ��ݏ���*/
			else if ((Status = strstr(g_filetext.file, "NUM_KEY")) != NULL)//�������Ĉ�v���Ă�����
			{
				int  nKey;
				
				for (int nCount = 0; nCount < 100; nCount++)//������̐����ǂݍ���
				{
					if ((isdigit(g_filetext.file[nCount])) != NULL)
					{
						nKey = atoi(&g_filetext.file[nCount]);//�ǂݍ��񂾕������int�^�ɕϊ�
						
						g_motion[g_filetext.nAnimaTion].keyNum += nKey;
						g_Player.x += 1;//�u���C�N�|�C���g�u������
					}
				}
			}
			/*�L�[�t���[��������*/
			else if ((Status = strstr(g_filetext.file, "FRAME")) != NULL)
			{
				for (int nCount = 0; nCount < 100; nCount++)//������̐����ǂݍ���
				{
					if ((isdigit(g_filetext.file[nCount])) != 0)
					{
						int  nKey = atoi(&g_filetext.file[nCount]);//�ǂݍ��񂾕������int�^�ɕϊ�
						g_motion[g_filetext.nAnimaTion].keySet[g_filetext.nFrame].frame += nKey;
						g_Player.z += 1;//�u���C�N�|�C���g�u������
					}
				}
			}
			else if ((Status = strstr(g_filetext.file, "KEY")) != NULL)
			{

			}
			/*�e���ʂ̍��W����*/
			else if ((Status = strstr(g_filetext.file, "POS")) != NULL)
			{
				char	sSymbolpos[]="POS =	";	//���������؂蕶��
				char	*testpos;			//���������e�L�X�g��ۑ�
				double	dpos[FILE_DATA];		//���W�̕ۑ�
				int		nCountpos =0;		//���WXYZ�̐��l�ۑ�

				testpos = strtok(g_filetext.file, sSymbolpos);
				while (testpos != NULL)
				{
					dpos[nCountpos] = atof(testpos);
					g_motion[g_filetext.nAnimaTion].keySet[g_filetext.nFrame].key[g_filetext.nKeySet].pos = D3DXVECTOR3(dpos[0], dpos[1], dpos[2]);
					testpos = strtok(NULL, sSymbolpos);
					nCountpos += 1;
				}
			}
			else if ((Status = strstr(g_filetext.file, "ROT")) != NULL)
			{
				char	sSymbolrot[] = "ROT =	";	//���������؂蕶��
				char	*testrot;					//���������e�L�X�g��ۑ�
				double	drot[FILE_DATA];			//���W�̕ۑ�
				int		nCountrot = 0;				//���WXYZ�̐��l�ۑ�

				testrot = strtok(g_filetext.file, sSymbolrot);
				while (testrot != NULL)
				{
					drot[nCountrot] = atof(testrot);
					g_motion[g_filetext.nAnimaTion].keySet[g_filetext.nFrame].key[g_filetext.nKeySet].rot = D3DXVECTOR3(D3DXToRadian(drot[0]), D3DXToRadian(drot[1]), D3DXToRadian(drot[2]));
					testrot = strtok(NULL, sSymbolrot);
					nCountrot += 1;
				}
			}
			if ((Status = strstr(g_filetext.file, "END_KEY")) != NULL)
			{
				g_filetext.nKeySet += 1;
			}
			if ((Status = strstr(g_filetext.file, "END_KEYSET")) != NULL)
			{
				g_filetext.nFrame += 1;
				g_filetext.nKeySet = 0;
			}
			if ((Status = strstr(g_filetext.file, "END_MOTIONSET")) != NULL)
			{
				g_filetext.nFrame = 0;
				g_filetext.nAnimaTion += 1;
			}
		}
		fclose(file);							//�e�L�X�g�����
	}
	
}
PLAYER*GetPlayer()
{
	return &g_Player;
}