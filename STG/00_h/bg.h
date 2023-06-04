//==========================================
//
//  �w�i�N���X(bg.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "object2D_Anim.h"

//==========================================
//  �}�N����`
//==========================================
#define BG_NUM (3) //�w�i�̐�

//==========================================
//  �w�i�N���X��`
//==========================================
class CBg : public CObject2D_Anim
{
public:
	CBg(); //�R���X�g���N�^
	~CBg(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static HRESULT Load(void);
	static void UnLoad(void);
	static void Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:
	
	//�����o�ϐ�
	int m_nID; //�w�i�ԍ�
	int m_nSpeed; //�X�N���[�����x

	//�ÓI�����o�ϐ�
	static int m_nNum; //�w�i��
	static LPDIRECT3DTEXTURE9 m_pTexture[BG_NUM];

};

#endif
