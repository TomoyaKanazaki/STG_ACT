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

//==========================================
//  ゲームマネージャクラス定義
//==========================================
class CGameManager : public CScene
{
public:
	typedef enum
	{
		NONE = 0,
		TUTORIAL_CLOSE, //近接攻撃のチュートリアル
		TUTORIAL_FAR, //遠距離攻撃のチュートリアル
		BATTLE_CLOSE, //近距離メインの戦闘
		BATTLE_FAR, //遠距離メインの戦闘
		BATTLE_LAST, //遠近両方の戦闘
		BOSS_ATTACK, //ボスの直接攻撃
		BOSS_CREAR, //ボスの撃破
		FAZE_MAX, //ゲームフェーズの最大数
	}STATE;

	CGameManager(); //コンストラクタ
	~CGameManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static STATE GetState(void) { return m_State; }
	static void SetState(STATE state) { m_State = state; }
	static CObject_Fan *GetFan(void) { return m_pFan; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static CTarget *GetTarget(void) { return m_pTarget; }
	static CEnemyManager *GetEnemyManager(void) { return m_pEnemy; }

private:

	//メンバ変数

	//静的メンバ変数
	static STATE m_State; //ゲームの状態
	static CObject_Fan *m_pFan;
	static CPlayer *m_pPlayer;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CTarget *m_pTarget;
	static CEnemyManager *m_pEnemy;

};

#endif
