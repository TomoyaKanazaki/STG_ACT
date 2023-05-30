//==========================================
//
//  �I�u�W�F�N�g�N���X(object.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

//==========================================
//  �}�N����`
//==========================================
#define MAX_OBJECT (1048576) //�I�u�W�F�N�g�̍ő吔

//==========================================
//  �I�u�W�F�N�g�N���X����
//==========================================
class CObject
{
public:
	CObject();
	virtual ~CObject();

	//�����o�֐�
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	int GetID(void) { return m_nID; }

	//�ÓI�����o�֐�
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

protected:

	//�����o�֐�
	void Release(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos; //�I�u�W�F�N�g�̒��S���W
	D3DXVECTOR3 m_rot; //�I�u�W�F�N�g�̌���
	D3DXVECTOR3 m_size; //�I�u�W�F�N�g�̃T�C�Y

private:

	//�ÓI�����o�ϐ�
	static CObject *m_apObject[MAX_OBJECT]; //�I�u�W�F�N�g�̃|�C���^
	static int m_nNumObject; //�I�u�W�F�N�g�̑���

	//�����o�ϐ�
	int m_nID; //�������g�̃C���f�b�N�X

};

#endif
