//==================================================================
//
// �N���C�A���g�ʐM communication.cpp
// Author:�����
//
//==================================================================

//==================================================================
// �C���N���[�h�t�@�C��
//==================================================================
#include "communication.h"
#include "game.h"
//==================================================================
// �ÓI�����o�ϐ��錾
//==================================================================
int CCommunication::m_nPlayer = 0;
int CCommunication::m_nPlayerTurn = 0;
bool CCommunication::m_bPlayer = false;
bool CCommunication::m_bHit = false;
int CCommunication::m_nMode = CGame::MODE_CONTINUE;
char CCommunication::m_aRecvBuff[BUFFER_NUM] = {};
bool CCommunication::m_abTooth[MAX_TOOTH] = {};
CTcpClient *CCommunication::m_pClient = NULL;
bool CCommunication::m_bRecv = false;
int CCommunication::nTooth = 0;
int CCommunication::nDie = 0;
//==================================================================
// �R���X�g���N�^
//==================================================================
CCommunication::CCommunication()
{
	//�ϐ��N���A
	m_nLoss = 0;
	nDie = 0;
	nTooth = 0;
	m_bRecv = false;
	m_pClient = NULL;
	m_nMode = CGame::MODE_CONTINUE;
	m_bHit = false;
	m_bPlayer = false;
	m_nPlayer = 0;
	m_nPlayerTurn = 0;
	memset(m_abTooth, 0, sizeof(m_abTooth));
}

//==================================================================
// �f�X�g���N�^
//==================================================================
CCommunication::~CCommunication()
{
}

//==================================================================
// ����
//==================================================================
CCommunication * CCommunication::Create(void)
{
	CCommunication *pCommunication = new CCommunication;

	//������
	if (FAILED(pCommunication->Init(IP_ADDR, SERVER_PORT_NUM)))
	{
		//false���A���Ă�����J������
		delete pCommunication;
		pCommunication = NULL;

	}

	m_bPlayer = true;                         //�v���C���[���g�p���Ă����Ԃɂ���
	memset(&m_abTooth, 1, sizeof(m_abTooth)); //�����g�p���Ă����Ԃɂ���

	std::thread thWorker(RecvPlayer);
	thWorker.detach();

	return pCommunication;
}

//==================================================================
// ������
//==================================================================
HRESULT CCommunication::Init(const char * pHostName, int nPartNum)
{
	//TCP�N���C�A���g����
	m_pClient=CTcpClient::Create(pHostName, nPartNum);

	return S_OK;
}

//==================================================================
// �I��
//==================================================================
void CCommunication::Uninit(void)
{
	CTcpClient *pClient = new CTcpClient;
	pClient->Relese();
}

//==================================================================
// �v���C���[���Z�Ԃ���������
//==================================================================
void CCommunication::PicPlayer(int nNumTooth)
{

	char aSendBuffer[BUFFER_NUM];
	int nTooth= nNumTooth;
	nTooth = htonl(nTooth);

	//�o�b�t�@�ɑI�񂾎��̔ԍ�������
	memcpy(&aSendBuffer[0], &nTooth, sizeof(int));
	if (nNumTooth != -1)
	{
		//�I�΂ꂽ����s�g�p��Ԃɂ���
		m_abTooth[nNumTooth] = false;
	}
	//���M
	int SendBuff = m_pClient->Send(aSendBuffer, sizeof(aSendBuffer));
}

//==================================================================
// �v���C���[���擾
//==================================================================
void CCommunication::RecvPlayer(void)
{

	memset(m_aRecvBuff, 0, sizeof(m_aRecvBuff)); //�o�b�t�@0�N���A

	 //��M
	int nRecvSize = m_pClient->Recv(m_aRecvBuff, sizeof(m_aRecvBuff));
	if (nRecvSize < 0)
	{
		return;
	}

	int nIndexRecv = 0;                          //�C���f�b�N�X��������

												 //���[�h
	m_nMode = *(int*)&m_aRecvBuff[nIndexRecv];
	nIndexRecv += sizeof(int);					//�G���f�B�A���ύX(�d�v)
	m_nMode= ntohl(m_nMode);
												 //�v���C���[�������Ă��邩
	int nData = *(int*)&m_aRecvBuff[nIndexRecv];
	nIndexRecv += sizeof(int);                   //�C���f�b�N�X��i�߂�
	nData = ntohl(nData);                        //�G���f�B�A���ύX(�d�v)
	if (nData != 0)                              //�v���C���[�̎g�p���
	{
		m_bPlayer = false;
	}
	else
	{
		m_bPlayer = true;
	}

	//�G���f�B�A���ϊ�
	m_nPlayer = *(int*)&m_aRecvBuff[nIndexRecv]; //�v���C���[�̔ԍ�
	m_nPlayer = ntohl(m_nPlayer);                //�G���f�B�A���ύX(�d�v)
	nIndexRecv += sizeof(int);                   //�C���f�b�N�X��i�߂�

		 
	nTooth = *(int*)&m_aRecvBuff[nIndexRecv];//�O�̃v���C���[���I�񂾔ԍ�
	nIndexRecv += sizeof(int);                   //�C���f�b�N�X��i�߂�
	nTooth = ntohl(nTooth);                      //�G���f�B�A���ύX(�d�v)
	if (nTooth != -1)
	{
		m_abTooth[nTooth] = false;                   //����s�g�p��Ԃɂ���
	}

	nDie= *(int*)&m_aRecvBuff[nIndexRecv];	//�v���C���[������Ă��邩
	nIndexRecv += sizeof(int);               //�C���f�b�N�X��i�߂�
	nDie = ntohl(nDie);                      //�G���f�B�A���ύX(�d�v)


	m_bRecv = true;
}

//==================================================================
// �v���C���[�̏��Ԃ����炷
//==================================================================
bool CCommunication::DisplacePlayer(void)
{
	//�����̃^�[��
	if (m_nMode != CGame::MODE_SETTLED)
	{
		if (m_nPlayer == 0)
		{
			if (m_bPlayer)
			{
				//�v���C���[�������Ă����ꍇ�A����I��
				return true;
			}
		}
	}
	return false;
}

//==================================================================
// ���Ҕ���
//==================================================================
int CCommunication::Winner(void)
{
	int nNum = PLAYERSTATE_NONE;

	if (m_bPlayer)
	{
		//�����c�����v���C���[
		nNum = PLAYERSTATE_ALIVE;
	}
	else
	{
		//���񂾃v���C���[
		nNum = PLAYERSTATE_DEAD;
	}

	return nNum;
}

//==================================================================
// ���[�h�ݒ�
//==================================================================
void CCommunication::SetMode(int nMode)
{
	m_nMode = nMode;
}
