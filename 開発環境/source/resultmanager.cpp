//==========================================
//
//  リザルトマネージャ(resultmanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "resultmanager.h"
#include "manager.h"
#include "debugproc.h"
#include "scenemanager.h"
#include "input.h"
#include "logo.h"
#include "bg.h"
#include "debris.h"
#include "ranking.h"
#include "rank.h"
#include "score.h"
#include "sound.h"

//==========================================
//  コンストラクタ
//==========================================
CResultManager::CResultManager()
{
	m_nCntScene = 0;
	m_nRank = 0;
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
	//RESULTの表示
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.2f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.1f, 0.0f), CLogo::RESULT);

	//今回の順位の表示
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.35f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.1f, 0.0f), CLogo::RANK);

	//スコアの表示
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.7f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.1f, 0.0f), CLogo::RANK);

	//背景の生成
	CBg::Create();

	//順位の取得
	m_nRank = CRanking::GetRank();
	CRank::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.2f, 0.0f), m_nRank);

	//スコアの取得
	CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.85f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.2f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CScore::GetScore());

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
void CResultManager::Uninit(void)
{
	//BGMの停止
	CManager::GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CResultManager::Update(void)
{
	//シーン経過時間を加算
	m_nCntScene++;

	//画面遷移
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || m_nCntScene >= 1500)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::TITLE);
		CManager::GetSound()->Play(CSound::SOUND_LABEL_ENTER);
		return;
	}

	CManager::GetDebugProc()->Print("順位 : %d\n", m_nRank);
}

//==========================================
//  描画処理
//==========================================
void CResultManager::Draw(void)
{

}
