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
	virtual HRESULT Init(void);
	void Uninit(void);
	virtual void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetPosR(void) { return m_posR; }
	D3DXVECTOR3 GetPosV(void) { return m_posV; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXMATRIX GetMtxPro(void) { return m_mtxProjection; }
	D3DXMATRIX CreateViewMatrix(void);

protected:

#define CAMERA_DISTANCE (500.0f) //���_����v���C���[�̋���
#define HEIGHT (300.0f) //���_�̍���
#define MAX_ROT (D3DX_PI * 0.99f) //���_�̌��E�p
#define MIN_ROT (D3DX_PI * 0.01f) //���_�̌��E�p

	//�����o�ϐ�
	D3DXVECTOR3 m_posV; //���_
	D3DXVECTOR3 m_posR; //�����_
	D3DXVECTOR3 m_vecU; //������x�N�g��
	D3DXMATRIX m_mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView; //�r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot; //X�̌v�Z�Ɏg�p����p�x
	D3DXVECTOR3 m_diff; //�v���C���[���W�Ƃ̍���
	float m_fFov; //����p

private:

	//�����o�֐�
	void Rotate(void);

};

#endif
