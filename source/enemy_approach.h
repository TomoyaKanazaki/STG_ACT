//==========================================
//
//  �t���Ă���G�̃N���X(enemy_approach.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_APPROACH_H_
#define _ENEMY_APPROACH_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemyApproach : public CEnemy
{
public:
	CEnemyApproach(); //�R���X�g���N�^
	~CEnemyApproach(); //�R���X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�֐�
	void Move(void);

};

#endif
