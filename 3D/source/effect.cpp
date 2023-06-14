//==========================================
//
//  エフェクトクラス(effect.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
int CEffect::m_nNum = 0;

//==========================================
//  コンストラクタ
//==========================================
CEffect::CEffect(int nPriority) : CObject3D(nPriority)
{
	m_vecDeffSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_fLifeRatio = 0;
	m_nNum++;
}

//==========================================
//  デストラクタ
//==========================================
CEffect::~CEffect()
{
	m_nNum--;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CEffect::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject3D::Init(pos, size, rot)))
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
void CEffect::Uninit(void)
{
	CObject3D::Uninit();
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
	m_size.z -= m_vecDeffSize.z * m_fLifeRatio;

	//移動量を加算する
	m_pos += m_move;

	//更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CEffect::Draw(void)
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
CEffect *CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXCOLOR col, int nLife)
{
	//インスタンス生成
	CEffect *pEffect = NULL;

	//NULLチェック
	if (pEffect == NULL)
	{
		//メモリを確保
		pEffect = new CEffect;
	}

	if (pEffect == NULL)
	{
		return NULL;
	}

	//初期化
	pEffect->Init(pos, size, rot);

	//テクスチャを割り当てる
	pEffect->BindTexture(CManager::GetTexture()->GetAddress(0));

	//デフォルトサイズを保存する
	pEffect->m_vecDeffSize = size;

	//寿命を設定する
	pEffect->m_nLife = nLife;
	pEffect->m_fLifeRatio = 1.0f / nLife;

	//色を設定する
	pEffect->SetCol(col);

	//ポインタを返す
	return pEffect;
}

//==========================================
//  生成処理
//==========================================
CEffect * CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	//インスタンス生成
	CEffect *pEffect = Create(pos, size, rot, col, nLife);

	//移動量を設定
	pEffect->m_move = move;

	//ポインタを返す
	return pEffect;
}
