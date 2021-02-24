//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	player.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _PLAYER_H_
#define _PLAYER_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "animation.h"
#include "main.h"
#include "manager.h"
#include "model.h"
#include "object.h"
//�E�E�E�E�E�E�E�Ex�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define START_LIFE (100)

#define ASSAULT_RIFLE_RATE (5)
#define HANDGUN_RATE (5)
#define PLAYER_MODEL_COUNT (16)
#define PLAYER_MOVE_SPEED (1.0f)
#define PLAYER_MOVE_SPEED_SPRINT (1.5f)
#define PLAYER_MOVE_SPEED_AIM (0.75f)
#define PLAYER_MOVE_SPEED_CROUCH (0.5f)
#define COLLISION_RAY_COUNT (16)
#define PLAYER_COLLISION_HEIGHT (5.0f)
#define PLAYER_COLLISION_RADIUS (7.5f)
#define SENSI_RATE (0.01f)
#define START_SENSI (15)
#define GAMEOVER_COUNT (180)
#define MAGAZINE_SIZE_AR (30)
#define MAGAZINE_SIZE_HG (16)
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CAnimation;
class CCrosshair;
class CInputKeyboard;
class CDamage_ui;
class CBullet_ui;
class CItem_ui;
class CWeapons_ui;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CObject
{
public:
    typedef enum    //�p�[�c
    {
        PARTS_CHEST,             //��
        PARTS_BELLY,             //��
        PARTS_WAIST,             //��
        PARTS_HEAD,              //��
        PARTS_RIGHT_SHOULDER,    //�E��
        PARTS_RIGHT,             //�E�r
        PARTS_RIGHT_HAND,        //�E��
        PARTS_LEFT_SHOULDER,     //����
        PARTS_LEFT,              //���r
        PARTS_LEFT_HAND,         //����
        PARTS_RIGHT_THIGHS,      //�E������
        PARTS_RIGHT_CALF,        //�E�ӂ���͂�
        PARTS_RIGHT_FOOT,        //�E��
        PARTS_LEFT_THIGHS,       //��������
        PARTS_LEFT_CALF,         //���ӂ���͂�
        PARTS_LEFT_FOOT,         //����
        PARTS_MAX
    } PLAYER_PARTS;

    typedef enum
    {
        STATE_STAND = 0,
        STATE_WALK,
        STATE_SPRINT,
        STATE_CROUCH,
        STATE_CROUCH_WALK,
        STATE_AIM,
        STATE_RELOAD,
        STATE_RELOAD_WALK,
        STATE_DEATH,
        STATE_MAX
    } STATE;
    CPlayer();
    ~CPlayer();
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
    static void Load(void);
    static void Unload(void);

    D3DXVECTOR3 GetPos(void);
    D3DXVECTOR3 GetPartsPos(int nParts);
	D3DXVECTOR3 GetCenter(void);
    D3DXVECTOR3 GetRot(void);
    STATE GetState(void);

    void AddLife(int Value);
    int GetLife(void);
	void AddItem(void);
private:
    typedef struct
    {
        char* FileName;          //�t�@�C���̖��O
        int nParent;             //�e�p�[�c
        D3DXVECTOR3 Partspos;    //�p�[�c���W
    } PARTS_DATA;

    void PartsUpdate(void);     //�p�[�c�A�b�v�f�[�g�֐�
    void AnimaControl(void);    //�A�j���[�V�����R���g���[���֐�
    BOOL CheckHitBullet(CModel::MODELDATA modeldata, BOOL* pHit, float* pDistance, D3DXVECTOR3 spread);
    CObject* GetHitObject(void);
    BOOL Collision(CModel::MODELDATA modeldata, D3DXVECTOR3* pHittedPolyNormal, int* pCountHit);
    void FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvecVertices);
    D3DXVECTOR3 CalcWallScratchVector(D3DXVECTOR3 move, D3DXVECTOR3 nomal);

    static PARTS_DATA m_PartsData[PARTS_MAX];                                  //�p�[�c���
    static char* m_PattsWeapon[CManager::WEAPONS_MODE_MAX];                    //����p�[�c�̏��
    D3DXVECTOR3 m_Partsrot[PARTS_MAX];                                         //�p�[�crot���
    D3DXVECTOR3 m_Partspos[PARTS_MAX];                                         //�p�[�cpos���
    D3DXVECTOR3 m_Partssize[PARTS_MAX];                                        //�p�[�csize���
    static CAnimation* m_pAnimaSave;                                           //�A�j���[�V�����ۑ��|�C���^
    CAnimation* m_pAnima;                                                      //�A�j���[�V�����|�C���^
    CAnimation::MOTION_PLAYER m_AnimaMotion;                                   //�A�j���[�V�����p�^�[��
    CModel* m_apModelWorld;                                                    //���[���h���W�擾�p���f��
    CModel* m_apModel[PARTS_MAX];                                              //���f���|�C���^
    static CModel::MODELDATA m_modeldata[PARTS_MAX];                           //���f�����
    static CModel::MODELDATA m_modelWeaponData[CManager::WEAPONS_MODE_MAX];    //���f���E�F�|�����
    static D3DXMATERIAL* m_pMat;
    D3DXVECTOR3 m_pos;    //�ʒu
    D3DXVECTOR3 m_rot;         //����
    D3DXVECTOR3 m_AnimaRot;    //�A�j���[�V��������
    float m_fMoveVector;       //�ړ�����
    D3DXVECTOR3 m_size;
    STATE m_state;
    int m_nLife;
    CCrosshair* m_pCrosshair;
    static int m_nSensi;
    CDamage_ui* m_pDamageUi;    //�_���[�WUI�̃|�C���^
    CBullet_ui* m_pBulletUi[MAGAZINE_SIZE_AR];
	int m_nRemainingAmmo;
	int m_nMagazineSize;		//�ő�e��
	int m_nHaveItem;
	CItem_ui* m_apItemUI[5];
	CWeapons_ui *m_Weapons_UI;
};
#endif
