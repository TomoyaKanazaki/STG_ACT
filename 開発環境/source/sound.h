//==========================================
//
//  サウンドクラス(sound.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SOUND_H_
#define _SOUND_H_
#include "main.h"

//==========================================
//  サウンドクラス定義
//==========================================
class CSound
{
public:
	//サウンド一覧
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0, //BGM0
		SOUND_LABEL_BGM001, //BGM1
		SOUND_LABEL_ATTACK, //攻撃
		SOUND_LABEL_BLOCK, //ブロック
		SOUND_LABEL_DEAD, //死ね
		SOUND_LABEL_ENTER, //決定
		SOUND_LABEL_EXPLOSION, //爆発
		SOUND_LABEL_PRESS, //接触
		SOUND_LABEL_PUSH, //弾き
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	// サウンド情報の構造体定義
	typedef struct
	{
		char *pFilename; //ファイル名
		int nCntLoop; //ループカウント
	} SOUNDINFO;

	CSound(); //コンストラクタ
	~CSound(); //デストラクタ

	//メンバ関数
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:

	//メンバ関数
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//メンバ変数
	IXAudio2 *m_pXAudio2; //XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice; //マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX]; //ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX]; //オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX]; //オーディオデータサイズ

	//静的メンバ変数
	static SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX];

};

#endif
