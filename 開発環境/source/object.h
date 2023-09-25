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
#define PRIORITY_NUM (8) //�D�揇�ʂ̍ő吔

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
		TYPE_NORMAL_ENEMY, //�G
		TYPE_BLOCK_ENEMY, //�~�߂�G
		TYPE_PUSH_ENEMY, //�e���G
		TYPE_BULLET_ENEMY, //�e�̓G
		TYPE_EXPLOSION, //����
		TYPE_BG, //�w�i
		TYPE_EFFECT, //�G�t�F�N�g
		TYPE_NUMBER, //����
		TYPE_TIMER, //�^�C�}�[
		TYPE_SCORE, //�X�R�A
		TYPE_FIELD, //��
		TYPE_SHADOW, //�e
		TYPE_TARGET, //�ڕW
		TYPE_FADE, //�t�F�[�h
		TYPE_ROCKON, //���b�N�I��
		TYPE_DEBRIS, //�X�y�[�X�f�u��
		METHOD_MAX
	}TYPE;

	CObject(int nPriority = 3); //�R���X�g���N�^
	virtual ~CObject(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	CObject *GetNext(void) { return m_pNext; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetOldPos(void) { return m_oldPos; }
	D3DXVECTOR3 GetOldRot(void) { return m_oldRot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	TYPE GetType(void) { return m_type; }
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }
	void SetSize(const D3DXVECTOR3 size) { m_size = size; }
	void SetType(TYPE type) { m_type = type; }

	virtual int GetCombo() { return NULL; } //�G�̃R���{���̎擾

	//�ÓI�����o�֐�
	static CObject *GetTop(int nPriority) { return m_apTop[nPriority]; }
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static int GetNum(void) { return m_nNumObject; }

protected:

	//�����o�֐�
	void Release(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos; //�I�u�W�F�N�g�̒��S���W
	D3DXVECTOR3 m_rot; //�I�u�W�F�N�g�̌���
	D3DXVECTOR3 m_move; //�I�u�W�F�N�g�̈ړ���
	D3DXVECTOR3 m_size; //�I�u�W�F�N�g�̃T�C�Y
	D3DXVECTOR3 m_oldPos; //�I�u�W�F�N�g�̑O����W
	D3DXVECTOR3 m_oldRot; //�I�u�W�F�N�g�̑O��p�x

private:

	//�����o�ϐ�
	CObject *m_pNext; //���̃I�u�W�F�N�g�̃|�C���^
	CObject *m_pPrev; //�O�̃I�u�W�F�N�g�̃|�C���^
	int m_nPriority; //�`��D�揇��
	TYPE m_type; //���
	bool m_bDeath; //���S�t���O

	//�ÓI�����o�ϐ�
	static int m_nNumObject; //�I�u�W�F�N�g�̑���
	static CObject *m_apTop[PRIORITY_NUM]; //�擪�I�u�W�F�N�g�̃|�C���^�z��
	static CObject *m_apCur[PRIORITY_NUM]; //�Ō���I�u�W�F�N�g�̃|�C���^�z��

};

#endif
