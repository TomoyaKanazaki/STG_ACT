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
//  �ÓI�����o�ϐ��錾
//==========================================
const float CTarget::mc_fRate = 80.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CTarget::CTarget(int nPriority) : CObject2D(nPriority)
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
	//�l��ݒ肷��
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	m_size = D3DXVECTOR3(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f, 0.0f);

	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	//�^�C�v�̐ݒ�
	SetType(TYPE_TARGET);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTarget::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTarget::Update(void)
{
	//�ړ�
	D3DXVECTOR3 move = CManager::GetMouse()->GetMouseMove();
	m_pos += move * mc_fRate;

	//�X�V
	CObject2D::Update();
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
	CObject2D::Draw();

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
CTarget *CTarget::Create(void)
{
	//�C���X�^���X����
	CTarget *pTarget = new CTarget;

	if (pTarget == NULL)
	{
		assert(false);
		return NULL;
	}

	//������
	pTarget->Init();

	//�e�N�X�`�������蓖�Ă�
	pTarget->BindTexture(CManager::GetTexture()->GetAddress(CTexture::TARGET));

	//�|�C���^��Ԃ�
	return pTarget;
}
