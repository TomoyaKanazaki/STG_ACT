//==========================================
//
//  普通の敵(enemy_normal.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_normal.h"
#include "model.h"
#include "motion.h"
#include "input.h"
#include "collision.h"
#include "gamemanager.h"
#include "object_fan.h"
#include "player.h"

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Normal::CEnemy_Normal(int nPriority) : CEnemy(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemy_Normal::~CEnemy_Normal()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy_Normal::Init(void)
{
	//タイプの設定
	SetType(CObject::TYPE_NORMAL_ENEMY);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::NORMAL_LAYER);

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

	CEnemy::Init();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemy_Normal::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy_Normal::Update(void)
{
	//移動の処理
	if (CGameManager::GetFan()->OnMesh(m_pos))
	{
		if (this->GetType() == CObject::TYPE_NORMAL_ENEMY) //プレイヤー追いかけ
		{
			//移動
			Move();

			//プレイヤーを弾く
			if (Collision::CollisionPlayer(m_pos, 30.0f))
			{
				CGameManager::GetPlayer()->SetMove(m_move * 10.0f);
			}
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
				this->SetType(CObject::TYPE_NORMAL_ENEMY);
			}
		}
	}

	//床から落ちる
	if (!CGameManager::GetFan()->OnMesh(m_pos))
	{
		m_move.y -= 1.0f;
	}

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy_Normal::Draw(void)
{
	CEnemy::Draw();
}
