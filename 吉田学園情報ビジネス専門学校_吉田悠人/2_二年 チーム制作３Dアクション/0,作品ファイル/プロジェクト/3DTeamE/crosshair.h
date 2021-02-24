//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	crosshair.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _CROSSHAIR_H_
#define _CROSSHAIR_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "object.h"
#include "object2d.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define MAX_SPREAD (200)
#define CROSSHAIR_PART_SIZE D3DXVECTOR3(6, 20, 0)

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CCrosshair : public CObject
{
public:
    CCrosshair();
    ~CCrosshair();
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    void AddSpread(float value);
    void SetMinSpread(float minspread);
    float GetSpread(void);
    static void Load(void);
	static void Unload(void);
    static CCrosshair* Create(float minSpread);

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // �e�N�X�`���ւ̃|�C���^
    CObject2D* m_apObject2d[4];
    float m_fspread;
    float m_fminspread;
};

#endif
