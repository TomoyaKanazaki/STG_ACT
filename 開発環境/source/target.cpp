//==========================================
//
//  ���b�N�I���N���X(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include "renderer.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CTarget::CTarget(int nPriority) : CObject3D(nPriority)
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
	//�ړ�
	m_pos += CManager::GetMouse()->GetMouseMove() * 500.0f;
	CManager::GetDebugProc()->Print("�^�[�Q�b�g���W : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);
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

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

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

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CTarget *CTarget::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CTarget *pTarget = new CTarget;

	if (pTarget == NULL)
	{
		assert(false);
		return NULL;
	}

	//�e�����ݒ肷��
	pTarget->m_pos = pos;
	pTarget->m_pos.y = 30.0f;
	pTarget->m_size = size;

	//������
	pTarget->Init();

	//�e�N�X�`�������蓖�Ă�
	pTarget->BindTexture(CManager::GetTexture()->GetAddress(CTexture::TARGET));

	//�|�C���^��Ԃ�
	return pTarget;
}
