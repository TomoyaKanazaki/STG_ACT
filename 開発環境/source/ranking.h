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

	//静的メンバ関数
	static void Save(int nNewScore);
	static int GetScore(void) { return m_nScore; }
	static int GetRank(void) { return m_nRank; }

private:

	//メンバ関数
	void Load(void);

	//静的メンバ関数
	static void Reset(void);
	static int Descending(const void * n0, const void * n1);

	//静的メンバ変数
	static int m_nNumData;
	static int *m_pScore;
	static const char m_sPass[128];
	static int m_nRank;
	static int m_nScore;

};

#endif
