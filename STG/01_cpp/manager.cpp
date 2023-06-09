//==========================================
//
//  マネージャクラス(manager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "object2D.h"
#include "player.h"
#include "bullet.h"
#include "debugproc.h"
#include "enemy.h"
#include "explosion.h"
#include "bg.h"
#include "effect.h"
#include "score.h"
#include "timer.h"
#include "number.h"
#include "pause.h"
#include "sound.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CRenderer *CManager::m_pRenderer = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CMouse *CManager::m_pMouse = NULL;
CJoyPad *CManager::m_pJoyPad[MAX_PLAYER] = {};
CDebugProc *CManager::m_pDebugProc = NULL;
CPause *CManager::m_pPause = NULL;
CScore *CManager::m_pScore = NULL;
CTimer *CManager::m_pTimer = NULL;
CSound *CManager::m_pSound = NULL;

//==========================================
//  コンストラクタ
//==========================================
CManager::CManager()
{

}

//==========================================
//  デストラクタ
//==========================================
CManager::~CManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダラーの生成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}

	//レンダラーの初期化
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return E_FAIL;
		}
	}
	
	//サウンドの生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}

	//サウンドの初期化
	if (m_pSound != NULL)
	{
		if (FAILED(m_pSound->Init(hWnd)))
		{
			return E_FAIL;
		}
	}

	//テクスチャの読み込み
	CPlayer::Load();
	CEnemy::Load();
	CBullet::Load();
	CExplosion::Load();
	CBg::Load();
	CEffect::Load();
	CNumber::Load();

	//デバッグ表示の生成
	if (m_pDebugProc == NULL)
	{
		m_pDebugProc = new CDebugProc;
	}

	//デバッグ表示の初期化
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Init();
	}

	//キーボードの生成
	if (m_pKeyboard == NULL)
	{
		m_pKeyboard = new CKeyboard;
	}

	//キーボードの初期化
	if (m_pKeyboard != NULL)
	{
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//マウスの生成
	if (m_pMouse == NULL)
	{
		m_pMouse = new CMouse;
	}

	//マウスの初期化
	if (m_pMouse != NULL)
	{
		if (FAILED(m_pMouse->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//ポーズの生成
	if (m_pPause == NULL)
	{
		m_pPause = new CPause;
	}

	//ポーズの初期化
	if (m_pPause != NULL)
	{
		if (FAILED(m_pPause->Init()))
		{
			return E_FAIL;
		}
	}

	//スコアの生成
	if (m_pScore == NULL)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 25.0f, 0.0f), D3DXVECTOR3(500.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	}

	//タイマーの生成
	if (m_pTimer == NULL)
	{
		m_pTimer = CTimer::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f), D3DXVECTOR3(187.5f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120);
	}

	////ジョイパッドの生成
	//if (m_pJoyPad[0] == NULL)
	//{
	//	m_pJoyPad[0] = new CJoyPad;
	//}

	////ジョイパッドの初期化
	//if (m_pJoyPad[0] != NULL)
	//{
	//	if (FAILED(m_pJoyPad[0]->Init(hInstance, hWnd)))
	//	{
	//		return E_FAIL;
	//	}
	//}

	//プレイヤーの生成
	CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	//背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//BGMの再生
	m_pSound->Play(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CManager::Uninit(void)
{

	//オブジェクトの終了
	CObject::ReleaseAll();

	//レンダラーの終了、破棄
	if (m_pRenderer != NULL)
	{
		m_pSound->Stop();
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//デバッグ表示の終了、破棄
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}

	//キーボードの終了、破棄
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	//マウスの終了、破棄
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}

	//ポーズの終了、破棄
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;
	}

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

	//テクスチャの破棄
	CPlayer::UnLoad();
	CEnemy::UnLoad();
	CBullet::UnLoad();
	CExplosion::UnLoad();
	CBg::UnLoad();
	CEffect::UnLoad();
	CNumber::UnLoad();
}

//==========================================
//  更新処理
//==========================================
void CManager::Update(void)
{
	//キーボードの更新処理
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}

	//マウスの更新処理
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}

	//ポーズの更新処理
	if (m_pPause != NULL)
	{
		m_pPause->Update();
	}

	//レンダラーの更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	//デバッグ表示の更新処理
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Update();
	}
}

//==========================================
//  描画処理
//==========================================
void CManager::Draw(void)
{
	//レンダラーの描画処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}
