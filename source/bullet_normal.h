//==========================================
//
//  ���i����e�̃N���X(bullet_normal.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BULLET_NORMAL_H_
#define _BULLET_NORMAL_H_
#include "main.h"
#include "bullet.h"

//==========================================
//  �N���X��`
//==========================================
class CBulletNormal : public CBullet
{
public:
	CBulletNormal(); //�R���X�g���N�^
	~CBulletNormal(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	

};

#endif
