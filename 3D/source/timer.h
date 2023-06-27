//==========================================
//
//  �^�C���N���X(timer.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "object.h"

//==========================================
//  �}�N����`
//==========================================
#define TIME_DIGIT (3) //�^�C�}�[�̌���

//==========================================
//  �O���錾
//==========================================
class CNumber;

//==========================================
//  �^�C���N���X��`
//==========================================
class CTimer : public CObject
{
public:
	CTimer(int nPriority = 5); //�R���X�g���N�^
	~CTimer(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nTimeDeff);

private:

	//�����o�ϐ�
	CNumber *m_apNumber[TIME_DIGIT];
	int m_aTime[TIME_DIGIT]; //�\������l
	int m_nTime; //�^�C�}�[�̒l
	int m_nTimeDeff; //�����l
	int m_nBaseTime; //�����
	int m_nPauseStartTime; //�|�[�Y��ԂɂȂ�������
	int m_nPauseEndTime; //�|�[�Y��Ԃ��I���������
	int m_nPauseTime; //�|�[�Y��Ԃ���������
	bool m_bOldPause; //�O�t���[���̃|�[�Y���

	//�����o�֐�
	void CalcTime(void);
	D3DXVECTOR3 CalcPos(int nCnt);
	void CalcPauseTime(int nCurrentTime);

};

#endif
