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
#include "gamemanager.h"
#include "player.h"
#include "particle.h"
#include "enemy_manager.h"
#include "camera.h"
#include "sound.h"

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
bool Collision::CollisionPlayer(D3DXVECTOR3 pos, float fLange)
{
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//�v���C���[�ւ̃x�N�g�����Z�o����
	D3DXVECTOR3 vecToPlayer = pos - posPlayer;

	//�v���C���[�܂ł̃x�N�g���̑傫�����Z�o
	float fLangePlayer = (vecToPlayer.x * vecToPlayer.x) + (vecToPlayer.z * vecToPlayer.z);

	//��������
	if (fLange * fLange >= fLangePlayer)
	{
		CManager::GetSound()->Play(CSound::SOUND_LABEL_PRESS);

		//�����������ʂ�Ԃ��Ċ֐����I��
		return true;
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
			if (pObj->GetType() == CObject::TYPE_NORMAL_ENEMY || pObj->GetType() == CObject::TYPE_BULLET_ENEMY || pObj->GetType() == CObject::TYPE_BLOCK_ENEMY)
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
					//2�̃x�N�g���Ŕ��������
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
					//�Ώۂ̓G��e�ɕύX
					pObj->SetType(CObject::TYPE_BULLET_ENEMY);

					//�v���C���[����e�ւ̃x�N�g�����Z�o
					D3DXVECTOR3 vecToBullet = CGameManager::GetCamera()->GetPosR() - CGameManager::GetPlayer()->GetPos();
					vecToBullet.y = 0.0f;
					D3DXVec3Normalize(&vecToBullet, &vecToBullet);

					//�e�̈ړ��ʂɂ���
					pObj->SetMove(vecToBullet * 150.0f);
				}
			}

			//�m�F����A�h���X�����炷
			pObj = pNext;
		}
	}
}
