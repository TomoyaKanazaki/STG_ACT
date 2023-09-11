//==========================================
//
//  �����̃N���X(explosion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#include "object3D_Anim.h"

//==========================================
//  �N���X��`
//==========================================
class CExplosion : public CObject3D_Anim
{
public:

	//�����o�֐�
	CExplosion(int nPriority = 6);
	~CExplosion();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CExplosion *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nPattern, int nInterval, bool bLoop, UVTYPE type);

};

#endif
