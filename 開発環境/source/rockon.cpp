//==========================================
//
//  ���b�N�I���N���X(rockon.cpp)
//  Author : Tomoya Kanzaki
//
//==========================================
#include "rockon.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CRockon::CRockon(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CRockon::~CRockon()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CRockon::Init(void)
{
	//�傫����ݒ肷��
	m_size = D3DXVECTOR3(50.0f, 0.0f, 50.0f);

	//������
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//�r���{�[�h�ɐݒ肷��
	SwitchBillboard();

	//�^�C�v�̐ݒ�
	SetType(TYPE_ROCKON);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CRockon::Uninit(void)
{
	//�I��
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CRockon::Update(void)
{
	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CRockon::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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
}

//==========================================
//  ��������
//==========================================
CRockon *CRockon::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CRockon *pRockon = new CRockon;

	if (pRockon == NULL)
	{
		assert(false);
		return NULL;
	}

	//�e�����ݒ肷��
	pRockon->m_pos = pos;

	//������
	pRockon->Init();

	//�e�N�X�`�������蓖�Ă�
	pRockon->BindTexture(CManager::GetTexture()->GetAddress(CTexture::ROCKON));

	//�|�C���^��Ԃ�
	return pRockon;
}
