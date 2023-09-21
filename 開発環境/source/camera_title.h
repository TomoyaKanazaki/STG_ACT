//==========================================
//
//  �Q�[���J�����N���X(camera.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_TITLE_H_
#define _CAMERA_TITLE_H_
#include "main.h"
#include "camera.h"

//==========================================
//  �J�����N���X�̒�`
//==========================================
class CCameraTitle : public CCamera
{
public:
	CCameraTitle(); //�R���X�g���N�^
	~CCameraTitle(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Update(void) override;

private:

	//�����o�ϐ�
	float m_fAngle;

};

#endif
