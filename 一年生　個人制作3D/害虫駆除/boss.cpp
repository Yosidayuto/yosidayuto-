#include "boss.h"
#include "model.h"
#include "map.h"
#include "fade.h"
#include"enemy.h"
#include "magic.h"
#include <time.h>
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// �e�q�֌W		
}FIR;
void SetAnimation(int playerAnimation);
void UpdateAnimation();
/*--�O���[�o���ϐ�--*/
/*���f�����*/
D3DXMATERIAL *pMatBoos[BOOS_PARTS_MAX];
/*�p�[�c�Q�̍\����*/
BOOS g_Boos;
/*���݂̃t���[����*/
int g_frameCount = 0;
/*�Đ����̃L�[�Z�b�g�C���f�b�N�X*/
int g_playKeySetlndex = 0;
/*�Đ����̃A�j�����[�V����*/
int g_boosCurrentAnimation = 0;
bool g_anime;
int g_animeCount = 0;
Animation g_motion[MOTION_ANIMATION_NUM]=
{
	{ true,2,
		{
			{ 60,
				{
					{ D3DXVECTOR3(10,0,0),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,0,0),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(10,0,0),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(-10,0,0),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(10,0,0),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },

				}
			},

			{ 60,
				{
					{ D3DXVECTOR3(-10,0,0),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,0,0),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(-10,0,0),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,0,0),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(-10,0,0),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },

				}
			},
		}
	},
	{ false,2,
		{
			{30,
				{
					{ D3DXVECTOR3(0,-450,-600),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,200,200),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,50,50),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,50,50),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,50,50),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
				}
			},
			
			{ 30,
				{
					{ D3DXVECTOR3(0,-300,-300),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,200,200),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,50,50),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,50,50),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,50,50),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
				}
			},
		}

	},
	{ false,1,
		{
			{ 30,
				{
					{ D3DXVECTOR3(0,-300,-300),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,200,200),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,50,50),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,50,50),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
					{ D3DXVECTOR3(0,50,50),D3DXVECTOR3(D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0)) },
				}
			}
		}

	},
	/*{ false,1,3 },
	{ false,1,4 },*/
};
/*----------------*/
/*�t�@�C��*/
FIR g_Fir_Boos[BOOS_PARTS_MAX] =
{
	{ "data/Xfile/centipede_head.x", -1 },
	{ "data/Xfile/centipede_star.x", 0 },
	{ "data/Xfile/centipede_grass.x", 1 },
	{ "data/Xfile/centipede_fire.x", 2 },
	{ "data/Xfile/centipede_water.x", 3 },

};
/*----------------*/

