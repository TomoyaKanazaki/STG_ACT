//==========================================
//
//  リザルトマネージャ(resultmanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "resultmanager.h"
#include "manager.h"
#include "scenemanager.h"
#include "input.h"

//==========================================
//  コンストラクタ
//==========================================
CResultManager::CResultManager()
{

}

//==========================================
//  デストラクタ
//==========================================
CResultManager::~CResultManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CResultManager::Init(void)
{
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CResultManager::Uninit(void)
{

}

//==========================================
//  更新処理
//==========================================
void CResultManager::Update(void)
{
#if _DEBUG
	//画面遷移テスト
	if (CManager::GetKeyboard()->GetTrigger(DIK_0))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::TITLE);
		return;
	}
#endif
}

//==========================================
//  描画処理
//==========================================
void CResultManager::Draw(void)
{

}
