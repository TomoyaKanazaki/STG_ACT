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
#include "motion.h"
#include "particle.h"
#include "enemy_manager.h"
#include "object_fan.h"
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "enemy_normal.h"
#include "enemy_block.h"
#include "enemy_push.h"
#include "smoke.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CEnemy::mc_fSize = 75.0f;

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_nCntBullet = 0;
	m_nCombo = 1;
	m_fSpeed = 0.0f;
	m_ppModel = NULL;
	m_pLayer = NULL;
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

	//モーション情報の破棄
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//自分自身の破棄
	Release();
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

	//床から落ちる
	if (!CGameManager::GetFan()->OnMesh(m_pos))
	{
		m_move.y -= 1.0f;
	}

	//弾状態に煙を付ける
	if (this->GetType() == CObject::TYPE_BULLET_ENEMY)
	{
		CSmoke::Create(m_pos, m_size * 1.5f, D3DXCOLOR(1.0f, 1.0f - (0.12f * m_nCombo), 0.0f, 1.0f), 10);
	}

	//前回の座標を保存する
	m_oldPos = m_pos;
	
	//移動量の適用
	m_pos += m_move;

	//落ちたら死ぬ
	if (m_pos.y < -5000.0f)
	{
		//パーティクルを呼び出し
		CParticle::Create(m_pos, D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(0.98f, 0.87f, 0.28f, 0.5f), 10, 30, 10, 5);

		Uninit();
	}

	//敵同士の判定
	AvertEnemy();
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
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, ENEMY_TYPE type)
{
	//インスタンス生成
	CEnemy *pEnemy = NULL;

	//NULLチェック
	if (pEnemy == NULL)
	{
		switch (type)
		{
		case NORMAL:
			pEnemy = new CEnemy_Normal;
			break;
		case BLOCK:
			pEnemy = new CEnemy_Block;
			break;
		case PUSH:
			pEnemy = new CEnemy_Push;
			break;
		default:
			return NULL;
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

			if ((pObj->GetType() == CObject::TYPE_BULLET_ENEMY || pObj->GetType() == CObject::TYPE_NORMAL_ENEMY) && pObj != this) //敵の場合
			{
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
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}
}

//==========================================
//  連鎖の判定
//==========================================
void CEnemy::Chain(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//自分のアドレスを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			if ((pObj->GetType() == CObject::TYPE_BULLET_ENEMY || pObj->GetType() == CObject::TYPE_NORMAL_ENEMY) && pObj != this)
			{
				//現在の敵と自分を結ぶベクトルを取得する
				D3DXVECTOR3 posObj = pObj->GetPos();
				D3DXVECTOR3 vecToObj = m_pos - posObj;

				//ベクトルの大きさを算出
				float fLength = (vecToObj.x * vecToObj.x) + (vecToObj.z * vecToObj.z);

				//接触範囲内にいた場合
				if (fLength < mc_fSize * mc_fSize)
				{
					//コンボ数を加算
					m_nCombo++;

					//衝突対象は弾になる
					pObj->SetType(CObject::TYPE_BULLET_ENEMY);

					//衝突対象に移動量を押し付ける
					pObj->SetMove(m_move * 1.5f);

					//自分は敵に戻る
					this->SetType(CObject::TYPE_NORMAL_ENEMY);
					m_nCntBullet = 0;
				}
			}
			
			//次のアドレスにずらす
			pObj = pNext;
		}
	}
}

//==========================================
//  プレイヤーに向かう処理
//==========================================
void CEnemy::Move(void)
{
	//プレイヤーの座用を取得
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//プレイヤーに向かうベクトルを算出
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;

	//プレイヤーの方向を向く
	float fRot = atan2f(-vecToPlayer.x, -vecToPlayer.z);
	m_rot.y = fRot;

	//ベクトルを正規化
	vecToPlayer.y = 0.0f;
	D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

	//移動量を適用
	m_move = vecToPlayer * 5.0f;
}
