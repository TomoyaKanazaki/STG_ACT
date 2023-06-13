//==========================================
//
//  �J�����N���X(camera.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//==========================================
//  �J�����N���X�̒�`
//==========================================
class CCamera
{
public:
	CCamera(); //�R���X�g���N�^
	~CCamera(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void FirstPerson(void);
	void ThirdPerson(void);
	void Move(void);

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_posV; //���_
	D3DXVECTOR3 m_posR; //�����_
	D3DXVECTOR3 m_vecU; //������x�N�g��
	D3DXMATRIX m_mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView; //�r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot; //X�̌v�Z�Ɏg�p����p�x

};

//==========================================
//  �J�����\���̒�`
//==========================================
typedef struct
{
	D3DXVECTOR3 posV; //���_
	D3DXVECTOR3 posR; //�����_
	D3DXVECTOR3 vecU; //������x�N�g��
	D3DXMATRIX mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView; //�r���[�}�g���b�N�X
	D3DXVECTOR3 rot; //X�̌v�Z�Ɏg�p����p�x
}Camera;

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
void FPSCamera(void);
void TPSCamera(void);
void CameraMove(void);

#endif
