//=============================================================================
// �T�E���h���� [sound.cpp]
//=============================================================================
#include "sound.h"
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
CSound::PARAM CSound::m_aParam[LABEL_MAX] =
{
	//BGM
	{ "data/BGM/Title.wav", 0 },	//�^�C�g��
	{ "data/BGM/Select.wav", 0 },	//�Z���N�g
	{ "data/BGM/Stage_1.wav", 0 },	//�X�e�[�W�P
	{ "data/BGM/Stage_2.wav", 0 },	//�X�e�[�W�Q
	{ "data/BGM/Stage_3.wav", 0 },	//�X�e�[�W�R
	{ "data/BGM/Boss1.wav", 0 },	//�{�X�P
	{ "data/BGM/Boss2.wav", 0 },	//�{�X�Q
	{ "data/BGM/Boss3.wav", 0 },	//�{�X�R
	{ "data/BGM/Ranking.wav", 0 },	//�����L���O
	//SE
	{ "data/SE/SE_Button.wav", 0 },	//�N���b�N
	{ "data/SE/SE_Cancel.wav", 0 },	//�L�����Z��
	{ "data/SE/SE_Start.wav", 0 },	//�X�^�[�g
	{ "data/SE/SE_Shots.wav", 0 },	//�V���b�g
	{ "data/SE/SE_Laser.wav", 0 },	//���[�U�[
	{ "data/SE/SE_Homing.wav", 0 },	//�z�[�~���O
	{ "data/SE/SE_Die.wav", 0 },	//���񂾂Ƃ�
	{ "data/SE/SE_Warning.wav", 0 },//���[�j���O
	{ "data/SE/SE_Boss1.wav", 0 },	//���񂾃{�X(1��3)
	{ "data/SE/SE_Boss2.wav", 0 },	//���񂾃{�X(2)
	{ "data/SE/SE_Result.wav", 0 },	//���U���g�t�@���t�@�[��
};

//---------------------------------
//�R���X�g���N�^
//---------------------------------
CSound::CSound()
{
	//����������
	m_pXAudio2 = NULL;
	m_pMasteringVoice = NULL;
	for (int nCountSound = 0; nCountSound < LABEL_MAX; nCountSound++)
	{
		m_apSourceVoice[nCountSound] = NULL;
		m_apDataAudio[nCountSound] = NULL;
		m_aSizeAudio[nCountSound] = NULL;

	}
	
}
//---------------------------------
//�f�X�g���N�^
//--------------------------------
CSound::~CSound()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSound::Init(HWND hWnd)
{
	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	if(FAILED(XAudio2Create(&m_pXAudio2, 0)))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}
	
	// �}�X�^�[�{�C�X�̐���
	if(FAILED(m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice)))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if(m_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for(int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(m_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		// WAVE�t�@�C���̃`�F�b�N
		if(FAILED(CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition)))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if(FAILED(ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition)))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �t�H�[�}�b�g�`�F�b�N
		if(FAILED(CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition)))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if(FAILED(ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition)))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		if(FAILED(CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition)))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
		if(FAILED(ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition)))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �\�[�X�{�C�X�̐���
		if(FAILED(m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format))))
		{
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = m_aParam[nCntSound].nCntLoop;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void CSound::Uninit(void) 
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;
	
	if(m_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}


//=============================================================================
// �Z�O�����g�Đ�(�Đ����Ȃ��~)
//=============================================================================
HRESULT CSound::Play(LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;
	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = m_aParam[label].nCntLoop;
	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[label]->Stop(0);
		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);
	// �Đ�
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}


//=============================================================================
// �Z�O�����g��~(���x���w��)
//=============================================================================
void CSound::Stop(LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
}


//=============================================================================
// �Z�O�����g��~(�S��)
//=============================================================================
void CSound::Stop(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}


//=============================================================================
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD * pChunkSize, DWORD * pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}


//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void * pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

