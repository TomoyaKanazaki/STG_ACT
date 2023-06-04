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

//==========================================
//  静的メンバ変数宣言
//==========================================
CRenderer *CManager::m_pRenderer = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CMouse *CManager::m_pMouse = NULL;
CJoyPad *CManager::m_pJoyPad[MAX_PLAYER] = {};
CDebugProc *CManager::m_pDebugProc = NULL;

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

	//テクスチャの読み込み
	CPlayer::Load();
	CEnemy::Load();
	CBullet::Load();
	CExplosion::Load();
	CBg::Load();

	//プレイヤーの生成
	CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	//背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	//キーボードの終了、破棄
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}

	//テクスチャの破棄
	CPlayer::UnLoad();
	CEnemy::UnLoad();
	CBullet::UnLoad();
	CExplosion::UnLoad();
	CBg::UnLoad();
}

//==========================================
//  更新処理
//==========================================
void CManager::Update(void)
{
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

	//敵の生成
	if (CEnemy::GetNum() == 0 || m_pKeyboard->GetTrigger(DIK_RETURN))
	{
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.3f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.4f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.6f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.7f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.9f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
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
