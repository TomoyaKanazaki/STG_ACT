//==========================================
//
//  アニメーション2Dクラス(object2D.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object2D_Anim.h"

//==========================================
//  コンストラクタ
//==========================================
CObject2D_Anim::CObject2D_Anim()
{
	m_Type = TYPE_NONE;
	m_nNumPattern = 0;
	m_nAnimPattern = 0;
	m_nAnimCounter = 0;
	m_nUpdateFrame = 0;
	m_bLoop = 0;
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
HRESULT CObject2D_Anim::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

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
	//カウンターの更新
	m_nAnimCounter++;

	//アニメーションの更新
	if (m_nAnimCounter % m_nUpdateFrame == 0)
	{
		//ローカル変数宣言
		float fUVPos;
		D3DXVECTOR2 min, max;

		//テクスチャ座標の最小値を算出する
		fUVPos = (1.0f / m_nNumPattern) * m_nAnimPattern;

		//値を適応する
		switch (m_Type)
		{
		case TYPE_U:
			min = D3DXVECTOR2(fUVPos, 0.0f);
			break;
		case TYPE_V:
			min = D3DXVECTOR2(0.0f, fUVPos);
			break;
		default:
			break;
		}

		//テクスチャ座標の最大値を算出する
		if (CObject::TYPE_BG == this->m_Type)
		{
			fUVPos += 1.0f;
		}
		else
		{
			fUVPos = (1.0f / m_nNumPattern) * (m_nAnimPattern + 1);
		}

		//値を適応する
		switch (m_Type)
		{
		case TYPE_U:
			max = D3DXVECTOR2(fUVPos, 1.0f);
			break;
		case TYPE_V:
			max = D3DXVECTOR2(1.0f, fUVPos);
			break;
		default:
			break;
		}

		//テクスチャ座標の更新
		SetTex(min, max);

		if (m_nAnimPattern >= m_nNumPattern) //最後のアニメーションの場合
		{
			if (m_bLoop) //ループする場合
			{
				m_nAnimPattern = 0;
			}
			else
			{
				this->Release();
				return;
			}
		}
		else
		{
			//アニメーション番号を更新する
			m_nAnimPattern++;
		}
	}

	//更新する
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CObject2D_Anim::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  アニメーション情報の設定
//==========================================
void CObject2D_Anim::SetAnim(int nPattern, int nInterval, bool bLoop, UVTYPE type)
{
	m_Type = type;
	m_nNumPattern = nPattern;
	m_nUpdateFrame = nInterval;
	m_bLoop = bLoop;
}
