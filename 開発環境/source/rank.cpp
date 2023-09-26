//==========================================
//
//  順位(rank.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "rank.h"
#include "number.h"

//==========================================
//  コンストラクタ
//==========================================
CRank::CRank(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < RANK_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
		m_aRank[nCnt] = 0;
	}
	m_nRank = 0;
}

//==========================================
//  デストラクタ
//==========================================
CRank::~CRank()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CRank::Init(void)
{
	//表示する数字の計算
	CalcRank();

	//オブジェクト生成
	for (int nCnt = 0; nCnt < RANK_DIGIT; nCnt++)
	{
		//NULLチェック
		if (m_apNumber[nCnt] == NULL)
		{
			//生成する座標を計算
			D3DXVECTOR3 NumPos = CalcPos(nCnt);

			if (nullptr == (m_apNumber[nCnt] = CNumber::Create(NumPos, D3DXVECTOR3(m_size.x / RANK_DIGIT, m_size.y, m_size.z), m_rot, m_aRank[nCnt])))
			{
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CRank::Uninit(void)
{
	Release();
}

//==========================================
//  更新処理
//==========================================
void CRank::Update(void)
{

}

//==========================================
//  描画処理
//==========================================
void CRank::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CRank *CRank::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nRank)
{
	//インスタンス生成
	CRank *pRank = NULL;

	//NULLチェック
	if (pRank == NULL)
	{
		//メモリを確保
		pRank = new CRank;
	}

	pRank->m_pos = pos;
	pRank->m_size = size;
	pRank->m_nRank = nRank;

	//初期化
	if (pRank != NULL)
	{
		pRank->Init();
	}

	//ポインタを返す
	return pRank;
}

//==========================================
//  計算処理
//==========================================
void CRank::CalcRank(void)
{
	//ローカル変数宣言
	int nCalc = m_nRank; //一時保管

	//テクスチャ座標の計測
	for (int nCntRank = RANK_DIGIT - 1; nCntRank >= 0; nCntRank--)
	{
		m_aRank[nCntRank] = nCalc % 10;
		nCalc /= 10;
	}
}

//==========================================
//  数字の座標を計算する処理
//==========================================
D3DXVECTOR3 CRank::CalcPos(int nCnt)
{
	//ローカル変数宣言
	D3DXVECTOR3 NumPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//x座標を計算する
	NumPos.x = m_pos.x + ((m_size.x / (RANK_DIGIT * 2)) * (nCnt * 2 + 1));

	//y座標を代入する
	NumPos.y = m_pos.y;

	//値を返す
	return NumPos;
}
