//==========================================
//
//  タイムクラス(timer.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "timer.h"
#include "number.h"
#include "manager.h"
#include "pause.h"

//==========================================
//  コンストラクタ
//==========================================
CTimer::CTimer(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
		m_aTime[nCnt] = 0;
	}
	m_nTime = 0;
	m_nTimeDeff = 0;
	m_nBaseTime = 0;
	m_nPauseStartTime = 0;
	m_nPauseEndTime = 0;
	m_nPauseTime = 0;
	m_bOldPause = false;
}

//==========================================
//  デストラクタ
//==========================================
CTimer::~CTimer()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTimer::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//各種情報を保存
	m_pos = pos;
	m_size = size;
	m_rot = rot;

	//計算処理
	CalcTime();

	//オブジェクト生成
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		//NULLチェック
		if (m_apNumber[nCnt] == NULL)
		{
			//生成する座標を計算
			D3DXVECTOR3 NumPos = CalcPos(nCnt);

			if (FAILED(m_apNumber[nCnt] = CNumber::Create(NumPos, D3DXVECTOR3(size.x / TIME_DIGIT, size.y, size.z), rot, m_aTime[nCnt])))
			{
				return E_FAIL;
			}
		}
	}

	//タイプを割り当てる
	SetType(TYPE_TIMER);

	//変数の初期化
	m_nBaseTime = timeGetTime();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CTimer::Uninit(void)
{
	//メモリを開放する
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;
		}
	}
}

//==========================================
//  更新処理
//==========================================
void CTimer::Update(void)
{
	//表示可能範囲を超えた場合
	if (m_nTime < 0 || 999 < m_nTime)
	{
		return;
	}

	//ローカル変数宣言
	int nCurrentTime = timeGetTime(); //現在時間の取得 (1/1000秒)
	int nBetweenTime = 0; //基準時間と現在時間の差 (1/1秒)

	//ポーズ時間の補正
	CalcPauseTime(nCurrentTime);

	//基準時間と現在時間の差を取得 (1/1秒)
	nBetweenTime = (nCurrentTime - m_nBaseTime) / 1000;

	//残り時間の更新
	if (CManager::GetPause()->GetState() == false)
	{
		m_nTime = m_nTimeDeff - nBetweenTime;
	}

	//計算処理
	CalcTime();

	//計算結果を割り当てる
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->SetNum(m_aTime[nCnt]);
	}
}

//==========================================
//  描画処理
//==========================================
void CTimer::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CTimer * CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nTimeDeff)
{
	//インスタンス生成
	CTimer *pTime = NULL;

	//NULLチェック
	if (pTime == NULL)
	{
		//メモリを確保
		pTime = new CTimer;
	}

	//値を割り当てる
	pTime->m_nTime = nTimeDeff;
	pTime->m_nTimeDeff = nTimeDeff;

	//初期化
	if (pTime != NULL)
	{
		pTime->Init(pos, size, rot);
	}

	//ポインタを返す
	return pTime;
}

//==========================================
//  計算処理
//==========================================
void CTimer::CalcTime(void)
{
	//ローカル変数宣言
	int nCalc = m_nTime; //一時保管

	//テクスチャ座標の計測
	for (int nCntScore = TIME_DIGIT - 1; nCntScore >= 0; nCntScore--)
	{
		m_aTime[nCntScore] = nCalc % 10;
		nCalc /= 10;
	}
}

//==========================================
//  数字の座標を計算する処理
//==========================================
D3DXVECTOR3 CTimer::CalcPos(int nCnt)
{
	//ローカル変数宣言
	D3DXVECTOR3 NumPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//x座標を計算する
	NumPos.x = m_pos.x + ((m_size.x / (TIME_DIGIT * 2)) * (nCnt * 2 + 1));

	//y座標を代入する
	NumPos.y = m_pos.y;

	//値を返す
	return NumPos;
}

//==========================================
//  ポーズ中の処理
//==========================================
void CTimer::CalcPauseTime(int nCurrentTime)
{
	//ポーズが開かれた瞬間の時間を保存
	if (m_bOldPause == false && CManager::GetPause()->GetState())
	{
		m_nPauseStartTime = nCurrentTime;
	}

	//ポーズを閉じた時の処理
	if (m_bOldPause && CManager::GetPause()->GetState() == false)
	{
		//ポーズが閉じられた瞬間の時間を保存
		m_nPauseEndTime = nCurrentTime;

		//ポーズが開かれていた時間を算出
		int nPauseTime = m_nPauseEndTime - m_nPauseStartTime;

		//ポーズが開かれていた時間分基準時間を加算する
		m_nBaseTime += nPauseTime;
	}

	m_bOldPause = CManager::GetPause()->GetState();
}
