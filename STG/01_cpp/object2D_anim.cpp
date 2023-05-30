//==========================================
//
//  アニメーションオブジェクト2D(object2D_anim.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object2D_anim.h"
#include "manager.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  マクロ定義
//==========================================
#define ANIM_UPDATE (5) //パターン更新フレーム

//==========================================
//  静的メンバ変数宣言
//==========================================
LPDIRECT3DTEXTURE9 CObject2D_Anim::m_pTexture = NULL;

//==========================================
//  コンストラクタ
//==========================================
CObject2D_Anim::CObject2D_Anim()
{
	m_nNumPattern = 0;
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
}

//==========================================
//  デストラクタ
//==========================================
CObject2D_Anim::~CObject2D_Anim()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CObject2D_Anim::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, const int nAnimPattern)
{
	if (FAILED(CObject2D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//アニメーションパターンを設定
	m_nNumPattern = nAnimPattern;

	//頂点バッファの呼び出し
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	this->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * m_nPatternAnim, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * (m_nPatternAnim + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * m_nPatternAnim, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * (m_nPatternAnim + 1), 1.0f);

	//頂点バッファをアンロック
	this->GetBuff()->Unlock();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CObject2D_Anim::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CObject2D_Anim::Update(void)
{
	//カウントを加算
	m_nCountAnim++;

	if (m_nCountAnim % ANIM_UPDATE == 0)
	{
		//テクスチャ座標の切り替え
		m_nPatternAnim++;
	
		//パターンの切り替え
		m_nPatternAnim %= m_nNumPattern;
	
		//頂点バッファの呼び出し
		VERTEX_2D *pVtx;
	
		//頂点バッファをロック
		this->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);
	
		//テクスチャ座標の更新
		pVtx[0].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * m_nPatternAnim, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * (m_nPatternAnim + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * m_nPatternAnim, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((1.0f / m_nNumPattern) * (m_nPatternAnim + 1), 1.0f);
	
		//頂点バッファをアンロック
		this->GetBuff()->Unlock();
	}
}

//==========================================
//  描画処理
//==========================================
void CObject2D_Anim::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  テクスチャの読み込み
//==========================================
HRESULT CObject2D_Anim::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/explosion.png", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  テクスチャの破棄
//==========================================
void CObject2D_Anim::UnLoad(void)
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
CObject2D_Anim * CObject2D_Anim::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const int nAnimPattern, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CObject2D_Anim *pObject2D_Anim = NULL;

	//NULLチェック
	if (pObject2D_Anim == NULL)
	{
		//メモリを確保
		pObject2D_Anim = new CObject2D_Anim;
	}

	//初期化
	if (pObject2D_Anim != NULL)
	{
		pObject2D_Anim->Init(pos, size, rot, nAnimPattern);
	}

	//テクスチャを割り当てる
	pObject2D_Anim->BindTexture(m_pTexture);

	//ポインタを返す
	return pObject2D_Anim;
}
