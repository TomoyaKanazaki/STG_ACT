//==========================================
//
//  ゲームマネージャクラス(gamemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gamemanager.h"
#include "manager.h"
#include "sound.h"
#include "object_fan.h"
#include "player.h"
#include "enemy_manager.h"
#include "light.h"
#include "camera.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"
#include "scenemanager.h"
#include "model.h"
#include "renderer.h"
#include "target.h"
#include "enemy.h"
#include "debugproc.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CGameManager::STATE CGameManager::m_State = NONE;
CPlayer *CGameManager::m_pPlayer = NULL;
CObject_Fan *CGameManager::m_pFan = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CTarget *CGameManager::m_pTarget = NULL;
CEnemyManager *CGameManager::m_pEnemy = NULL;

//==========================================
//  コンストラクタ
//==========================================
CGameManager::CGameManager()
{
	m_State = NONE;
}

//==========================================
//  デストラクタ
//==========================================
CGameManager::~CGameManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CGameManager::Init(void)
{
	//床の生成
	m_pFan = CObject_Fan::Create(D3DXVECTOR3(0.0f, 0.01f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 2000.0f);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//エネミーマネージャの生成
	m_pEnemy = CEnemyManager::Create();

	//カメラの生成
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
		m_pCamera->Init();
	}

	//ライトの生成
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//ターゲットを生成
	m_pTarget = CTarget::Create();

	//BGMの再生
	//CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CGameManager::Uninit(void)
{
	//カメラの終了、破棄
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

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
void CGameManager::Update(void)
{
#if _DEBUG
	//画面遷移テスト
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) && CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RESULT);
		return;
	}
#endif

	//カメラの更新
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//ライトの更新
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	//フェーズ移行
	CManager::GetDebugProc()->Print("撃破数 : %d\n", CEnemyManager::GetDeth());
	CManager::GetDebugProc()->Print("フェーズ : %d\n", m_State);

	if (CEnemyManager::GetDeth() >= m_State * 10 && m_State != BOSS_CREAR)
	{
		//フェーズを進める
		m_State = (CGameManager::STATE)((int)m_State + 1);

		//敵をリセット
		for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
		{
			//オブジェクトを取得
			CObject *pObj = CObject::GetTop(nCntPriority);

			//NULLチェック
			while (pObj != NULL)
			{
				//次のアドレスを保存
				CObject *pNext = pObj->GetNext();

				//ボスの場合
				if (pObj->GetType() != CObject::TYPE_ENEMY)
				{
					//次のアドレスにずらす
					pObj = pNext;
					continue;
				}

				//敵を消す
				pObj->Uninit();

				//次のアドレスにずらす
				pObj = pNext;
			}
		}

		//撃破数をリセット
		CEnemyManager::ResetDeth();

		if (m_State == BOSS_ATTACK)
		{
			for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
			{
				//オブジェクトを取得
				CObject *pObj = CObject::GetTop(nCntPriority);

				//NULLチェック
				while (pObj != NULL)
				{
					//次のアドレスを保存
					CObject *pNext = pObj->GetNext();

					//ボスの場合
					if (pObj->GetType() != CObject::TYPE_BOSS)
					{
						//次のアドレスにずらす
						pObj = pNext;
						continue;
					}

					//ボスを撃破し画面遷移する
					pObj->Uninit();
					break;
				}
			}
		}
	}

	//遷移
	if (m_State == BOSS_CREAR)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RESULT);
	}
}

//==========================================
//  描画処理
//==========================================
void CGameManager::Draw(void)
{

}
