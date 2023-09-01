//==========================================
//
//  ロックオンクラス(rockon.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ROCKON_H_
#define _ROCKON_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CRockon : public CObject3D
{
public:
	CRockon(int nPriority = 7); //コンストラクタ
	~CRockon(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CRockon *Create(D3DXVECTOR3 pos);

private:

};

#endif
