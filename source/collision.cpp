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
#include "player.h"

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
		//�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		//NULL�`�F�b�N
		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject *pNext = pObj->GetNext();

			//�G�̏ꍇ
			if (pObj->GetType() != CObject::TYPE_ENEMY)
			{
				//���̃A�h���X�ɂ��炷
				pObj = pNext;
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
					CGameManager::GetScore()->Add(100);

					pObj->Uninit();
				}

				return true;
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}

	//�������Ă��Ȃ�
	return false;
}

//==========================================
//  �G�Ƃ̓����蔻��
//==========================================
bool Collision::HomingEnemy(D3DXVECTOR3 pos, float fLange, bool bRelease, CObject **pObject)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject *pNext = pObj->GetNext();

			if (pObj->GetType() != CObject::TYPE_ENEMY) //�G�̏ꍇ
			{
				pObj = pNext;
				continue;
			}

			//�G�̊e�����擾����
			D3DXVECTOR3 enemyPos = pObj->GetPos();
			D3DXVECTOR3 size = pObj->GetSize();

			//�G�ƒe�̋������擾
			float fLength = (enemyPos.x - pos.x) * (enemyPos.x - pos.x) + (enemyPos.z - pos.z) * (enemyPos.z - pos.z);

			if (fLength < fLange * fLange)
			{
				//����ۑ�
				*pObject = pObj;

				//����
				if (bRelease)
				{
					//�A�C�e�����h���b�v����
					CItem::Create(pObj->GetPos(), CItem::ENERGY);

					pObj->Uninit();
				}
				return true;
			}
			pObj = pNext;
		}
	}

	//�������Ă��Ȃ�
	return false;
}

//==========================================
//  ��`�̓����̓G��j��
//==========================================
void Collision::InSquare(D3DXVECTOR3 *pVtx, float fLength)
{
	//����ɗ��p����4�̃x�N�g�����Z�o
	D3DXVECTOR3 vecLine[2] = 
	{
		pVtx[1] - pVtx[0],
		pVtx[3] - pVtx[2]
	};

	//�S�`��D�揇�ʂ��m�F
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		//�S�ẴI�u�W�F�N�g���m�F
		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject *pNext = pObj->GetNext();

			//�ΏۃI�u�W�F�N�g���G�̏ꍇ
			if (pObj->GetType() == CObject::TYPE_ENEMY)
			{
				//����t���O
				bool bIn = true;

				//����ɕK�v�ȃx�N�g�����Z�o
				D3DXVECTOR3 posObj = pObj->GetPos(), vecToPos[4] =
				{
					posObj - pVtx[0],
					posObj - pVtx[2]
				};

				//�����̔�������
				D3DXVECTOR3 vecLength = posObj - CGameManager::GetPlayer()->GetPos();

				//���苗�����̏ꍇ
				if (fLength >= vecLength.x * vecLength.x + vecLength.z * vecLength.z)
				{
					//4�̃x�N�g���Ŕ��������
					for (int nCntVec = 0; nCntVec < 2; nCntVec++)
					{
						//�O�ς��Z�o
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

				//�����ɑ��݂����ꍇ
				if (bIn)
				{
					//�A�C�e�����h���b�v����
					CItem::Create(pObj->GetPos(), CItem::SCORE);

					//�X�R�A�����Z����
					CGameManager::GetScore()->Add(100);

					//�Ώۂ̃I�u�W�F�N�g���I��
					pObj->Uninit();
				}
			}

			//�m�F����A�h���X�����炷
			pObj = pNext;
		}
	}
}

//==========================================
//  ��`�̓����̓G�𐁂���΂�
//==========================================
void Collision::InSquare(D3DXVECTOR3 * pVtx, float fLength, float fPressure)
{
	//����ɗ��p����4�̃x�N�g�����Z�o
	D3DXVECTOR3 vecLine[4] =
	{
		pVtx[1] - pVtx[0],
		pVtx[2] - pVtx[1],
		pVtx[3] - pVtx[2],
		pVtx[0] - pVtx[3]
	};

	//�S�`��D�揇�ʂ��m�F
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		//�S�ẴI�u�W�F�N�g���m�F
		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject *pNext = pObj->GetNext();

			//�ΏۃI�u�W�F�N�g���G�̏ꍇ
			if (pObj->GetType() == CObject::TYPE_ENEMY)
			{
				//����t���O
				bool bIn = true;

				//����ɕK�v�ȃx�N�g�����Z�o
				D3DXVECTOR3 posObj = pObj->GetPos(), vecToPos[4] =
				{
					posObj - pVtx[0],
					posObj - pVtx[1],
					posObj - pVtx[2],
					posObj - pVtx[3]
				};

				//4�̃x�N�g���Ŕ��������
				for (int nCntVec = 0; nCntVec < 4; nCntVec++)
				{
					//�O�ς��Z�o
					float fDot = 0.0f;
					fDot = vecLine[nCntVec].z * vecToPos[nCntVec].x - vecLine[nCntVec].x * vecToPos[nCntVec].z;

					if (fDot <= 0.0f)
					{
						bIn = false;
						break;
					}
				}

				//�����ɑ��݂����ꍇ
				if (bIn)
				{
					//�v���C���[�̈ʒu���擾
					D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

					//�v���C���[����I�u�W�F�N�g�܂ł̃x�N�g�����擾
					D3DXVECTOR3 vecPlayer = posObj - posPlayer;
					vecPlayer.y = 0.0f;

					//�x�N�g���𐳋K��
					D3DXVec3Normalize(&vecPlayer, &vecPlayer);

					//�x�N�g����␳
					vecPlayer *= fPressure;
				}
			}

			//�m�F����A�h���X�����炷
			pObj = pNext;
		}
	}
}
