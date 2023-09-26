//==========================================
//
//  ランキング(ranking.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ranking.h"
#include "score.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const char CRanking::m_sPass[128] = "data\\BIN\\Ranking.bin";
int CRanking::m_nNumData = 1;
int *CRanking::m_pScore = NULL;
int CRanking::m_nRank = 0;
int CRanking::m_nScore = 0;

//==========================================
//  コンストラクタ
//==========================================
CRanking::CRanking()
{

}

//==========================================
//  デストラクタ
//==========================================
CRanking::~CRanking()
{

}

//==========================================
//  初期化処理
//==========================================
void CRanking::Init(void)
{
	//前回までのデータを読み込み
	Load();
}

//==========================================
//  終了処理
//==========================================
void CRanking::Uninit(void)
{
	Reset();
}

//==========================================
//  更新処理
//==========================================
void CRanking::Update(void)
{

}

//==========================================
//  描画処理
//==========================================
void CRanking::Draw(void)
{

}

//==========================================
//  読み込み処理
//==========================================
void CRanking::Load(void)
{
	//ローカル変数宣言
	FILE *pFile; //ファイル名

	//ファイルを読み込み専用で開く
	pFile = fopen(&m_sPass[0], "rb");

	//NULLチェック
	if (pFile != NULL)
	{
		//データ数を取得
		fread(&m_nNumData, sizeof(int), 1, pFile);

		//データを取得
		Reset();
		m_pScore = new int[m_nNumData];
		fread(m_pScore, sizeof(int), m_nNumData, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
}

//==========================================
//  書き出し処理
//==========================================
void CRanking::Save(int nNewScore)
{
	//ローカル変数宣言
	FILE *pFile; //ファイル名

	//ファイルを読み込み専用で開く
	pFile = fopen(&m_sPass[0], "rb");

	//NULLチェック
	if (pFile != NULL)
	{
		//データ数を取得
		fread(&m_nNumData, sizeof(int), 1, pFile);

		//データを取得
		Reset();
		m_pScore = new int[m_nNumData + 1];
		fread(m_pScore, sizeof(int), m_nNumData, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}

	//データを追加
	m_pScore[m_nNumData] = nNewScore;
	m_nScore = nNewScore;
	m_nNumData++;

	//ソート処理
	qsort
	(
		m_pScore,
		m_nNumData ,
		sizeof(int),
		Descending
	);

	//ファイルを書き込み専用で開く
	pFile = fopen(&m_sPass[0], "wb");

	//NULLチェック
	if (pFile != NULL)
	{
		//データ数を取得
		fwrite(&m_nNumData, sizeof(int), 1, pFile);

		//データを取得
		fwrite(m_pScore, sizeof(int), m_nNumData, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}

	//順位を設定
	for (int nCnt = 0; nCnt < m_nNumData; nCnt++)
	{
		if (m_pScore[nCnt] == nNewScore)
		{
			m_nRank = nCnt + 1;
			break;
		}
	}

	//データを破棄
	Reset();
}

//==========================================
//  スコアの初期化
//==========================================
void CRanking::Reset(void)
{
	//スコアが既に存在していたら削除する
	if (m_pScore != NULL)
	{
		delete[] m_pScore;
		m_pScore = NULL;
	}
}

//==========================================
//  降順指定
//==========================================
int CRanking::Descending(const void * n0, const void * n1)
{
	//n0とn1の値を比較した結果によって返り値を決定する
	if (*(int *)n0 < *(int *)n1)
	{
		return 1;
	}
	else if (*(int *)n0 > *(int *)n1)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
