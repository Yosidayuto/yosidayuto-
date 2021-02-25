//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
// �`���[�g���A������ [tutorial.h]
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "gamemode.h"
#include "main.h"
//*****************************************************************************
//  �O���錾
//*****************************************************************************
class CCamera;
class CPlayer;
class CPolygon3D;
class CTutorialStage;
class CCrosshair;
class CWoodenBox;
class CComputer;
class CWeapons_ui;
class CTrap;
class CClothBox;
class CIronBox;
class CStage01;
class CStage02;
class CStage03;
class CTitleLogo;
class CItem_ui;
class CDamage_ui;
class CBullet_ui;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTutorial : public CGamemode
{
  public:
    CTutorial();
    ~CTutorial();

    HRESULT Init(void);
    void Update(void);
    void Draw(void);
    void Uninit(void);
    static void Load(void);
    static void Unload(void);

  private:
    static LPDIRECT3DTEXTURE9 m_apTexture[13];    // �e�N�X�`���ւ̃|�C���^
    CWeapons_ui* m_pWeaponsUi;           //����UI�̃|�C���^
    CCamera* m_pCamera;                  //�J���|�C���^
    CPlayer* m_pPlayer;                  //�v���C���[�|�C���^
    CTutorialStage* m_pTutorialStage;    //�X�e�[�W�|�C���^
    CCrosshair* m_pCrosshair;            //�N���X�w�b�_�[�|�C���^
    CWoodenBox* m_pWoodenBox;            //�ؔ��|�C���^
    CClothBox* m_pClothBox;              //�z�t�����|�C���^
    CComputer* m_pComputer;              //�R���s���[�^�|�C���^
    CTrap* m_Trap;                       //�g���b�v�|�C���^
    CIronBox* m_pIronBox;
    CStage01* m_pStage01;
    CStage02* m_pStage02;
    CStage03* m_pStage03;
    CTitleLogo* m_pTitleLogo;
    CItem_ui* m_pItemUi;        //�񕜃A�C�e��UI�̃|�C���^
    CDamage_ui* m_pDamageUi;    //�_���[�WUI�̃|�C���^
    CBullet_ui* m_pBulletUi;    //�eUI�̃|�C���^
};
#endif
