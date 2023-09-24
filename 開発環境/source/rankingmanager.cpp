//==========================================
//
//  ランキングマネージャ(rankingmanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "rankingmanager.h"
#include "logo.h"
#include "bg.h"
#include "manager.h"
#include "input.h"
#include "scenemanager.h"

//==========================================
//  コンストラクタ
//==========================================
CRankingManager::CRankingManager()
{
	m_nCntScene = 0;
}

//==========================================
//  デストラクタ
//==========================================
CRankingManager::~CRankingManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CRankingManager::Init(void)
{
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.2f, 0.0f), CLogo::RANKING);

	//背景の生成
	CBg::Create();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CRankingManager::Uninit(void)
{

}

//==========================================
//  更新処理
//==========================================
void CRankingManager::Update(void)
{
	//シーンの経過時間を加算
	m_nCntScene++;

	//画面遷移
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || m_nCntScene >= 600)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::TITLE);
		return;
	}
}

//==========================================
//  描画処理
//==========================================
void CRankingManager::Draw(void)
{

}
