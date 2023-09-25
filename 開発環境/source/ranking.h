//==========================================
//
//  ランキング(ranking.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "main.h"

//==========================================
//  クラス定義
//==========================================
class CRanking
{
public:

	//メンバ関数
	CRanking();
	~CRanking();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

};

#endif
