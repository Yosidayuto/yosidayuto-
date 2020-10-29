#include "main.h"
#include "meshfield2.h"

#define MAX_SIZE 50
#define MAX_MESHFIELD2 2
//�O���[�o���ϐ�
/*���b�V���t�B�[���h�̃e�N�X�`��*/
LPDIRECT3DTEXTURE9 g_pTextureMeshField2 = NULL;
/*���_�o�b�t�@�ւ̃|�C���^*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField2 = NULL;
/*�C���f�b�N�X�o�b�t�@�ւ̃|�C���g*/
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField2 = NULL;
/*�|���S���̈ʒu*/
D3DXVECTOR3 g_posMeshField2;
/*�|���S���̌���*/
D3DXVECTOR3 g_rotMeshField2;
/*�|���S���̃��[���h�}�g���b�N�X*/
D3DXMATRIX g_mtxWorldMeshField2;

MESHFIELD2 g_meshfield2[MAX_MESHFIELD2];
int index, texpos = 0;
int g_nAlpha[99];

void InitMeshField2(void)
{

	//g_posMeshField2 = D3DXVECTOR3(0,30, 0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntMeshField2 = 0; nCntMeshField2 < MAX_MESHFIELD2; nCntMeshField2++)
	{
		//g_meshfield2[nCntMeshField2].pos= D3DXVECTOR3(0, 0, 0);
		g_meshfield2[nCntMeshField2].rot = D3DXVECTOR3(0, 0, 0);
		g_meshfield2[nCntMeshField2].bUse = false;
	}
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIEL2_VERTEX_NUM*MAX_MESHFIELD2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField2,
		NULL);
	VERTEX_3D*pVtx = NULL;
	/*���_�o�b�t�@�̐����i���O�p�`�͈ӎ����Ȃ��j*/
	/*���_�o�b�t�@�����b�N*/
	g_pVtxBuffMeshField2->Lock(0, 0, (void**)&pVtx, 0);
	/*���_���W�̐ݒ�*/
	for (int nCntMeshField2 = 0; nCntMeshField2 < MAX_MESHFIELD2; nCntMeshField2++)
	{
		for (int vIndex = 0; vIndex < MESHFIEL2_Y_BLOCK + 1; vIndex++)
		{
			texpos = 0;
			for (int hlndex = 0; hlndex < MESHFIE2L_X_BLOCK + 1; hlndex++)
			{

				/*���W*/
				float angle = hlndex * 45;
				pVtx[index].pos = D3DXVECTOR3(sinf(D3DXToRadian(-angle))*(MAX_SIZE / 2) + g_posMeshField2.x,
					-vIndex*(MAX_SIZE / 10) + g_posMeshField2.y,
					cosf(D3DXToRadian(-angle))*(MAX_SIZE / 2) + g_posMeshField2.z);
				/*�e���_�̖@���̐ݒ�i�x�N�g���̑傫���͂P�ɂ���K�v������j*/
				pVtx[index].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				D3DXVECTOR3 g_rotMeshField2;
				D3DXVec3Normalize(&g_rotMeshField2, &g_rotMeshField2);
				//���_�J���[�̓����x

				if (index >= 0 && index <= 8)//��i��
				{
					g_nAlpha[index] = 255;
				}
				else if (index >= 9 && index <= 17)//��i��
				{
					g_nAlpha[index] = 232;
				}
				else if (index >= 18 && index <= 26)//�O�i��
				{
					g_nAlpha[index] = 209;
				}
				else if (index >= 27 && index <= 35)//�l�i��
				{
					g_nAlpha[index] = 186;
				}
				else if (index >= 36 && index <= 44)//�ܒi��
				{
					g_nAlpha[index] = 163;
				}
				else if (index >= 45 && index <= 53)//�Z�i��
				{
					g_nAlpha[index] = 140;
				}
				else if (index >= 54 && index <= 62)//���i��
				{
					g_nAlpha[index] = 117;
				}
				else if (index >= 63 && index <= 71)//���i��
				{
					g_nAlpha[index] = 94;
				}
				else if (index >= 72 && index <= 80)//��i��
				{
					g_nAlpha[index] = 71;
				}
				else if (index >= 81 && index <= 89)//�\�i��
				{
					g_nAlpha[index] = 48;
				}
				else if (index >= 90 && index <= 98)
				{
					g_nAlpha[index] = 25;
				}



				/*���_�J���[�̐ݒ�*/
				pVtx[index].col = D3DCOLOR_RGBA(0, 0, 255, g_nAlpha[index]);
				/*�e�N�X�`��*/
				pVtx[index].tex = D3DXVECTOR2(texpos*0.125, vIndex);
				index += 1;
				texpos += 1;
			}


		}

	}



	/*���_�o�b�t�@�̃A�����b�N*/
	g_pVtxBuffMeshField2->Unlock();
	/*�e�N�X�`���̐ݒ�*/
	D3DXCreateTextureFromFile(pDevice, "�摜/NRR2016150966_1[].jpg", &g_pTextureMeshField2);
	/*�C���f�b�N�X�o�b�t�@�i�|���S���o�b�t�@�j�̐���*/
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIEL2_INDEX_NUM*MAX_MESHFIELD2,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField2,
		NULL);
	/*�C���f�b�N�X�o�b�t�@�����b�N*/
	WORD*pldx;
	g_pIdxBuffMeshField2->Lock(0, 0, (void**)&pldx, 0);
	for (int nCntMeshField2 = 0; nCntMeshField2 < MAX_MESHFIELD2; nCntMeshField2++)
	{
		pldx[0] = 9;//��i��
		pldx[1] = 0;
		pldx[2] = 10;
		//---------------------------
		pldx[3] = 1;
		pldx[4] = 11;
		pldx[5] = 2;
		//---------------------------
		pldx[6] = 12;
		pldx[7] = 3;
		pldx[8] = 13;
		//---------------------------
		pldx[9] = 4;
		pldx[10] = 14;
		pldx[11] = 5;
		//---------------------------
		pldx[12] = 15;
		pldx[13] = 6;
		pldx[14] = 16;
		//---------------------------
		pldx[15] = 7;
		pldx[16] = 17;
		pldx[17] = 8;//��i��

					 //----------------------------
		pldx[18] = 8;//�i������
		pldx[19] = 18;

		//----------------------------
		pldx[20] = 18;//��i��
		pldx[21] = 9;
		pldx[22] = 19;
		//---------------------------
		pldx[23] = 10;
		pldx[24] = 20;
		pldx[25] = 11;
		//---------------------------
		pldx[26] = 21;
		pldx[27] = 12;
		pldx[28] = 22;
		//---------------------------
		pldx[29] = 13;
		pldx[30] = 23;
		pldx[31] = 14;
		//---------------------------
		pldx[32] = 24;
		pldx[33] = 15;
		pldx[34] = 25;
		//---------------------------
		pldx[35] = 16;
		pldx[36] = 26;
		pldx[37] = 17;//��i��

					  //---------------------------
		pldx[38] = 17;//�i������
		pldx[39] = 27;

		//----------------------------
		pldx[40] = 27;//�O�i��
		pldx[41] = 18;
		pldx[42] = 28;
		//---------------------------
		pldx[43] = 19;
		pldx[44] = 29;
		pldx[45] = 20;
		//---------------------------
		pldx[46] = 30;
		pldx[47] = 21;
		pldx[48] = 31;
		//---------------------------
		pldx[49] = 22;
		pldx[50] = 32;
		pldx[51] = 23;
		//---------------------------
		pldx[52] = 33;
		pldx[53] = 24;
		pldx[54] = 34;
		//---------------------------
		pldx[55] = 25;//�O�i��
		pldx[56] = 35;
		pldx[57] = 26;

		//----------------------------
		pldx[58] = 26;//�i������
		pldx[59] = 36;

		//----------------------------
		pldx[60] = 36;//�l�i��
		pldx[61] = 27;
		pldx[62] = 37;
		//---------------------------
		pldx[63] = 28;
		pldx[64] = 38;
		pldx[65] = 29;
		//---------------------------
		pldx[66] = 39;
		pldx[67] = 30;
		pldx[68] = 40;
		//---------------------------
		pldx[69] = 31;
		pldx[70] = 41;
		pldx[71] = 32;
		//---------------------------
		pldx[72] = 42;
		pldx[73] = 33;
		pldx[74] = 43;
		//---------------------------
		pldx[75] = 34;
		pldx[76] = 44;
		pldx[77] = 35;//�l�i��

					  //----------------------------
		pldx[78] = 35;//�i������
		pldx[79] = 45;

		//----------------------------
		pldx[80] = 45;//�ܒi��
		pldx[81] = 36;
		pldx[82] = 46;
		//---------------------------
		pldx[83] = 37;
		pldx[84] = 47;
		pldx[85] = 38;
		//---------------------------
		pldx[86] = 48;
		pldx[87] = 39;
		pldx[88] = 49;
		//---------------------------
		pldx[89] = 40;
		pldx[90] = 50;
		pldx[91] = 41;
		//---------------------------
		pldx[92] = 51;
		pldx[93] = 42;
		pldx[94] = 52;
		//---------------------------
		pldx[95] = 43;
		pldx[96] = 53;
		pldx[97] = 44;//�ܒi��

					  //----------------------------
		pldx[98] = 44;//�i������
		pldx[99] = 54;

		//----------------------------
		pldx[100] = 54;//�Z�i��
		pldx[101] = 45;
		pldx[102] = 55;
		//---------------------------
		pldx[103] = 46;
		pldx[104] = 56;
		pldx[105] = 47;
		//---------------------------
		pldx[106] = 57;
		pldx[107] = 48;
		pldx[108] = 58;
		//---------------------------
		pldx[109] = 49;
		pldx[110] = 59;
		pldx[111] = 50;
		//---------------------------
		pldx[112] = 60;
		pldx[113] = 51;
		pldx[114] = 61;
		//---------------------------
		pldx[115] = 52;
		pldx[116] = 62;
		pldx[117] = 53;//�Z�i��

					   //----------------------------
		pldx[118] = 53;//�i������
		pldx[119] = 63;

		//----------------------------
		pldx[120] = 63;//���i��
		pldx[121] = 54;
		pldx[122] = 64;
		//---------------------------
		pldx[123] = 55;
		pldx[124] = 65;
		pldx[125] = 56;
		//---------------------------
		pldx[126] = 66;
		pldx[127] = 57;
		pldx[128] = 67;
		//---------------------------
		pldx[129] = 58;
		pldx[130] = 68;
		pldx[131] = 59;
		//---------------------------
		pldx[132] = 69;
		pldx[133] = 60;
		pldx[134] = 70;
		//---------------------------
		pldx[135] = 61;
		pldx[136] = 71;
		pldx[137] = 62;//���i��

					   //----------------------------
		pldx[138] = 62;//�i������
		pldx[139] = 72;

		//----------------------------
		pldx[140] = 72;//���i��
		pldx[141] = 63;
		pldx[142] = 73;
		//---------------------------
		pldx[143] = 64;
		pldx[144] = 74;
		pldx[145] = 65;
		//---------------------------
		pldx[146] = 75;
		pldx[147] = 66;
		pldx[148] = 76;
		//---------------------------
		pldx[149] = 67;
		pldx[150] = 77;
		pldx[151] = 68;
		//---------------------------
		pldx[152] = 78;
		pldx[153] = 69;
		pldx[154] = 79;
		//---------------------------
		pldx[155] = 70;
		pldx[156] = 80;
		pldx[157] = 71;//���i��

					   //----------------------------
		pldx[158] = 71;//�i������
		pldx[159] = 81;

		//----------------------------
		pldx[160] = 81;//��i��
		pldx[161] = 72;
		pldx[162] = 82;
		//---------------------------
		pldx[163] = 73;
		pldx[164] = 83;
		pldx[165] = 74;
		//---------------------------
		pldx[166] = 84;
		pldx[167] = 75;
		pldx[168] = 85;
		//---------------------------
		pldx[169] = 76;
		pldx[170] = 86;
		pldx[171] = 77;
		//---------------------------
		pldx[172] = 87;
		pldx[173] = 78;
		pldx[174] = 88;
		//---------------------------
		pldx[175] = 79;
		pldx[176] = 89;
		pldx[177] = 80;//��i��

					   //----------------------------
		pldx[178] = 80;//�i������
		pldx[179] = 90;

		//----------------------------
		pldx[180] = 90;//�\�i��
		pldx[181] = 81;
		pldx[182] = 91;
		//---------------------------
		pldx[183] = 82;
		pldx[184] = 92;
		pldx[185] = 83;
		//---------------------------
		pldx[186] = 93;
		pldx[187] = 84;
		pldx[188] = 94;
		//---------------------------
		pldx[189] = 85;
		pldx[190] = 95;
		pldx[191] = 86;
		//---------------------------
		pldx[192] = 96;
		pldx[193] = 87;
		pldx[194] = 97;
		//---------------------------
		pldx[195] = 88;
		pldx[196] = 98;
		pldx[197] = 89;//�\�i��
					   //----------------------------
	}
	//int ncunt=9;
	//for(int npldx=0;npldx<197; npldx++)
	//{
	//
	//		/*�C���f�b�N�X�w��*/
	//		pldx[npldx] = ncunt;
	//		if (ncunt/ncunt==0)
	//		{
	//			ncunt -=9;
	//		}
	//		else if(ncunt/ncunt==1)
	//		{
	//			ncunt += 10;
	//		}
	//	
	//}

	g_pIdxBuffMeshField2->Unlock();
}
void UninitMeshField2(void)
{
	/*���_�o�b�t�@�̉��*/
	if (g_pVtxBuffMeshField2 != NULL)
	{
		g_pVtxBuffMeshField2->Release();
		g_pVtxBuffMeshField2 = NULL;
	}
	if (g_pTextureMeshField2 != NULL)
	{
		g_pTextureMeshField2->Release();
		g_pTextureMeshField2 = NULL;
	}
	if (g_pIdxBuffMeshField2 != NULL)
	{
		g_pIdxBuffMeshField2->Release();
		g_pIdxBuffMeshField2 = NULL;
	}
}
void UpdateMeshField2(void)
{
	VERTEX_3D*pVtx = NULL;
	for (int nCntMeshField2 = 0; nCntMeshField2 < MAX_MESHFIELD2; nCntMeshField2++)
	{
		if (g_meshfield2[nCntMeshField2].bUse == true)
		{

			for (int n = 0; n < 99; n++)
			{
				g_nAlpha[n]++;
				if (g_nAlpha[n] == 255)
				{
					g_nAlpha[n] = 0;
				}
				/*���_�o�b�t�@�����b�N*/
				g_pVtxBuffMeshField2->Lock(0, 0, (void**)&pVtx, 0);
				/*���_�J���[�̐ݒ�*/
				pVtx[n].col = D3DCOLOR_RGBA(0, 0, 255, g_nAlpha[n]);
				g_pIdxBuffMeshField2->Unlock();

			}
		}
	}
}

