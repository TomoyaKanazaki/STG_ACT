//==========================================
//
//  エネミーマネージャクラス(enemy_manager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_manager.h"
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "gamemanager.h"
#include "player.h"

//==========================================
//  マクロ定義
//==========================================
#define ENEMY_FILEPASS "data\\BIN\\EnemyData.bin"

//==========================================
//  静的メンバ変数宣言
//==========================================
int CEnemyManager::m_nDead = 0;
int CEnemyManager::m_nNumData = 0;
CEnemyManager::CreateData *CEnemyManager::m_pCreateData = NULL;

//==========================================
//  コンストラクタ
//==========================================
CEnemyManager::CEnemyManager()
{
	m_vecError = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		m_nPopCounter[nCnt] = 0;
		m_bPop[nCnt] = false;
	}
	m_nNumEnemy = 0;
	m_nTime = 0;
}

//==========================================
//  デストラクタ
//==========================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyManager::Init(void)
{
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemyManager::Uninit(void)
{
	Release();
}

//==========================================
//  更新処理
//==========================================
void CEnemyManager::Update(void)
{
	//経過フレームを加算
	//m_nTime++;

	//現在のフェーズを取得
	int nFaze = (int)CGameManager::GetState();

	//エネミーデータを参照
	for (int nCnt = 0; nCnt < m_nNumData; nCnt++)
	{
		//生成されるフェーズを参照する
		if (nFaze == m_pCreateData[nCnt].fase)
		{
			//生成回数を参照する
			if (m_pCreateData[nCnt].nCount > 0 || m_pCreateData[nCnt].nCount == -1)
			{
				//生成フレームを参照する
				if (m_nTime % m_pCreateData[nCnt].nInterval == 0)
				{
					//敵を生成
					CEnemy::Create(m_pCreateData[nCnt].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), (CEnemy::TYPE)m_pCreateData[nCnt].type);

					//生成回数を減らす
					if (m_pCreateData[nCnt].nCount != -1)
					{
						m_pCreateData[nCnt].nCount--;
					}
				}
			}
		}
	}

#ifdef _DEBUG
	//接近する敵
	if (CManager::GetKeyboard()->GetTrigger(DIK_E))
	{
		for (int nCntEnemy = 0; nCntEnemy < 3; nCntEnemy++)
		{
			//生成中心座標を生成
			m_pos = D3DXVECTOR3((float)(rand() % 600 - 300), 0.0f, 0.0f);
			m_pos = D3DXVECTOR3(m_pos.x, 0.0f, -600.0f);

			//敵を生成
			CEnemy::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_NORMAL);
		}
	}
	
	//射撃する敵
	if (CManager::GetKeyboard()->GetTrigger(DIK_Q))
	{
		for (int nCntEnemy = 0; nCntEnemy < 3; nCntEnemy++)
		{
			//生成中心座標を生成
			m_pos = D3DXVECTOR3((float)(rand() % 600 - 300), 0.0f, 0.0f);
			m_pos = D3DXVECTOR3(m_pos.x, 0.0f, -600.0f);

			//敵を生成
			CEnemy::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_SHOT);
		}
	}
#endif
}

//==========================================
//  描画処理
//==========================================
void CEnemyManager::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CEnemyManager *CEnemyManager::Create(void)
{
	//インスタンス生成
	CEnemyManager *pEnemyManager = NULL;

	//NULLチェック
	if (pEnemyManager == NULL)
	{
		//メモリを確保
		pEnemyManager = new CEnemyManager;
	}

	//初期化
	if (pEnemyManager != NULL)
	{
		pEnemyManager->Init();
	}

	//ポインタを返す
	return pEnemyManager;
}

//==========================================
//  読み込み処理
//==========================================
void CEnemyManager::Load(void)
{
	//ローカル変数宣言
	FILE *pFile; //ファイル名

	//ファイルを読み取り専用で開く
	pFile = fopen(ENEMY_FILEPASS, "rb");

	if (pFile != NULL)
	{
		//保存されているデータ数を取得する
		fread(&m_nNumData, sizeof(int), 1, pFile);

		//必要数のメモリを確保する
		m_pCreateData = new CreateData[m_nNumData];

		//保存されているデータを全て読み込む
		for (int nCnt = 0; nCnt < m_nNumData; nCnt++)
		{
			fread(&m_pCreateData[nCnt], sizeof(CreateData), 1, pFile);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}

//==========================================
//  読み込み処理
//==========================================
void CEnemyManager::Load(char *aPass)
{
	//ファイルを書き込み専用で開く
	FILE *pFile = fopen(aPass, "rb");

	if (pFile != NULL)
	{
		//保存されているデータ数を取得する
		fread(&m_nNumData, sizeof(int), 1, pFile);

		//必要数のメモリを確保する
		m_pCreateData = new CreateData[m_nNumData];

		//保存されているデータを全て読み込む
		for (int nCnt = 0; nCnt < m_nNumData; nCnt++)
		{
			fread(&m_pCreateData[nCnt], sizeof(CreateData), 1, pFile);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}

//==========================================
//  データの破棄
//==========================================
void CEnemyManager::Unload(void)
{
	if (m_pCreateData != NULL)
	{
		delete[] m_pCreateData;
		m_pCreateData = NULL;
	}
}
