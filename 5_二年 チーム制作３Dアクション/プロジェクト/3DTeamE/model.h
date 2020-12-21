//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	model.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _MODEL_H_
#define _MODEL_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "object3d.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define MAX_MATERIAL (30)

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CModel : public CObject3D
{
public:
    typedef struct
    {
        LPD3DXBUFFER pBuffMat;                        // �}�e���A�����ւ̃|�C���^
        DWORD nNumMat;                                // �}�e���A�����̐�
        LPD3DXMESH pMesh;                             // ���b�V�����ւ̃|�C���^
        LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];    // �e�N�X�`���ւ̃|�C���^
        D3DXMATRIX mtxWorld;                          // �A�j���[�V�������
    } MODELDATA;

    CModel();
    virtual ~CModel();
    virtual HRESULT Init(void);
    virtual void Uninit(void);
    virtual void Update(void);
    virtual void Draw(void);
    static CModel* Create(CModel* pParentModel, CObject* pParentObject, MODELDATA modeldata, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
    void SetAnimationRot(D3DXVECTOR3 rot)
    {
        m_rotAnime = rot;
    }
    void SetAnimationPos(D3DXVECTOR3 pos)
    {
        m_posAnime = pos;
    }
    void SetAnimationSize(D3DXVECTOR3 size)
    {
        m_sizeAnime = size;
    }
    MODELDATA GetModelData(void);
    void BindModel(MODELDATA modeldata);
    CObject* GetParentObject(void);

private:
    CModel* m_pParentModel;
    MODELDATA m_ModelData;
    D3DXVECTOR3 m_posAnime;
    D3DXVECTOR3 m_rotAnime;
    D3DXVECTOR3 m_sizeAnime;
    CObject* m_pParentObject;
};
#endif
