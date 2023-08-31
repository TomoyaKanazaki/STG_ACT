//==========================================
//
//  ���b�N�I���N���X(target.h)
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
	CTarget(int nPriority = 6); //�R���X�g���N�^
	~CTarget(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CTarget *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);

private:

};

#endif
