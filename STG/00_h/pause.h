//==========================================
//
//  ポーズクラス(pause.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"

//==========================================
//  ポーズクラス定義
//==========================================
class CPause
{
public:
	CPause(); //コンストラクタ
	~CPause(); //デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetState(void) { return m_bPause; }

private:

	//メンバ変数
	bool m_bPause;

};

#endif
