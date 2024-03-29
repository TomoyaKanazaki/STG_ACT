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
#include "player.h"
#include "enemy_manager.h"
#include "light.h"
#include "camera.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"
#include "scenemanager.h"
#include "model.h"
#include "renderer.h"
#include "enemy.h"
#include "debugproc.h"
#include "target.h"
#include "score.h"
#include "bg.h"
#include "camera_game.h"
#include "timer.h"
#include "ranking.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CPlayer *CGameManager::m_pPlayer = NULL;
CObject_Fan *CGameManager::m_pFan = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CEnemyManager *CGameManager::m_pEnemy = NULL;
CTarget *CGameManager::m_pTarget = NULL;
CScore *CGameManager::m_pScore = NULL;
CTime *CGameManager::m_pTime = NULL;

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
	m_pFan = CObject_Fan::Create(D3DXVECTOR3(0.0f, 0.01f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 2000.0f);

	//背景の生成
	CBg::Create();

	//的の生成
	m_pTarget = CTarget::Create(D3DXVECTOR3(500.0f, 500.0f, 500.0f), D3DX_PI, 2000.0f);
	m_pTarget = CTarget::Create(D3DXVECTOR3(500.0f, 500.0f, 500.0f), 0.0f, 2000.0f);
	m_pTarget = CTarget::Create(D3DXVECTOR3(500.0f, 500.0f, 500.0f), D3DX_PI * -0.5f, 2000.0f);
	m_pTarget = CTarget::Create(D3DXVECTOR3(500.0f, 500.0f, 500.0f), D3DX_PI * 0.5f, 2000.0f);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//エネミーマネージャの生成
	m_pEnemy = CEnemyManager::Create();

	//スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.75f, 40.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.25f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//タイマーの生成
	m_pTime = CTime::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.1f, 80.0f, 0.0f), 120, CTime::SAB);

	//カメラの生成
	if (m_pCamera == NULL)
	{
		m_pCamera = CSceneManager::GetCamera();
		m_pCamera->Init();
	}

	//ライトの生成
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//BGMの再生
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CGameManager::Uninit(void)
{
	//スコアを記録する
	CRanking::Save(m_pScore->SendScore());

	//ライトの終了、破棄
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	m_pCamera = NULL;

	//タイムの終了、破棄
	if (m_pTime != NULL)
	{
		m_pTime->Uninit();
		delete m_pTime;
		m_pTime = NULL;
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
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) && CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RESULT);
		return;
	}
#endif

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
