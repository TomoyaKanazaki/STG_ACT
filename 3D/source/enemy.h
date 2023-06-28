//==========================================
//
//  �G�l�~�[�N���X(enemy.h)
//  Author : Tomoay Kanazaki
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "object.h"

//==========================================
//  �O���錾
//==========================================
class CModel;
class CShadow;

//==========================================
//  �G�l�~�[�N���X��`
//==========================================
class CEnemy : public CObject
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0, //���ʂ̓G
		TYPE_MAX
	}TYPE;

	CEnemy(int nPriority = 4); //�R���X�g���N�^
	~CEnemy(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetOldPos(void) { return m_oldPos; }

	//�ÓI�����o�ϐ�
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, CEnemy::TYPE type);

private:

	//�����o�֐�
	void Load(void); //�G�l�~�[���̓ǂݍ���

	//�����o�ϐ�
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_oldPos;
	int m_nLife;
	int m_nNumModel;
	float m_fSpeed;
	bool m_bRand;

	//���f�����
	CModel **m_apModel;
	CShadow *m_pShadow;

};

#endif
