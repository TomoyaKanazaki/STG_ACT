//==========================================
//
//  �^�[�Q�b�g�N���X(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "renderer.h"
#include "debugproc.h"

//==========================================
//  �}�N����`
//==========================================
#define TARGET_RANGE (-250.0f) //�^�[�Q�b�g�̋���

//==========================================
//  �R���X�g���N�^
//==========================================
CTarget::CTarget()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CTarget::~CTarget()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTarget::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//�r���{�[�h�ɐݒ肷��
	SwitchBillboard();

	//�^�C�v�̐ݒ�
	SetType(TYPE_TARGET);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTarget::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTarget::Update(void)
{
	//�����X�V
	m_rot = CManager::GetPlayer()->GetRot();
	m_pos = D3DXVECTOR3
	(
		CManager::GetPlayer()->GetPos().x + sinf(m_rot.y) * TARGET_RANGE,
		10.0f,
		CManager::GetPlayer()->GetPos().z + cosf(m_rot.y) * TARGET_RANGE
	);

	//�f�o�b�O�\��
	CManager::GetDebugProc()->Print("�^�[�Q�b�g���W : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);
	CManager::GetDebugProc()->Print("�^�[�Q�b�g���� : ( %f, %f, %f )\n", m_rot.x, m_rot.y, m_rot.z);

	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CTarget::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�`��
	CObject3D::Draw();

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CTarget *CTarget::Create(const D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CTarget *pTarget = NULL;

	//NULL�`�F�b�N
	if (pTarget == NULL)
	{
		//���������m��
		pTarget = new CTarget;
	}

	if (pTarget == NULL)
	{
		return NULL;
	}

	//�l��ݒ�
	pTarget->m_size = size;
	pTarget->m_rot = CManager::GetPlayer()->GetRot();
	pTarget->m_pos = D3DXVECTOR3
	(
		CManager::GetPlayer()->GetPos().x + sinf(pTarget->m_rot.y) * TARGET_RANGE,
		10.0f,
		CManager::GetPlayer()->GetPos().z + cosf(pTarget->m_rot.y) * TARGET_RANGE
	);

	//������
	pTarget->Init();

	//�e�N�X�`�������蓖�Ă�
	pTarget->BindTexture(CManager::GetTexture()->GetAddress(3));

	//�|�C���^��Ԃ�
	return pTarget;
}
