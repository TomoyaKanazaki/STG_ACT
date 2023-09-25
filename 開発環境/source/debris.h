//==========================================
//
//  �X�y�[�X�f�u��(debris.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _DEBRIS_H_
#define _DEBRIS_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CDebris : public CEnemy
{
public:

	CDebris(int nPriority = 4); //�R���X�g���N�^
	~CDebris(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CDebris *Create();

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_Rotate;

};

#endif
