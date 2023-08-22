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
#include "bullet_normal.h"
#include "bullet_homing.h"

//==========================================
//  マクロ定義
//==========================================
#define BULLET_SPEED (10.0f) //弾速
#define BULLET_LIFE (256) //寿命
#define HIT_LENGTH (20.0f) //ヒット判定距離

//==========================================
//  コンストラクタ
//==========================================
CBullet::CBullet(int nPriority) : CObject3D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = BULLET_LIFE;
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
	//消滅条件
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	//敵との接触
	if (m_user == CBullet::PLAYER)
	{
		if (Collision::CollisionEnemy(m_pos, HIT_LENGTH, true))
		{
			Uninit();
			return;
		}
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
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, USER user, TYPE type)
{
	//インスタンス生成
	CBullet *pBullet = NULL;

	//NULLチェック
	if (pBullet == NULL)
	{
		//メモリを確保
		switch (type)
		{
		case NORMAL_BULLET:

			pBullet = new CBulletNormal;
			break;

		case HOMING_BULLET:

			pBullet = new CBulletHoming;
			break;

		default:
			break;
		}
	}

	if (pBullet == NULL)
	{
		return NULL;
	}

	//値を設定
	pBullet->m_user = user;
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
