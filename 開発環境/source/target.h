//==========================================
//
//  ロックオンクラス(target.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TARGET_H_
#define _TARGET_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CTarget : public CObject2D
{
public:
	CTarget(int nPriority = 7); //コンストラクタ
	~CTarget(); //デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static CTarget *Create(void);

private:

	//静的メンバ変数
	static const float mc_fRate;
};

#endif
