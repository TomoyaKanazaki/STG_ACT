//==========================================
//
//  ���b�N�I���N���X(rockon.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ROCKON_H_
#define _ROCKON_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CRockon : public CObject3D
{
public:
	CRockon(int nPriority = 7); //�R���X�g���N�^
	~CRockon(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CRockon *Create(D3DXVECTOR3 pos);

private:

};

#endif
