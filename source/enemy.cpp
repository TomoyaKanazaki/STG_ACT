//==========================================
//
//  エネミークラス(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <windows.h>
#include "enemy.h"
#include "player.h"
#include "gamemanager.h"
#include "renderer.h"
#include "effect.h"
#include "sound.h"
#include "debugproc.h"
#include "model.h"
#include "shadow.h"
#include "motion.h"
#include "item.h"
#include "motion.h"
#include "enemy_approach.h"
#include "enemy_shot.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
int CEnemy::m_nCntEnemy = 0;

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_fSpeed = 0.0f;
	m_ppModel = NULL;
	m_pLayer = NULL;
	m_pShadow = NULL;
	m_pMotion = NULL;
	m_bRand = true;
	m_nCntEnemy++;
}

//==========================================
//  デストラクタ
//==========================================
CEnemy::~CEnemy()
{
	m_nCntEnemy--;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy::Init(void)
{
	//タイプの設定
	SetType(CObject::TYPE_ENEMY);

	//影を生成
	if (m_pShadow == NULL)
	{
		m_pShadow = CShadow::Create(m_pos, m_size, m_rot);
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemy::Uninit(void)
{
	//モデルのポインタを破棄
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Uninit();
				m_ppModel[nCnt] = NULL;
			}
		}
		delete[] m_ppModel;
		m_ppModel = NULL;
	}

	//影のポインタを破棄
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
	}

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

	//実体を移動する
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				if (m_ppModel[nCnt]->GetParent() == NULL)
				{
					m_ppModel[nCnt]->SetTransform(m_pos, m_rot);
				}
			}
		}
	}

	//影の情報を更新する
	if (m_pShadow != NULL)
	{
		m_pShadow->SetTransform(m_pos, m_rot);
	}
	else
	{
		//再生成
		m_pShadow = CShadow::Create(m_pos, m_size, m_rot);
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
		switch (type)
		{
		case CEnemy::TYPE_NORMAL:

			pEnemy = new CEnemyApproach;
			break;

		case CEnemy::TYPE_SHOT:

			pEnemy = new CEnemyShot;
			break;

		default:
			return NULL;
			break;
		}
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
