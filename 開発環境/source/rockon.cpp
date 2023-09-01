//==========================================
//
//  ロックオンクラス(rockon.cpp)
//  Author : Tomoya Kanzaki
//
//==========================================
#include "rockon.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CRockon::CRockon(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CRockon::~CRockon()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CRockon::Init(void)
{
	//大きさを設定する
	m_size = D3DXVECTOR3(50.0f, 0.0f, 50.0f);

	//初期化
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//ビルボードに設定する
	SwitchBillboard();

	//タイプの設定
	SetType(TYPE_ROCKON);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CRockon::Uninit(void)
{
	//終了
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CRockon::Update(void)
{
	//更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CRockon::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
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
}

//==========================================
//  生成処理
//==========================================
CRockon *CRockon::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	CRockon *pRockon = new CRockon;

	if (pRockon == NULL)
	{
		assert(false);
		return NULL;
	}

	//各種情報を設定する
	pRockon->m_pos = pos;

	//初期化
	pRockon->Init();

	//テクスチャを割り当てる
	pRockon->BindTexture(CManager::GetTexture()->GetAddress(CTexture::ROCKON));

	//ポインタを返す
	return pRockon;
}
