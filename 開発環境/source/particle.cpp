//==========================================
//
//  パーティクルクラス(particle.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "particle.h"
#include "effect.h"

//==========================================
//  コンストラクタ
//==========================================
CParticle::CParticle()
{
	m_range = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nEffectNum = 0;
	m_nEffectLife = 0;
	m_nMove = 0;
	m_nLife = 0;
}

//==========================================
//  コンストラクタ
//==========================================
CParticle::~CParticle()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CParticle::Init(void)
{
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CParticle::Uninit(void)
{
	Release();
}

//==========================================
//  更新処理
//==========================================
void CParticle::Update(void)
{
	//寿命がない場合破棄する
	if (m_nLife <= 0)
	{
		this->Release();
		return;
	}

	//エフェクトの生成
	for (int nCnt = 0; nCnt < m_nEffectNum; nCnt++)
	{
		//エフェクトの移動量を算出
		D3DXVECTOR3 range;
		range.x = (float)((rand() % 200) - 100) * m_range.x;
		range.y = (float)((rand() % 200) - 100) * m_range.y;
		range.z = (float)((rand() % 200) - 100) * m_range.z;
		D3DXVec3Normalize(&range, &range);
		range.x *= m_nMove;
		range.y *= m_nMove;
		range.z *= m_nMove;

		//エフェクトを生成
		if (nullptr == (CEffect::Create(m_pos, m_size, m_col, m_nEffectLife, range)))
		{
			return;
		}
	}

	//寿命を減らす
	m_nLife--;
}

//==========================================
//  描画処理
//==========================================
void CParticle::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CParticle *CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 range, D3DXCOLOR col, int nEffectNum, int nEffectLife, int nMove, int nLife)
{
	//インスタンス生成
	CParticle *pParticle = NULL;

	//NULLチェック
	if (pParticle == NULL)
	{
		//メモリを確保
		pParticle = new CParticle;
	}

	//各種ステータスを設定
	pParticle->m_pos = pos;
	pParticle->m_size = size;
	pParticle->m_range = range;
	pParticle->m_col = col;
	pParticle->m_nEffectNum = nEffectNum;
	pParticle->m_nEffectLife = nEffectLife;
	pParticle->m_nMove = nMove;
	pParticle->m_nLife = nLife;

	//初期化
	if (pParticle != NULL)
	{
		pParticle->Init();
	}

	return pParticle;
}
