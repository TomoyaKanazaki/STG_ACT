//==========================================
//
//  ���Z����^�C�}�[�N���X(timer_sab.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TIMER_SAB_H_
#define _TIMER_SAB_H_
#include "main.h"
#include "timer.h"

//==========================================
//  �N���X��`
//==========================================
class CTimer_Sab : public CTime
{
public:

	//�����o�֐�
	CTimer_Sab(int nPriority = 6);
	~CTimer_Sab();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�ϐ�
	int m_nProgress;

};

#endif
