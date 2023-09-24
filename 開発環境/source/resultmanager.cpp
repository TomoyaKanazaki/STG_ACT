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
#include "bg.h"

//==========================================
//  コンストラクタ
//==========================================
CResultManager::CResultManager()
{
	m_nCntScene = 0;
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
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.2f, 0.0f), CLogo::RESULT);

	//背景の生成
	CBg::Create();

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
	//シーン経過時間を加算
	m_nCntScene++;

	//画面遷移
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || m_nCntScene >= 600)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RANKING);
		return;
	}
}

//==========================================
//  描画処理
//==========================================
void CResultManager::Draw(void)
{

}
