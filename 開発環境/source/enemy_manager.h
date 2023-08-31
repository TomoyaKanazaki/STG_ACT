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

	//生成アルゴリズムに使用するデータ群
	struct CreateData
	{
		D3DXVECTOR3 pos; //初期位置
		int type; //敵の種類
		int fase; //出現するフェーズ
		int nCount; //生成される回数
		int nInterval; //生成間隔
	};

	CEnemyManager(); //コンストラクタ
	~CEnemyManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CEnemyManager *Create(void);
	static int GetDeth(void) { return m_nDead; }
	static void AddDeth(void) { m_nDead++; }
	static void ResetDeth(void) { m_nDead = 0; }
	static void Load(void);
	static void Unload(void);

private:
	
	//メンバ変数
	D3DXVECTOR3 m_vecError; //生成位置の誤差
	int m_nPopCounter[24]; //生成タイミング
	bool m_bPop[24]; //生成済みフラグ
	int m_nNumEnemy; //一度に生成する敵の数
	int m_nTime;

	//静的メンバ変数
	static int m_nDead;
	static int m_nNumData;
	static CreateData *m_pCreateData;
};

#endif
