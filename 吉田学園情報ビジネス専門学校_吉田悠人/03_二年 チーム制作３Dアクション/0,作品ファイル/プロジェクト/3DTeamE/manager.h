//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	manager.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CRenderer;
class CInput;
class CCamera;
class CPlayer;
class CTutorialStage;
class CFade;
class CTitle;
class CTutorial;
class CGamemain;
class CModel;
class CAnimation;
class CInputJoystick;
class CMap01;
class CMap02;
class CMap03;
class CMap04;
class CResult;
class CWeaponSelect;
class CSound;
class CPause;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CManager
{
public:
    //���[�h�^�C�v
    typedef enum
    {
        MODE_TITLE = 0,
        MODE_TUTORIAL,
        MODE_WEAPONSELECT,
        MODE_MAP01,
        MODE_MAP02,
        MODE_MAP03,
		MODE_MAP04,
        MODE_SELECT,
        MODE_RESULT,
        MODE_MAX
    } MODE;
    //�E�F�|���^�C�v
    typedef enum
    {
        WEAPONS_MODE_NONE = -1,
        WEAPONS_MODE_AR,
        WEAPONS_MODE_HG,
        WEAPONS_MODE_MAX
    } WEAPONS_MODE;

    CManager();     //�R���X�g���N�^
    ~CManager();    //�f�X�g���N�^

    HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);    //�������֐�
    void Uninit(void);                                             //�I���֐�
    void Update(void);                                             //�X�V�֐�
    void Draw(void);                                               //�`��֐�
    static CRenderer* GetRenderer(void);                           //�Q�b�^�[
    static CInput* GetInputKey(void);
    static CInput* GetInputMou(void);
    static CInputJoystick* GetInputJoystick(void);
    static CCamera* GetCamera(void);
    static CPlayer* GetPlayer(void);
    static CModel* GetStageModel(void);
    static WEAPONS_MODE GetWeaponsMode(void);    //�E�F�|���X�e�[�g�擾
    static CSound* GetSound(void)
    {
        return m_pSound;
    }
    static void SetWeaponsMode(WEAPONS_MODE WeaponsMode);    //�E�F�|���X�e�[�g�Z�b�g
    static void SetStageModel(CModel* pModel);
    static void SetPlayer(CPlayer* pPlayer);
    static void BindCamera(CCamera* pCamera);
    static void LoadFile(void);
    static void UnloadFiles(void);
    static void SetMode(MODE mode);    // ���[�h�ؑ�
    static MODE GetMode(void);
    static CFade* GetFade(void)
    {
        return m_pFade;
    }    // �t�F�[�h�̎擾
    static void EndPause(void);

private:
    static CRenderer* m_pRenderer;    //�����_���̃|�C���^
    static CInput* m_pInputKey;       //�C���v�b�g�̃|�C���^
    static CInput* m_pInputMou;
    static CCamera* m_pCamera;
    static CPlayer* m_pPlayer;
    static CSound* m_pSound;
    static CModel* m_pStageModel;
    static CFade* m_pFade;            // �t�F�[�h�̃|�C���^
    static MODE m_mode;               // ���[�h�̕ϐ�
    static CTitle* m_pTitle;          // �^�C�g���̃|�C���^
    static CGamemain* m_pGamemain;    // �Q�[�����C���ւ̃|�C���^
    static CTutorial* m_pTutorial;    // �`���[�g���A���̃|�C���^
    static CMap01* m_pMap01;
    static CMap02* m_pMap02;
    static CMap03* m_pMap03;
	static CMap04* m_pMap04;
    static CResult* m_pResult;
    static CWeaponSelect* m_pWeaponSelect;
    static CAnimation* m_pAnimation;
    static CInputJoystick* m_pInputJoystick;
    static WEAPONS_MODE m_WeaponsMode;    //�E�F�|���^�C�v�ۑ�
    static CPause* m_pPause;
};

#endif
