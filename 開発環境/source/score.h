//==========================================
//
//  スコアクラス(score.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#include "object.h"

//==========================================
//  マクロ定義
//==========================================
#define SCORE_DIGIT (8) //スコアの桁数

//==========================================
//  前方宣言
//==========================================
class CNumber;

//==========================================
//  スコアクラス定義
//==========================================
class CScore : public CObject
{
public:
	CScore(int nPriority = 7); //コンストラクタ
	~CScore(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Add(const int nAdd);
	void AddScale(const float fScale) { m_fScale += fScale; }
	int SendScore(void) {return m_nScore; }

	//静的メンバ関数
	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nScoreDeff);
	static int GetScore(void) { return m_prevScore; }

private:
	
	//メンバ変数
	CNumber *m_apNumber[SCORE_DIGIT];
	int m_aScore[SCORE_DIGIT]; //表示する値
	int m_nScore; //スコアの値
	float m_fScale; //スコアの倍率

	//メンバ関数
	void CalcScore(void);
	D3DXVECTOR3 CalcPos(int nCnt);

	//静的メンバ変数
	static int m_prevScore;

};

#endif
