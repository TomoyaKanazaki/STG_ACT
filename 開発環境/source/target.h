//==========================================
//
//  �I�N���X(target.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TARGET_H_
#define _TARGET_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CTarget : public CObject3D
{
public:

	//�����o�֐�
	CTarget();
	~CTarget();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CTarget *Create(D3DXVECTOR3 size, float fRot, float fDistance);

private:

	//�����o�ϐ�
	float m_fDistance;

};

#endif
