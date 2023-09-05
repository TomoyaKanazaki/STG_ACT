//==========================================
//
//  ロックオンクラス(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "gamemanager.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CTarget::mc_fRate = 300.0f;
const float CTarget::mc_fDistance = 1000.0f;

//==========================================
//  コンストラクタ
//==========================================
CTarget::CTarget(int nPriority) : CObject3D(nPriority)
{

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
HRESULT CTarget::Init(void)
{
	//値を設定する
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();
	D3DXVECTOR3 rotPlayer = CGameManager::GetPlayer()->GetRot();
	m_pos = D3DXVECTOR3(posPlayer.x - (sinf(rotPlayer.y) * mc_fDistance), 0.0f, posPlayer.z - (cosf(rotPlayer.y) * mc_fDistance));
	m_size = D3DXVECTOR3(mc_fRate, 0.0f, mc_fRate);
	m_rot.y = rotPlayer.y;
	m_rot.x = D3DX_PI * 0.5f;

	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//タイプの設定
	SetType(TYPE_TARGET);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CTarget::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTarget::Update(void)
{
	//移動
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();
	D3DXVECTOR3 rotPlayer = CGameManager::GetPlayer()->GetRot();
	m_pos = D3DXVECTOR3(posPlayer.x - (sinf(rotPlayer.y) * mc_fDistance), 0.0f, posPlayer.z - (cosf(rotPlayer.y) * mc_fDistance));
	m_rot.y = rotPlayer.y;

	//更新
	CObject3D::Update();

	CManager::GetDebugProc()->Print("ターゲットの座標 : %f, %f, %f\n", m_pos.x, m_pos.y, m_pos.z);

}

//==========================================
//  描画処理
//==========================================
void CTarget::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//描画
	CObject3D::Draw();

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CTarget *CTarget::Create(void)
{
	//インスタンス生成
	CTarget *pTarget = new CTarget;

	if (pTarget == NULL)
	{
		assert(false);
		return NULL;
	}

	//初期化
	pTarget->Init();

	//テクスチャを割り当てる
	pTarget->BindTexture(CManager::GetTexture()->GetAddress(CTexture::TARGET));

	//ポインタを返す
	return pTarget;
}
