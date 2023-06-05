//==========================================
//
//  エフェクトクラス(effect.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture;
int CEffect::m_nNum;

//==========================================
//  コンストラクタ
//==========================================
CEffect::CEffect()
{
	m_nLife = 0;
}

//==========================================
//  デストラクタ
//==========================================
CEffect::~CEffect()
{
	
}

//==========================================
//  初期化処理
//==========================================
HRESULT CEffect::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//タイプの設定
	SetType(TYPE_EFFECT);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEffect::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEffect::Update(void)
{
	//寿命を減らす
	m_nLife--;

	//寿命がなくなったら削除する
	if (m_nLife <= 0)
	{
		this->Release();
		return;
	}

	//サイズを小さくする
	m_size.x -= m_vecDeffSize.x * m_fLifeRatio;
	m_size.y -= m_vecDeffSize.y * m_fLifeRatio;

	//更新
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CEffect::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//描画
	CObject2D::Draw();

	//アルファブレンディングをの設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==========================================
//  読み込み処理
//==========================================
HRESULT CEffect::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/effect.jpg", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  テクスチャの終了処理
//==========================================
void CEffect::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==========================================
//  生成処理
//==========================================
CEffect *CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nLife)
{
	//インスタンス生成
	CEffect *pEffect = NULL;

	//NULLチェック
	if (pEffect == NULL)
	{
		//メモリを確保
		pEffect = new CEffect;
	}

	//初期化
	if (pEffect != NULL)
	{
		pEffect->Init(pos, size, rot);
	}

	//テクスチャを割り当てる
	pEffect->BindTexture(m_pTexture);

	//デフォルトサイズを保存する
	pEffect->m_vecDeffSize = size;

	//寿命を設定する
	pEffect->m_nLife = nLife;
	pEffect->m_fLifeRatio = 1.0f / nLife;

	//ポインタを返す
	return pEffect;
}
