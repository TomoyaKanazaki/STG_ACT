//==========================================
//
//  弾を撃つ敵のクラス(enemy_shot.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_SHOT_H_
#define _ENEMY_SHOT_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemyShot : public CEnemy
{
public:
	CEnemyShot(); //コンストラクタ
	~CEnemyShot(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ関数
	void Shot(void);

};

#endif
