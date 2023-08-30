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
#include "logo.h"

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
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_HEIGHT), CLogo::RESULT);

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
	//画面遷移テスト
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::TITLE);
		return;
	}
}

//==========================================
//  描画処理
//==========================================
void CResultManager::Draw(void)
{

}
