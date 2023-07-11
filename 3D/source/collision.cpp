//==========================================
//
//  当たり判定ライブラリ(collision.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "collision.h"
#include "manager.h"
#include "debugproc.h"
#include "object.h"
#include "item.h"
#include "score.h"
#include "gamemanager.h"

//==========================================
//  二直線の交点の取得
//==========================================
D3DXVECTOR3 Collision::GetRevisionVec(const D3DXVECTOR3 vecMove, const D3DXVECTOR3 vecLine, const D3DXVECTOR3 vecToPos)
{
	//ローカル変数宣言
	float fRate = 0.0f;
	D3DXVECTOR3 vecRevision = vecMove;

	//補正値を算出する
	fRate = (vecToPos.z * vecLine.x) - (vecToPos.x * vecLine.z);
	fRate /= (vecMove.z * vecLine.x) - (vecMove.x * vecLine.z);

	CManager::GetDebugProc()->Print("fRate : %f\n", fRate);

	//ベクトルを補正する
	if (fRate >= 0.0f && fRate <= 1.0f)
	{
		vecRevision = D3DXVECTOR3(vecMove.x * fRate, vecMove.y * fRate, vecMove.z * fRate);
	}

	//補正後の値を返す
	return vecRevision;
}

//==========================================
//  敵との当たり判定
//==========================================
bool Collision::CollisionEnemy(D3DXVECTOR3 pos, float fLange, bool bRelease, D3DXVECTOR3 *pPos)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			//オブジェクトを取得
			CObject *pObj = CObject::GetObject(nCntPriority, nCntObj);

			//NULLチェック
			if (pObj == NULL)
			{
				continue;
			}

			if (pObj->GetType() != CObject::TYPE_ENEMY) //敵の場合
			{
				continue;
			}

			//敵の各情報を取得する
			D3DXVECTOR3 enemyPos = pObj->GetPos();
			D3DXVECTOR3 size = pObj->GetSize();

			//敵と弾の距離を取得
			float fLength = (enemyPos.x - pos.x) * (enemyPos.x - pos.x) + (enemyPos.z - pos.z) * (enemyPos.z - pos.z);

			if (fLength < fLange * fLange)
			{
				//位置を保存
				if (pPos != NULL)
				{
					*pPos = pObj->GetPos();
				}

				//死ぬ
				if (bRelease)
				{
					//アイテムをドロップする
					switch (CGameManager::GetState())
					{
					case CGameManager::SHOT:
						CItem::Create(pObj->GetPos(), CItem::ENERGY);
						break;
					case CGameManager::BLADE:
						CItem::Create(pObj->GetPos(), CItem::SCORE);
						break;
					default:
						break;
					}

					//スコアを加算する
					CGameManager::GetScore()->AddScore(100);

					pObj->Uninit();
				}

				return true;
			}
		}
	}

	//当たっていない
	return false;
}
