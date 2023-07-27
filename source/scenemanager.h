//==========================================
//
//  画面遷移管理クラス(scenemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "main.h"

//==========================================
//  前方宣言
//==========================================
class CScene;
class CFade;

//==========================================
//  画面遷移クラス定義
//==========================================
class CSceneManager
{
public:
	enum SCENE
	{
		NONE = 0,
		TITLE,
		GAME,
		RESULT,
		RANKING,
		MAX
	};

	CSceneManager(); //コンストラクタ
	~CSceneManager(); //デストラクタ

	//メンバ関数
	void Init(SCENE newsecene);
	void Uninit(SCENE next = NONE);
	void Update(void);
	void Draw(void);
	void SetNext(SCENE next);

	//静的メンバ関数
	static CSceneManager *Create(SCENE scene = TITLE);

private:

	//メンバ変数
	SCENE m_Scene; //現在のゲームモード
	SCENE m_Next; //次のゲームモード
	CScene *m_pScene; //シーンのポインタ
	CFade *m_pFade; //フェードのポインタ

};

#endif
