//==========================================
//
//  ����(rank.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RANK_H_
#define _RANK_H_
#include "object.h"

//==========================================
//  �O���錾
//==========================================
class CNumber;

//==========================================
//  �N���X��`
//==========================================
class CRank : public CObject
{
public:

	//�����o�֐�
	CRank(int nPriority = 6);
	~CRank();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CRank *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nRank);

private:

#define RANK_DIGIT (3) //�����N�̌���

	//�����o�ϐ�
	int m_nRank;
	int m_aRank[RANK_DIGIT];
	CNumber *m_apNumber[RANK_DIGIT];

	//�����o�֐�
	void CalcRank(void);
	D3DXVECTOR3 CalcPos(int nCnt);

};

#endif
