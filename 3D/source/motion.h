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
		PLAYER_SHOT, //�e������
		MOTION_MAX
	}CHARA;

	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		D3DXVECTOR3 rot; //�p�x
	}KEY;

	typedef struct
	{
		int nframe; //�t���[����
		KEY *pKey; //�L�[���
	}KEY_INFO;

	typedef struct
	{
		bool bLoop; //���[�v�̗L��
		int nNumKey; //�L�[��
		KEY_INFO *pKeyInfo; //�L�[���
	}INFO;

	CMotion(); //�R���X�g���N�^
	~CMotion(); //�f�X�g���N�^

	//�����o�֐�
	void Update(void);
	void SetModel(CModel **ppModel, int nNum, CHARA type);
	void Set(int type);
	
	//�ÓI�����o�֐�
	static void Load(void);
	static void UnLoad(void);

private:

	//�����o�ϐ�
	CModel **m_ppModel;
	CHARA m_Chara;
	INFO m_Info;
	int m_nNumModel;

	//�ÓI�����o�ϐ�
	static INFO *m_pInfo;
	static int m_nNumMotion;

};

#endif
