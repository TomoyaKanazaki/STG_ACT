//==========================================
//
//  ���N���X(field.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  �e�N���X�̒�`
//==========================================
class CField : public CObject3D
{
public:
	CField(int nPriority = 6); //�R���X�g���N�^
	~CField(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CField *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

};

#endif
