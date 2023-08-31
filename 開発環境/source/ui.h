//==========================================
//
//  UIクラス(ui.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _UI_H_
#define _UI_H_
#include "main.h"
#include "enemy_manager.h"

//==========================================
//  クラス定義
//==========================================
class CUi
{
public:
	CUi(); //コンストラクタ
	~CUi(); //デストラクタ

	//メンバ関数
	void Init(HWND hWnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static CUi *Create(HWND hWnd);

private:

	//エネミーマネージャの管理用
	struct EnemyData
	{
		CEnemyManager::CreateData CreateData;
		bool bUse;
	};

	//メンバ関数
	void Save(void);

	//メンバ変数
	HWND m_hWnd;
	EnemyData m_EnemyData[256];

	//静的メンバ変数
	static char m_sPass[256];

};

#endif
