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
#include "gamemanager.h"
#include "player.h"
#include "particle.h"
#include "enemy_manager.h"
#include "camera.h"
#include "sound.h"

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
bool Collision::CollisionPlayer(D3DXVECTOR3 pos, float fLange)
{
	//プレイヤーの位置を取得
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//プレイヤーへのベクトルを算出する
	D3DXVECTOR3 vecToPlayer = pos - posPlayer;

	//プレイヤーまでのベクトルの大きさを算出
	float fLangePlayer = (vecToPlayer.x * vecToPlayer.x) + (vecToPlayer.z * vecToPlayer.z);

	//距離判定
	if (fLange * fLange >= fLangePlayer)
	{
		CManager::GetSound()->Play(CSound::SOUND_LABEL_PRESS);

		//当たった結果を返して関数を終了
		return true;
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
			if (pObj->GetType() == CObject::TYPE_NORMAL_ENEMY || pObj->GetType() == CObject::TYPE_BULLET_ENEMY || pObj->GetType() == CObject::TYPE_BLOCK_ENEMY)
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
					//2つのベクトルで判定をする
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
					//対象の敵を弾に変更
					pObj->SetType(CObject::TYPE_BULLET_ENEMY);

					//プレイヤーから弾へのベクトルを算出
					D3DXVECTOR3 vecToBullet = CGameManager::GetCamera()->GetPosR() - CGameManager::GetPlayer()->GetPos();
					vecToBullet.y = 0.0f;
					D3DXVec3Normalize(&vecToBullet, &vecToBullet);

					//弾の移動量にする
					pObj->SetMove(vecToBullet * 150.0f);
				}
			}

			//確認するアドレスをずらす
			pObj = pNext;
		}
	}
}
