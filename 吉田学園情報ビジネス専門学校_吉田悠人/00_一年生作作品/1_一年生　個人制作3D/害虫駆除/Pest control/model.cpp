#include "main.h"
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "billboard.h"
#include "block.h"
#include "polygon.h"
#include "enemy.h"
#include "item.h"
#include "fade.h"
#include "magic.h"
#include "magic_ui.h"
#include "map.h"
#include "boss.h"
#include "sound.h"
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// �e�q�֌W		
}FIR;
//void SetPlayeAnimation(int playerAnimation);
//void UpdatePlayeAnimation();

/*--�O���[�o���ϐ�--*/
/*���f�����*/
D3DXMATERIAL *pMat[MODEL_LABEL_MAX];
/*�p�[�c�Q�̍\����*/
PLAYER g_Player;
/*�e�̏���*/
int g_Shadow=0;
/*���f���̌��������i�r���{�[�h�����j*/
D3DXVECTOR3 g_dir;
JOYINFOEX JOYPAD2; //�O��̃W���C�X�e�B�b�N�̃f�[�^
/*----------------*/
/*���݂̃t���[����*/
int g_frameCountModel = 0;
/*�Đ����̃L�[�Z�b�g�C���f�b�N�X*/
int g_playKeySetlndexModel = 0;
/*�Đ����̃A�j�����[�V����*/
int g_boosCurrentAnimationModel = 0;

/*�t�@�C��*/
FIR g_Fir[MODEL_LABEL_MAX] =
{
	{ "data/Xfile/staff.x", -1 },		

};
/*----------------*/

