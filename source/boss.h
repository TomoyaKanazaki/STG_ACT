//==========================================
//
//  �{�X�G�N���X(boss.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CBoss : public CEnemy
{
public:
	CBoss(); //�R���X�g���N�^
	~CBoss(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�֐�
	void Rotate();

};

#endif
