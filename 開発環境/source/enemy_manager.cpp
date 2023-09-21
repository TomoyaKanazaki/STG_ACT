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
	m_pCreater = NULL;
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
	//生成データを記録する
	m_pCreater = new CreateData[m_nNumData];
	for (int nCnt = 0; nCnt < m_nNumData; nCnt++)
	{
		m_pCreater[nCnt] = m_pCreateData[nCnt];
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemyManager::Uninit(void)
{
	//削除
	delete[] m_pCreater;
	m_pCreater = NULL;
	Release();
}

//==========================================
//  更新処理
//==========================================
void CEnemyManager::Update(void)
{
	//経過フレームを加算
	m_nTime++;

	//エネミーデータを参照
	for (int nCnt = 0; nCnt < m_nNumData; nCnt++)
	{
		//生成回数を参照する
		if (m_pCreater[nCnt].nCount > 0 || m_pCreater[nCnt].nCount == -1)
		{
			//生成フレームを参照する
			if (m_nTime % m_pCreater[nCnt].nInterval == 0)
			{
				//敵を生成
				CEnemy::Create(m_pCreater[nCnt].pos, D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), (CEnemy::ENEMY_TYPE)m_pCreater[nCnt].nType);

				//生成回数を減らす
				if (m_pCreater[nCnt].nCount != -1)
				{
					m_pCreater[nCnt].nCount--;
				}
			}
		}
	}

#ifdef _DEBUG
	//接近する敵
	if (CManager::GetKeyboard()->GetTrigger(DIK_1))
	{
		//敵を生成
		CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::NORMAL);
	}

	//止める敵
	if (CManager::GetKeyboard()->GetTrigger(DIK_2))
	{
		//敵を生成
		CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -1500.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::BLOCK);
	}

	//弾く敵
	if (CManager::GetKeyboard()->GetTrigger(DIK_3))
	{
		//敵を生成
		CEnemy::Create(D3DXVECTOR3(1500.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::PUSH);
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
