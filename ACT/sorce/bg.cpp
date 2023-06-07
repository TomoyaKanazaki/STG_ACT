//==========================================
//
//  背景クラス(bg.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bg.h"
#include "object2D_Anim.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  マクロ定義
//==========================================
#define SCROLL_ROUND (1000) //スクロール基準速度

//==========================================
//  静的メンバ変数宣言
//==========================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};

//==========================================
//  コンストラクタ
//==========================================
CBg::CBg(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apObject[nCnt] = NULL;
	}
}

//==========================================
//  デストラクタ
//==========================================
CBg::~CBg()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBg::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//オブジェクト生成
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//NULLチェック
		if (m_apObject[nCnt] == NULL)
		{
			if (FAILED(m_apObject[nCnt] = CObject2D_Anim::Create(pos, size, rot, SCROLL_ROUND * nCnt, 1, true, CObject2D_Anim::TYPE_V)))
			{
				return E_FAIL;
			}
		}

		if (m_apObject[nCnt] != NULL)
		{
			//テクスチャの設定
			m_apObject[nCnt]->BindTexture(m_apTexture[nCnt]);

			//タイプの設定
			m_apObject[nCnt]->SetType(CObject::TYPE_BG);
		}
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CBg::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			m_apObject[nCnt]->Uninit();
			m_apObject[nCnt] = NULL;
		}
	}
}

//==========================================
//  更新処理
//==========================================
void CBg::Update(void)
{

}

//==========================================
//  描画処理
//==========================================
void CBg::Draw(void)
{

}

//==========================================
//  読み込み処理
//==========================================
HRESULT CBg::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &m_apTexture[0])))
	{
		return E_FAIL;
	}
	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTexture[1])))
	{
		return E_FAIL;
	}
	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTexture[2])))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  破棄処理
//==========================================
void CBg::UnLoad(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//==========================================
//  生成処理
//==========================================
CBg *CBg::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CBg *pBg = NULL;

	//NULLチェック
	if (pBg == NULL)
	{
		//メモリを確保
		pBg = new CBg;
	}

	//初期化
	if (pBg != NULL)
	{
		pBg->Init(pos, size, rot);
	}

	return pBg;
}
