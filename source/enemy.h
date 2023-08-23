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
#include "layer.h"

//==========================================
//  �O���錾
//==========================================
class CModel;
class CMotion;
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
		TYPE_SHOT, //�������U���̓G
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
	void SetLife(const int nDamage) { if (m_nLife > 0) m_nLife -= nDamage; }

	//�ÓI�����o�ϐ�
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, CEnemy::TYPE type);
	static int m_nCntEnemy;

protected:

	//���f�����
	CModel **m_ppModel; //���f�����
	CLayer::LAYERDATA *m_pLayer; //�K�w�\�����
	CMotion *m_pMotion;
	CShadow *m_pShadow;

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_oldPos;
	int m_nNumModel;
	int m_nLife;
	float m_fSpeed;
	bool m_bRand;

};

#endif
