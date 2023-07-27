//==========================================
//
//  ��ʑJ�ڃN���X(scene.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//==========================================
//  ��ʑJ�ڃN���X��`
//==========================================
class CScene
{
public:
	CScene(); //�R���X�g���N�^
	~CScene(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

};

#endif
