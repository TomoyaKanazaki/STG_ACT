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

	//�e�̎��
	enum TYPE
	{
		NORMAL_BULLET = 0, //���i����e
		HOMING_BULLET, //�ǔ�����e
		MAX_TYPE
	};

	//�e���g�����[�U�[�̎��
	enum USER
	{
		USER_NONE = 0, //�N�̂��̂ł��Ȃ�
		PLAYER, //�v���C���[���������e
		ENEMY, //�G����������
		USER_MAX
	};

	CBullet(int nPriority = 4); //�R���X�g���N�^
	~CBullet(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, USER user, TYPE type);

private:

	//�����o�ϐ�
	int m_nLife;
	USER m_user;

};

#endif
