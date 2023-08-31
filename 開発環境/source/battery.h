//==========================================
//
//  バッテリークラス(battery.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BATTERY_H_
#define _BATTERY_H_
#include "main.h"
#include "object2D.h"

//===========================================
//  クラス定義
//==========================================
class CBattery : public CObject2D
{
public:
	CBattery(int nPriority = 7); //コンストラクタ
	~CBattery(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Add(const float fAdd);
	void Sab(const float fSab);

	//静的メンバ関数
	static CBattery *Create();

private:

	//メンバ変数
	float m_fBattery; //現在のバッテリー量

	//静的メンバ変数
	static const float mc_fMax; //ゲージの最大値
	static const float mc_fTime; //何もしなかった場合の制限時間
	static const float mc_fSab; //1fで減少する値

};

#endif
