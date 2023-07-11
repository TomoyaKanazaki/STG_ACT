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
#include "energy.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CGameManager::STATE CGameManager::m_state = SHOT;
CScore *CGameManager::m_pScore = NULL;
CTimer *CGameManager::m_pTimer = NULL;
CPlayer *CGameManager::m_pPlayer = NULL;
CObject_Fan *CGameManager::m_pFan = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CEnergy *CGameManager::m_pEnergy = NULL;

//==========================================
//  コンストラクタ
//==========================================
CGameManager::CGameManager()
{

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

	//スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 25.0f, 0.0f), D3DXVECTOR3(500.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//タイマーの生成
	m_pTimer = CTimer::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f), D3DXVECTOR3(187.5f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120);

	//エネルギーの生成
	m_pEnergy = CEnergy::Create(D3DXVECTOR3(1200.0f, SCREEN_HEIGHT * 0.5f, 0.0f), 20.0f);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CGameManager::Uninit(void)
{
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

	if (m_state == SHOT)
	{
		if (m_pEnergy->IsMax())
		{
			if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
			{
				m_state = BLADE;
			}
			CManager::GetDebugProc()->Print("\nエネルギーMAX\n");
		}
		--*m_pScore;
	}
	else if (m_state == BLADE)
	{
		if (m_pEnergy->IsMin())
		{
			m_state = SHOT;
		}
		--*m_pEnergy;
	}
}

//==========================================
//  描画処理
//==========================================
void CGameManager::Draw(void)
{

}
