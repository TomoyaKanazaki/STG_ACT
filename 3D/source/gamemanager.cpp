//==========================================
//
//  ゲームマネージャクラス(gamemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gamemanager.h"
#include "object_fan.h"
#include "score.h"
#include "timer.h"
#include "player.h"
#include "enemy_manager.h"
#include "light.h"
#include "camera.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CScore *CGameManager::m_pScore = NULL;
CTimer *CGameManager::m_pTimer = NULL;
CPlayer *CGameManager::m_pPlayer = NULL;
CObject_Fan *CGameManager::m_pFan = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;

//==========================================
//  コンストラクタ
//==========================================
CGameManager::CGameManager()
{
	m_state = SHOT;
}

//==========================================
//  デストラクタ
//==========================================
CGameManager::~CGameManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CGameManager::Init(void)
{
	//床の生成
	m_pFan = CObject_Fan::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 128, 1000.0f);

	//スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 25.0f, 0.0f), D3DXVECTOR3(500.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//タイマーの生成
	m_pTimer = CTimer::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f), D3DXVECTOR3(187.5f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//エネミーマネージャの生成
	CEnemyManager::Create();

	//ライトの生成
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//カメラの生成
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
		m_pCamera->Init();
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CGameManager::Uninit(void)
{
	//スコアの終了、破棄
	if (m_pScore != NULL)
	{
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = NULL;
	}

	//タイマーの終了、破棄
	if (m_pTimer != NULL)
	{
		m_pTimer->Uninit();
		delete m_pTimer;
		m_pTimer = NULL;
	}

	//カメラの終了、破棄
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//ライトの終了、破棄
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
}

//==========================================
//  更新処理
//==========================================
void CGameManager::Update(void)
{
	//カメラの更新
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//ライトの更新
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}
}

//==========================================
//  描画処理
//==========================================
void CGameManager::Draw(void)
{

}
