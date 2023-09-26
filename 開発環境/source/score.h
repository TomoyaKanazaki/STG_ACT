//==========================================
//
//  �X�R�A�N���X(score.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#include "object.h"

//==========================================
//  �}�N����`
//==========================================
#define SCORE_DIGIT (8) //�X�R�A�̌���

//==========================================
//  �O���錾
//==========================================
class CNumber;

//==========================================
//  �X�R�A�N���X��`
//==========================================
class CScore : public CObject
{
public:
	CScore(int nPriority = 7); //�R���X�g���N�^
	~CScore(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Add(const int nAdd);
	void AddScale(const float fScale) { m_fScale += fScale; }
	int SendScore(void) {return m_nScore; }

	//�ÓI�����o�֐�
	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nScoreDeff);
	static int GetScore(void) { return m_prevScore; }

private:
	
	//�����o�ϐ�
	CNumber *m_apNumber[SCORE_DIGIT];
	int m_aScore[SCORE_DIGIT]; //�\������l
	int m_nScore; //�X�R�A�̒l
	float m_fScale; //�X�R�A�̔{��

	//�����o�֐�
	void CalcScore(void);
	D3DXVECTOR3 CalcPos(int nCnt);

	//�ÓI�����o�ϐ�
	static int m_prevScore;

};

#endif
