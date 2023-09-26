//==========================================
//
//  スコアクラス(score.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "score.h"
#include "number.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  静的メンバ変数
//==========================================
int CScore::m_prevScore = 0;

//==========================================
//  コンストラクタ
//==========================================
CScore::CScore(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
		m_aScore[nCnt] = 0;
	}
	m_nScore = 0;
	m_fScale = 1.0f;
}

//==========================================
//  デストラクタ
//==========================================
CScore::~CScore()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CScore::Init(void)
{
	//計算処理
	CalcScore();

	//オブジェクト生成
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		//NULLチェック
		if (m_apNumber[nCnt] == NULL)
		{
			//生成する座標を計算
			D3DXVECTOR3 NumPos = CalcPos(nCnt);

			if (nullptr == (m_apNumber[nCnt] = CNumber::Create(NumPos, D3DXVECTOR3(m_size.x / SCORE_DIGIT, m_size.y, m_size.z), m_rot, m_aScore[nCnt])))
			{
				return E_FAIL;
			}
		}
	}

	//タイプを割り当てる
	SetType(TYPE_SCORE);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CScore::Uninit(void)
{
	m_prevScore = m_nScore;
	Release();
}

//==========================================
//  更新処理
//==========================================
void CScore::Update(void)
{
	CManager::GetDebugProc()->Print("スコア倍率 : %f\n", m_fScale);
}

//==========================================
//  描画処理
//==========================================
void CScore::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nScoreDeff)
{
	//インスタンス生成
	CScore *pScore = NULL;

	//NULLチェック
	if (pScore == NULL)
	{
		//メモリを確保
		pScore = new CScore;
	}

	//値を割り当てる
	pScore->m_nScore = nScoreDeff;
	pScore->m_pos = pos;
	pScore->m_size = size;
	pScore->m_rot = rot;

	//初期化
	if (pScore != NULL)
	{
		pScore->Init();
	}

	//ポインタを返す
	return pScore;
}

//==========================================
//  計算処理
//==========================================
void CScore::CalcScore(void)
{
	//ローカル変数宣言
	int nCalc = m_nScore; //一時保管

	//テクスチャ座標の計測
	for (int nCntScore = SCORE_DIGIT - 1; nCntScore >= 0; nCntScore--)
	{
		m_aScore[nCntScore] = nCalc % 10;
		nCalc /= 10;
	}
}

//==========================================
//  加算処理
//==========================================
void CScore::Add(const int nAdd)
{
	//スコアを加算する
	m_nScore += (int)((float)nAdd * m_fScale);

	//計算処理
	CalcScore();

	//計算結果を割り当てる
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->SetNum(m_aScore[nCnt]);
	}
}

//==========================================
//  数字の座標を計算する処理
//==========================================
D3DXVECTOR3 CScore::CalcPos(int nCnt)
{
	//ローカル変数宣言
	D3DXVECTOR3 NumPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//x座標を計算する
	NumPos.x = m_pos.x + ((m_size.x / (SCORE_DIGIT * 2)) * (nCnt * 2 + 1));

	//y座標を代入する
	NumPos.y = m_pos.y;

	//値を返す
	return NumPos;
}
