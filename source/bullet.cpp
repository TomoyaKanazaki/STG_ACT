//==========================================
//
//  バレットクラス(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "texture.h"
#include "effect.h"
#include "collision.h"
#include "object.h"

//==========================================
//  マクロ定義
//==========================================
#define BULLET_SPEED (10.0f) //弾速
#define BULLET_LIFE (256) //寿命
#define HOMING_LENGTH (200.0f) //ホーミング判定距離
#define HOMING_POWER (0.3f) //ホーミングの強さ
#define HOMING_TIMER (30) //ホーミング時間
#define HIT_LENGTH (20.0f) //ヒット判定距離

//==========================================
//  コンストラクタ
//==========================================
CBullet::CBullet(int nPriority) : CObject3D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = BULLET_LIFE;
	m_Target.pObj = NULL;
	m_Target.nCounter = 0;
	m_Target.bHoming = false;
}

//==========================================
//  デストラクタ
//==========================================
CBullet::~CBullet()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBullet::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//タイプの設定
	SetType(TYPE_BULLET);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CBullet::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBullet::Update(void)
{
	//ホーミング処理
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

	//消滅条件
	if (m_nLife <= 0 || Collision::CollisionEnemy(m_pos, HIT_LENGTH, true))
	{
		Uninit();
		return;
	}

	//寿命を減らす
	m_nLife--;

	//移動量を加算する
	D3DXVec3Normalize(&m_move, &m_move);
	m_pos += m_move * BULLET_SPEED;

	//エフェクトを呼ぶ
	CEffect::Create(m_pos, m_size, D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f), 10);

	//更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CBullet::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//描画
	CObject3D::Draw();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	//インスタンス生成
	CBullet *pBullet = NULL;

	//NULLチェック
	if (pBullet == NULL)
	{
		//メモリを確保
		pBullet = new CBullet;
	}

	if (pBullet == NULL)
	{
		return NULL;
	}

	//値を設定
	pBullet->m_pos = pos;
	pBullet->m_size = size;
	pBullet->m_move = move;
	pBullet->m_move.x = move.x * BULLET_SPEED;
	pBullet->m_move.z = move.z * BULLET_SPEED;
	pBullet->m_rot.x = D3DX_PI * 0.5f;

	//初期化
	pBullet->Init();

	//テクスチャを割り当てる
	pBullet->BindTexture(CManager::GetTexture()->GetAddress(4));

	//ポインタを返す
	return pBullet;
}
