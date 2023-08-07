//==========================================
//
//  ゲームマネージャクラス(gamemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gamemanager.h"
#include "manager.h"
#include "sound.h"
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
#include "scenemanager.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CGameManager::STATE CGameManager::m_State = SHOT;
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

	//BGMの再生
	//CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM001);

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

	//BGMの停止
	CManager::GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CGameManager::Update(void)
{
#if _DEBUG
	//画面遷移テスト
	if (CManager::GetKeyboard()->GetTrigger(DIK_0))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RESULT);
		return;
	}
#endif

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

	if (m_State == SHOT)
	{
		if (m_pEnergy->IsMax())
		{
			if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
			{
				m_State = BLADE;
			}
			CManager::GetDebugProc()->Print("\nエネルギーMAX\n");
		}
		//スコアの倍率を下げる処理
	}
	else if (m_State == BLADE)
	{
		if (m_pEnergy->IsMin())
		{
			m_State = SHOT;
		}
		//エネルギーを減らす処理
	}

	//画面遷移
	//if (m_pTimer->GetTime() <= 0)
	//{
	//	CManager::GetSceneManager()->SetNext(CSceneManager::RESULT);
	//	return;
	//}
}

//==========================================
//  描画処理
//==========================================
void CGameManager::Draw(void)
{

}
