//==========================================
//
//  エネルギークラス(energy.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENERGY_H_
#define _ENERGY_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  エネルギークラス定義
//==========================================
class CEnergy : public CObject2D
{
public:
	CEnergy(); //コンストラクタ
	~CEnergy(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool IsMax(void) { return m_fEnergy >= 700.0f ? true : false; }
	bool IsMin(void) { return m_fEnergy <= 0.0f ? true : false; }

	//静的メンバ関数
	static CEnergy *Create(const D3DXVECTOR3 pos, const float fWidth);

	//演算子のオーバーロード
	CEnergy &operator++(void);
	CEnergy &operator--(void);

private:

	//メンバ変数
	float m_fEnergy;
	float m_fBaseHight; //基準位置

};

#endif
