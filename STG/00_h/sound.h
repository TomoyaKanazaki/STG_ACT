//==========================================
//
//  �T�E���h�N���X(sound.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SOUND_H_
#define _SOUND_H_
#include "main.h"

//==========================================
//  �T�E���h�N���X��`
//==========================================
class CSound
{
public:
	//�T�E���h�ꗗ
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0, //BGM0
		SOUND_LABEL_BGM001, //BGM1
		SOUND_LABEL_SE_SHOT, //�e���ˉ�
		SOUND_LABEL_SE_START, //�Q�[���X�^�[�g��
		SOUND_LABEL_SE_ENEMYPOP, //�G�o����
		SOUND_LABEL_SE_PLAYEREXPLOSION, //�v���C���[������
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	// �T�E���h���̍\���̒�`
	typedef struct
	{
		char *pFilename; //�t�@�C����
		int nCntLoop; //���[�v�J�E���g
	} SOUNDINFO;

	CSound(); //�R���X�g���N�^
	~CSound(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:

	//�����o�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//�����o�ϐ�
	IXAudio2 *m_pXAudio2; //XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice; //�}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX]; //�\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX]; //�I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX]; //�I�[�f�B�I�f�[�^�T�C�Y

	//�ÓI�����o�ϐ�
	static SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX];

};

#endif
