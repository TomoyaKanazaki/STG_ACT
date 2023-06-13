//==========================================
//
//  ���C�g�N���X(light.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "main.h"

//==========================================
//  �}�N����`
//==========================================
#define NUM_LIGHT (3) //���C�g�̐�

//==========================================
//  ���C�g�N���X��`
//==========================================
class CLight
{
public:
	CLight(); //�R���X�g���N�^
	~CLight(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

	//�����o�ϐ�
	D3DLIGHT9 m_Light[NUM_LIGHT]; //���C�g���

};

#endif
