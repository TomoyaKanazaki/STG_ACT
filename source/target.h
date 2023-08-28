//==========================================
//
//  ロックオンクラス(target.h)
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
	CTarget(int nPriority = 6); //コンストラクタ
	~CTarget(); //デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static CTarget *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);

private:

};

#endif
