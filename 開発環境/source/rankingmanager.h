//==========================================
//
//  ランキングマネージャ(rankingmanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RANKINGMANAGER_H_
#define _RANKINGMANAGER_H_
#include "main.h"
#include "scene.h"

//==========================================
//  タイトルマネージャクラス定義
//==========================================
class CRankingManager : public CScene
{
public:
	CRankingManager(); //コンストラクタ
	~CRankingManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ変数
	int m_nCntScene;

};

#endif
