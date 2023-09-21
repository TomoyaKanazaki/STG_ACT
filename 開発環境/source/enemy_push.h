//==========================================
//
//  押し出しの敵クラス(enemy_push.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_PUSH_H_
#define _ENEMY_PUSH_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy_Push : public CEnemy
{
public:

	CEnemy_Push(int nPriority = 4); //コンストラクタ
	~CEnemy_Push(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ関数
	void Push(void);
	void Target(void);

	//静的メンバ変数
	const static float mc_fPush;

};

#endif
