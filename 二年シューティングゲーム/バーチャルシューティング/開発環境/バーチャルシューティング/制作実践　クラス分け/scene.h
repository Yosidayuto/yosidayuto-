#ifndef _SCENE_H_
#define _SCENE_H_

#include"main.h"
//------------------------------------
//前置処理
//------------------------------------
//class CPause;
//----------------------------------------------
//マクロ定義
//----------------------------------------------
#define MAX_PRIORITY 6
//----------------------------------------------
//シーンクラス
//----------------------------------------------
class CScene
{
public:
	CScene(int nPriorit = 3);
	virtual ~CScene();

	typedef enum  //ポリゴン種類
	{
		OBJ_TYPE_NONE = 0,
		OBJ_TYPE_PLAYER,		//プレイヤー
		OBJ_TYPE_BULLET,		//バレット
		OBJ_TYPE_ENEMY,			//エネミー
		LABEL_MAX,
	}OBJTYPE;

	virtual	HRESULT Init(void)=0;
	virtual	void	Uninit(void) = 0;
	virtual void	Draw(void) = 0;
	virtual void	Update(void) = 0;
	static void		UpdateAll(void);
	static void		DrawAll(void);
	static void		ReleaseAll(void);
	
	void			SetObjType(OBJTYPE objType);
	OBJTYPE			GetObjType(void);
	static CScene	*GetScene(int nPriorty, int nCntScene);


private:

	OBJTYPE			m_nType;
	static CScene	*m_apScene[MAX_PRIORITY][MAX_SCENE];
	static int		m_nNumAll;
	int				m_nID;
	int				m_nPiority;
	//static GAME_MODE m_Mode;
	static bool		bPause;
	//static void		Pause(void);
	//static CPause	*m_pPause;
protected:
	void Release(void);

};
#endif