//=====================================================================
//
// �N���C�A���g�ʐM tcp_client.h
// Author:�����
//
//=====================================================================

#ifndef _TCP_CLIENT_H
#define _TCP_CLIENT_H

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "main.h"

//=====================================================================
// TCP�N���C�A���g�N���X
//=====================================================================
class CTcpClient
{
public:
	CTcpClient();
	~CTcpClient();

	//�����o�֐�
	static CTcpClient *Create(const char *pHostName, int nPartNum);     //����(�N���C�A���g)
	static CTcpClient *CreateServer(SOCKET sock);                       //����(�T�[�o�[)
	void Relese(void);                                                  //�J��
	bool Init(const char *pHostName, int nPortNum);                     //������(�N���C�A���g)
	bool InitServer(SOCKET sock);                                       //������(�T�[�o�[)
	int Send(char *pSendData, int nSendDateSize);                       //���M
	int Recv(char *pRecvBuf, int nRecvBufSize);                         //��M
	void Close();                                                       //�I��

private:
	//�����o�ϐ�
	SOCKET m_sock;                                                      //��M�p
	bool m_bRecv;                                                       //��M�t���O
};

#endif // !_TCP_CLIENT_H