void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA* pCamera = GetCamera();
	MAP* pMap = GetMap();
	for (int i = 0; i < MODEL_LABEL_MAX; i++)
	{

		/*X�t�@�C���̓ǂݍ���*/
		D3DXLoadMeshFromX(
			g_Fir[i].pFilename,
			D3DXMESH_MANAGED,
			pDevice,
			NULL,
			&g_Player.modelParts[i].pBuffMat,
			NULL,
			&g_Player.modelParts[i].nNumMat,
			&g_Player.modelParts[i].pMesh);

		/*�}�e���A���f�[�^�ւ̃|�C���^���擾*/
		pMat[i] = (D3DXMATERIAL*)g_Player.modelParts[i].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.modelParts[i].nNumMat; nCntMat++)
		{
			if (pMat[i][nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[i][nCntMat].pTextureFilename, &g_Player.modelParts[i].pTextureModel[nCntMat]);
			}
		}

	}
	g_Player.state = PLAYERSTATE_NORMAL;
	/*�����ʒu*/
	g_Player.pos = D3DXVECTOR3(0.0f, 10.0f, 600.0f);
	/*��������*/
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotDest= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	/*�����̏�������*/
	g_dir = D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y)), 0, -cosf(D3DXToRadian(pCamera->rot.y)));
	/*�̗͏���������*/
	g_Player.nLife = 3;
	/*�e�̏�������*/
	g_Shadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 0, g_Player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	/*�}�W�b�N�X�C�b�`*/
	g_Player.nMagic = 0;

}
void UninitModel(void)
{
	for (int i = 0; i < MODEL_LABEL_MAX; i++)
	{
		/*���b�V���̔j��*/
		if (g_Player.modelParts[i].pMesh != NULL)
		{
			g_Player.modelParts[i].pMesh->Release();
			g_Player.modelParts[i].pMesh = NULL;
		}

		/*�}�e���A���̔j��*/
		if (g_Player.modelParts[i].pBuffMat != NULL)
		{
			g_Player.modelParts[i].pBuffMat->Release();
			g_Player.modelParts[i].pBuffMat = NULL;
		}
		/*�e�N�X�`��*/
		for (int nCnt = 0; nCnt < (int)g_Player.modelParts[i].nNumMat; nCnt++)
		{
			if (g_Player.modelParts[i].pTextureModel[nCnt] != NULL)
			{
				g_Player.modelParts[i].pTextureModel[nCnt]->Release();
				g_Player.modelParts[i].pTextureModel[nCnt] = NULL;
			}
		}
	}


}
void UpdateModel(void)
{
	/*�R���g���[���[�̏���*/
	JOYINFOEX JOYPAD; //���݂̃W���C�X�e�B�b�N�̃f�[�^
	
	CAMERA* pCamera = GetCamera();
	ENEMY* pEnemy = GetEnemy();
	MAGIC_NUMBER* pMagic = GetMagic_Number();
	MAP* pMap = GetMap();
	SetPositionShadow(g_Shadow, D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y - 10, g_Player.pos.z));
	
	/*�W���C�p�b�g�̓���*/
	JOYPAD.dwSize = sizeof(JOYINFOEX);
	JOYPAD.dwFlags = JOY_RETURNALL; // �S�Ă̏����擾



	/*�J�����̌�������A�O�㍶�E�Ƀ��f�����ړ�������*/
	if (joyGetPosEx(JOYSTICKID1, &JOYPAD)==JOYERR_NOERROR)
	{
		/*�r���{�[�h*/
		if ((JOYPAD.dwButtons&1)==1
			&& (JOYPAD2.dwButtons&1)==0)
		{
			PlaySound( SOUND_LABEL_SE_MAGIC2);
			SetBillboard(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 5, g_Player.pos.z), D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y+180)), 0, cosf(D3DXToRadian(pCamera->rot.y+180))));
		}
		if ((JOYPAD.dwButtons & 2) != 0
			&& (JOYPAD2.dwButtons & 2) == 0)
		{
			if (pMagic->Number[g_Player.nMagic] > 0)
			{
				pMagic->Number[g_Player.nMagic] -= 1;
				PlaySound(SOUND_LABEL_SE_MAGIC1);
				SetMagic(g_Player.nMagic, D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y+5, g_Player.pos.z), g_Player.rot, D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y + 180)), 0, cosf(D3DXToRadian(pCamera->rot.y + 180))));

			}
		}
		if ((JOYPAD.dwButtons & 8) != 0
			&& (JOYPAD2.dwButtons & 8) == 0)
		{
			g_Player.nMagic += 1;
		}
		else if ((JOYPAD.dwButtons & 4) != 0
			&& (JOYPAD2.dwButtons & 4) == 0)
		{
			g_Player.nMagic -= 1;
		}
		
		if (JOYPAD.dwXpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
		{
			g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y - 90)) * 1.0f;
			g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y - 90)) * 1.0f;
		}
		if (JOYPAD.dwXpos < 0x7FFF - 0x4000)//�E�ɓ|���X�e�B�b�N
		{
			g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y + 90)) * 1.0f;
			g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y + 90)) * 1.0f;
		}
		if (JOYPAD.dwYpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
		{
			g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y)) * 1.0f;
			g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y)) * 1.0f;
		}
		if (JOYPAD.dwYpos < 0x7FFF - 0x4000)//�O�ɓ|���X�e�B�b�N
		{
			g_Player.movePos.x -= sinf(D3DXToRadian(pCamera->rot.y)) * 1.0f;
			g_Player.movePos.z -= cosf(D3DXToRadian(pCamera->rot.y)) * 1.0f;
		}
		/*---------------------------------------------------------------------*/
		/*����*/
		if (JOYPAD.dwXpos > 0x7FFF + 0x4000)//�E�ɓ|���X�e�B�b�N
		{
			g_dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y + 270)), 0, cosf(D3DXToRadian(pCamera->rot.y + 270)));
			g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 90);
			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 135);
				g_dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y + 315)), 0, cosf(D3DXToRadian(pCamera->rot.y + 315)));

			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 45);
				g_dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y + 225)), 0, cosf(D3DXToRadian(pCamera->rot.y + 225)));

			}
		}

		else if (JOYPAD.dwXpos < 0x7FFF - 0x4000)//���ɓ|���X�e�B�b�N
		{
			g_dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y + 90)), 0, cosf(D3DXToRadian(pCamera->rot.y + 90)));

			g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 270);

			if (JOYPAD.dwYpos > 0x7FFF + 0x4000)
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 225);
				g_dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y + 45)), 0, cosf(D3DXToRadian(pCamera->rot.y + 45)));

			}
			if (JOYPAD.dwYpos < 0x7FFF - 0x4000)
			{
				g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 315);
				g_dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y + 135)), 0, cosf(D3DXToRadian(pCamera->rot.y + 135)));

			}
		}
		else if (JOYPAD.dwYpos > 0x7FFF + 0x4000)//���ɓ|���X�e�B�b�N
		{
			g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 180);
			g_dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y)), 0, cosf(D3DXToRadian(pCamera->rot.y)));

		}
		else if (JOYPAD.dwYpos < 0x7FFF - 0x4000)//�O�ɓ|���X�e�B�b�N
		{
			g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 0);
			g_dir = D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y)), 0, -cosf(D3DXToRadian(pCamera->rot.y)));

		}
		/*---------------------------------------------------------------------------*/
		JOYPAD2 = JOYPAD;
	}
	
	if (Getkeyboardpress(DIK_UP))
	{
		g_Player.movePos.x -= sinf(D3DXToRadian(pCamera->rot.y)) * 1.0f;
		g_Player.movePos.z -= cosf(D3DXToRadian(pCamera->rot.y)) * 1.0f;
		g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 0);
		g_dir = D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y)), 0, -cosf(D3DXToRadian(pCamera->rot.y)));
	}
	if (Getkeyboardpress(DIK_DOWN))
	{
		g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y)) * 1.0f;
		g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y)) * 1.0f;
		g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 180);
		g_dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y)), 0, cosf(D3DXToRadian(pCamera->rot.y)));
	}
	if (Getkeyboardpress(DIK_LEFT))
	{
		g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y + 90)) * 1.0f;
		g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y + 90)) * 1.0f;
		g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 270);
		g_dir = D3DXVECTOR3(sinf(D3DXToRadian(pCamera->rot.y + 90)), 0, cosf(D3DXToRadian(pCamera->rot.y + 90)));
	}
	if (Getkeyboardpress(DIK_RIGHT))
	{
		g_Player.movePos.x += sinf(D3DXToRadian(pCamera->rot.y - 90)) * 1.0f;
		g_Player.movePos.z += cosf(D3DXToRadian(pCamera->rot.y - 90)) * 1.0f;
		g_Player.rotDest.y = D3DXToRadian(pCamera->rot.y + 90);
		g_dir = D3DXVECTOR3(-sinf(D3DXToRadian(pCamera->rot.y + 90)), 0, -cosf(D3DXToRadian(pCamera->rot.y + 90)));
	}
	/*----------------------------------------------------------------------------------*/
	/*�U���������*/
	if (g_Player.rot.y >= D3DXToRadian(pCamera->rot.y + 180) && g_Player.rotDest.y == D3DXToRadian(pCamera->rot.y + 0))//�E��菈��
	{
		if (g_Player.rot.y >= D3DXToRadian(pCamera->rot.y + 270) && g_Player.rot.y < D3DXToRadian(pCamera->rot.y + 314))
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y - 90);
		}
		else if (g_Player.rot.y <= D3DXToRadian(pCamera->rot.y + 315))
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y - 45);
		}
		else
		{
			g_Player.rot += (g_Player.rotDest - g_Player.rot)* 0.09f;
		}
	}
	else if (g_Player.rot.y <= D3DXToRadian(pCamera->rot.y + 90))//�����
	{
		if (g_Player.rotDest.y == D3DXToRadian(pCamera->rot.y + 270))
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 360);
		}
		else if (g_Player.rotDest.y == D3DXToRadian(pCamera->rot.y + 315))
		{
			g_Player.rot.y = D3DXToRadian(pCamera->rot.y + 360);
		}
		else
		{
			g_Player.rot += (g_Player.rotDest - g_Player.rot)* 0.09f;
		}
	}
	else
	{
		g_Player.rot += (g_Player.rotDest - g_Player.rot)* 0.09f;
	}
	/*----------------------------------------------------------------------------------*/

	///*�W�����v����*/
	//if (GetKeyboardTrigger(DIK_Z))
	//{
	//	if (CollisionBlock(&g_Player.pos, &g_Player.posOld, D3DXVECTOR3(10, 13, 10)) == true
	//		|| CollisionPolygon(&g_Player.pos, &g_Player.posOld, D3DXVECTOR3(10, 13, 10)) == true)
	//	{
	//		g_Player.movePos.y += 40.5f;
	//	}
	//}
	/*-------------------------------------------------------------------------------------*/
	/*����*/
	g_Player.movePos.x += (0.0f - g_Player.movePos.x)*0.5f;
	g_Player.movePos.y += (0.0f - g_Player.movePos.y)*0.5f;
	g_Player.movePos.z += (0.0f - g_Player.movePos.z)*0.5f;
	/*�ʒu�X�V*/
	g_Player.pos += g_Player.movePos;
	/*�d�͉����x�X�V*/
	g_Player.movePos.y += (float)g_Player.vy;
	/*�ʒu�̋L�^*/
	g_Player.posOld = g_Player.pos;
	/*------------------------------------------------------------------------------------*/
	/*�r���{�[�h*/
	if (GetKeyboardTrigger(DIK_Z))
	{
		SetBillboard(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 5, g_Player.pos.z), g_dir);
	}

	if (GetKeyboardTrigger(DIK_X)&& pMagic->Number[g_Player.nMagic]>0)
	{
		pMagic->Number[g_Player.nMagic]-=1;
		SetMagic(g_Player.nMagic, D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z), g_Player.rot,g_dir);
	}
	/*�}�W�b�N�X�C�b�`�ύX*/
	if (GetKeyboardTrigger(DIK_A))
	{
		g_Player.nMagic += 1;
		
	}
	else if (GetKeyboardTrigger(DIK_D))
	{
		g_Player.nMagic -= 1;
		
	}
	if (g_Player.nMagic < 0)
	{
		g_Player.nMagic = 3;
	}
	else if (g_Player.nMagic > 3)
	{
		g_Player.nMagic = 0;
	}
	/*-------------------------------------------------------------------------------------*/
	CollisionItem(&g_Player.pos, &g_Player.posOld, D3DXVECTOR3(10, 13, 10));
	/*-------------------------------------------------------------------------------------*/
	D3DXIntersect(
		pMap->Mesh,
		&D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z),
		&D3DXVECTOR3(0,-1,0),
		&g_Player.Hit,
		NULL,
		NULL,
		NULL,
		&g_Player.fDist,
		NULL,
		NULL);
	/*�u���b�N�ɏ�������̏���*/
	if (CollisionBlock(&g_Player.pos, &g_Player.posOld, D3DXVECTOR3(10, 13, 10)) == true)
	{
		g_Player.movePos.y = 0;
		g_Player.vy = 0;
	}
	else if (g_Player.Hit&&g_Player.fDist < 13.0f)
	{	
		
		g_Player.pos.y = g_Player.pos.y - g_Player.fDist+13.0f;
		g_Player.vy = 0;	
	}
	else
	{
		/*�d��*/
		g_Player.vy = -0.9f;
	}
	//UpdatePlayeAnimation();
	/*-------------------1------------------------------------------------------------------*/
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
		/*�v���C���[�̈ʒu���擾*/
		break;
	case PLAYERSTATE_DEATH:
		SetFade(MODE_GAMEOVER);
		return;
		break;
	}
}
void DrawModel(void)
{
	/*�f�o�C�X�ւ̃|�C���^*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxParent;
	/*���݂̃}�e���A���ێ��p*/
	D3DMATERIAL9 matDef;
	int nCntMat;
	/*���[���h�}�g���N�X�̏���������*/
	D3DXMatrixIdentity(&g_Player.mtxWorld );
	/*�����𔽉f*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);
	/*�ʒu�𔽉f*/
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);
	for (int i = 0; i < MODEL_LABEL_MAX; i++)
	{
		/*�p�[�c���[���h�}�g���N�X�̏���������*/
		D3DXMatrixIdentity(&g_Player.modelParts[i].mtxWorld);
		/*�p�[�c�����𔽉f*/
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.modelParts[i].rot.y, g_Player.modelParts[i].rot.x, g_Player.modelParts[i].rot.z);
		D3DXMatrixMultiply(&g_Player.modelParts[i].mtxWorld, &g_Player.modelParts[i].mtxWorld, &mtxRot);
		/*�p�[�c�ʒu�𔽉f*/
		D3DXMatrixTranslation(&mtxTrans, g_Player.modelParts[i].pos.x, g_Player.modelParts[i].pos.y, g_Player.modelParts[i].pos.z);
		D3DXMatrixMultiply(&g_Player.modelParts[i].mtxWorld, &g_Player.modelParts[i].mtxWorld, &mtxTrans);
		/*�e���f���̃}�g���b�N�X�̔��f*/
		if (g_Fir[i].nCntLoop == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.modelParts[g_Fir[i].nCntLoop].mtxWorld;
		}

		D3DXMatrixMultiply(&g_Player.modelParts[i].mtxWorld,&g_Player.modelParts[i].mtxWorld, &mtxParent);
		/*���[���h�}�g���b�N�X�̐ݒ�*/
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.modelParts[i].mtxWorld);
		/*���݂̃}�e���A�����擾����*/
		pDevice->GetMaterial(&matDef);
		for (nCntMat = 0; nCntMat < (int)g_Player.modelParts[i].nNumMat; nCntMat++)
		{
			/*�}�e���A���̐ݒ�*/
			pDevice->SetMaterial(&pMat[i][nCntMat].MatD3D);
			pDevice->SetTexture(0, g_Player.modelParts[i].pTextureModel[nCntMat]);
			/*���f���p�[�c�̕`��*/
			g_Player.modelParts[i].pMesh->DrawSubset(nCntMat);
		}
		/*�ێ����Ă����}�e���A����߂�*/
		pDevice->SetMaterial(&matDef);
	}
}
void HitModel(int nDamage, int nEnemy,int nHit)
{
	BOOS*pBoos = GetBoos();
	ENEMY* pEnemy = GetEnemy();
	if (g_Player.state == PLAYERSTATE_NORMAL)
	{
		g_Player.nLife -= nDamage;
		if (nHit == 0)
		{
			g_Player.fAngle = atan2f((-g_Player.pos.x - -pBoos->modelParts[nEnemy].pos.x), (-g_Player.pos.z - -pBoos->modelParts[nEnemy].pos.z));

		}
		else if (nHit == 1)
		{
			g_Player.fAngle = atan2f((-g_Player.pos.x - -pEnemy[nEnemy].pos.x), (-g_Player.pos.z - -pEnemy[nEnemy].pos.z));

		}
		/*�G�̔��Ε����ɂ̂�����*/
		g_Player.movePos.x = sinf(g_Player.fAngle)*-50.0f;
		g_Player.movePos.z = cosf(g_Player.fAngle)*-50.0f;
		if (g_Player.nLife <= 0)
		{/*���C�t���O�ɂȂ����Ƃ�*/
			g_Player.state = PLAYERSTATE_DEATH;//���S��ԂɈڍs
		}
		else
		{/*�_���[�W��ԃJ�E���^�[��ԂɈڍs*/
			g_Player.state = PLAYERSTATE_DAMAGE;//�_���[�W��ԂɈڍs
			g_Player.nDamage = 100;
		}
	}
	
}
//void SetPlayeAnimation(int playerAnimation)
//{
//	if (g_boosCurrentAnimationModel != playerAnimation)
//	{
//		g_frameCountModel = 0;
//		g_playKeySetlndexModel = 0;
//	}
//	g_boosCurrentAnimationModel = playerAnimation;
//	g_motionModel[g_boosCurrentAnimationModel].keySet[g_playKeySetlndexModel];
//
//}
//void UpdatePlayeAnimation()
//{
//	if (g_frameCountModel == 0)
//	{
//	
//		for (int nAnime = 0; nAnime < BOOS_PARTS_MAX; nAnime++)
//		{
//			g_Player.modelParts[nAnime].rotAnime = (g_motionModel[g_boosCurrentAnimationModel].keySet[g_playKeySetlndexModel].key[nAnime].rot - g_Player.modelParts[nAnime].rot) / g_motionModel[g_boosCurrentAnimationModel].keySet[g_playKeySetlndexModel].frame;
//			g_Player.modelParts[nAnime].posAnime = (g_motionModel[g_boosCurrentAnimationModel].keySet[g_playKeySetlndexModel].key[nAnime].pos - g_Player.modelParts[nAnime].pos) / g_motionModel[g_boosCurrentAnimationModel].keySet[g_playKeySetlndexModel].frame;
//		}
//	}
//	g_frameCountModel++;
//	if (g_motionModel[g_boosCurrentAnimationModel].keySet[g_playKeySetlndexModel].frame == g_frameCountModel)
//	{
//		g_frameCountModel = 0;
//		g_playKeySetlndexModel++;
//		if (g_playKeySetlndexModel == g_motionModel[g_boosCurrentAnimationModel].keyNum&&g_motionModel[g_boosCurrentAnimationModel].isLoop)
//		{
//			g_playKeySetlndexModel = 0;
//		}
//		else
//		{
//			SetPlayeAnimation(0);
//			g_frameCountModel = 0;
//		}
//	}
//	for (int nAnime = 0; nAnime < BOOS_PARTS_MAX; nAnime++)
//	{
//		g_Player.modelParts[nAnime].rot += g_Player.modelParts[nAnime].rotAnime;
//		g_Player.modelParts[nAnime].pos += g_Player.modelParts[nAnime].posAnime;
//	}
//
//}

PLAYER*GetPlayer()
{
	return &g_Player;
}