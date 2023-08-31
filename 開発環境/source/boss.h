//==========================================
//
//  ボス敵クラス(boss.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CBoss : public CEnemy
{
public:
	CBoss(); //コンストラクタ
	~CBoss(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ関数
	void Rotate();

};

#endif
