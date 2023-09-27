//==========================================
//
//  �I�N���X(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "debugproc.h"
#include "renderer.h"
#include "particle.h"
#include "effect.h"
#include "texture.h"
#include "sound.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CTarget::CTarget(int nPriority) : CObject3D(nPriority)
{
	m_fDistance = 0.0f;
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
HRESULT CTarget::Init()
{
	//���S�Ƃ̋���������W��ݒ肷��
	m_pos = D3DXVECTOR3
	(
		sinf(m_rot.y) * m_fDistance,
		0.0f,
		cosf(m_rot.y) * m_fDistance
	);

	//������
	CObject3D::Init();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTarget::Uninit()
{
	//�I��
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTarget::Update()
{
	//�p�x���X�V
	m_rot.y -= 0.001f;

	//�p�x�̕␳
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	//���S�Ƃ̋���������W��ݒ肷��
	m_pos = D3DXVECTOR3
	(
		sinf(m_rot.y) * m_fDistance,
		0.0f,
		cosf(m_rot.y) * m_fDistance
	);

	//�����蔻��
	D3DXVECTOR3 pos;
	if (CObject3D::Collision(CObject::TYPE_BULLET_ENEMY, &pos))
	{
		CManager::GetSound()->Play(CSound::SOUND_LABEL_EXPLOSION);

		//�p�[�e�B�N�����Ăяo��
		CParticle::Create(pos, D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(0.98f, 0.87f, 0.28f, 0.5f), 10, 30, 10, 5);
	}

	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CTarget::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�`��
	CObject3D::Draw();

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CTarget *CTarget::Create(D3DXVECTOR3 size, float fRot, float fDistance)
{
	//�C���X�^���X����
	CTarget *pTarget = NULL;

	//NULL�`�F�b�N
	if (pTarget == NULL)
	{
		pTarget = new CTarget;
	}

	//�e����̕ۑ�
	pTarget->m_size = size;
	pTarget->m_rot.y = fRot;
	pTarget->m_fDistance = fDistance;

	//������
	if (pTarget != NULL)
	{
		pTarget->Init();
	}

	//�e�N�X�`�������蓖��
	pTarget->BindTexture(CManager::GetTexture()->GetAddress(CTexture::TARGET));

	//�|�C���^��Ԃ�
	return pTarget;
}
