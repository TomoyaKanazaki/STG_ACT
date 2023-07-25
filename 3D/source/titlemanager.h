//==========================================
//
//  タイトルマネージャ(titlemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TITLEMANAGER_H_
#define _TITLEMANAGER_H_
#include "main.h"
#include "scene.h"

//==========================================
//  タイトルマネージャクラス定義
//==========================================
class CTitleManager : public CScene
{
public:
	CTitleManager(); //コンストラクタ
	~CTitleManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

};

#endif
