//==========================================
//
//  �����N���X(explosion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#include "object2D_Anim.h"

//==========================================
//  �����N���X��`
//==========================================
class CExplosion : public CObject2D_Anim
{
public:
	CExplosion(int nPriority = 2); //�R���X�g���N�^
	~CExplosion(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static HRESULT Load(void);
	static void UnLoad(void);
	static CExplosion *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;

};

#endif
