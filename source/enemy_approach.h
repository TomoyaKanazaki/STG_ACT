//==========================================
//
//  付いてくる敵のクラス(enemy_approach.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_APPROACH_H_
#define _ENEMY_APPROACH_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemyApproach : public CEnemy
{
public:
	CEnemyApproach(); //コンストラクタ
	~CEnemyApproach(); //コンストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ関数
	void Move(void);

};

#endif
