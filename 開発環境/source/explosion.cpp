//==========================================
//
//  爆発クラス(explosion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "explosion.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"

//==========================================
//  コンストラクタ
//==========================================
CExplosion::CExplosion(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CExplosion::~CExplosion()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CExplosion::Init(void)
{
	CObject3D_Anim::Init();
	CObject3D::SwitchBillboard();
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CExplosion::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CExplosion::Update(void)
{
	CObject3D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CExplosion::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D_Anim::Draw();

	//アルファブレンディングの設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

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
CExplosion *CExplosion::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nPattern, int nInterval, bool bLoop, UVTYPE type)
{
	//インスタンス生成
	CExplosion *pExplosion = new CExplosion;

	if (pExplosion == NULL)
	{
		assert(false);
		return NULL;
	}

	//各種情報を設定する
	pExplosion->m_pos = pos;
	pExplosion->m_size = size;
	pExplosion->m_rot = rot;

	//アニメーション情報を設定する
	pExplosion->SetAnim(nPattern, nInterval, bLoop, type);

	//初期化
	pExplosion->Init();

	//テクスチャを割り当てる
	pExplosion->BindTexture(CManager::GetTexture()->GetAddress(CTexture::EXPLOSION));

	//デフォルトサイズを保存する
	pExplosion->m_size = size;

	//ポインタを返す
	return pExplosion;
}
