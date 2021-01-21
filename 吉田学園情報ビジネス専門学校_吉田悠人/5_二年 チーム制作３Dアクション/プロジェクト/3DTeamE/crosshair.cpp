//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	crosshair.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "crosshair.h"

#include "camera.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CCrosshair::m_pTexture = NULL;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCrosshair::CCrosshair()
{
    m_fspread    = 0;
    m_fminspread = 0;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCrosshair::~CCrosshair()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CCrosshair::Init(void)
{
    //2D�|���S���̐���
    for(int nCount = 0; nCount < 4; nCount++)
    {
        if(m_apObject2d[nCount] != NULL)
        {
            m_apObject2d[nCount] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), CROSSHAIR_PART_SIZE, 2);
            m_apObject2d[nCount]->SetRot(nCount * 90.0f);
            m_apObject2d[nCount]->SetCol(D3DCOLOR_RGBA(0, 255, 0, 255));
            m_apObject2d[nCount]->BindTexture(m_pTexture);
        }
    }
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::Uninit(void)
{
    //�|���S���̏I��
    for(int nCount = 0; nCount < 4; nCount++)
    {
        if(m_apObject2d[nCount] != NULL)
        {
            m_apObject2d[nCount]->Uninit();
        }
    }
    Release();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::Update(void)
{
    D3DXVECTOR3 pos;
    if(m_fspread > 0)
    {
        m_fspread -= 2;
        if(m_fspread < 0)
        {
            m_fspread = 0;
        }
    }
    if(m_fspread > MAX_SPREAD)
    {
        m_fspread = MAX_SPREAD;
    }
    for(int nCount = 0; nCount < 4; nCount++)
    {
        //��ʂ̒��S����L���蕪�O���Ƀ|���S���̈ʒu���ړ�
        if(m_apObject2d[nCount] != NULL)
        {
            switch(nCount)
            {
                case 0:
                    pos = D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - (m_fminspread + m_fspread), 0);
                    break;
                case 1:
                    pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (m_fminspread + m_fspread), SCREEN_HEIGHT / 2, 0);
                    break;
                case 2:
                    pos = D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + (m_fminspread + m_fspread), 0);
                    break;
                case 3:
                    pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (m_fminspread + m_fspread), (SCREEN_HEIGHT / 2), 0);
                    break;
            }
            m_apObject2d[nCount]->SetPos(pos);
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::Draw(void)
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCrosshair* CCrosshair::Create(float minSpread)
{
    CCrosshair* pCrosshair   = NULL;
    pCrosshair               = new CCrosshair;
    pCrosshair->m_fminspread = minSpread;
    pCrosshair->Init();
    return pCrosshair;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�L����̕ύX
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::AddSpread(float value)
{

    m_fspread += value;
}
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�L����̍Œ�l�̕ύX
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::SetMinSpread(float minspread)
{
    m_fminspread = minspread;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�L������擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
float CCrosshair::GetSpread(void)
{
    return m_fspread + m_fminspread;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e�N�X�`�����[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Data/Texture/crosshair.png", &m_pTexture);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e�N�X�`���A�����[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}