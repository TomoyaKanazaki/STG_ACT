//==========================================
//
//  追尾弾のクラス(bullet_homing.cpp)
//  Author :Tomoya Kanazaki
//
//==========================================
#include "bullet_homing.h"
#include "collision.h"

//==========================================
//  マクロ定義
//==========================================
#define HOMING_LENGTH (200.0f) //ホーミング判定距離
#define HOMING_POWER (0.3f) //ホーミングの強さ
#define HOMING_TIMER (30) //ホーミング時間

//==========================================
//  コンストラクタ
//==========================================
CBulletHoming::CBulletHoming()
{
	m_Target.pObj = NULL;
	m_Target.nCounter = 0;
	m_Target.bHoming = false;
}

//==========================================
//  デストラクタ
//==========================================
CBulletHoming::~CBulletHoming()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBulletHoming::Init(void)
{
	CBullet::Init();
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CBulletHoming::Uninit(void)
{
	CBullet::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBulletHoming::Update(void)
{
	Follow();
	CBullet::Update();
}

//==========================================
//  描画処理
//==========================================
void CBulletHoming::Draw(void)
{
	CBullet::Draw();
}

//==========================================
//  追尾処理
//==========================================
void CBulletHoming::Follow(void)
{
	if (m_Target.bHoming)
	{
		if (m_Target.nCounter <= HOMING_TIMER)
		{
			if
				(
					m_Target.pObj->GetPos().x > -500.0f &&
					m_Target.pObj->GetPos().x < 500.0f &&
					m_Target.pObj->GetPos().z > -500.0f &&
					m_Target.pObj->GetPos().z < 500.0f
					)
			{
				//ホーミングムーブ
				D3DXVECTOR3 move = m_Target.pObj->GetPos() - m_pos;
				move.y = 0.0f;

				//移動量の正規化
				D3DXVec3Normalize(&move, &move);

				//移動量の適応
				D3DXVECTOR3 moveDiff = m_move - move;

				//一定時間経過していたら直撃する
				if (m_Target.nCounter > 20)
				{
					m_move -= moveDiff;
				}
				else
				{
					m_move -= moveDiff * HOMING_POWER;
				}

				//時間を加算する
				m_Target.nCounter++;
			}
			else
			{
				m_Target.bHoming = false;
			}
		}
	}
	else if (Collision::HomingEnemy(m_pos, HOMING_LENGTH, false, &m_Target.pObj) && m_Target.bHoming == false)
	{
		//ホーミングムーブ
		D3DXVECTOR3 move = m_Target.pObj->GetPos() - m_pos;
		move.y = 0.0f;

		//移動量の正規化
		D3DXVec3Normalize(&move, &move);

		//移動量の適応
		D3DXVECTOR3 moveDiff = m_move - move;
		m_move -= moveDiff * HOMING_POWER;

		//ホーミング時間のリセット
		m_Target.nCounter = 0;

		//ホーミング済フラグを立てる
		m_Target.bHoming = true;
	}
}
