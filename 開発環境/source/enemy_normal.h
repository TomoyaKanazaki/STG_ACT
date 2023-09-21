//==========================================
//
//  雑魚敵クラス(enemy_normal.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_NORMAL_H_
#define _ENEMY_NORMAL_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy_Normal : public CEnemy
{
public:

	CEnemy_Normal(int nPriority = 4); //コンストラクタ
	~CEnemy_Normal(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

};

#endif
