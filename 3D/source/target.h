//==========================================
//
//  ターゲットクラス(target.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TARGET_H_
#define _TARGET_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  ターゲットクラス定義
//==========================================
class CTarget : public CObject3D
{
public:
	CTarget(); //コンストラクタ
	~CTarget(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CTarget *Create(const D3DXVECTOR3 size);

private:

};

#endif
