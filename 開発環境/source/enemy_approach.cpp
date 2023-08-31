//==========================================
//
//  付いてくる敵のクラス(enemy_approach.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_approach.h"
#include "gamemanager.h"
#include "player.h"
#include "model.h"
#include "motion.h"

//==========================================
//  マクロ定義
//==========================================
#define SPEED (2.0f) //移動速度
#define DETECTION (10000.0f) //索敵範囲

//==========================================
//  コンストラクタ
//==========================================
CEnemyApproach::CEnemyApproach()
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyApproach::~CEnemyApproach()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyApproach::Init(void)
{
	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::ENEMY_APPROACH_LAYER);

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

	CEnemy::Init();
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemyApproach::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyApproach::Update(void)
{
	//移動
	Move();
	AvertEnemy();
	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemyApproach::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  移動処理
//==========================================
void CEnemyApproach::Move(void)
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

	//算出したベクトルから角度を算出
	float rotVector = atan2f(-posTarget.x, -posTarget.z);

	//算出した角度を自分の方向にする
	m_rot.y = rotVector;
}
