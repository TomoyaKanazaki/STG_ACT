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
//  前方宣言
//==========================================
class CRockon;

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
	void Targeted(void);

	//メンバ変数
	int m_nInterval; //弾の発射間隔
	CRockon *m_pRockon;

};

#endif
