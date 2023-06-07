//==========================================
//
//  ナンバークラス(number.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "number.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//==========================================
//  コンストラクタ
//==========================================
CNumber::CNumber(int nPriority) : CObject2D(nPriority)
{
	m_nNumber = 0;
}

//==========================================
//  デストラクタ
//==========================================
CNumber::~CNumber()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CNumber::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//タイプの設定
	SetType(TYPE_NUMBER);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CNumber::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CNumber::Update(void)
{
	//ローカル変数宣言
	D3DXVECTOR2 min, max;

	//表示する値にテクスチャ座標を合わせる
	min = D3DXVECTOR2(m_nNumber * 0.1f, 0.0f);
	max = D3DXVECTOR2(min.x + 0.1f, 1.0f);

	//テクスチャ座標を割り当てる
	SetTex(min, max);
}

//==========================================
//  描画処理
//==========================================
void CNumber::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  読み込み処理
//==========================================
HRESULT CNumber::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number.png", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  テクスチャ破棄
//==========================================
void CNumber::UnLoad(void)
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
CNumber * CNumber::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nNumber)
{
	//インスタンス生成
	CNumber *pNumber = NULL;

	//NULLチェック
	if (pNumber == NULL)
	{
		//メモリを確保
		pNumber = new CNumber;
	}

	//値を割り当てる
	pNumber->m_nNumber = nNumber;

	//初期化
	if (pNumber != NULL)
	{
		pNumber->Init(pos, size, rot);
	}

	//テクスチャを割り当てる
	pNumber->BindTexture(m_pTexture);

	//ポインタを返す
	return pNumber;
}
