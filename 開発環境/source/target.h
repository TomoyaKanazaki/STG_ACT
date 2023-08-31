//==========================================
//
//  ���b�N�I���N���X(target.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TARGET_H_
#define _TARGET_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CTarget : public CObject2D
{
public:
	CTarget(int nPriority = 7); //�R���X�g���N�^
	~CTarget(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CTarget *Create(void);

private:

	//�ÓI�����o�ϐ�
	static const float mc_fRate;
};

#endif
