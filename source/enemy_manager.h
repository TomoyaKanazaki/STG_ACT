//==========================================
//
//  �G�l�~�[�}�l�[�W���N���X(enemy_manager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_
#include "main.h"
#include "object.h"

//==========================================
//  �G�l�~�[�}�l�[�W���N���X��`
//==========================================
class CEnemyManager : public CObject
{
public:
	CEnemyManager(); //�R���X�g���N�^
	~CEnemyManager(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CEnemyManager *Create(void);

private:
	
	//�����o�ϐ�
	D3DXVECTOR3 m_vecError; //�����ʒu�̌덷
	int m_nPopCounter[24]; //�����^�C�~���O
	bool m_bPop[24]; //�����ς݃t���O
	int m_nNumEnemy; //��x�ɐ�������G�̐�
	int m_nTime;


};

#endif
