//==========================================
//
//  �����蔻�胉�C�u����(collision.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "collision.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  �񒼐��̌�_�̎擾
//==========================================
D3DXVECTOR3 Collision::GetRevisionVec(const D3DXVECTOR3 vecMove, const D3DXVECTOR3 vecLine, const D3DXVECTOR3 vecToPos)
{
	//���[�J���ϐ��錾
	float fRate = 0.0f;
	D3DXVECTOR3 vecRevision = vecMove;

	////�␳�l���Z�o����
	//fRate = (vecToPos.z * vecLine.x) - (vecToPos.x * vecLine.z);
	//fRate /= (vecMove.z * vecLine.x) - (vecMove.x * vecLine.z);

	//CManager::GetDebugProc()->Print("fRate : %f\n", fRate);

	////�x�N�g����␳����
	//if (fRate >= 0.0f && fRate <= 1.0f)
	//{
	//	vecRevision = D3DXVECTOR3(vecMove.x * fRate, vecMove.y * fRate, vecMove.z * fRate);
	//}

	//�␳��̒l��Ԃ�
	return vecRevision;
}