void InitBoos(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nBoos = 0; nBoos<BOOS_PARTS_MAX; nBoos++)
	{
		g_anime = false;
		/*X�t�@�C���̓ǂݍ���*/
		D3DXLoadMeshFromX(
			g_Fir_Boos[nBoos].pFilename,
			D3DXMESH_MANAGED,
			pDevice,
			NULL,
			&g_Boos.modelParts[nBoos].pBuffMat,
			NULL,
			&g_Boos.modelParts[nBoos].nNumMat,
			&g_Boos.modelParts[nBoos].pMesh);

		/*�}�e���A���f�[�^�ւ̃|�C���^���擾*/
		pMatBoos[nBoos] = (D3DXMATERIAL*)g_Boos.modelParts[nBoos].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Boos.modelParts[nBoos].nNumMat; nCntMat++)
		{
			if (pMatBoos[nBoos][nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMatBoos[nBoos][nCntMat].pTextureFilename, &g_Boos.modelParts[nBoos].pTextureModel[nCntMat]);
			}
		}
	}
	/*�����ʒu*/
	g_Boos.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	/*��������*/
	g_Boos.rot = D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f);
	/*�̗͏���������*/
	g_Boos.nLife = 20;
	g_Boos.pattern = BOOS_PATTERN_0;
	g_Boos.state = BOOS_STATE_NORMAL;
}
void UninitBoos(void)
{
	for (int nBoos = 0; nBoos<BOOS_PARTS_MAX; nBoos++)
	{
		/*���b�V���̔j��*/
		if (g_Boos.modelParts[nBoos].pMesh != NULL)
		{						
			g_Boos.modelParts[nBoos].pMesh->Release();
			g_Boos.modelParts[nBoos].pMesh = NULL;
		}

		/*�}�e���A���̔j��*/
		if (g_Boos.modelParts[nBoos].pBuffMat != NULL)
		{						
			g_Boos.modelParts[nBoos].pBuffMat->Release();
			g_Boos.modelParts[nBoos].pBuffMat = NULL;
		}
		/*�e�N�X�`��*/
		for (int nCnt = 0; nCnt < (int)g_Boos.modelParts[nBoos].nNumMat; nCnt++)
		{
			if (g_Boos.modelParts[nBoos].pTextureModel[nCnt] != NULL)
			{						
				g_Boos.modelParts[nBoos].pTextureModel[nCnt]->Release();
				g_Boos.modelParts[nBoos].pTextureModel[nCnt] = NULL;
			}
		}
	}


}
void UpdateBoos(void) 
{
	MAP* pMap = GetMap();
	PLAYER *pPlayer = GetPlayer();
	/*----------------------------------------------------------------------------------*/
	/*�v���C���[����������̊p�x���擾*/
	g_Boos.fRot = atan2f((g_Boos.pos.x - pPlayer->pos.x), (g_Boos.pos.z - pPlayer->pos.z));
	/*�v���C���[������p�x�Ɍ���*/
	g_Boos.rotDest.y = (g_Boos.fRot);
	if (g_Boos.rotDest.y>g_Boos.rot.y + D3DXToRadian(180))
	{/*-180�x����180�x�ɂȂ鏈��*/
		g_Boos.rot.y = D3DXToRadian(180);
		g_Boos.rotDest.y=D3DXToRadian(180);
	}
	else if (g_Boos.rotDest.y<g_Boos.rot.y + D3DXToRadian(-180))
	{/*180�x����-180�x�ɂȂ鏈��*/
		g_Boos.rot.y = D3DXToRadian(-180);
		g_Boos.rotDest.y = D3DXToRadian(-180);
	}

	/*�U���������*/
	g_Boos.rot += (g_Boos.rotDest - g_Boos.rot)* 0.09;	
	/*����*/
	g_Boos.movePos.x += (0.0f - g_Boos.movePos.x)*0.5f;
	g_Boos.movePos.y += (0.0f - g_Boos.movePos.y)*0.5f;
	g_Boos.movePos.z += (0.0f - g_Boos.movePos.z)*0.5f;
	/*�ʒu�X�V*/
	g_Boos.pos += g_Boos.movePos;
	/*�����蔻��*/
	for (int nBoos = 0; nBoos < BOOS_PARTS_MAX; nBoos++)
	{
		/*�s������*/
		if (g_Boos.modelParts[nBoos].pos.x + 250 >= pPlayer->pos.x
			&&g_Boos.modelParts[nBoos].pos.x - 250 <= pPlayer->pos.x
			&&g_Boos.modelParts[nBoos].pos.y + 250 >= pPlayer->pos.y
			&&g_Boos.modelParts[nBoos].pos.y - 250 <= pPlayer->pos.y
			&&g_Boos.modelParts[nBoos].pos.z + 150 >= pPlayer->pos.z
			&&g_Boos.modelParts[nBoos].pos.z - 150 <= pPlayer->pos.z)
		{
			HitModel(1, nBoos,0);
		}
	}
	if (g_Boos.nLife == 15)
	{
		g_Boos.pos = D3DXVECTOR3(0.0f, -50.0f, 0.0f);
	}
	else if(g_Boos.nLife == 10)
	{
		g_Boos.pos = D3DXVECTOR3(0.0f, -150.0f, 0.0f);
	}
	else if (g_Boos.nLife == 5)
	{
		g_Boos.pos = D3DXVECTOR3(0.0f, -250.0f, 0.0f);
	}


	/*-------------------------------------------------------------------------------------*/
	switch (g_Boos.state)
	{
	case BOOS_STATE_NORMAL:
		break;
	case BOOS_STATE_DAMAGE:
		g_Boos.nDamage--;
		
		if (g_Boos.nDamage <= 0)
		{
			/*�ʏ�`��ɖ߂�����*/
			g_Boos.state = BOOS_STATE_NORMAL;
		}
		break;
	case BOOS_STATE_DEATH:
		SetFade(MODE_RESULE);
		break;
	}

	
	switch (g_Boos.pattern)
	{ 
	case BOOS_PATTERN_0:
		g_animeCount++;
		if (g_animeCount == 400)
		{
			SetEnemy(0, D3DXVECTOR3(g_Boos.pos.x+50, g_Boos.pos.y, g_Boos.pos.z));
			g_animeCount = 0;
		}
		if (g_Boos.nLife == 15)
		{
			g_animeCount = 0;
			g_Boos.pattern = BOOS_PATTERN_1;
		}
		break;
	case BOOS_PATTERN_1:
		g_animeCount++;
		if (g_animeCount == 400)
		{
			SetEnemy(1, D3DXVECTOR3(g_Boos.pos.x + 150, g_Boos.pos.y+70, g_Boos.pos.z));
			SetEnemy(1, D3DXVECTOR3(g_Boos.pos.x - 150, g_Boos.pos.y+70, g_Boos.pos.z));
		}
		if (g_animeCount == 600)
		{
			g_animeCount = 0;
			SetAnimation(1);
		}
		if (g_Boos.nLife==10)
		{
			g_animeCount = 0;
			g_Boos.pattern = BOOS_PATTERN_2;
		}
		break;
	case BOOS_PATTERN_2:
		g_animeCount++;
		if (g_animeCount == 400)
		{
			g_animeCount = 0;
			SetAnimation(1);

		}
		if (g_animeCount == 300)
		{

			SetEnemy(2, D3DXVECTOR3(g_Boos.pos.x - 50, g_Boos.pos.y + 170, g_Boos.pos.z));
		}
		if (g_Boos.nLife == 5)
		{
			g_animeCount = 0;
			g_Boos.pattern = BOOS_PATTERN_3;
		}
		break;
	case BOOS_PATTERN_3:
		g_animeCount++;
		if (g_animeCount == 400)
		{
			g_animeCount = 0;
			SetAnimation(1);
		}
		if (g_animeCount == 150)
		{

			SetEnemy(3, D3DXVECTOR3(g_Boos.pos.x + 50, g_Boos.pos.y + 270.0f, g_Boos.pos.z));
			SetEnemy(3, D3DXVECTOR3(g_Boos.pos.x + 50, g_Boos.pos.y + 270.0f, g_Boos.pos.z));
		}
		break;
	}
	/*�A�j���[�V����*/
	UpdateAnimation();//�A�j���[�V�����ɍ��킹�Ĉʒu�E��]�𔽉f����
}
void DrawBoos(void)
{
	/*�f�o�C�X�ւ̃|�C���^*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxParent;
	/*���݂̃}�e���A���ێ��p*/
	D3DMATERIAL9 matDef;
	int nCntMat;
	/*���[���h�}�g���N�X�̏���������*/
	D3DXMatrixIdentity(&g_Boos.mtxWorld);
	/*�����𔽉f*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Boos.rot.y, g_Boos.rot.x, g_Boos.rot.z);
	D3DXMatrixMultiply(&g_Boos.mtxWorld, &g_Boos.mtxWorld, &mtxRot);
	/*�ʒu�𔽉f*/
	D3DXMatrixTranslation(&mtxTrans, g_Boos.pos.x, g_Boos.pos.y, g_Boos.pos.z);
	D3DXMatrixMultiply(&g_Boos.mtxWorld, &g_Boos.mtxWorld, &mtxTrans);
	for (int nBoos = 0; nBoos<BOOS_PARTS_MAX; nBoos++)
	{
		/*�p�[�c���[���h�}�g���N�X�̏���������*/
		D3DXMatrixIdentity(&g_Boos.modelParts[nBoos].mtxWorld);
		/*�p�[�c�����𔽉f*/
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Boos.modelParts[nBoos].rot.y, g_Boos.modelParts[nBoos].rot.x, g_Boos.modelParts[nBoos].rot.z);
		D3DXMatrixMultiply(&g_Boos.modelParts[nBoos].mtxWorld, &g_Boos.modelParts[nBoos].mtxWorld, &mtxRot);
		/*�p�[�c�ʒu�𔽉f*/
		D3DXMatrixTranslation(&mtxTrans, g_Boos.modelParts[nBoos].pos.x, g_Boos.modelParts[nBoos].pos.y, g_Boos.modelParts[nBoos].pos.z);
		D3DXMatrixMultiply(&g_Boos.modelParts[nBoos].mtxWorld, &g_Boos.modelParts[nBoos].mtxWorld, &mtxTrans);
		/*�e���f���̃}�g���b�N�X�̔��f*/
		if (g_Fir_Boos[nBoos].nCntLoop == -1)
		{
			mtxParent = g_Boos.mtxWorld;
		}
		else
		{
			mtxParent = g_Boos.modelParts[g_Fir_Boos[nBoos].nCntLoop].mtxWorld;
		}

		D3DXMatrixMultiply(&g_Boos.modelParts[nBoos].mtxWorld, &g_Boos.modelParts[nBoos].mtxWorld, &mtxParent);
		/*���[���h�}�g���b�N�X�̐ݒ�*/
		pDevice->SetTransform(D3DTS_WORLD, &g_Boos.modelParts[nBoos].mtxWorld);
		/*���݂̃}�e���A�����擾����*/
		pDevice->GetMaterial(&matDef);
		for (nCntMat = 0; nCntMat < (int)g_Boos.modelParts[nBoos].nNumMat; nCntMat++)
		{
			/*�}�e���A���̐ݒ�*/
			pDevice->SetMaterial(&pMatBoos[nBoos][nCntMat].MatD3D);
			pDevice->SetTexture(0, g_Boos.modelParts[nBoos].pTextureModel[nCntMat]);
			/*���f���p�[�c�̕`��*/
			g_Boos.modelParts[nBoos].pMesh->DrawSubset(nCntMat);
		}
		/*�ێ����Ă����}�e���A����߂�*/
		pDevice->SetMaterial(&matDef);
	}
}
void HitBoos(int nDamage,int nMagicType)
{
	if (g_Boos.state == BOOS_STATE_NORMAL)
	{
		if (g_Boos.pattern == nMagicType)
		{
			g_Boos.nLife -= nDamage;
		}
		
		if (g_Boos.nLife <= 0)
		{/*���C�t���O�ɂȂ����Ƃ�*/
			g_Boos.state = BOOS_STATE_DEATH;//���S��ԂɈڍs
		}
		else
		{/*�_���[�W��ԃJ�E���^�[��ԂɈڍs*/
			g_Boos.state = BOOS_STATE_DAMAGE;//�_���[�W��ԂɈڍs
		}
	}
}
void SetAnimation(int playerAnimation)
{
	if (g_boosCurrentAnimation != playerAnimation)
	{
		g_frameCount = 0;
		g_playKeySetlndex = 0;
	}
	g_boosCurrentAnimation = playerAnimation;
	g_motion[g_boosCurrentAnimation].keySet[g_playKeySetlndex];
	
}
void UpdateAnimation()
{
	if (g_frameCount == 0)
	{
		g_anime = true;
		for (int nAnime = 0; nAnime < BOOS_PARTS_MAX; nAnime++)
		{
			g_Boos.modelParts[nAnime].rotAnime =(g_motion[g_boosCurrentAnimation].keySet[g_playKeySetlndex].key[nAnime].rot-g_Boos.modelParts[nAnime].rot) / g_motion[g_boosCurrentAnimation].keySet[g_playKeySetlndex].frame;
			g_Boos.modelParts[nAnime].posAnime = (g_motion[g_boosCurrentAnimation].keySet[g_playKeySetlndex].key[nAnime].pos - g_Boos.modelParts[nAnime].pos) / g_motion[g_boosCurrentAnimation].keySet[g_playKeySetlndex].frame;
		}
	}
	g_frameCount++;
	if (g_motion[g_boosCurrentAnimation].keySet[g_playKeySetlndex].frame == g_frameCount)
	{
		g_anime = false;
		g_frameCount = 0;
		g_playKeySetlndex++;
		if (g_playKeySetlndex ==g_motion[g_boosCurrentAnimation].keyNum&&g_motion[g_boosCurrentAnimation].isLoop)
		{
			g_playKeySetlndex = 0;
		}
		else
		{
			SetAnimation(0);
			g_frameCount = 0;
		}
	}
	for (int nAnime = 0; nAnime < BOOS_PARTS_MAX; nAnime++)
	{
		g_Boos.modelParts[nAnime].rot += g_Boos.modelParts[nAnime].rotAnime;
		g_Boos.modelParts[nAnime].pos += g_Boos.modelParts[nAnime].posAnime;
	}
	
}
BOOS*GetBoos()
{
	return &g_Boos;
}