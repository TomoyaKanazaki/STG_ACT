//==========================================
//
//  �Q�[���J�����N���X(camera.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_GAME_H_
#define _CAMERA_GAME_H_
#include "main.h"
#include "camera.h"

//==========================================
//  �J�����N���X�̒�`
//==========================================
class CCameraGame : public CCamera
{
public:
	CCameraGame(); //�R���X�g���N�^
	~CCameraGame(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Update(void) override;

private:

	//�����o�֐�
	void FirstPerson(void);
	void ThirdPerson(void);
	void Move(void);

};

#endif
