//����H
//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "window.h"		
#include "manager.h"	
#include "renderer.h"	
#include "inputmouse.h"	
#include "button.h"		
#include "score.h"		
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
LPDIRECT3DTEXTURE9	CWindow::m_Texture[WINDOW_TYPE_MAX] = {};
char *				CWindow::m_pcTexture[WINDOW_TYPE_MAX] =
{
	"data/TEXTURE/Window_Description.png",
};
bool CWindow::m_Window[WINDOW_TYPE_MAX] = 
{
	false
};

//----------------------------------
//�R���X�g���N�^
//----------------------------------
CWindow::CWindow(int nPriorit)
{
	m_pos = D3DXVECTOR3(0,0,0);
}

//----------------------------------
//�f�X�g���N�^
//----------------------------------
CWindow::~CWindow()
{
}

//----------------------------------
//��������
//----------------------------------
CWindow * CWindow::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 size, WINDOW_TYPE Type)
{
	if (m_Window[Type] == false)
	{
		CWindow *pWindow;
		pWindow = new CWindow;
		pWindow->m_pos = Pos;
		pWindow->m_size = size;
		//�ʒu
		pWindow->SetPos(pWindow->m_pos);
		//�T�C�Y
		pWindow->SetSize(pWindow->m_size);
		pWindow->BindTexture(m_Texture[Type]);
		pWindow->Init();
		m_Window[Type] = true;
		return pWindow;

	}
	return NULL;
}

//----------------------------------
//�e�N�X�`���ǂݍ��ݏ���
//----------------------------------
HRESULT CWindow::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < WINDOW_TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, m_pcTexture[nCount], &m_Texture[nCount]);
	}
	return S_OK;
}

//----------------------------------
//�e�N�X�`���j������
//----------------------------------
void CWindow::Unload(void)
{
	for (int nCount = 0; nCount < WINDOW_TYPE_MAX; nCount++)
	{
		if (m_Texture[nCount] != NULL)
		{
			m_Texture[nCount]->Release();
			m_Texture[nCount] = NULL;
		}


	}
}

//----------------------------------
//����������
//----------------------------------
HRESULT CWindow::Init(void)
{
	//����������
	CScene2d::Init();

	return S_OK;
}

//----------------------------------
//�I������
//----------------------------------
void CWindow::Uninit(void)
{

	CScene2d::Uninit();
}

//----------------------------------
//�X�V����
//----------------------------------
void CWindow::Update(void)
{
	CInihMouse *pMouse = CManager::GetMouse();			//�}�E�X�擾

	if (pMouse->GetClickTrigger(1) == true)
	{
		Uninit();
	}
}

//----------------------------------
//�`�揈��
//----------------------------------
void CWindow::Draw(void)
{
	CScene2d::Draw();
}

bool CWindow::Window(void)
{
	return m_Window[0];
}

