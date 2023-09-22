//==========================================
//
//  �Q�[���J�����N���X(camera_result.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_RESULT_H_
#define _CAMERA_RESULT_H_
#include "main.h"
#include "camera.h"

//==========================================
//  �J�����N���X�̒�`
//==========================================
class CCameraResult : public CCamera
{
public:
	CCameraResult(); //�R���X�g���N�^
	~CCameraResult(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Update(void) override;

private:

	//�����o�ϐ�
	float m_fAngle;

};

#endif
