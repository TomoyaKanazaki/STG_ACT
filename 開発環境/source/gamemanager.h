//==========================================
//
//  ゲームマネージャクラス(gamemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include "main.h"
#include "scene.h"

//==========================================
//  前方宣言
//==========================================
class CObject_Fan;
class CPlayer;
class CCamera;
class CLight;
class CTarget;
class CEnemyManager;
class CTarget;
class CScore;
class CTime;

//==========================================
//  ゲームマネージャクラス定義
//==========================================
class CGameManager : public CScene
{
public:

	CGameManager(); //コンストラクタ
	~CGameManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CObject_Fan *GetFan(void) { return m_pFan; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static CEnemyManager *GetEnemyManager(void) { return m_pEnemy; }
	static CTarget *GetTarget(void) { return m_pTarget; }
	static CScore *GetScore(void) { return m_pScore; }

private:

	//メンバ変数

	//静的メンバ変数
	static CObject_Fan *m_pFan;
	static CPlayer *m_pPlayer;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CEnemyManager *m_pEnemy;
	static CTarget *m_pTarget;
	static CScore *m_pScore;
	static CTime *m_pTime;

};

#endif
