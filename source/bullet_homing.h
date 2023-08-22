//==========================================
//
//  �ǔ��e�̃N���X(bullet_homing.h)
//  Author :Tomoya Kanazaki
//
//==========================================
#ifndef _BULET_HOMING_H_
#define _BULET_HOMING_H_
#include "main.h"
#include "bullet.h"

//==========================================
//  �N���X��`
//==========================================
class CBulletHoming : public CBullet
{
public:
	CBulletHoming(); //�R���X�g���N�^
	~CBulletHoming(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�z�[�~���O�̏����Ɏg�p����f�[�^�\����
	struct Homing
	{
		CObject *pObj; // 0 : Priority, 1 : ID
		int nCounter;
		bool bHoming;
	};

	//�����o�֐�
	void Follow(void);

	//�����o�ϐ�
	Homing m_Target;

};

#endif
