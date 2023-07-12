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
//  �O���錾
//==========================================
class CModel;

//==========================================
//  ���[�V�����N���X��`
//==========================================
class CMotion
{
public:
	typedef enum
	{
		MOTION_NONE = 0, //�Ȃ�
		PLAYER,
		ENEMY,
		MOTION_MAX
	}CHARA;

	CMotion(); //�R���X�g���N�^
	~CMotion(); //�f�X�g���N�^

	//�����o�֐�
	void Uninit(void);
	void Update(void);

	void SetModel(CModel **ppModel, int nNum);
	void SetChara(CHARA nChara) { chara = nChara; }

	void Set(int type);

	static void Load(void);

private:

	//�����o�ϐ�
	CModel **m_ppModel;
	CHARA chara;
	int m_nNumModel;

};

#endif
