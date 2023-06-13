//==========================================
//
//  �e�N���X(bullet.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  �e�N���X�̒�`
//==========================================
class CBullet : public CObject2D
{
public:
	CBullet(int nPriority = 3); //�R���X�g���N�^
	~CBullet(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static HRESULT Load(void);
	static void UnLoad(void);
	static int GetNum(void) { return m_nNum; }
	static CBullet *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

	//�����o�֐�
	bool CollisionEnemy(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_move;
	float m_fSpeed;
	int m_nLife;

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static int m_nNum;

};

#endif