void SetMeshField2(D3DXVECTOR3 pos)
{
	for (int nCntMeshField2 = 0; nCntMeshField2 < MAX_MESHFIELD2; nCntMeshField2++)
	{
		if (g_meshfield2[nCntMeshField2].bUse == false)
		{
			g_meshfield2[nCntMeshField2].bUse = true;
			g_meshfield2[nCntMeshField2].pos = pos;

			break;
		}
	}
}
void DrawMeshField2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntMeshField2 = 0; nCntMeshField2 < MAX_MESHFIELD2; nCntMeshField2++)
	{
		if (g_meshfield2[nCntMeshField2].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;
			/*���[���h�}�g���N�X�̏���������*/
			D3DXMatrixIdentity(&g_meshfield2[nCntMeshField2].mtxWorld);
			/*�����𔽉f*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshfield2[nCntMeshField2].rot.y, g_meshfield2[nCntMeshField2].rot.x, g_meshfield2[nCntMeshField2].rot.z);
			D3DXMatrixMultiply(&g_meshfield2[nCntMeshField2].mtxWorld, &g_meshfield2[nCntMeshField2].mtxWorld, &mtxRot);
			/*�ʒu�𔽉f*/
			D3DXMatrixTranslation(&mtxTrans, g_meshfield2[nCntMeshField2].pos.x, g_meshfield2[nCntMeshField2].pos.y, g_meshfield2[nCntMeshField2].pos.z);
			D3DXMatrixMultiply(&g_meshfield2[nCntMeshField2].mtxWorld, &g_meshfield2[nCntMeshField2].mtxWorld, &mtxTrans);
			/*���[���h�}�g���N�X�̐ݒ�*/
			pDevice->SetTransform(D3DTS_WORLD, &g_meshfield2[nCntMeshField2].mtxWorld);
			/*�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�*/
			pDevice->SetIndices(g_pIdxBuffMeshField2);
			/*���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�*/
			pDevice->SetStreamSource(0, g_pVtxBuffMeshField2, 0, sizeof(VERTEX_3D));
			/*���_�t�H�[�}�b�g�̐ݒ�*/
			pDevice->SetFVF(FVF_VERTEX_3D);
			/*�e�N�X�`���̕`��*/
			pDevice->SetTexture(0, g_pTextureMeshField2);
			/*�|���S���`��*/
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIEL2_VERTEX_NUM, 0, MESHFIEL2_PRIMITIVE_NUM);


			pDevice->SetTexture(0, NULL);
		}
	}
}
