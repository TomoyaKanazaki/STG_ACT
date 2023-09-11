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
#include "motion.h"
#include "particle.h"
#include "enemy_manager.h"
#include "object_fan.h"
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"

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
	//タイプの設定
	SetType(CObject::TYPE_ENEMY);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::ENEMY_LAYER);

	//モデル用のメモリの確保
	if (m_ppModel == NULL)
	{
		m_ppModel = new CModel*[m_pLayer->nNumModel];
	}

	//必要なモデルを生成
	for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
	{
		//空にする
		m_ppModel[nCnt] = NULL;

		//親が存在しない場合
		if (m_pLayer->pParentID[nCnt] == -1)
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt]);
		}
		else
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt], m_ppModel[m_pLayer->pParentID[nCnt]]);
		}
	}

	//モーション情報の生成
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
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
	//前回の座標を保存する
	m_oldPos = m_pos;

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
	
	//移動量の適用
	m_pos += m_move;

	//落ちたら死ぬ
	if (m_pos.y < -5000.0f)
	{
		//パーティクルを呼び出し
		CParticle::Create(m_pos, D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(0.98f, 0.87f, 0.28f, 0.5f), 10, 30, 10, 5);

		Uninit();
	}

	//床から落ちる
	if (!CGameManager::GetFan()->OnMesh(m_pos))
	{
		m_move.y -= 1.0f;
		return;
	}

	//移動の処理
	if (this->GetType() == CObject::TYPE_ENEMY) //プレイヤー追いかけ
	{
		//移動
		Move();

		//プレイヤーを殺す
		Collision::CollisionPlayer(m_pos, 30.0f);
	}
	else
	{
		//慣性による移動の停止
		m_move.x += (0.0f - m_move.x) * 0.1f;
		m_move.z += (0.0f - m_move.z) * 0.1f;

		//連鎖の判定
		Chain();

		//時間のカウント
		m_nCntBullet++;

		//一定時間経過で敵に戻る
		if (m_nCntBullet >= 30 || (fabsf(m_move.x) <= 0.1f && fabsf(m_move.z) <= 0.1f))
		{
			m_nCntBullet = 0;
			this->SetType(CObject::TYPE_ENEMY);
		}
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
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CEnemy *pEnemy = NULL;

	//NULLチェック
	if (pEnemy == NULL)
	{
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

			if ((pObj->GetType() == CObject::TYPE_BULLET_ENEMY || pObj->GetType() == CObject::TYPE_ENEMY) && pObj != this) //敵の場合
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

			if ((pObj->GetType() == CObject::TYPE_BULLET_ENEMY || pObj->GetType() == CObject::TYPE_ENEMY) && pObj != this)
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

					//衝突対象は連鎖しない弾になる
					pObj->SetType(CObject::TYPE_BULLET_ENEMY);

					//衝突対象の速度を取得
					D3DXVECTOR3 moveObj = pObj->GetMove();

					//衝突対象の移動量と自身の移動量の差分を求める
					D3DXVECTOR3 vecSab = m_move - moveObj;

					//前回座標
					D3DXVECTOR3 vecToOld = m_oldPos - posObj;

					//ベクトルを正規化
					D3DXVec3Normalize(&vecToOld, &vecToOld);

					//ベクトルの内積
					float fDot = D3DXVec3Dot(&vecSab, &vecToOld);

					//反発定数
					D3DXVECTOR3 vecConst = (fDot * 0.5f) * vecToOld;

					//衝突後速度ベクトルの算出
					m_move = (vecConst + m_move);
					pObj->SetMove(vecConst + moveObj);

					//衝突後位置の算出
					m_pos = m_pos + (m_move * 3.0f);
					pObj->SetPos(posObj + (pObj->GetMove() * 3.0f));
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
