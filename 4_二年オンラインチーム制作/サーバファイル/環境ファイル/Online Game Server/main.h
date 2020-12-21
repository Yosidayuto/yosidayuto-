//--------------------------------------------------
//サーバー制作クラス化
//吉田悠人
//--------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

#define MAX_RANKING 10
#define MAX_TEETH 20			

#pragma comment(lib,"ws2_32.lib")
typedef enum	//歯の状態
{
	TEETH_NONE =0,	//選択済み
	TEETH_PER,		//当たり
	TEETH_OFF,		//外れ
	TEETH_MAX
}TEETH;

typedef struct
{
	int nPlayer;
	bool bPlayer;
}PlayerData;

typedef enum
{
	COMMAND_TYPE_NONE = 0,


} COMMAND_TYPE;

#endif
