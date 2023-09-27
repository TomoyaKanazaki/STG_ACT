//==========================================
//
//  的クラス(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "debugproc.h"
#include "renderer.h"
#include "particle.h"
#include "effect.h"
#include "texture.h"
#include "sound.h"

//==========================================
//  コンストラクタ
//==========================================
CTarget::CTarget(int nPriority) : CObject3D(nPriority)
{
	m_fDistance = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
CTarget::~CTarget()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTarget::Init()
{
	//中心との距離から座標を設定する
	m_pos = D3DXVECTOR3
	(
		sinf(m_rot.y) * m_fDistance,
		0.0f,
		cosf(m_rot.y) * m_fDistance
	);

	//初期化
	CObject3D::Init();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CTarget::Uninit()
{
	//終了
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTarget::Update()
{
	//角度を更新
	m_rot.y -= 0.001f;

	//角度の補正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	//中心との距離から座標を設定する
	m_pos = D3DXVECTOR3
	(
		sinf(m_rot.y) * m_fDistance,
		0.0f,
		cosf(m_rot.y) * m_fDistance
	);

	//当たり判定
	D3DXVECTOR3 pos;
	if (CObject3D::Collision(CObject::TYPE_BULLET_ENEMY, &pos))
	{
		CManager::GetSound()->Play(CSound::SOUND_LABEL_EXPLOSION);

		//パーティクルを呼び出し
		CParticle::Create(pos, D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(0.98f, 0.87f, 0.28f, 0.5f), 10, 30, 10, 5);
	}

	//更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CTarget::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//描画
	CObject3D::Draw();

	//ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CTarget *CTarget::Create(D3DXVECTOR3 size, float fRot, float fDistance)
{
	//インスタンス生成
	CTarget *pTarget = NULL;

	//NULLチェック
	if (pTarget == NULL)
	{
		pTarget = new CTarget;
	}

	//各種情報の保存
	pTarget->m_size = size;
	pTarget->m_rot.y = fRot;
	pTarget->m_fDistance = fDistance;

	//初期化
	if (pTarget != NULL)
	{
		pTarget->Init();
	}

	//テクスチャを割り当て
	pTarget->BindTexture(CManager::GetTexture()->GetAddress(CTexture::TARGET));

	//ポインタを返す
	return pTarget;
}
