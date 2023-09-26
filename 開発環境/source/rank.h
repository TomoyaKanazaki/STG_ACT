//==========================================
//
//  順位(rank.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RANK_H_
#define _RANK_H_
#include "object.h"

//==========================================
//  前方宣言
//==========================================
class CNumber;

//==========================================
//  クラス定義
//==========================================
class CRank : public CObject
{
public:

	//メンバ関数
	CRank(int nPriority = 6);
	~CRank();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CRank *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nRank);

private:

#define RANK_DIGIT (3) //ランクの桁数

	//メンバ変数
	int m_nRank;
	int m_aRank[RANK_DIGIT];
	CNumber *m_apNumber[RANK_DIGIT];

	//メンバ関数
	void CalcRank(void);
	D3DXVECTOR3 CalcPos(int nCnt);

};

#endif
