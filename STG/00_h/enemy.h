//==========================================
//
//  �G�l�~�[�N���X(enemy.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  �G�l�~�[�N���X��`
//==========================================
class CEnemy : public CObject2D
{
public:
	CEnemy(); //�R���X�g���N�^
	~CEnemy(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static HRESULT Load(void);
	static void UnLoad(void);
	static int GetNum(void) { return m_nNum; }

	//�ÓI�����o�ϐ�
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//�����o�֐�
	void Move(void);
	void Rotate(void);
	void Collision(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_move;
	float m_nSpeed;
	float m_fRotMove;
	float m_fRotDest;
	float m_fRotDiff;

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static int m_nNum;
};

#endif
