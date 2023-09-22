//==========================================
//
//  タイマークラス(time.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "object.h"

//==========================================
//  前方宣言
//==========================================
class CNumber;

//==========================================
//  クラス定義
//==========================================
class CTime : public CObject
{
public:

	//タイマー形式の列挙型定義
	enum Time
	{
		ADD = 0, //加算
		SAB, //減算
		MAX
	};

	//メンバ関数
	CTime(int nPriority = 6);
	~CTime();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	//静的メンバ関数
	static CTime *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int max, Time kind);

protected:

	//メンバ変数
	int m_nCurrent;
	int m_nMax;

private:

#define TIMER_DIGIT (3) //スコアの桁数

	//メンバ変数
	CNumber *m_apNumber[TIMER_DIGIT];
	int m_aTime[TIMER_DIGIT]; //表示する値

	//メンバ関数
	void CalcScore(void);
	D3DXVECTOR3 CalcPos(int nCnt);


};

#endif
