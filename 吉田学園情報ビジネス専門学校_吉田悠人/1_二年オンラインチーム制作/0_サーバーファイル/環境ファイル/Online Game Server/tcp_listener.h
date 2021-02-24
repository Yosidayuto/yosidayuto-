//--------------------------------------------------
//�T�[�o�[����N���X��
//�g�c�I�l
//--------------------------------------------------
#pragma once
#include <winsock2.h>
#include "tcp_client.h"
#include "main.h"
//---------------------------------------------------
//	�O���錾
//---------------------------------------------------
class CTcpClient;
//---------------------------------------------------
//	TCP�ڑ���t�N���X
//---------------------------------------------------
class CTcpListener
{
public:
	CTcpListener();					//�R���X�g���N�^
	~CTcpListener();				//�f�X�g���N�^

	static CTcpListener * Create(int nPortNum);	//CTcpListener����
	bool Init(int nPortNum);				//����������
	CTcpClient * Accept(void);				//�ڑ���t����
	void Release(void);						//�j������
	void Close(void);						//�N���[�Y����
private:
	SOCKET m_serverSock;		// �ڑ���t�p�\�P�b�g
	

};