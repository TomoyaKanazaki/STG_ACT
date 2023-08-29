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
#include "particle.h"
#include "boss.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
int CEnemy::m_nDead = 0;
const float CEnemy::mc_fSize = 75.0f;

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

	//パーティクルを呼び出し
	CParticle::Create(m_pos, D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(0.98f, 0.87f, 0.28f, 0.5f), 10, 30, 10, 5);

	//自分自身の破棄
	Release();

	//撃破数を加算
	m_nDead++;
}

//==========================================
//  更新処理
//==========================================
void CEnemy::Update(void)
{
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

	//移動量の適用
	m_pos += m_move;
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

		case CEnemy::TYPE_BOSS:

			pEnemy = new CBoss;
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

//==========================================
//  敵同士がぶつかる判定
//==========================================
void CEnemy::AvertEnemy(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//自分のアドレスを取得
		CObject *pObj = this->GetNext();

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			if (pObj->GetType() != CObject::TYPE_ENEMY) //敵の場合
			{
				pObj = pNext;
				continue;
			}

			//現在の敵と自分を結ぶベクトルを取得する
			D3DXVECTOR3 posObj = pObj->GetPos();
			D3DXVECTOR3 vecToObj = m_pos - posObj;

			//ベクトルの大きさを算出
			float fLength = (vecToObj.x * vecToObj.x) + (vecToObj.z * vecToObj.z);

			//接触範囲内にいた場合
			if (fLength < mc_fSize * mc_fSize)
			{
				//接点座標を求める
				D3DXVECTOR3 contact = (posObj + m_pos) * 0.5f;

				//ベクトルの角度を求める
				float rotVector = atan2f(vecToObj.x, vecToObj.z);

				//x,zの補正値を求める
				D3DXVECTOR2 correction = { sinf(rotVector), cosf(rotVector) };

				//座標を補正する
				m_pos.x = correction.x * (mc_fSize * 0.5f) + contact.x;
				m_pos.z = correction.y * (mc_fSize * 0.5f) + contact.z;
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}
}
