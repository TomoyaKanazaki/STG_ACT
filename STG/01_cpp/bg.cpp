//==========================================
//
//  背景クラス(bg.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bg.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  マクロ定義
//==========================================
#define SCROLL_ROUND (1000) //スクロール基準速度

//==========================================
//  静的メンバ変数宣言
//==========================================
int CBg::m_nNum = 0;
LPDIRECT3DTEXTURE9 CBg::m_pTexture[BG_NUM] = {};

//==========================================
//  コンストラクタ
//==========================================
CBg::CBg()
{
	m_nID = m_nNum;
	m_nNum++;
	m_nSpeed = SCROLL_ROUND * m_nNum;
}

//==========================================
//  デストラクタ
//==========================================
CBg::~CBg()
{
	m_nNum--;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CBg::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D_Anim::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//アニメーション情報の登録
	SetAnim(m_nSpeed, 1, true, TYPE_V);

	//タイプの設定
	SetType(TYPE_BG);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CBg::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBg::Update(void)
{
	CObject2D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CBg::Draw(void)
{
	CObject2D_Anim::Draw();
}

//==========================================
//  読み込み処理
//==========================================
HRESULT CBg::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/bg100.png", &m_pTexture[0])))
	{
		return E_FAIL;
	}
	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/bg101.png", &m_pTexture[1])))
	{
		return E_FAIL;
	}
	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/bg102.png", &m_pTexture[2])))
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
	for (int nCnt = 0; nCnt < BG_NUM; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//==========================================
//  生成処理
//==========================================
void CBg::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	for (int nCnt = 0; nCnt < BG_NUM; nCnt++)
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

		//テクスチャを割り当てる
		pBg->BindTexture(m_pTexture[nCnt]);
	}
}
