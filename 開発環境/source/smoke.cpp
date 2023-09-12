//==========================================
//
//  煙のクラス(smoke.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "smoke.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CSmoke::CSmoke(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CSmoke::~CSmoke()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CSmoke::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//ビルボードに設定する
	SwitchBillboard();

	//タイプの設定
	SetType(TYPE_EFFECT);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CSmoke::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CSmoke::Update(void)
{
	//寿命を減らす
	m_nLife--;

	//寿命がなくなったら削除する
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	//サイズを小さくする
	m_size.x -= m_vecDeffSize.x * m_fLifeRatio;
	m_size.y -= m_vecDeffSize.y * m_fLifeRatio;
	m_size.z -= m_vecDeffSize.z * m_fLifeRatio;

	//移動量を加算する
	m_pos += m_move;

	//慣性による移動の停止
	m_move.x += (0.0f - m_move.x) * 0.3f;
	m_move.z += (0.0f - m_move.z) * 0.3f;

	//更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CSmoke::Draw(void)
{
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

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

	//ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CSmoke * CSmoke::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nLife)
{
	//インスタンス生成
	CSmoke *pSmoke = new CSmoke;

	if (pSmoke == NULL)
	{
		assert(false);
		return NULL;
	}

	//各種情報を設定する
	pSmoke->m_pos = pos;
	pSmoke->m_pos.y = 10.0f;
	pSmoke->m_size = size;

	//初期化
	pSmoke->Init();
	pSmoke->SetCol(col);


	//テクスチャを割り当てる
	pSmoke->BindTexture(CManager::GetTexture()->GetAddress(CTexture::SMOKE));

	//デフォルトサイズを保存する
	pSmoke->m_vecDeffSize = size;

	//寿命を設定する
	pSmoke->m_nLife = nLife;
	pSmoke->m_fLifeRatio = 1.0f / nLife;

	//ポインタを返す
	return pSmoke;
}
