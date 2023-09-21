//==========================================
//
//  �����o���̓G�N���X(enemy_push.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_PUSH_H_
#define _ENEMY_PUSH_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy_Push : public CEnemy
{
public:

	CEnemy_Push(int nPriority = 4); //�R���X�g���N�^
	~CEnemy_Push(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�֐�
	void Push(void);
	void Target(void);

	//�ÓI�����o�ϐ�
	const static float mc_fPush;

};

#endif
