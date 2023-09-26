//==========================================
//
//  ロゴのクラス(logo.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LOGO_H_
#define _LOGO_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CLogo : public CObject2D
{
public:

	//種類
	enum TYPE
	{
		TITLE = 0, //タイトル
		RESULT, //リザルト
		RANKING, //ランキング
		ENTER, //エンター
		RANK, //今回の順位
		SCORE, //スコア
		MAX
	};

	CLogo(int nPriority = 7); //コンストラクタ
	~CLogo(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);

private:

	//メンバ変数
	TYPE m_type;
	float m_fCounter;

};

#endif
