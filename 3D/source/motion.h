//==========================================
//
//  ���[�V�����N���X(motion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"

//==========================================
//  ���[�V�����N���X��`
//==========================================
class CMotion
{
public:
	typedef enum
	{
		MOTION_NONE = 0, //�Ȃ�
		PLAYER_SHOT, //�e������
		MOTION_MAX
	}MOTIONS;

	CMotion(); //�R���X�g���N�^
	~CMotion(); //�f�X�g���N�^

private:

};

#endif
