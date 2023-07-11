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
#include "debugproc.h"
#include "pause.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "model.h"
#include "layer.h"
#include "gamemanager.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CRenderer *CManager::m_pRenderer = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CMouse *CManager::m_pMouse = NULL;
CJoyPad *CManager::m_pJoyPad = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CPause *CManager::m_pPause = NULL;
CSound *CManager::m_pSound = NULL;
CTexture *CManager::m_pTexture = NULL;
CGameManager *CManager::m_pGameManager = NULL;

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
	if (m_pTexture == NULL)
	{
		//インスタンス生成
		m_pTexture = new CTexture;

		//読み込みが済んでいるか否か
		if (m_pTexture != NULL)
		{
			if (CTexture::GetLoadState() == false)
			{
				//テクスチャを読み込む
				m_pTexture->Load();
			}
		}
	}

	//モデルの読み込み
	if (CModel::GetLoadState() == false)
	{
		//モデルを読み込む
		CModel::Load();
	}

	//階層構造を読み込む
	CLayer::Load();

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

	//ジョイパッドの生成
	if (m_pJoyPad == NULL)
	{
		m_pJoyPad = new CJoyPad;
	}

	//ジョイパッドの初期化
	if (m_pJoyPad != NULL)
	{
		m_pJoyPad->Init(hInstance, hWnd);
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

	//ゲームマネージャの生成
	if (m_pGameManager == NULL)
	{
		m_pGameManager = new CGameManager;
	}

	//ポーズの初期化
	if (m_pGameManager != NULL)
	{
		if (FAILED(m_pGameManager->Init()))
		{
			return E_FAIL;
		}
	}

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
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//サウンドの終了、破棄
	if (m_pSound != NULL)
	{
		m_pSound->Stop();
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
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
	
	//ジョイパッドの終了、破棄
	if (m_pJoyPad != NULL)
	{
		m_pJoyPad->Uninit();
		delete m_pJoyPad;
		m_pJoyPad = NULL;
	}

	//ポーズの終了、破棄
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;
	}

	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->UnLoad();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	//モデルを破棄
	if (CModel::GetLoadState())
	{
		//モデルを破棄
		CModel::UnLoad();
	}

	//階層構造を破棄
	CLayer::UnLoad();

	//ゲームマネージャの終了、破棄
	if (m_pGameManager != NULL)
	{
		m_pGameManager->Uninit();
		delete m_pGameManager;
		m_pGameManager = NULL;
	}
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
	
	//ジョイパッドの更新処理
	if (m_pJoyPad != NULL)
	{
		m_pJoyPad->Update();
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

	//ゲームマネージャの更新
	if (m_pGameManager != NULL)
	{
		m_pGameManager->Update();
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
