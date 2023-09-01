//==========================================
//
//  �e�����G�̃N���X(enemy_shot.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_SHOT_H_
#define _ENEMY_SHOT_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  �O���錾
//==========================================
class CRockon;

//==========================================
//  �N���X��`
//==========================================
class CEnemyShot : public CEnemy
{
public:
	CEnemyShot(); //�R���X�g���N�^
	~CEnemyShot(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�֐�
	void Shot(void);
	void Targeted(void);

	//�����o�ϐ�
	int m_nInterval; //�e�̔��ˊԊu
	CRockon *m_pRockon;

};

#endif
