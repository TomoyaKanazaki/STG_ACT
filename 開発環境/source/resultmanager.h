//==========================================
//
//  リザルトマネージャ(resultmanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RESULTMANAGER_H_
#define _RESULTMANAGER_H_
#include "main.h"
#include "scene.h"

//==========================================
//  タイトルマネージャクラス定義
//==========================================
class CResultManager : public CScene
{
public:
	CResultManager(); //コンストラクタ
	~CResultManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ変数
	int m_nCntScene;
	int m_nRank;

};

#endif
