//==========================================
//
//  当たり判定ライブラリ(collision.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "collision.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  二直線の交点の取得
//==========================================
D3DXVECTOR3 Collision::GetRevisionVec(const D3DXVECTOR3 vecMove, const D3DXVECTOR3 vecLine, const D3DXVECTOR3 vecToPos)
{
	//ローカル変数宣言
	float fRate = 0.0f;
	D3DXVECTOR3 vecRevision = vecMove;

	////補正値を算出する
	//fRate = (vecToPos.z * vecLine.x) - (vecToPos.x * vecLine.z);
	//fRate /= (vecMove.z * vecLine.x) - (vecMove.x * vecLine.z);

	//CManager::GetDebugProc()->Print("fRate : %f\n", fRate);

	////ベクトルを補正する
	//if (fRate >= 0.0f && fRate <= 1.0f)
	//{
	//	vecRevision = D3DXVECTOR3(vecMove.x * fRate, vecMove.y * fRate, vecMove.z * fRate);
	//}

	//補正後の値を返す
	return vecRevision;
}
