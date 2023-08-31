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
	//外部ファイルから読み込み
	m_vecError = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	m_nNumEnemy = 15;

	//ボスを配置
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_BOSS);

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
	m_nTime++;
	if (m_nTime % 60 == 0)
	{
		for (int nCntEnemy = 0; nCntEnemy < m_nNumEnemy; nCntEnemy++)
		{
			//生成中心座標を生成
			m_pos = D3DXVECTOR3((float)(rand() % 600 - 300), 0.0f, 0.0f);
			m_pos = D3DXVECTOR3(m_pos.x, 0.0f, -600.0f);

			//敵を生成
			CEnemy::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_NORMAL);
		}
	}

#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetPress(DIK_E))
	{
		for (int nCntEnemy = 0; nCntEnemy < m_nNumEnemy; nCntEnemy++)
		{
			//生成中心座標を生成
			m_pos = D3DXVECTOR3((float)(rand() % 600 - 300), 0.0f, 0.0f);
			m_pos = D3DXVECTOR3(m_pos.x, 0.0f, -600.0f);

			//敵を生成
			CEnemy::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_NORMAL);
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
		fread(m_pCreateData, sizeof(CreateData), m_nNumData, pFile);

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
