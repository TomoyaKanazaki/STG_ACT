//==========================================
//
//  ���C�g�N���X(light.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "light.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CLight::CLight()
{
	for (int nCnt = 0; nCnt < NUM_LIGHT; nCnt++)
	{
		m_Light[nCnt] = {};
	}
}

//==========================================
//  �f�X�g���N�^
//==========================================
CLight::~CLight()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CLight::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���[�J���ϐ��錾
	D3DXVECTOR3 vecDir; //�ݒ�p�̕����x�N�g��

	for (int nCnt = 0; nCnt < NUM_LIGHT; nCnt++)
	{
		//���C�g���̃N���A
		ZeroMemory(&m_Light[nCnt], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		m_Light[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		m_Light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���C�g�̕�����ݒ�
		switch (nCnt)
		{
		case 0:
			vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
			break;
		case 1:
			vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
		}

		D3DXVec3Normalize(&vecDir, &vecDir); //�x�N�g���̐��K��
		m_Light[nCnt].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &m_Light[nCnt]);

		//���C�g��L��������
		pDevice->LightEnable(nCnt, TRUE);
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CLight::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CLight::Update(void)
{

}
