//==========================================
//
//  �|�[�Y�N���X(pause.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"

//==========================================
//  �|�[�Y�N���X��`
//==========================================
class CPause
{
public:
	CPause(); //�R���X�g���N�^
	~CPause(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetState(void) { return m_bPause; }

private:

	//�����o�ϐ�
	bool m_bPause;

};

#endif
