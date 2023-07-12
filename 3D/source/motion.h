//==========================================
//
//  モーションクラス(motion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"

//==========================================
//  前方宣言
//==========================================
class CModel;

//==========================================
//  モーションクラス定義
//==========================================
class CMotion
{
public:
	typedef enum
	{
		MOTION_NONE = 0, //なし
		PLAYER,
		ENEMY,
		MOTION_MAX
	}CHARA;

	CMotion(); //コンストラクタ
	~CMotion(); //デストラクタ

	//メンバ関数
	void Uninit(void);
	void Update(void);

	void SetModel(CModel **ppModel, int nNum);
	void SetChara(CHARA nChara) { chara = nChara; }

	void Set(int type);

	static void Load(void);

private:

	//メンバ変数
	CModel **m_ppModel;
	CHARA chara;
	int m_nNumModel;

};

#endif
