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
#include "target.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CGameManager::STATE CGameManager::m_State = NONE;
CPlayer *CGameManager::m_pPlayer = NULL;
CObject_Fan *CGameManager::m_pFan = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CTarget *CGameManager::m_pTarget = NULL;

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
	m_pFan = CObject_Fan::Create(D3DXVECTOR3(0.0f, 0.01f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 550.0f);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	//ターゲットを生成
	m_pTarget = CTarget::Create(m_pCamera->GetPosR(), D3DXVECTOR3(50.0f, 0.0f, 50.0f));

	//BGMの再生
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM001);

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
}

//==========================================
//  描画処理
//==========================================
void CGameManager::Draw(void)
{

}
