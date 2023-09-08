//==========================================
//
//  的クラス(target.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TARGET_H_
#define _TARGET_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CTarget : public CObject3D
{
public:

	//メンバ関数
	CTarget();
	~CTarget();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CTarget *Create(D3DXVECTOR3 size, float fRot, float fDistance);

private:

	//メンバ変数
	float m_fDistance;

};

#endif
