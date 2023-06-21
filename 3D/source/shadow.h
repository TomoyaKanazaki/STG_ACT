//==========================================
//
//  シャドークラス(shadow.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  シャドークラス定義
//==========================================
class CShadow : public CObject3D
{
public:
	CShadow(int nPriority = 5); //コンストラクタ
	~CShadow(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTransform(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	//静的メンバ関数
	static CShadow *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

	//メンバ変数

};

#endif
