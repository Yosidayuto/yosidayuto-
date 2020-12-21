//=====================================================================
//
// �ʐM communication.h
// Author:�����
//
//=====================================================================

#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "tcp_client.h"
#include "main.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define MAX_TOOTH       (20)                //���̍ő吔
#define MAX_LOSS        (3)                 //�͂���̍ő吔
#define BUFFER_NUM      (128)               //�o�b�t�@�ő吔
#define IP_ADDR			"127.0.0.1"		//�ڑ����IP�A�h���X
#define SERVER_PORT_NUM (12345)             //�ڑ���T�[�o�[�̃|�[�g
#define MAX_PLAYER      (3)                 //�v���C���[�ő吔

//=====================================================================
// �ʐM�N���X
//=====================================================================
class CCommunication
{
public:

	typedef enum	//���̏��
	{
		TEETH_NONE = 0,	//�I���ς�
		TEETH_PER,		//������
		TEETH_OFF,		//�O��
		TEETH_MAX
	}TEETH;

	typedef enum //�v���C���[�̏��
	{
		PLAYERSTATE_NONE = 0,
		PLAYERSTATE_ALIVE,
		PLAYERSTATE_DEAD,
		PLAYERSTATE_MAX
	}PLAYERSTATE;

	CCommunication();
	~CCommunication();

	//�����o�֐�
	static CCommunication *Create(void);                        //����
	HRESULT Init(const char *pHostName, int nPartNum);          //������
	void Uninit(void);                                          //�I��

	void PicPlayer(int nNumTooth);                              //�v���C���[���Z�Ԃ���������
	static void RecvPlayer(void);                               //�v���C���[���擾
	bool DisplacePlayer(void);                                  //�v���C���[�̏��Ԃ����炷
	int Winner(void);                                           //���Ҕ���

																//�Q�b�g�A�Z�b�g
	static int GetPlayerTurn(void) { return m_nPlayerTurn; }     //�v���C���[�^�[���擾
	static int GetnPlayer(void) { return m_nPlayer; }            //�v���C���[�ԍ��擾
	static bool GetbHit(void) { return m_bHit; }                 //�����肩�͂��ꂩ�擾
	static int GetMode(void) { return m_nMode; }                 //���݂̃��[�h�擾
	static void SetMode(int nMode);                              //���[�h�ݒ�
	static bool GetbPlayer(void) { return m_bPlayer; }           //�v���C���[�̎g�p��Ԏ擾
	static bool GetabTooth(int nNum) { return m_abTooth[nNum]; } //���̏��擾
	static bool GetbRecv(void) { return m_bRecv; }
	static void SetbRecv(void) { m_bRecv = false; }				 //��M�󂯎���
	static int  GetnTooth(void) { return nTooth; }
	static int  GetnDie(void){ return nDie-1; }					//���ꂽ�v���C���[�̏�Ԏ擾
private:
	//�����o�ϐ�
	int  m_nLoss;                                               //�͂����
	static bool m_bHit;                                         //�����肩�ǂ���
	static bool  m_abTooth[MAX_TOOTH];                          //���̔z��
	static int  m_nPlayerTurn;                                  //�v���C���[�̃^�[��
	static int  m_nPlayer;                                      //���Ԗڂ̃v���C���[��
	static bool m_bPlayer;                                      //�g�p����Ă��邩
	static int  m_nMode;                                        //���݂̃��[�h
	static char m_aRecvBuff[BUFFER_NUM];                        //��M�p�o�b�t�@
	static CTcpClient *m_pClient;
	static bool m_bRecv;										//��M���I�������
	static int  nTooth;											//�O�ɑI�񂾎��̏��
	static int  nDie;											//���ꂽ�v���C���[
};

#endif // !_COMMUNICATION_H_

