//==========================================
//
//  ���̃N���X(smoke.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "smoke.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CSmoke::CSmoke(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CSmoke::~CSmoke()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CSmoke::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//�r���{�[�h�ɐݒ肷��
	SwitchBillboard();

	//�^�C�v�̐ݒ�
	SetType(TYPE_EFFECT);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CSmoke::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CSmoke::Update(void)
{
	//���������炷
	m_nLife--;

	//�������Ȃ��Ȃ�����폜����
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	//�T�C�Y������������
	m_size.x -= m_vecDeffSize.x * m_fLifeRatio;
	m_size.y -= m_vecDeffSize.y * m_fLifeRatio;
	m_size.z -= m_vecDeffSize.z * m_fLifeRatio;

	//�ړ��ʂ����Z����
	m_pos += m_move;

	//�����ɂ��ړ��̒�~
	m_move.x += (0.0f - m_move.x) * 0.3f;
	m_move.z += (0.0f - m_move.z) * 0.3f;

	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CSmoke::Draw(void)
{
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

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

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`��
	CObject3D::Draw();

	//�A���t�@�u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

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
CSmoke * CSmoke::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nLife)
{
	//�C���X�^���X����
	CSmoke *pSmoke = new CSmoke;

	if (pSmoke == NULL)
	{
		assert(false);
		return NULL;
	}

	//�e�����ݒ肷��
	pSmoke->m_pos = pos;
	pSmoke->m_pos.y = 10.0f;
	pSmoke->m_size = size;

	//������
	pSmoke->Init();
	pSmoke->SetCol(col);


	//�e�N�X�`�������蓖�Ă�
	pSmoke->BindTexture(CManager::GetTexture()->GetAddress(CTexture::SMOKE));

	//�f�t�H���g�T�C�Y��ۑ�����
	pSmoke->m_vecDeffSize = size;

	//������ݒ肷��
	pSmoke->m_nLife = nLife;
	pSmoke->m_fLifeRatio = 1.0f / nLife;

	//�|�C���^��Ԃ�
	return pSmoke;
}
