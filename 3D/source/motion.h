//==========================================
//
//  ���[�V�����N���X(motion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"
#include "model.h"

//==========================================
//  �}�N����`
//==========================================
#define MAX_PARTS (16) //���f���̍ő吔
#define MAX_MOTION (32) //���[�V�����̍ő吔

//==========================================
//  ���[�V�����N���X��`
//==========================================
class CMotion
{
public:

	typedef struct
	{
		D3DXVECTOR3 pos[MAX_MODEL]; //���f�������̈ʒu���
		D3DXVECTOR3 rot[MAX_MODEL]; //���f�������̊p�x���
		int nFrame; //�؂�ւ��܂łɂ�����t���[����
	}KEY_INFO; //�L�[���

	typedef struct
	{
		KEY_INFO aKeyMotion[MAX_MOTION]; //�L�[�����̃L�[���
		int nLoop; //���[�v�̗L��
	}INFO;

	CMotion(); //�R���X�g���N�^
	~CMotion(); //�f�X�g���N�^

	//�����o�֐�
	void Init(char *sFileName);
	void Uninit(void);
	void Update(void);
	void SetType(int Type);
	int GetType(void);
	bool IsFinish(void);

	//�ÓI�����o�֐�
	static CMotion *Set(CModel *pModel, int nNumAll);

private:

	//�����o�ϐ�
	INFO *m_apInfo; //���[�V�������
	int m_nNumAll; //���[�V�����̑���
	int m_nType; //���s���郂�[�V����
	int m_nNumKey; //���̃L�[
	int m_nKey; //���݂̃L�[
	int m_nNumModel; //���f����
	int m_nCounter; //�L�[�J�E���^�[
	bool m_bLoop; //���[�v�t���O
	bool m_bFinish; //
	CModel *m_pModel; //���f���̃|�C���^

};

#endif
