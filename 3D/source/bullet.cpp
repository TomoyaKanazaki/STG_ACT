//==========================================
//
//  バレットクラス(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "debugproc.h"
#include "texture.h"
#include "effect.h"
#include "collision.h"

//==========================================
//  マクロ定義
//==========================================
#define BULLET_SPEED (10.0f) //弾速
#define BULLET_LIFE (256) //寿命
#define HOMING_LENGTH (200.0f) //ホーミング判定距離
#define HOMING_POWER (0.2f) //ホーミングの強さ
#define HOMING_TIMER (30) //ホーミング時間
#define HIT_LENGTH (20.0f) //ヒット判定距離

//==========================================
//  コンストラクタ
//==========================================
CBullet::CBullet()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = BULLET_LIFE;
	m_nHomingCounter = 0;
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
	//ホーミングターゲットの位置を保存する変数
	D3DXVECTOR3 Target;

	//ホーミング処理
	if (Collision::CollisionEnemy(m_pos, HOMING_LENGTH, false, &Target))
	{
		if (m_nHomingCounter <= HOMING_TIMER)
		{
			//ホーミングムーブ
			D3DXVECTOR3 move = Target - m_pos;

			//移動量の正規化
			D3DXVec3Normalize(&move, &move);

			//移動量の適応
			D3DXVECTOR3 moveDiff = m_move - move;
			m_move -= moveDiff * HOMING_POWER;

			//時間を加算する
			m_nHomingCounter++;
		}
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
	CEffect::Create(m_pos, m_size, m_rot, D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f), 10);

	//更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CBullet::Draw(void)
{
	//描画
	CObject3D::Draw();
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
