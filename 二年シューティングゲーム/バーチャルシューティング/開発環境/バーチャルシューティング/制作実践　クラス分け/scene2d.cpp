#include"scene2d.h"

#include"manager.h"
#include"input.h"
#include"inihkeyboard.h"
#include"renderer.h"
CScene2d::CScene2d(int nPriorit):CScene(nPriorit)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}
CScene2d::~CScene2d()
{

}
HRESULT CScene2d::Init(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&m_pVtxBuff,//�ϐ������ς��ƕύX���K�v
		NULL);
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	////�����v�Z
	g_fLengthpos = sqrtf(pow(m_sizePolygon.x / 2, 2.0f) + pow(m_sizePolygon.y / 2, 2.0f));
	g_Angle = atan2(m_sizePolygon.x / 2, m_sizePolygon.y / 2);


	// �e�N�X�`���̐���
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);


	// ���_�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(-m_sizePolygon.x / 2 + m_posPolygon.x, -m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_sizePolygon.x / 2 + m_posPolygon.x, -m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_sizePolygon.x / 2 + m_posPolygon.x, m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_sizePolygon.x / 2 + m_posPolygon.x, m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);


	// ���_����ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();


	return S_OK;
}


void CScene2d::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

void CScene2d::Set(D3DXVECTOR3 Pos)
{
	m_posPolygon = Pos;
}

void CScene2d::TextureAnim(D3DXVECTOR2 *Texture)//size�͂P/�e�N�X�`���̕�����
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�f�[�^�����b�N

	pVtx[0].tex = Texture[0];
	pVtx[1].tex = Texture[1];
	pVtx[2].tex = Texture[2];
	pVtx[3].tex = Texture[3];
	
	m_pVtxBuff->Unlock();						//���_�f�[�^���A�����b�N����
}

//�|���S����]����
void CScene2d::SetRotate(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	float fAngleX = g_fLengthpos*cos(g_Angle);
	float fAngleY = g_fLengthpos*sin(g_Angle);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// ���_�o�b�t�@�̈ړ�
	pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x + fAngleX, m_posPolygon.y + fAngleY, 0.0f);
	fAngleX = g_fLengthpos*cos(g_Angle + D3DXToRadian(90));
	fAngleY = g_fLengthpos*sin(g_Angle + D3DXToRadian(90));
	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x + fAngleX, m_posPolygon.y + fAngleY, 0.0f);
	fAngleX = g_fLengthpos*cos(g_Angle + D3DXToRadian(-90));
	fAngleY = g_fLengthpos*sin(g_Angle + D3DXToRadian(-90));

	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x + fAngleX, m_posPolygon.y + fAngleY, 0.0f);
	fAngleX = g_fLengthpos*cos(g_Angle + D3DXToRadian(180));
	fAngleY = g_fLengthpos*sin(g_Angle + D3DXToRadian(180));

	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x + fAngleX, m_posPolygon.y + fAngleY, 0.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
	g_Angle += 0.1f;

}




void CScene2d::ColChange(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�f�[�^�����b�N

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();						//���_�f�[�^���A�����b�N����

}

void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//�e�N�X�`���̊��蓖��
	m_pTexture = pTexture;
}

CScene2d *CScene2d::Create(D3DXVECTOR3 Pos)
{
	CScene2d *pScene2d;
	pScene2d = new CScene2d;
	pScene2d->Set(Pos);
	pScene2d->Init();
	
	return pScene2d;
}


void CScene2d::Update(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^�[
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// ���_�o�b�t�@�̈ړ�
	pVtx[0].pos = D3DXVECTOR3(-m_sizePolygon.x / 2 + m_posPolygon.x, -m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_sizePolygon.x / 2 + m_posPolygon.x, -m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_sizePolygon.x / 2 + m_posPolygon.x, m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_sizePolygon.x / 2 + m_posPolygon.x, m_sizePolygon.y / 2 + m_posPolygon.y, 0.0f);


	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CScene2d::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

