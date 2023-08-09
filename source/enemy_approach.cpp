//==========================================
//
//  付いてくる敵のクラス(enemy_approach.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_approach.h"
#include "gamemanager.h"
#include "player.h"

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
}
