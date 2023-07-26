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
#if _DEBUG
	//画面遷移テスト
	if (CManager::GetKeyboard()->GetTrigger(DIK_0))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::GAME);
		return;
	}
#endif
}

//==========================================
//  描画処理
//==========================================
void CTitleManager::Draw(void)
{

}
