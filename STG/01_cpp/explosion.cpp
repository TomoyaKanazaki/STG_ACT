//==========================================
//
//  爆発クラス(explosion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "explosion.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  マクロ定義
//==========================================
#define UPDATECOUNT (5) //更新間隔
#define ANIM_PATTERN (8) //アニメーションパターン数

//==========================================
//  静的メンバ変数宣言
//==========================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//==========================================
//  コンストラクタ
//==========================================
CExplosion::CExplosion()
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
HRESULT CExplosion::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D_Anim::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//アニメーション情報の登録
	SetAnim(ANIM_PATTERN, UPDATECOUNT, false, TYPE_U);

	//タイプの設定
	SetType(TYPE_EXPLOSION);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CExplosion::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CExplosion::Update(void)
{
	CObject2D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CExplosion::Draw(void)
{
	CObject2D_Anim::Draw();
}

//==========================================
//  読み込み処理
//==========================================
HRESULT CExplosion::Load(void)
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
//  破棄処理
//==========================================
void CExplosion::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==========================================
//  オブジェクト生成処理
//==========================================
CExplosion *CExplosion::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CExplosion *pExplosion = NULL;

	//NULLチェック
	if (pExplosion == NULL)
	{
		//メモリを確保
		pExplosion = new CExplosion;
	}

	//初期化
	if (pExplosion != NULL)
	{
		pExplosion->Init(pos, size, rot);
	}

	//テクスチャを割り当てる
	pExplosion->BindTexture(m_pTexture);

	//ポインタを返す
	return pExplosion;
}
