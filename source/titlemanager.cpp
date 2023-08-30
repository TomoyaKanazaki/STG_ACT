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

//==========================================
//  コンストラクタ
//==========================================
CTitleManager::CTitleManager()
{

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
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CLogo::TITLE);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CTitleManager::Uninit(void)
{

}

//==========================================
//  更新処理
//==========================================
void CTitleManager::Update(void)
{
	//画面遷移テスト
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::GAME);
		return;
	}
}

//==========================================
//  描画処理
//==========================================
void CTitleManager::Draw(void)
{

}
