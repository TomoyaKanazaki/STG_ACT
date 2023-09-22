//==========================================
//
//  減算するタイマーのクラス(timer_sab.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "precompile.h"
#include "timer_sab.h"
#include "manager.h"
#include "scenemanager.h"
#include "debugproc.h"

//==========================================
//  コンストラクタ
//==========================================
CTimer_Sab::CTimer_Sab(int nPriority) : CTime(nPriority)
{
	m_nProgress = 0;
}

//==========================================
//  デストラクタ
//==========================================
CTimer_Sab::~CTimer_Sab()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTimer_Sab::Init(void)
{
	//初期値を代入
	m_nCurrent = m_nMax;

	return CTime::Init();
}

//==========================================
//  終了処理
//==========================================
void CTimer_Sab::Uninit(void)
{

}

//==========================================
//  更新処理
//==========================================
void CTimer_Sab::Update(void)
{
	//制限時間で遷移する
	if (m_nCurrent <= 0)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RESULT);
	}

	//経過時間を加算
	m_nProgress++;

	//現在時刻を計算
	m_nCurrent = m_nMax - (m_nProgress / 60);

	CManager::GetDebugProc()->Print("残り時間 : %d\n", m_nCurrent);

	CTime::Update();
}

//==========================================
//  描画処理
//==========================================
void CTimer_Sab::Draw(void)
{

}
