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

//==========================================
//  静的メンバ変数宣言
//==========================================
int CEnemy::m_nCntEnemy = 0;

//==========================================
//  マクロ定義
//==========================================
#define SPEED (2.0f) //移動速度
#define DETECTION (700.0f) //索敵範囲

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

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

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
	while (1)
	{
		if (m_pMotion == NULL)
		{
			m_pMotion = new CMotion;

			//モーション情報にモデルを追加する
			m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_SHOT);
		}
		else
		{
			break;
		}
	}

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

	//モーションのポインタを破棄
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
	//移動の処理
	Move();

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

	//モーションを更新する
	if (m_pMotion != NULL)
	{
		m_pMotion->Update();
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
//  移動処理
//==========================================
void CEnemy::Move(void)
{
	//慣性による移動の停止
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//プレイヤーの位置を取得
	D3DXVECTOR3 posTarget = CGameManager::GetPlayer()->GetPos();

	//プレイヤーに向かうベクトルを算出
	posTarget -= m_pos;

	//プレイヤーとの距離が近い場合
	if (posTarget.x * posTarget.x + posTarget.z * posTarget.z < DETECTION * DETECTION)
	{
		//Y座標への補正を削除する
		posTarget.y = 0.0f;

		//ベクトルの正規化
		D3DXVec3Normalize(&posTarget, &posTarget);

		//移動量を補正して適用
		m_move = posTarget * SPEED;
	}
}
