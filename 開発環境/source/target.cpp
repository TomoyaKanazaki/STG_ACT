//==========================================
//
//  ロックオンクラス(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include "renderer.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CTarget::mc_fRate = 80.0f;

//==========================================
//  コンストラクタ
//==========================================
CTarget::CTarget(int nPriority) : CObject2D(nPriority)
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
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	m_size = D3DXVECTOR3(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f, 0.0f);

	if (FAILED(CObject2D::Init()))
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
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTarget::Update(void)
{
	//移動
	D3DXVECTOR3 move = CManager::GetMouse()->GetMouseMove();
	m_pos += move * mc_fRate;

	//更新
	CObject2D::Update();
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
	CObject2D::Draw();

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
