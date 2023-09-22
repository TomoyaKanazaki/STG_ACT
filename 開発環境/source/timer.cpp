//==========================================
//
//  タイマークラス(timer.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "precompile.h"
#include "timer.h"
#include "timer_add.h"
#include "timer_sab.h"
#include "number.h"

//==========================================
//  コンストラクタ
//==========================================
CTime::CTime(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < TIMER_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
		m_aTime[nCnt] = 0;
	}
	m_nCurrent = 0;
	m_nMax = 0;
}

//==========================================
//  デストラクタ
//==========================================
CTime::~CTime()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTime::Init(void)
{
	//表示する値を計算
	CalcScore();

	//オブジェクト生成
	for (int nCnt = 0; nCnt < TIMER_DIGIT; nCnt++)
	{
		//NULLチェック
		if (m_apNumber[nCnt] == NULL)
		{
			//生成する座標を計算
			D3DXVECTOR3 NumPos = CalcPos(nCnt);

			if (nullptr == (m_apNumber[nCnt] = CNumber::Create(NumPos, D3DXVECTOR3(m_size.x / TIMER_DIGIT, m_size.y, m_size.z), m_rot, m_aTime[nCnt])))
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
void CTime::Uninit(void)
{

}

//==========================================
//  更新処理
//==========================================
void CTime::Update(void)
{
	//時間を計算する
	CalcScore();

	//計算結果を割り当てる
	for (int nCnt = 0; nCnt < TIMER_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->SetNum(m_aTime[nCnt]);
	}
}

//==========================================
//  描画処理
//==========================================
void CTime::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CTime *CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int max, Time kind)
{
	//インスタンス生成
	CTime *pTime = NULL;

	//NULLチェック
	if (pTime == NULL)
	{
		switch (kind)
		{
		case ADD:

			pTime = new CTimer_Add;
			break;

		case SAB:

			pTime = new CTimer_Sab;
			break;
		}
	}

	//値を割り当てる
	pTime->m_pos = pos;
	pTime->m_size = size;
	pTime->m_nMax = max;

	//初期化
	if (pTime != NULL)
	{
		pTime->Init();
	}

	//ポインタを返す
	return pTime;
}

//==========================================
//  数字の座標を計算する処理
//==========================================
D3DXVECTOR3 CTime::CalcPos(int nCnt)
{
	//ローカル変数宣言
	D3DXVECTOR3 NumPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//x座標を計算する
	NumPos.x = m_pos.x + ((m_size.x / (TIMER_DIGIT * 2)) * (nCnt * 2 + 1));

	//y座標を代入する
	NumPos.y = m_pos.y;

	//値を返す
	return NumPos;
}

//==========================================
//  計算処理
//==========================================
void CTime::CalcScore(void)
{
	//ローカル変数宣言
	int nCalc = m_nCurrent; //一時保管

	//テクスチャ座標の計測
	for (int nCntTime = TIMER_DIGIT - 1; nCntTime >= 0; nCntTime--)
	{
		m_aTime[nCntTime] = nCalc % 10;
		nCalc /= 10;
	}
}
