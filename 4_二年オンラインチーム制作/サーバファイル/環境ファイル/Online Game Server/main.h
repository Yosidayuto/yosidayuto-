//--------------------------------------------------
//�T�[�o�[����N���X��
//�g�c�I�l
//--------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

#define MAX_RANKING 10
#define MAX_TEETH 20			

#pragma comment(lib,"ws2_32.lib")
typedef enum	//���̏��
{
	TEETH_NONE =0,	//�I���ς�
	TEETH_PER,		//������
	TEETH_OFF,		//�O��
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
