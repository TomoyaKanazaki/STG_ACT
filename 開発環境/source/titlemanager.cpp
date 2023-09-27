//==========================================
//
//  タイトルマネージャ(titlemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "titlemanager.h"
#include "manager.h"
#include "scenemanager.h"
#include "input.h"
#include "logo.h"
#include "camera.h"
#include "light.h"
#include "bg.h"
#include "camera_title.h"
#include "debris.h"
#include "sound.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CLight *CTitleManager::m_pLight = NULL;

//==========================================
//  コンストラクタ
//==========================================
CTitleManager::CTitleManager()
{
	m_nCntScene = 0;
}

//==========================================
//  デストラクタ
//==========================================
CTitleManager::~CTitleManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTitleManager::Init(void)
{
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.2f, 0.0f), CLogo::TITLE);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.6f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.15f, 0.0f), CLogo::ENTER);

	//背景の生成
	CBg::Create();

	//ライトの生成
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//ごみの生成
	for (int nCnt = 0; nCnt < 100; nCnt++)
	{
		CDebris::Create();
	}

	//BGMの再生
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CTitleManager::Uninit(void)
{
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
void CTitleManager::Update(void)
{
	//シーン経過時間を加算
	//m_nCntScene++;

	//画面遷移
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetMouse()->GetTrigger(CMouse::BUTTON_LEFT))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::GAME);
		CManager::GetSound()->Play(CSound::SOUND_LABEL_ENTER);
		return;
	}
	else if (m_nCntScene >= 900)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RANKING);
		return;
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
void CTitleManager::Draw(void)
{

}
