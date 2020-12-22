//=============================================================================
//
// �T�[�o�[���� [tcp_listener.cpp]
// Author : �g�c �I�l
//
//=============================================================================
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "tcp_listener.h"
//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_ACCEPT_CONN 100		//�ڑ���t�ő吔

//=============================================================================
// ��������
//=============================================================================
CTcpListener *CTcpListener::Create(int nPortNum)
{
	//�������̓��I�m��
	CTcpListener*pTcpListener = new CTcpListener;
	if (pTcpListener->Init(nPortNum)==false)
	{
		//�������̊J��
		delete pTcpListener;
		pTcpListener = NULL;
	}
	return pTcpListener;
}
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTcpListener::CTcpListener()
{
	m_serverSock = -1;		//�ڑ���t�p�\�P�b�g�̏�����
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTcpListener::~CTcpListener()
{

}

//=============================================================================
// ����������
//=============================================================================
bool CTcpListener::Init(int nPortNum)
{
	struct sockaddr_in addr;
	// �ڑ���t�p�\�P�b�g�̐��� (socket)
	m_serverSock = socket(AF_INET, SOCK_STREAM, 0);
	//�ڑ���t���̐ݒ�
	addr.sin_family = AF_INET;					//IPv4
	addr.sin_port = htons(nPortNum);			//�|�[�g�ԍ�
	addr.sin_addr.S_un.S_addr = INADDR_ANY;		//���ׂĂ̐ڑ����󂯕t����

	if (m_serverSock == NULL)	//serverSock��NULL��������
	{
		return false;
	}
	//�\�P�b�g��IP�A�h���X�ƃ|�[�g�ԍ���ݒ肷��
	bind(m_serverSock, (struct sockaddr*)&addr, sizeof(addr));

	//�ڑ��v����t���J�n����
	listen(m_serverSock, MAX_ACCEPT_CONN);

	return true;
}

//=============================================================================
//�ڑ���t����
//=============================================================================
CTcpClient *CTcpListener::Accept()
{
	if (m_serverSock < 0)
	{
		return NULL;
	}

	struct sockaddr_in client;
	int nAddrLength = sizeof(client);

	// �ڑ���t����
	SOCKET sock = accept(m_serverSock, (struct sockaddr*)&client, &nAddrLength);
	CTcpClient *pTcpClient = CTcpClient::Create(sock);
	return pTcpClient;
}

//=============================================================================
//�j������
//=============================================================================
void CTcpListener::Release()
{
	// �ؒf����
	Close();
	// �C���X�^���X�폜
	delete this;
}

//=============================================================================
//�N���[�Y����
//=============================================================================
void CTcpListener::Close()
{
	if (m_serverSock < 0)
	{
		return;
	}
	//�҂��󂯃\�P�b�g���N���[�Y
	closesocket(m_serverSock);

}