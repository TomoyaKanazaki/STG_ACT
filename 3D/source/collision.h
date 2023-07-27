//==========================================
//
//  �����蔻�胉�C�u����(collision.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "main.h"

//==========================================
//  �O���錾
//==========================================
class CObject;

//==========================================
//  �R���W�������C�u������`
//==========================================
namespace Collision
{
	D3DXVECTOR3 GetRevisionVec(const D3DXVECTOR3 vecMove, const D3DXVECTOR3 vecLine, const D3DXVECTOR3 vecToPos); //�񒼐��̌�_�̎擾
	bool CollisionEnemy(D3DXVECTOR3 pos, float fLange, bool bRelease, D3DXVECTOR3 *pPos = NULL); //�G�Ƃ̋�������
	bool HomingEnemy(D3DXVECTOR3 pos, float fLange, bool bRelease, CObject **pObject); //�G�Ƃ̋�������
	void InSquare(D3DXVECTOR3 *pVtx); //��`�̓����̓G��j��
	void InSquare(D3DXVECTOR3 *pVtx, float fPressure); //��`�̓����̓G��j��
}

#endif
