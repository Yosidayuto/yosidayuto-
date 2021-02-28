#include"scene2d.h"
#include"manager.h"
#include"input.h"
#include"renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2d::CScene2d(int nPriorit):CScene(nPriorit)
{
	m_Texture	= NULL;					// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff	= NULL;					// ���_�o�b�t�@�ւ̃|�C���^
	m_pos		= D3DXVECTOR3(0, 0, 0); // �|���S���̈ʒu
	m_fRot		= 0.0f;					// �|���S���̌���
	m_col		= D3DCOLOR_RGBA(255, 255, 255, 255);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2d::~CScene2d()
{

}

//=============================================================================
// ��������
//=============================================================================
CScene2d *CScene2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float frot, LPDIRECT3DTEXTURE9 pTexture, int nPriority)
{
	CScene2d *pScene2d=NULL;
	pScene2d = new CScene2d(nPriority);
	
	//NULL�`�F�b�N
	if (pScene2d != NULL)
	{
		//�ʒu�ݒ�
		pScene2d->SetPos(pos);
		//�傫���ݒ�
		pScene2d->SetSize(size);
		//�����ݒ�
		pScene2d->SetRot(frot);
		//�e�N�X�`���̐ݒ�
		pScene2d->BindTexture(pTexture);
		//����������
		pScene2d->Init();

		return pScene2d;
	}
	return NULL;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2d::Init(void)
{
	//���_���ւ̃|�C���^�[
	VERTEX_2D *pVtx;
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,			//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				//(�Œ�)
		FVF_VERTEX_2D,					//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				//�i�Œ�j
		&m_pVtxBuff,					//�ϐ������ς��ƕύX���K�v
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_����ݒ�
	pVtx[0].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)m_size.y / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)m_size.y / 2, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//rhw�̐ݒ�i�l�͂P�C�O�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	
	// ���_����ݒ�
	pVtx[0].col = m_col;    //a�͓����x
	pVtx[1].col = m_col;    //a�͓����x
	pVtx[2].col = m_col;    //a�͓����x
	pVtx[3].col = m_col;    //a�͓����x

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
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

//=============================================================================
// �X�V����
//=============================================================================
void CScene2d::Update(void)
{
	D3DXMATRIX posMatrix;       // ���_�s��
	D3DXMATRIX rotateMatrix;    // ��]�s��
	VERTEX_2D* pVtx;

	//�s��̏������i�P�ʍs�񐶐��j
	D3DXMatrixIdentity(&posMatrix);
	D3DXMatrixIdentity(&rotateMatrix);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�X�V
	pVtx[0].pos = D3DXVECTOR3((float)-m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3((float)-m_size.x / 2, (float)m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)m_size.x / 2, (float)m_size.y / 2, 0.0f);

	//���_�J���[�X�V
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	m_pVtxBuff->Unlock();

	//��]�s�񐶐�
	D3DXMatrixRotationZ(&rotateMatrix, D3DXToRadian(m_fRot));

	for (int nCount = 0; nCount < 4; nCount++)
	{
		//���_���W���s��ɕϊ�
		D3DXMatrixTranslation(&posMatrix, pVtx[nCount].pos.x, pVtx[nCount].pos.y, pVtx[nCount].pos.z);
		//��]�s����s��ɂ�����
		posMatrix *= rotateMatrix;
		//��]��̍��W�𒸓_���W�ɓ����
		pVtx[nCount].pos.x = posMatrix._41;
		pVtx[nCount].pos.y = posMatrix._42;
		pVtx[nCount].pos.z = posMatrix._43;
		//m_pos���ړ�������
		pVtx[nCount].pos += m_pos;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene2d::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �ʒu�Z�b�^�[�֐�
//=============================================================================
void CScene2d::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �����Z�b�^�[�֐�
//=============================================================================
void CScene2d::SetRot(float frot)
{
	m_fRot = frot;
}

//=============================================================================
// �T�C�Y�Z�b�^�[�֐�
//=============================================================================
void CScene2d::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �J���[�Z�b�^�[�֐�
//=============================================================================
void CScene2d::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// �ʒu�Q�b�^�[�֐�
//=============================================================================
D3DXVECTOR3 CScene2d::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �T�C�Y�Q�b�^�[�֐�
//=============================================================================
D3DXVECTOR3 CScene2d::GetSize(void)
{
	return m_size;
}

//=============================================================================
// �����Q�b�^�[�֐�
//=============================================================================
float CScene2d::GetRot(void)
{
	return m_fRot;
}

//=============================================================================
// �J���[�Q�b�^�[�֐�
//=============================================================================
D3DXCOLOR CScene2d::GetCol(void)
{
	return m_col;
}

//=============================================================================
//�e�N�X�`���̃Z�b�g�֐�
//=============================================================================
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//�e�N�X�`���̊��蓖��
	m_Texture = pTexture;
}

//=============================================================================
// �e�N�X�`���A�j���[�V�����֐�
//=============================================================================
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
