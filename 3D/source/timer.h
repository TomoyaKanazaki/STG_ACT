//==========================================
//
//  タイムクラス(timer.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "object.h"

//==========================================
//  マクロ定義
//==========================================
#define TIME_DIGIT (3) //タイマーの桁数

//==========================================
//  前方宣言
//==========================================
class CNumber;

//==========================================
//  タイムクラス定義
//==========================================
class CTimer : public CObject
{
public:
	CTimer(int nPriority = 5); //コンストラクタ
	~CTimer(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nTimeDeff);

private:

	//メンバ変数
	CNumber *m_apNumber[TIME_DIGIT];
	int m_aTime[TIME_DIGIT]; //表示する値
	int m_nTime; //タイマーの値
	int m_nTimeDeff; //初期値
	int m_nBaseTime; //基準時間
	int m_nPauseStartTime; //ポーズ状態になった時間
	int m_nPauseEndTime; //ポーズ状態が終わった時間
	int m_nPauseTime; //ポーズ状態だった時間
	bool m_bOldPause; //前フレームのポーズ状態

	//メンバ関数
	void CalcTime(void);
	D3DXVECTOR3 CalcPos(int nCnt);
	void CalcPauseTime(int nCurrentTime);

};

#endif
