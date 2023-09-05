//==========================================
//
//  �o���b�g�N���X(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "gamemanager.h"
#include "target.h"
#include "renderer.h"
#include "debugproc.h"
#include "texture.h"
#include "effect.h"
#include "collision.h"
#include "object.h"
#include "bullet_normal.h"
#include "bullet_homing.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CBullet::mc_fExplosion = 300.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CBullet::CBullet(int nPriority) : CObject3D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DefaultPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpeed = 0.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBullet::~CBullet()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBullet::Init(void)
{
	m_size = D3DXVECTOR3(30.0f, 30.0f, 30.0f);

	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	SwitchBillboard();

	//�^�C�v�̐ݒ�
	SetType(TYPE_BULLET);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CBullet::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBullet::Update(void)
{
	//�ړ��ʂ��Z�o
	D3DXVECTOR3 move = m_TargetPos - m_DefaultPos;
	D3DXVECTOR3 ratio = m_pos - m_DefaultPos;
	float fRatio = (ratio.x * ratio.x + ratio.z * ratio.z) / (move.x * move.x + move.z * move.z);
	move.y = 0.0f;
	D3DXVec3Normalize(&move, &move);
	move *= m_fSpeed;
	m_move = move;

	//�ړ��ʂ�K�p
	m_pos += m_move;
	m_pos.y = sinf(fRatio * D3DX_PI) * 300.0f + m_DefaultPos.y;

	//�G�t�F�N�g���Ă�
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		//��������|�C���g
		D3DXVECTOR3 pos;
		D3DXVec3Lerp(&pos, &m_pos, &m_oldPos, 0.2f * nCnt);
		CEffect::Create(pos, m_size, D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f), 10);
	}

	//���ŏ���
	if (m_pos.y < 0.0f)
	{
		for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
		{
			//�����̃A�h���X���擾
			CObject *pObj = CObject::GetTop(nCntPriority);

			while (pObj != NULL)
			{
				//���̃A�h���X��ۑ�
				CObject *pNext = pObj->GetNext();

				if (pObj->GetType() == CObject::TYPE_ENEMY || pObj->GetType() == CObject::TYPE_BULLET) //�G�̏ꍇ
				{
					//�߂��ɂ��邩�̔���
					D3DXVECTOR3 vecToObj = m_pos - pObj->GetPos();
					float fLengh = (vecToObj.x * vecToObj.x) + (vecToObj.z * vecToObj.z);
					if (fLengh < mc_fExplosion * mc_fExplosion)
					{
						//�E��
						pObj->Uninit();
					}
				}

				//���̃A�h���X�ɂ��炷
				pObj = pNext;
			}
		}
		Uninit();
		return;
	}

	//�X�V
	CObject3D::Update();

	CManager::GetDebugProc()->Print("�e�̍��W : %f, %f, %f\n", m_pos.x, m_pos.y, m_pos.z);
	CManager::GetDebugProc()->Print("�ڕW�܂ł̊��� : %f\n", fRatio);
}

//==========================================
//  �`�揈��
//==========================================
void CBullet::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�`��
	CObject3D::Draw();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, float fSpeed)
{
	//�C���X�^���X����
	CBullet *pBullet = NULL;

	//���������m��
	pBullet = new CBullet;

	//�l��ݒ�
	pBullet->m_pos = pos;
	pBullet->m_DefaultPos = pos;
	pBullet->m_TargetPos = CGameManager::GetTarget()->GetPos();
	pBullet->m_fSpeed = fSpeed;

	//������
	pBullet->Init();

	//�e�N�X�`�������蓖�Ă�
	pBullet->BindTexture(CManager::GetTexture()->GetAddress(CTexture::BULLET));

	//�|�C���^��Ԃ�
	return pBullet;
}
