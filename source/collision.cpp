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
#include "player.h"

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
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		//NULLチェック
		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			//敵の場合
			if (pObj->GetType() != CObject::TYPE_ENEMY)
			{
				//次のアドレスにずらす
				pObj = pNext;
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
					CGameManager::GetScore()->Add(100);

					pObj->Uninit();
				}

				return true;
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}

	//当たっていない
	return false;
}

//==========================================
//  敵との当たり判定
//==========================================
bool Collision::HomingEnemy(D3DXVECTOR3 pos, float fLange, bool bRelease, CObject **pObject)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			if (pObj->GetType() != CObject::TYPE_ENEMY) //敵の場合
			{
				pObj = pNext;
				continue;
			}

			//敵の各情報を取得する
			D3DXVECTOR3 enemyPos = pObj->GetPos();
			D3DXVECTOR3 size = pObj->GetSize();

			//敵と弾の距離を取得
			float fLength = (enemyPos.x - pos.x) * (enemyPos.x - pos.x) + (enemyPos.z - pos.z) * (enemyPos.z - pos.z);

			if (fLength < fLange * fLange)
			{
				//情報を保存
				*pObject = pObj;

				//死ぬ
				if (bRelease)
				{
					//アイテムをドロップする
					CItem::Create(pObj->GetPos(), CItem::ENERGY);

					pObj->Uninit();
				}
				return true;
			}
			pObj = pNext;
		}
	}

	//当たっていない
	return false;
}

//==========================================
//  矩形の内部の敵を破棄
//==========================================
void Collision::InSquare(D3DXVECTOR3 *pVtx, float fLength)
{
	//判定に利用する4つのベクトルを算出
	D3DXVECTOR3 vecLine[2] = 
	{
		pVtx[1] - pVtx[0],
		pVtx[3] - pVtx[2]
	};

	//全描画優先順位を確認
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		//全てのオブジェクトを確認
		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			//対象オブジェクトが敵の場合
			if (pObj->GetType() == CObject::TYPE_ENEMY)
			{
				//判定フラグ
				bool bIn = true;

				//判定に必要なベクトルを算出
				D3DXVECTOR3 posObj = pObj->GetPos(), vecToPos[4] =
				{
					posObj - pVtx[0],
					posObj - pVtx[2]
				};

				//距離の判定を取る
				D3DXVECTOR3 vecLength = posObj - CGameManager::GetPlayer()->GetPos();

				//判定距離内の場合
				if (fLength >= vecLength.x * vecLength.x + vecLength.z * vecLength.z)
				{
					//4つのベクトルで判定をする
					for (int nCntVec = 0; nCntVec < 2; nCntVec++)
					{
						//外積を算出
						float fDot = 0.0f;
						fDot = vecLine[nCntVec].z * vecToPos[nCntVec].x - vecLine[nCntVec].x * vecToPos[nCntVec].z;

						if (fDot <= 0.0f)
						{
							bIn = false;
							break;
						}
					}
				}
				else
				{
					bIn = false;
				}

				//内部に存在した場合
				if (bIn)
				{
					//アイテムをドロップする
					CItem::Create(pObj->GetPos(), CItem::SCORE);

					//スコアを加算する
					CGameManager::GetScore()->Add(100);

					//対象のオブジェクトを終了
					pObj->Uninit();
				}
			}

			//確認するアドレスをずらす
			pObj = pNext;
		}
	}
}

//==========================================
//  矩形の内部の敵を吹き飛ばす
//==========================================
void Collision::InSquare(D3DXVECTOR3 * pVtx, float fLength, float fPressure)
{
	//判定に利用する4つのベクトルを算出
	D3DXVECTOR3 vecLine[4] =
	{
		pVtx[1] - pVtx[0],
		pVtx[2] - pVtx[1],
		pVtx[3] - pVtx[2],
		pVtx[0] - pVtx[3]
	};

	//全描画優先順位を確認
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		//全てのオブジェクトを確認
		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			//対象オブジェクトが敵の場合
			if (pObj->GetType() == CObject::TYPE_ENEMY)
			{
				//判定フラグ
				bool bIn = true;

				//判定に必要なベクトルを算出
				D3DXVECTOR3 posObj = pObj->GetPos(), vecToPos[4] =
				{
					posObj - pVtx[0],
					posObj - pVtx[1],
					posObj - pVtx[2],
					posObj - pVtx[3]
				};

				//4つのベクトルで判定をする
				for (int nCntVec = 0; nCntVec < 4; nCntVec++)
				{
					//外積を算出
					float fDot = 0.0f;
					fDot = vecLine[nCntVec].z * vecToPos[nCntVec].x - vecLine[nCntVec].x * vecToPos[nCntVec].z;

					if (fDot <= 0.0f)
					{
						bIn = false;
						break;
					}
				}

				//内部に存在した場合
				if (bIn)
				{
					//プレイヤーの位置を取得
					D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

					//プレイヤーからオブジェクトまでのベクトルを取得
					D3DXVECTOR3 vecPlayer = posObj - posPlayer;
					vecPlayer.y = 0.0f;

					//ベクトルを正規化
					D3DXVec3Normalize(&vecPlayer, &vecPlayer);

					//ベクトルを補正
					vecPlayer *= fPressure;
				}
			}

			//確認するアドレスをずらす
			pObj = pNext;
		}
	}
}
