//==========================================
//
//  減算するタイマークラス(timer_sab.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TIMER_SAB_H_
#define _TIMER_SAB_H_
#include "main.h"
#include "timer.h"

//==========================================
//  クラス定義
//==========================================
class CTimer_Sab : public CTime
{
public:

	//メンバ関数
	CTimer_Sab(int nPriority = 6);
	~CTimer_Sab();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ変数
	int m_nProgress;

};

#endif
