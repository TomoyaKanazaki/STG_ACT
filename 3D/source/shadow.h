//==========================================
//
//  �V���h�[�N���X(shadow.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  �V���h�[�N���X��`
//==========================================
class CShadow : public CObject3D
{
public:
	CShadow(int nPriority = 5); //�R���X�g���N�^
	~CShadow(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTransform(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	//�ÓI�����o�֐�
	static CShadow *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

	//�����o�ϐ�

};

#endif
