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
	CScore(int nPriority = 5); //�R���X�g���N�^
	~CScore(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void AddScore(const int nAdd);

	//�ÓI�����o�֐�
	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nScoreDeff);

private:
	
	//�����o�ϐ�
	CNumber *m_apNumber[SCORE_DIGIT];
	int m_aScore[SCORE_DIGIT]; //�\������l
	int m_nScore; //�X�R�A�̒l

	//�����o�֐�
	void CalcScore(void);
	D3DXVECTOR3 CalcPos(int nCnt);

};

#endif
