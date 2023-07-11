//==========================================
//
//  �����蔻�胉�C�u����(collision.cpp)
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
//  �񒼐��̌�_�̎擾
//==========================================
D3DXVECTOR3 Collision::GetRevisionVec(const D3DXVECTOR3 vecMove, const D3DXVECTOR3 vecLine, const D3DXVECTOR3 vecToPos)
{
	//���[�J���ϐ��錾
	float fRate = 0.0f;
	D3DXVECTOR3 vecRevision = vecMove;

	//�␳�l���Z�o����
	fRate = (vecToPos.z * vecLine.x) - (vecToPos.x * vecLine.z);
	fRate /= (vecMove.z * vecLine.x) - (vecMove.x * vecLine.z);

	CManager::GetDebugProc()->Print("fRate : %f\n", fRate);

	//�x�N�g����␳����
	if (fRate >= 0.0f && fRate <= 1.0f)
	{
		vecRevision = D3DXVECTOR3(vecMove.x * fRate, vecMove.y * fRate, vecMove.z * fRate);
	}

	//�␳��̒l��Ԃ�
	return vecRevision;
}

//==========================================
//  �G�Ƃ̓����蔻��
//==========================================
bool Collision::CollisionEnemy(D3DXVECTOR3 pos, float fLange, bool bRelease, D3DXVECTOR3 *pPos)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			//�I�u�W�F�N�g���擾
			CObject *pObj = CObject::GetObject(nCntPriority, nCntObj);

			//NULL�`�F�b�N
			if (pObj == NULL)
			{
				continue;
			}

			if (pObj->GetType() != CObject::TYPE_ENEMY) //�G�̏ꍇ
			{
				continue;
			}

			//�G�̊e�����擾����
			D3DXVECTOR3 enemyPos = pObj->GetPos();
			D3DXVECTOR3 size = pObj->GetSize();

			//�G�ƒe�̋������擾
			float fLength = (enemyPos.x - pos.x) * (enemyPos.x - pos.x) + (enemyPos.z - pos.z) * (enemyPos.z - pos.z);

			if (fLength < fLange * fLange)
			{
				//�ʒu��ۑ�
				if (pPos != NULL)
				{
					*pPos = pObj->GetPos();
				}

				//����
				if (bRelease)
				{
					//�A�C�e�����h���b�v����
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

					//�X�R�A�����Z����
					CGameManager::GetScore()->AddScore(100);

					pObj->Uninit();
				}

				return true;
			}
		}
	}

	//�������Ă��Ȃ�
	return false;
}
