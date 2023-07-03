//==========================================
//
//  エネミークラス(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <windows.h>
#include "enemy.h"
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "sound.h"
#include "debugproc.h"
#include "model.h"
#include "shadow.h"
#include "motion.h"

//==========================================
//  マクロ定義
//==========================================
#define TXTFILENAME_ENEMY "data\\TXT\\EnemyData.txt" //エネミー情報を持ったテキストファイルのパス

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_nLife = 10;
	m_fSpeed = 0.0f;
	m_apModel = NULL;
	m_bRand = true;
}

//==========================================
//  デストラクタ
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy::Init(void)
{
	//タイプの設定
	SetType(CObject::TYPE_ENEMY);

	//実体を生成
	Load();

	//影を生成
	m_pShadow = CShadow::Create(m_pos, m_size, m_rot);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemy::Uninit(void)
{
	//メモリを開放する
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		if (m_apModel != NULL)
		{
			if (m_apModel[nCnt] != NULL)
			{
				m_apModel[nCnt]->Uninit();
			}

			delete m_apModel;
			m_apModel = NULL;
		}
	}

	//影の削除
	m_pShadow->Uninit();

	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CEnemy::Update(void)
{
	//移動量の適用
	m_pos += m_move;

	//実体を動かす
	m_apModel[0]->SetTransform(m_pos, m_rot);

	//影の情報を更新する
	m_pShadow->SetTransform(m_pos, m_rot);

	//死亡判定
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
}

//==========================================
//  描画処理
//==========================================
void CEnemy::Draw()
{

}

//==========================================
//  オブジェクト生成処理
//==========================================
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, CEnemy::TYPE type)
{
	//インスタンス生成
	CEnemy *pEnemy = NULL;

	//NULLチェック
	if (pEnemy == NULL)
	{
		//メモリを確保
		pEnemy = new CEnemy;
	}

	//各種情報の保存
	pEnemy->m_pos = pos;
	pEnemy->m_size = size;
	pEnemy->m_rot = rot;

	//初期化
	if (pEnemy != NULL)
	{
		pEnemy->Init();
	}

	//ポインタを返す
	return pEnemy;
}

//==========================================
//  エネミー情報の読み込み
//==========================================
void CEnemy::Load(void)
{
	//ローカル変数宣言
	FILE *pFile; //ファイル名
	char aStr[256]; //不要な文字列の記録用

	//ファイルを読み取り専用で開く
	pFile = fopen(TXTFILENAME_ENEMY, "r");

	if (pFile != NULL)
	{
		//不要な文字列の読み込み
		for (int nCntDiscard = 0; nCntDiscard < 13; nCntDiscard++)
		{
			fscanf(pFile, "%s", &aStr[0]);
		}

		//モデル数の取得
		fscanf(pFile, "%d", &m_nNumModel);

		//モデルが存在する場合
		if (m_nNumModel > 0)
		{
			//必要なメモリを確保する
			if (m_apModel == NULL)
			{
				m_apModel = new CModel*[m_nNumModel];
			}
		}

		//メモリを確保した場合
		if (m_apModel != NULL)
		{
			//不要な文字列の読み込み
			for (int nCntDiscard = 0; nCntDiscard < 4; nCntDiscard++)
			{
				fscanf(pFile, "%s", &aStr[0]);
			}

			//各モデルを生成する
			for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
			{
				//モデル生成用変数
				D3DXVECTOR3 pos, size = D3DXVECTOR3(0.0f, 5.0f, 0.0f), rot;
				int nModelID, nParentID;

				//不要な文字列の読み込み
				for (int nCntDiscard = 0; nCntDiscard < 3; nCntDiscard++)
				{
					fscanf(pFile, "%s", &aStr[0]);
				}

				//位置情報を取得
				fscanf(pFile, "%f", &pos.x); fscanf(pFile, "%f", &pos.y); fscanf(pFile, "%f", &pos.z);

				//不要な文字列の読み込み
				fscanf(pFile, "%s", &aStr[0]);

				//角度を取得
				fscanf(pFile, "%f", &rot.x); fscanf(pFile, "%f", &rot.y); fscanf(pFile, "%f", &rot.z);

				//不要な文字列の読み込み
				fscanf(pFile, "%s", &aStr[0]);

				//使用するモデルの情報を取得
				fscanf(pFile, "%d", &nModelID);

				//不要な文字列の読み込み
				fscanf(pFile, "%s", &aStr[0]);

				//親の情報を取得
				fscanf(pFile, "%d", &nParentID);

				//取得した情報からモデルを生成
				if (nParentID == -1)
				{
					m_apModel[nCnt] = CModel::Create(pos, size, rot, nModelID);
				}
				else
				{
					m_apModel[nCnt] = CModel::Create(pos, size, rot, nModelID, m_apModel[nParentID]);
				}
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{

	}
}
