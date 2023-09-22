//==========================================
//
//  加算するタイマークラス(timer_add.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TIMER_ADD_H_
#define _TIMER_ADD_H_
#include "main.h"
#include "timer.h"

//==========================================
//  クラス定義
//==========================================
class CTimer_Add : public CTime
{
public:

	//メンバ関数
	CTimer_Add(int nPriority = 6);
	~CTimer_Add();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ変数
	int m_nProgress;

};

#endif
