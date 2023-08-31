//==========================================
//
//  シャドークラス(shadow.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object_fan.h"
#include "gamemanager.h"

//==========================================
//  コンストラクタ
//==========================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CShadow::~CShadow()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CShadow::Init(void)
{
	//初期化
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//タイプの設定
	SetType(TYPE_SHADOW);

	//床に貼り付ける
	m_pos.y = 0.01f;

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CShadow::Update(void)
{
	m_pos.y = CGameManager::GetFan()->GetPos().y + 0.5f;

	//更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CShadow::Draw(void)
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

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//描画
	CObject3D::Draw();

	//アルファブレンディングの設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

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
CShadow *CShadow::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CShadow *pShadow = NULL;

	//NULLチェック
	if (pShadow == NULL)
	{
		//メモリを確保
		pShadow = new CShadow;
	}

	if (pShadow == NULL)
	{
		return NULL;
	}

	//値を設定
	pShadow->m_pos = pos;
	pShadow->m_size = size;
	pShadow->m_rot = rot;

	//初期化
	pShadow->Init();

	//テクスチャを割り当てる
	pShadow->BindTexture(CManager::GetTexture()->GetAddress(CTexture::EFFECT));

	//ポインタを返す
	return pShadow;
}

//==========================================
//  情報の設定処理
//==========================================
void CShadow::SetTransform(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos.x = pos.x;
	m_pos.z = pos.z;
	m_rot = rot;
}
