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
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	SwitchBillboard();

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
	m_pos += CManager::GetMouse()->GetMouseMove() * 500.0f;
	CManager::GetDebugProc()->Print("ターゲット座標 : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);
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
CTarget *CTarget::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//インスタンス生成
	CTarget *pTarget = new CTarget;

	if (pTarget == NULL)
	{
		assert(false);
		return NULL;
	}

	//各種情報を設定する
	pTarget->m_pos = pos;
	pTarget->m_pos.y = 30.0f;
	pTarget->m_size = size;

	//初期化
	pTarget->Init();

	//テクスチャを割り当てる
	pTarget->BindTexture(CManager::GetTexture()->GetAddress(CTexture::TARGET));

	//ポインタを返す
	return pTarget;
}
