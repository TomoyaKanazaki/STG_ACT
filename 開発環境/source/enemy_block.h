//==========================================
//
//  �~�߂�G�̃N���X(enemy_block.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_BLOCK_H_
#define _ENEMY_BLOCK_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy_Block : public CEnemy
{
public:

	CEnemy_Block(int nPriority = 4); //�R���X�g���N�^
	~CEnemy_Block(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�֐�
	void Block(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_posDef;

	//�ÓI�����o�ϐ�
	const static float mc_fBlock;

};

#endif
