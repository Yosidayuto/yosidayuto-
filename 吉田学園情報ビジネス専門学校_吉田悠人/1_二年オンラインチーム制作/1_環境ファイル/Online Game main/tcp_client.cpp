//==========================================
// �`�[������ tcp_client.cpp
// Author:�����
//==========================================
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//==================================================
// �C���N���[�h�t�@�C��
//==================================================
#include "tcp_client.h"
#include <stdio.h>

//==================================================
// �R���X�g���N�^
//==================================================
CTcpClient::CTcpClient()
{
	m_sock = -1;
	m_bRecv = false;
}

//==================================================
// �f�X�g���N�^
//==================================================
CTcpClient::~CTcpClient()
{
}

//==================================================
// �C���X�^���X����
//==================================================
CTcpClient * CTcpClient::Create(const char * pHostName, int nPartNum)
{
	CTcpClient *pTcpClient = new CTcpClient;

	//������
	if (pTcpClient->Init(pHostName, nPartNum) == false)
	{
		//false���A���Ă�����J������
		delete pTcpClient;
		pTcpClient = NULL;

	}

	return pTcpClient;
}

//=============================================================================
// CTcpClient���� (accept�ɂ��ڑ�)
//=============================================================================
CTcpClient* CTcpClient::CreateServer(SOCKET sock)
{
	// TCP����M�N���X�̃C���X�^���X����
	CTcpClient *pTcpClient = new CTcpClient;

	//������
	if (pTcpClient->InitServer(sock) == false)
	{
		//false���A���Ă�����J������
		delete pTcpClient;
		pTcpClient = NULL;
	}

	return pTcpClient;
}

//==================================================
// �J��
//==================================================
void CTcpClient::Relese(void)
{
	Close(); //�I��

	delete this; //���̃|�C���^���J��
}

//==================================================
// ������
//==================================================
bool CTcpClient::Init(const char * pHostName, int nPortNum)
{
	//�ڑ��p�\�P�b�g���쐬
	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock == INVALID_SOCKET)
	{
		printf("socket:%d\n", WSAGetLastError());
		return false;
	}

	//�ڑ���t���̐ݒ�
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPortNum);
	addr.sin_addr.S_un.S_addr = inet_addr(pHostName);

	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		//���s
		printf("connect:%d\n", WSAGetLastError());

		m_bRecv = false;

		return false;
	}

	return true;
}

//=============================================================================
// ����������
//=============================================================================
bool CTcpClient::InitServer(SOCKET sock)
{
	m_sock = sock;
	return true;
}

//==================================================
// ���M
//==================================================
int CTcpClient::Send(char * pSendData, int nSendDateSize)
{
	if (m_sock < 0)
	{
		return 0;
	}

	//���M
	int nSendSize = send(m_sock, pSendData, nSendDateSize, 0);

	return nSendSize;
}

//==================================================
// ��M
//==================================================
int CTcpClient::Recv(char * pRecvBuf, int nRecvBufSize)
{
	if (m_sock < 0)
	{
		return 0;
	}

	//��M
	int nRecvSize = recv(m_sock, pRecvBuf, nRecvBufSize, 0);

	if (nRecvSize <= 0)
	{
		//�ؒf
		Close();
	}
	return nRecvSize;
}

//==================================================
// �I��
//==================================================
void CTcpClient::Close()
{
	if (m_sock < 0)
	{
		return;
	}
	//�\�P�b�g�ڑ����N���[�Y
	closesocket(m_sock);
	m_sock = -1;
}
