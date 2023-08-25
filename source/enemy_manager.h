//==========================================
//
//  エネミーマネージャクラス(enemy_manager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_
#include "main.h"
#include "object.h"

//==========================================
//  エネミーマネージャクラス定義
//==========================================
class CEnemyManager : public CObject
{
public:
	CEnemyManager(); //コンストラクタ
	~CEnemyManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CEnemyManager *Create(void);

private:
	
	//メンバ変数
	D3DXVECTOR3 m_vecError; //生成位置の誤差
	int m_nPopCounter[24]; //生成タイミング
	bool m_bPop[24]; //生成済みフラグ
	int m_nNumEnemy; //一度に生成する敵の数
	int m_nTime;


};

#endif
