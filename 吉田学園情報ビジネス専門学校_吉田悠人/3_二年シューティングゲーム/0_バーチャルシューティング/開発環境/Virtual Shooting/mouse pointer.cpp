//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SIZE (100)


#include "mouse pointer.h"
#include "inputmouse.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPointer::m_pTexture[POINTER_TYPE_MAX] = {};
char *CPointer::pTexture[POINTER_TYPE_MAX]=
{
	"data/TEXTURE/MousePointer_Select.png",
	"data/TEXTURE/MousePointer_Game.png"
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPointer::CPointer(int nPriorit) :CScene2d(nPriorit)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPointer::~CPointer()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CPointer::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// �e�N�X�`���̐���
	for (int nCount = 0; nCount < POINTER_TYPE_MAX; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, pTexture[nCount], &m_pTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CPointer::Unload(void)
{
	for (int nCount = 0; nCount < POINTER_TYPE_MAX; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �쐬����
//=============================================================================
CPointer * CPointer::Create(POINTER_TYPE Type)
{
	CPointer *pPointer;
	//�C���X�^���X����
	pPointer = new CPointer;

	//����������
	if (pPointer != NULL)
	{
		pPointer->Init(Type);
	}
	pPointer->SetPos(D3DXVECTOR3(0.0f,0.0f,0.0f));
	return pPointer;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPointer::Init(POINTER_TYPE Type)
{
	//�e�N�X�`���ݒ�
	BindTexture(m_pTexture[Type]);
	//�T�C�Y
	SetSize(D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f));

	//����������
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPointer::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPointer::Update(void)
{
	//�}�E�X�擾
	CInihMouse *pMouse = CManager::GetMouse();
	

	D3DXVECTOR3 MousePos = D3DXVECTOR3((float)pMouse->GetMousePos().x, (float)pMouse->GetMousePos().y, 0.0f);
	SetPos(MousePos);
	CScene2d::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPointer::Draw(void)
{
	CScene2d::Draw();
}
