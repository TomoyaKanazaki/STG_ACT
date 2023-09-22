//==========================================
//
//  ���Z����^�C�}�[�N���X(timer_add.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TIMER_ADD_H_
#define _TIMER_ADD_H_
#include "main.h"
#include "timer.h"

//==========================================
//  �N���X��`
//==========================================
class CTimer_Add : public CTime
{
public:

	//�����o�֐�
	CTimer_Add(int nPriority = 6);
	~CTimer_Add();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�ϐ�
	int m_nProgress;

};

#endif
