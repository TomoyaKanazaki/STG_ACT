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
	m_fCounter = 0.0f;
	m_type = MAX;
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
	HRESULT h = CObject2D::Init();
	if (m_type == ENTER)
	{
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	return h;
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
	//エンターを点滅する
	if (m_type == ENTER)
	{
		m_fCounter += 0.02f;
		float fAlpha = sinf(m_fCounter) * 0.5f + 0.5f;
		D3DXCOLOR col = GetCol();
		col.a = fAlpha;
		SetCol(col);
	}

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
	pLogo->m_type = type;

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

	case ENTER:

		pLogo->BindTexture(CManager::GetTexture()->GetAddress(CTexture::ENTER));
		break;

	case RANK:

		pLogo->BindTexture(CManager::GetTexture()->GetAddress(CTexture::RANK));
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
