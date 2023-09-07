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
//  前方宣言
//==========================================
class CObject;

//==========================================
//  コリジョンライブラリ定義
//==========================================
namespace Collision
{
	D3DXVECTOR3 GetRevisionVec(const D3DXVECTOR3 vecMove, const D3DXVECTOR3 vecLine, const D3DXVECTOR3 vecToPos); //二直線の交点の取得
	bool CollisionPlayer(D3DXVECTOR3 pos, float fLange); //プレイヤーとの距離判定
	bool HomingEnemy(D3DXVECTOR3 pos, float fLange, bool bRelease, CObject **pObject); //敵との距離判定
	void InSquare(D3DXVECTOR3 *pVtx, float fLength); //矩形の内部の敵を破棄
}

#endif
