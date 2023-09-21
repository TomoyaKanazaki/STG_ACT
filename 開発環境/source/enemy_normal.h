//==========================================
//
//  �G���G�N���X(enemy_normal.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_NORMAL_H_
#define _ENEMY_NORMAL_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy_Normal : public CEnemy
{
public:

	CEnemy_Normal(int nPriority = 4); //�R���X�g���N�^
	~CEnemy_Normal(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

};

#endif
