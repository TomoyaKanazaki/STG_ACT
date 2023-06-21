//==========================================
//
//  ���N���X(field.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  �e�N���X�̒�`
//==========================================
class CWall : public CObject3D
{
public:
	CWall(int nPriority = 0); //�R���X�g���N�^
	~CWall(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CWall *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

};

#endif
