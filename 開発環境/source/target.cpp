//==========================================
//
//  ���b�N�I���N���X(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "gamemanager.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CTarget::mc_fRate = 300.0f;
const float CTarget::mc_fDistance = 1000.0f;

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
	//�l��ݒ肷��
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();
	D3DXVECTOR3 rotPlayer = CGameManager::GetPlayer()->GetRot();
	m_pos = D3DXVECTOR3(posPlayer.x - (sinf(rotPlayer.y) * mc_fDistance), 0.0f, posPlayer.z - (cosf(rotPlayer.y) * mc_fDistance));
	m_size = D3DXVECTOR3(mc_fRate, 0.0f, mc_fRate);
	m_rot.y = rotPlayer.y;
	m_rot.x = D3DX_PI * 0.5f;

	if (FAILED(CObject3D::Init()))
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
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTarget::Update(void)
{
	//�ړ�
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();
	D3DXVECTOR3 rotPlayer = CGameManager::GetPlayer()->GetRot();
	m_pos = D3DXVECTOR3(posPlayer.x - (sinf(rotPlayer.y) * mc_fDistance), 0.0f, posPlayer.z - (cosf(rotPlayer.y) * mc_fDistance));
	m_rot.y = rotPlayer.y;

	//�X�V
	CObject3D::Update();

	CManager::GetDebugProc()->Print("�^�[�Q�b�g�̍��W : %f, %f, %f\n", m_pos.x, m_pos.y, m_pos.z);

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
