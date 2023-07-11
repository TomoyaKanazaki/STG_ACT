//==========================================
//
//  �A�C�e���N���X(item.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "gamemanager.h"

//==========================================
//  �}�N����`
//==========================================
#define GET_SPEED (10.0f) //�v���C���[�ɋ߂Â����x

//==========================================
//  �R���X�g���N�^
//==========================================
CItem::CItem(int nPriority) : CObject3D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = ITEMS_MAX;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CItem::~CItem()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CItem::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//�r���{�[�h�ɐݒ肷��
	SwitchBillboard();

	//�^�C�v�̐ݒ�
	SetType(TYPE_ITEM);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CItem::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CItem::Update(void)
{
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 TargetPos = CGameManager::GetPlayer()->GetPos();

	//�ړ���ւ̃x�N�g�����Z�o
	D3DXVECTOR3 vecMove = TargetPos - m_pos;

	//�v���C���[�Ƃ̋������Z�o
	D3DXVECTOR2 vec2 = D3DXVECTOR2(vecMove.x, vecMove.z);
	if (D3DXVec2Length(&vec2) < 5.0f)
	{
		//�߂Â��������
		Uninit();
		return;
	}

	//�l��␳
	D3DXVec3Normalize(&vecMove, &vecMove);
	m_move = vecMove * GET_SPEED;
	m_move.y = 0.0f;

	//�ړ�
	m_pos += m_move;

	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CItem::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	CObject3D::Draw();

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CItem *CItem::Create(D3DXVECTOR3 pos, ITEMS type)
{
	//�C���X�^���X����
	CItem *pItem = NULL;

	//NULL�`�F�b�N
	if (pItem == NULL)
	{
		//���������m��
		pItem = new CItem;
	}

	if (pItem == NULL)
	{
		return NULL;
	}

	//������
	pItem->Init();

	//��ނ�ݒ�
	pItem->m_pos = pos;
	pItem->m_pos.y += 5.0f;
	pItem->m_type = type;
	pItem->m_size = D3DXVECTOR3(10.0f, 0.0f, 10.0f);

	//�|�C���^��Ԃ�
	return pItem;
}
