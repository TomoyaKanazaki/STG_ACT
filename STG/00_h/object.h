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
#define MAX_OBJECT (2048) //�I�u�W�F�N�g�̍ő吔

//==========================================
//  �I�u�W�F�N�g�N���X����
//==========================================
class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0, //�s�g�p
		TYPE_PLAYER, //�v���C���[
		TYPE_ENEMY, //�G
		TYPE_BULLET, //�e
		TYPE_MAX
	}TYPE;

	CObject();
	virtual ~CObject();

	//�����o�֐�
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	CObject *GetObject(int nID) { return m_apObject[nID]; }
	int GetID(void) { return m_nID; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	void SetType(TYPE type) { m_type = type; }
	TYPE GetTypre(void) { return m_type; }

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
	TYPE m_type; //���

};

#endif
