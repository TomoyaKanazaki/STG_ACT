//==========================================
//
//  ロゴクラス(logo.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CLogo::CLogo(int nPriority) : CObject2D(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CLogo::~CLogo()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CLogo::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CLogo::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CLogo::Update(void)
{
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CLogo::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CLogo * CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	//インスタンス生成
	CLogo *pLogo = NULL;

	//NULLチェック
	if (pLogo == NULL)
	{
		//メモリを確保
		pLogo = new CLogo;
	}

	//値を割り当てる
	pLogo->m_pos = pos;
	pLogo->m_size = size;

	//テクスチャを割り当てる
	switch (type)
	{
	case TITLE:

		pLogo->BindTexture(CManager::GetTexture()->GetAddress(CTexture::TITLE));
		break;

	case RESULT:

		pLogo->BindTexture(CManager::GetTexture()->GetAddress(CTexture::RESULT));
		break;

	case RANKING:

		pLogo->BindTexture(CManager::GetTexture()->GetAddress(CTexture::RANKING));
		break;

	}

	//初期化
	if (pLogo != NULL)
	{
		pLogo->Init();
	}

	//ポインタを返す
	return pLogo;
}
