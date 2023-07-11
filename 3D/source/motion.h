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
//  モーションクラス定義
//==========================================
class CMotion
{
public:
	typedef enum
	{
		MOTION_NONE = 0, //なし
		PLAYER_SHOT, //弾を撃つ
		MOTION_MAX
	}MOTIONS;

	CMotion(); //コンストラクタ
	~CMotion(); //デストラクタ

private:

};

#endif
