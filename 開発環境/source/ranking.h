//==========================================
//
//  �����L���O(ranking.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "main.h"

//==========================================
//  �N���X��`
//==========================================
class CRanking
{
public:

	//�����o�֐�
	CRanking();
	~CRanking();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static void Save(int nNewScore);
	static int GetScore(void) { return m_nScore; }
	static int GetRank(void) { return m_nRank; }

private:

	//�����o�֐�
	void Load(void);

	//�ÓI�����o�֐�
	static void Reset(void);
	static int Descending(const void * n0, const void * n1);

	//�ÓI�����o�ϐ�
	static int m_nNumData;
	static int *m_pScore;
	static const char m_sPass[128];
	static int m_nRank;
	static int m_nScore;

};

#endif
