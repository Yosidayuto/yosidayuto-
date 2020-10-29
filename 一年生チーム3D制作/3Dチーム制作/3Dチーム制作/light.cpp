#include"main.h"
#include"light.h"
/*�O���[�o���ϐ�*/
D3DLIGHT9 g_light;//���C�g���

void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;//���C�g�̕����x�N�g��
	/*���C�g���N���A����*/
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));
	/*���C�g�̎�ނ�ݒ�*/
	g_light.Type = D3DLIGHT_DIRECTIONAL;

	/*���C�g�̊g�U����ݒ�*/
	g_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	/*���C�g�̕�����ݒ�*/
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);//���K������i�傫��1�̃x�N�g���ɂ���K�v������j
	g_light.Direction = vecDir;
	
	/*���C�g��ݒ肷��*/
	pDevice->SetLight(0, &g_light);
	/*���C�g��L���ɂ���*/
	pDevice->LightEnable(0, TRUE);
	
	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;
	pDevice->SetMaterial(&material);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);
}
void UninitLight(void)
{

}

void UpdateLight(void)
{

}