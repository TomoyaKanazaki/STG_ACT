//==========================================
//
//  �A�C�e���N���X(item.h)
//  Author :Tomoya Kanazaki
//
//==========================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  �A�C�e���N���X��`
//==========================================
class CItem : public CObject3D
{
public:
	typedef enum
	{
		ENERGY = 0, //�p���[�A�b�v�A�C�e��
		SCORE, //�X�R�A�A�C�e��
		ITEMS_MAX
	}ITEMS;

	CItem(); //�R���X�g���N�^
	~CItem(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CItem *Create(D3DXVECTOR3 pos, ITEMS type);

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_move;
	ITEMS m_type;

};

#endif
