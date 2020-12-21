#include"main.h"
#include"fade.h"

#define FADE_RATE (0.01f)
/*�O���[�o���ϐ�*/
LPDIRECT3DTEXTURE9 g_apTextureFade= NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade= NULL;		//���_�o�b�t�@�ւ̃|�C���^

MODE g_modeNext = MODE_TITLE;	//���̉�ʁi���[�h�j
FADE g_fade;										//�t�F�[�h���
D3DXCOLOR g_colorFade;								//�t�F�[�h�F

/*����������*/
void InitFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//������ʁi�����j

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,		//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,											//(�Œ�)
		FVF_VERTEX_2D,												//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,											//�i�Œ�j
		&g_pVtxBuffFade,												//�ϐ������ς��ƕύX���K�v
		NULL);
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾

	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


	//rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;


	g_pVtxBuffFade->Unlock();

}
void UninitFade(void)
{
	////�e�N�X�`���̐ݒ�
	//if (g_apTextureFade != NULL)
	//{
	//	g_apTextureFade->Release();
	//	g_apTextureFade = NULL;
	//}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
void UpdaFade(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾

	
		if (g_fade != FADE_NONE)
		{//�t�F�[�h������
			if (g_fade == FADE_IN)
			{//�t�F�[�h�C������
				g_colorFade.a -= FADE_RATE;			//a�l�����Z���Č��̉�ʂ𕂂��オ�点��
				if (g_colorFade.a <= 0.0f)
				{
					/*�t�F�[�h�����I��*/
					g_colorFade.a = 0.0f;
					g_fade = FADE_NONE;
				}
			}
			else if (g_fade == FADE_OUT)
			{//�t�F�[�h�A�E�g����
				g_colorFade.a += FADE_RATE;			//a�l�����Z���Č��̉�ʂ������Ă���
				if (g_colorFade.a >= 1.0f)
				{
					/*�t�F�[�h�C�������ɐ؂�ւ�*/
					g_colorFade.a = 1.0f;
					g_fade = FADE_IN;

					/*���[�h��ݒ�*/
					SetMode(g_modeNext);

				}
			}
		}
		
	
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;
	
	pVtx += 4;
	g_pVtxBuffFade->Unlock();
}

void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureFade);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

/*�t�F�[�h�̏�Ԑݒ�*/
void SetFade(MODE modeNext)
{
	
	g_fade = FADE_OUT;
	g_modeNext = modeNext;


}

FADE GetFade(void)
{
	return g_fade;
}