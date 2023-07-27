//==========================================
//
//  �^�[�Q�b�g�N���X(target.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TARGET_H_
#define _TARGET_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  �^�[�Q�b�g�N���X��`
//==========================================
class CTarget : public CObject3D
{
public:
	CTarget(); //�R���X�g���N�^
	~CTarget(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CTarget *Create(const D3DXVECTOR3 size);

private:

};

#endif
