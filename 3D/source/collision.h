//==========================================
//
//  当たり判定ライブラリ(collision.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "main.h"

//==========================================
//  コリジョンライブラリ定義
//==========================================
namespace Collision
{
	D3DXVECTOR3 GetRevisionVec(const D3DXVECTOR3 vecMove, const D3DXVECTOR3 vecLine, const D3DXVECTOR3 vecToPos); //二直線の交点の取得
}

#endif
