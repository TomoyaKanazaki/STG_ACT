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
	static CBullet *Create(D3DXVECTOR3 pos, float fSpeed);

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_TargetPos;
	D3DXVECTOR3 m_DefaultPos;
	float m_fSpeed;

	//�ÓI�����o�ϐ�
	const static float mc_fExplosion; //�r�Ŕ͈�

};

#endif
