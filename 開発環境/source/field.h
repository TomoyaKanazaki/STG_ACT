//==========================================
//
//  床クラス(field.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  弾クラスの定義
//==========================================
class CField : public CObject3D
{
public:
	CField(int nPriority = 6); //コンストラクタ
	~CField(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static CField *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

};

#endif
