//==========================================
//
//  �w�i�N���X(bg.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  �}�N����`
//==========================================
#define MAX_BG (3)

//==========================================
//  �w�i�N���X��`
//==========================================
class CBg : public CObject2D
{
public:
	CBg(); //�R���X�g���N�^
	~CBg() override; //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	CBg Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

	//�����o�ϐ�
	float m_fSpeed;

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;

};

#endif
