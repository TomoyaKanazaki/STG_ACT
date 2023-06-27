//==========================================
//
//  ターゲットクラス(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "renderer.h"
#include "debugproc.h"

//==========================================
//  マクロ定義
//==========================================
#define TARGET_RANGE (-250.0f) //ターゲットの距離

//==========================================
//  コンストラクタ
//==========================================
CTarget::CTarget()
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

	//ビルボードに設定する
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
	//情報を更新
	m_rot = CManager::GetPlayer()->GetRot();
	m_pos = D3DXVECTOR3
	(
		CManager::GetPlayer()->GetPos().x + sinf(m_rot.y) * TARGET_RANGE,
		10.0f,
		CManager::GetPlayer()->GetPos().z + cosf(m_rot.y) * TARGET_RANGE
	);

	//デバッグ表示
	CManager::GetDebugProc()->Print("ターゲット座標 : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);
	CManager::GetDebugProc()->Print("ターゲット方向 : ( %f, %f, %f )\n", m_rot.x, m_rot.y, m_rot.z);

	//更新
	CObject3D::Update();
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

	//ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CTarget *CTarget::Create(const D3DXVECTOR3 size)
{
	//インスタンス生成
	CTarget *pTarget = NULL;

	//NULLチェック
	if (pTarget == NULL)
	{
		//メモリを確保
		pTarget = new CTarget;
	}

	if (pTarget == NULL)
	{
		return NULL;
	}

	//値を設定
	pTarget->m_size = size;
	pTarget->m_rot = CManager::GetPlayer()->GetRot();
	pTarget->m_pos = D3DXVECTOR3
	(
		CManager::GetPlayer()->GetPos().x + sinf(pTarget->m_rot.y) * TARGET_RANGE,
		10.0f,
		CManager::GetPlayer()->GetPos().z + cosf(pTarget->m_rot.y) * TARGET_RANGE
	);

	//初期化
	pTarget->Init();

	//テクスチャを割り当てる
	pTarget->BindTexture(CManager::GetTexture()->GetAddress(3));

	//ポインタを返す
	return pTarget;
}
