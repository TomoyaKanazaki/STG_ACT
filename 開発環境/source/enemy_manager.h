//==========================================
//
//  �G�l�~�[�}�l�[�W���N���X(enemy_manager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_
#include "main.h"
#include "object.h"

//==========================================
//  �G�l�~�[�}�l�[�W���N���X��`
//==========================================
class CEnemyManager : public CObject
{
public:

	//�����A���S���Y���Ɏg�p����f�[�^�Q
	struct CreateData
	{
		D3DXVECTOR3 pos; //�����ʒu
		int type; //�G�̎��
		int fase; //�o������t�F�[�Y
		int nCount; //����������
		int nInterval; //�����Ԋu
	};

	CEnemyManager(); //�R���X�g���N�^
	~CEnemyManager(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CEnemyManager *Create(void);
	static int GetDeth(void) { return m_nDead; }
	static void AddDeth(void) { m_nDead++; }
	static void ResetDeth(void) { m_nDead = 0; }
	static void Load(void);
	static void Unload(void);

private:
	
	//�����o�ϐ�
	D3DXVECTOR3 m_vecError; //�����ʒu�̌덷
	int m_nPopCounter[24]; //�����^�C�~���O
	bool m_bPop[24]; //�����ς݃t���O
	int m_nNumEnemy; //��x�ɐ�������G�̐�
	int m_nTime;

	//�ÓI�����o�ϐ�
	static int m_nDead;
	static int m_nNumData;
	static CreateData *m_pCreateData;
};

#endif
