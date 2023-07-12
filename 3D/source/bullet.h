//==========================================
//
//  �o���b�g�N���X(bullet.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  �o���b�g�N���X��`
//==========================================
class CBullet : public CObject3D
{
public:
	CBullet(int nPriority = 4); //�R���X�g���N�^
	~CBullet(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);

private:

	typedef struct
	{
		int aInfo[2]; // 0 : Priority, 1 : ID
		int nCounter;
	}Homing;

	//�����o�ϐ�
	D3DXVECTOR3 m_move;
	int m_nLife;
	Homing m_Target;

};

#endif
