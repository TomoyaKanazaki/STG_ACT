//==========================================
//
//  ゲームマネージャクラス(gamemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include "main.h"

//==========================================
//  前方宣言
//==========================================
class CScore;
class CTimer;
class CObject_Fan;
class CPlayer;
class CCamera;
class CLight;

//==========================================
//  ゲームマネージャクラス定義
//==========================================
class CGameManager
{
public:
	typedef enum
	{
		NONE = 0, //なし
		SHOT, //射撃モード
		BLADE, //斬撃モード
		MAX
	}STATE;

	CGameManager(); //コンストラクタ
	~CGameManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static CScore *GetScore(void) { return m_pScore; }
	static CTimer *GetTimer(void) { return m_pTimer; }
	static CObject_Fan *GetFan(void) { return m_pFan; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }

private:

	//メンバ変数
	STATE m_state; //ゲームの状態

	//静的メンバ変数
	static CScore *m_pScore;
	static CTimer *m_pTimer;
	static CObject_Fan *m_pFan;
	static CPlayer *m_pPlayer;
	static CCamera *m_pCamera;
	static CLight *m_pLight;

};

#endif
